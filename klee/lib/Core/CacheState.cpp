//===-- CacheState.cpp -----------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "CacheState.h"
#include "CacheUtil.h"
#include "TimingSolver.h"
#include "klee/Internal/Support/ErrorHandling.h"

#include "llvm/Support/ErrorHandling.h"

#include <iostream> 
#include <time.h>

using namespace llvm;
using namespace klee;

Target::Target(Target& t) {
    addr = t.addr;
    info = t.info;

    for (auto &addr :t.conf_addrs)  {
        conf_addrs.insert(addr);
    }

    for (auto &p : t.conf_constrs) {
        conf_constrs.insert(PairExpr(p.first, p.second));
    }

    for (auto &p : t.unique_constrs) {
        ExprSet *es = new ExprSet();
        for (auto &s: *(p.second)) {
            es->insert(s);
        }
        unique_constrs.insert(PairExprSet(p.first, es));
    }

    for (auto &p : t.reloads) {
        ExprSet *es = new ExprSet();
        for (auto &s: *(p.second)) {
            es->insert(s);
        }
        reloads.insert(PairExprSet(p.first, es));
    }

}

Target::~Target() {
    conf_addrs.clear();
    conf_constrs.clear();

    for (auto it = unique_constrs.begin(); it != unique_constrs.end(); ++it) {
        ExprSet *es = static_cast<ExprSet *>(it->second);
        es->clear();
        delete es; 
    }   
    unique_constrs.clear();

    for (auto it = reloads.begin(); it != reloads.end(); ++it) {
        ExprSet *es = static_cast<ExprSet *>(it->second);
        es->clear();
        delete es; 
    }   
    reloads.clear();
}

ConstantCache::ConstantCache()
    : fullCount(CACHE_SET_SIZE) {
        for (int i = 0; i < fullCount; i++) {
            auto s =  new std::set<uint64_t>(); 
            ccState.push_back(s);
        }

    }

void ConstantCache::access(ref<Expr> &addr) {

    if (addr->getKind() != Expr::Constant) {
        return;
    }

    uint64_t set = CacheUtil::getSet(dyn_cast<ConstantExpr>(addr));
    auto &s = ccState[set];

    if (s->size() >= CacheConfig::cache_ways) {
        return;
    }

    uint64_t tag = CacheUtil::getTag(dyn_cast<ConstantExpr>(addr));

    if (s->find(tag) == s->end()) {
        s->insert(tag);
        if (s->size() == CacheConfig::cache_ways) {
            fullCount--;
        }
    }
}

ConstantCache::~ConstantCache() {
    for (auto &s : ccState) {
        delete s;
    }
}


void CacheState::setSpectreRecord(SpectreRecorder* sr) {
    this->recorder = sr;
}

void CacheState::recordResult(const InstructionInfo *temp, bool isVul) {
    recorder->recordCacheResult(temp, isVul);
}

CacheState::CacheState(ExecutionState &_state) 
    : state(_state), isSensitive(false), recorder(NULL){

    }

CacheState::CacheState(ExecutionState &_state, const CacheState &cs) 
    : state(_state), isSensitive(cs.isSensitive) {
        for (auto &t : cs.targets) {
            Target *tt = new Target(*(t.second));
            targets.insert(MapTarget(t.second->addr, tt));
        }
    }

CacheState::~CacheState() {
    for (auto &t : this->targets) {
        delete t.second;
    }

}

std::map<unsigned, int> CacheState::found_vuls;

bool CacheState::conflicConstr(ref<Expr> &addr1, ref<Expr> &addr2, ref<Expr> &result) {
    if (isa<ConstantExpr>(addr1) && isa<ConstantExpr>(addr2)) {
        if (CacheUtil::generateSetCnstrCC(addr1, addr2)) {
            if (CacheUtil::generateTagCnstrCC(addr1, addr2)) {
                result = ConstantExpr::alloc(1, Expr::Bool);
                return true; 
            }
        }
        result = ConstantExpr::alloc(0, Expr::Bool);
        return false;
    }

    ref<Expr> setConstr = CacheUtil::generateSetCnstr(addr1, addr2);
    ref<Expr> tagConstr = CacheUtil::generateTagCnstr(addr1, addr2);
    tagConstr = Expr::createIsZero(tagConstr);
    result = AndExpr::create(setConstr, tagConstr);
    return true;
}


bool CacheState::uniqueConstr(ref<Expr> &addr1, ref<Expr> &addr2, ref<Expr> &result) {
    if (isa<ConstantExpr>(addr1) && isa<ConstantExpr>(addr2)) {
        if (CacheUtil::generateSetCnstrCC(addr1, addr2)) {
            if (CacheUtil::generateTagCnstrCC(addr1, addr2)) {
                result = ConstantExpr::alloc(0, Expr::Bool);
                return false; 
            }
        }
        // if constant addresses tag1 != tag2 or set1 != set2, drop it. 
        return true;
    }

    ref<Expr> setConstr = CacheUtil::generateSetCnstr(addr1, addr2);
    ref<Expr> tagConstr = CacheUtil::generateTagCnstr(addr1, addr2);
    setConstr = Expr::createIsZero(setConstr);
    tagConstr = Expr::createIsZero(tagConstr);
    result =  OrExpr::create(setConstr, tagConstr);
    return false;

}

bool CacheState::reloadConstr(ref<Expr> &addr1, ref<Expr> &addr2, ref<Expr> &result) {
    if (isa<ConstantExpr>(addr1) && isa<ConstantExpr>(addr2)) {
        if (CacheUtil::generateSetCnstrCC(addr1, addr2)) {
            if (CacheUtil::generateTagCnstrCC(addr1, addr2)) {
                return true; 
            }
        }

        // if it is not a reload, resturn constraint with bool value True;
        result = ConstantExpr::alloc(1, Expr::Bool);
        return false;
    }
    ref<Expr> setConstr = CacheUtil::generateSetCnstr(addr1, addr2);
    ref<Expr> tagConstr = CacheUtil::generateTagCnstr(addr1, addr2);
    setConstr = Expr::createIsZero(setConstr);
    tagConstr = Expr::createIsZero(tagConstr);
    result =  OrExpr::create(setConstr, tagConstr);
    return false;

}

void CacheState::load(ref<Expr> &addr, const InstructionInfo *info) {
    if (addr.get()->getSensitive() || isSensitive) {
        handleAccess(addr, info);
    }
}

void CacheState::store(ref<Expr> &addr, const InstructionInfo *info) {

    if (state.isSpeculative) {
        return;
    }

    if (addr.get()->getSensitive() || isSensitive) {
        handleAccess(addr, info);
    }
}


void CacheState::handleAccess(ref<Expr> &addr, const InstructionInfo *info) {
    //llvm::errs() << "state: " << state.tag << "Addr: " << addr << "\n";

    if (state.isSpeculative && !addr.get()->getSensitive()) {
        // Do not record normal memory access on speculative paths. 
        return;
    }

    for (auto &mt : targets) {
        Target *target = mt.second; 

        /* constant check */
        target->ccstate.access(addr);
        if (target->ccstate.isFull()) {
            targets.erase(mt.first);
            const auto seconds = time::getUserTime().toMicroseconds();
            klee_message("@CM: No leakage (Constant eviction): %s: %u, ASM line=%u, state = %lu, time = %lu", target->info->file.c_str(), target->info->line, target->info->assemblyLine, state.tag, seconds);
            delete target;
            continue;
        }

        if (target->conf_addrs.find(addr) != target->conf_addrs.end()) {
            continue;
        }

        //llvm::errs() << "Recorded conflic address: " << target->conf_addrs.size() << "\n";

        // unique constraint
        for (auto &ca: target->conf_addrs) {
            ref<Expr> addr1 = ca;
            ref<Expr> unique;
            bool isUnique = uniqueConstr(addr1, addr, unique);

            //llvm::errs() << "Unique: " << addr1 <<  ", "  << isUnique<< "\n";

            if (!isUnique && unique.get() != 0)  {
                ExprMapSet::iterator mp = target->unique_constrs.find(addr1);
                if (mp != target->unique_constrs.end()) {
                    mp->second->insert(unique);
                } else {
                    ExprSet *uni_set = new ExprSet();
                    uni_set->insert(unique);
                    target->unique_constrs.insert(PairExprSet(addr1, uni_set));
                }
                //unique->dump();
            }
        } // unique 

        // reload constraint
        ref<Expr> reload;
        bool isReload = reloadConstr(target->addr, addr, reload);

        //llvm::errs() << "Is Not Reload constraint: " << isReload<<"\n";
        //reload->dump();

        if (isReload) {
            // constant addr reloads, just remove all records
            //llvm::errs() << "Sensitive address has been reloaded\n";
            target->conf_addrs.clear();
            target->conf_constrs.clear();

            for (auto &uc: target->unique_constrs) {
                delete(uc.second);
            }
            target->unique_constrs.clear();

            for (auto &r: target->reloads) {
                delete(r.second);
            }
            target->reloads.clear();
        } else {
            for (auto &ca: target->conf_addrs) {
                const auto &r = target->reloads.find(ca);
                //llvm::errs() << "Reload constr:\n";
                //reload->dump();
                if (r != target->reloads.end()) {
                    ExprSet *es = r->second;
                    es->insert(reload);
                    //llvm::errs() << "Insert a not reload constraint for address: "<<ca <<"\n";
                } else {
                    ExprSet *es = new ExprSet();
                    es->insert(reload);
                    target->reloads.insert(PairExprSet(ca, es));
                    //llvm::errs() << "Insert a not reload constraint for address(new): "<<ca <<"\n";
                }
            }
        }

        // conflict  constraint
        ref<Expr> target_addr = target->addr;
        ref<Expr> conflic;
        bool isPosConf = conflicConstr(target_addr, addr, conflic);

        if (isPosConf) {
            //llvm::errs() << "insert a new conflict address: " << addr <<"\n";
            //conflic->dump();
            target->conf_addrs.insert(addr);
            target->conf_constrs.insert(PairExpr(addr, conflic));
        }


    } // end for targets


    if (addr.get()->getSensitive()) {
        isSensitive = true;
        std::map<ref<Expr>, Target*>::iterator ems;
        ems = targets.find(addr);
        if (ems != targets.end()) {
            // totally same address
            Target *target = ems->second; 
            delete target;
        } 

        Target *target = new Target();
        target->addr = addr;
        target->info = info;
        targets.insert(MapTarget(addr, target));
        //llvm::errs()<<"Add new sensitive!\n" << addr<< "\n" << "Line: " << info->assemblyLine <<"\n";
        //llvm::errs() << "target size: " << targets.size() << "\n";
    }

    //llvm::errs() << "\n";
}


void CacheState::dump() {
    llvm::errs() <<"======== Cache State Summary ===========\n";   
    llvm::errs() << "Target number: " << targets.size() <<"\n";

    for (auto &tm : targets) {
        auto &target = tm.second;
        llvm::errs() << "Conflict address size: " << target->conf_addrs.size() << "\n";
        int i = 0;
        for (auto &ca: target->conf_addrs) {
            llvm::errs() << "CA "<< i++ <<": " << ca<<"\n";

            // Unique set
            llvm::errs() << "Unique size:" << target->unique_constrs.size() << "\n";
            const auto &us = target->unique_constrs.find(ca);
            if (us != target->unique_constrs.end()) {
                llvm::errs() << "Unique set size: " << us->second->size() << "\n";
            } else {
                llvm::errs() << "Unique set size: 0\n";
            }

            // Reload set 
            llvm::errs() << "Reload size:" << target->reloads.size() << "\n";
            const auto &rs = target->reloads.find(ca);
            if (rs != target->reloads.end()) {
                llvm::errs() << "Reload set size: " << rs->second->size() << "\n";
            } else {
                llvm::errs() << "Reload set size: 0\n";
            }

        }
    }

    llvm::errs() <<"======== cache summary end ===========\n";   
}


// verify whether there are sensitive data leakage
void CacheState::verifyCacheSideChannel(TimingSolver *solver) {

    if (targets.empty()) {
        return;
    }


    std::map<ref<Expr>, Target*>::iterator map_it;
    //klee_message("@@@@============== Verify Cache Side channle for state: %ld ==============", state.tag);
    //klee_message("Targets size: %ld", targets.size());
    // Dump for checking
    //dump();
    //
    //for (auto &t : targets) {
    //    llvm::errs() << "target:" << t.second->info->assemblyLine << "\n";
    //}

    // check for all sensitive address
    for (map_it = targets.begin(); map_it != targets.end(); ++map_it) {
        //int conflic_count = 0;
        Target *target = map_it->second;
        ref<Expr> addr1 = target->addr;

        ref<Expr> final_constraint = ConstantExpr::alloc(0, Expr::Int32);

        ExprSet::iterator es_it;
        ExprMap::iterator em_it;

        //klee_message("Conf_addr size: %ld, line: %d", target->conf_addrs.size(), target->info->line);
        for (es_it = target->conf_addrs.begin(); es_it != target->conf_addrs.end(); ++es_it) {
            ref<Expr> addr2 = static_cast<ref<Expr>>(*es_it);

            //llvm::errs() << "Conflic address: " <<addr2 << "\n";

            ref<Expr> conf_constr = ConstantExpr::alloc(1, Expr::Bool);
            ref<Expr> unique_constr = ConstantExpr::alloc(1, Expr::Bool);
            ref<Expr> reload_constr = ConstantExpr::alloc(1, Expr::Bool);


            ExprSet::iterator reload_es_it;
            em_it = target->conf_constrs.find(addr2);
            assert(em_it != target->conf_constrs.end() && "Should find constraint set in the constraint map");
            conf_constr = em_it->second;
            ExprMapSet::iterator ems_it;

            //llvm::errs() << "Conflic constraint:\n";
            //conf_constr->dump();

            // Generate union constraint for checking unique
            int unique_count = 0;
            ems_it = target->unique_constrs.find(addr2);

            //llvm::errs() << "unique size: "<<target->unique_constrs.size()<<"\n";
            if (ems_it != target->unique_constrs.end()) {
                ExprSet *conf_set = static_cast<ExprSet*>(ems_it->second);
                ExprSet::iterator conf_es_it;
                for (conf_es_it = conf_set->begin(); conf_es_it != conf_set->end(); ++conf_es_it) {
                    ref<Expr> unique = static_cast<ref<Expr>>(*conf_es_it);
                    if (unique_constr.get() == 0) {
                        unique_constr = unique;
                    } else {
                        unique_constr = AndExpr::create(unique_constr, unique);
                    }
                    unique_count++;
                }
            }

            // Generate union constraint for cheking no relaod
            int reload_count = 0;
            ExprMapSet::iterator reload_ems_it;
            reload_ems_it = target->reloads.find(addr2);

            if (reload_ems_it != target->reloads.end()) {
                ExprSet *reload_es = static_cast<ExprSet*>(reload_ems_it->second);
                //llvm::errs() << "reload size: "<<reload_es->size()<<"\n";
                for (auto e = reload_es->begin(); e != reload_es->end(); ++e) {
                    reload_constr = AndExpr::create(reload_constr, static_cast<ref<Expr>>(*e));
                    reload_count++;
                }
            }

            ref<Expr> conflict_constr = AndExpr::create(conf_constr, unique_constr);
            conflict_constr = AndExpr::create(conflict_constr, reload_constr);

            conflict_constr = ZExtExpr::create(conflict_constr, Expr::Int32);
            //llvm::errs() << "final len: " << final_constraint->getWidth() << "\n";
            //llvm::errs() << "conflict len: " << conflict_constr->getWidth() << "\n";
            final_constraint = AddExpr::create(final_constraint, conflict_constr);

        } // end

        // Totall confilicts less than Ways.
        // True --> leakage
        // False --> No leakage
        ref<Expr> cache_constr = UltExpr::create(final_constraint, ConstantExpr::alloc(CacheConfig::cache_ways, Expr::Int32));

        //bool result;
        //llvm::errs()<<"@@@@ Solving cache formula:\n";
        //final_constraint->dump();
        //ref<ConstantExpr> res;
        ref<Expr> cache_constr_optimize = optimizer.optimizeExpr(cache_constr, false);

        
        //llvm::errs()<<"@@@@ Solving cache formula:\n";
        //cache_constr_optimize->dump();

        //bool success = solver->getValue(state, cache_constr_optimize, res);
        Solver::Validity res;
        bool success = solver->evaluate(state, cache_constr_optimize, res);
        const auto seconds = time::getUserTime().toMicroseconds();
        //const auto seconds = elapsed().toMicroseconds();

        //klee_message("success");

        if (!success) {
            if (CacheState::found_vuls.find(target->info->assemblyLine) == CacheState::found_vuls.end()) {  
                CacheState::found_vuls[target->info->assemblyLine] = 0;
                klee_message("@CM found a leakage (solver failed): %s: %u, ASM line=%u, time = %lu, Cache ways: %d, Cache set: %d, count=%d", target->info->file.c_str(), target->info->line, target->info->assemblyLine, seconds, CacheConfig::cache_ways, CacheConfig::cache_set_size, CacheState::found_vuls[target->info->assemblyLine]);
            }
            CacheState::found_vuls[target->info->assemblyLine]++;
        } else {
            if (res == Solver::True || res == Solver::Unknown) {
                if (CacheState::found_vuls.find(target->info->assemblyLine) == CacheState::found_vuls.end()) {  
                    CacheState::found_vuls[target->info->assemblyLine] = 0;
                    //CacheState::found_vuls.insert(target->info->assemblyLine);
                    klee_message("@CM: found a leakage: %s: %u, ASM line=%u, time = %lu, Cache ways: %d, Cache set: %d, count=%d", target->info->file.c_str(), target->info->line, target->info->assemblyLine, seconds, CacheConfig::cache_ways, CacheConfig::cache_set_size, CacheState::found_vuls[target->info->assemblyLine]);
                }
                CacheState::found_vuls[target->info->assemblyLine]++;
            } else if (res == Solver::False) {
                //res == Solver::False or res == Solver::unkonw
                klee_message("@CM: No leakage for state: %ld,  %s: %u, ASM line=%u, time = %lu, Cache ways: %d, Cache set: %d", state.tag, target->info->file.c_str(), target->info->line, target->info->assemblyLine, seconds, CacheConfig::cache_ways, CacheConfig::cache_set_size);
                //klee_message("@CM: False" );
            } else {
                klee_message("@CM: Unkown");
            }
        }

    } // end targets
    //klee_message("============== Verify End for state: %ld ==============", state.tag);
}

void CacheState::mergeSpecCacheState() {
    assert(state.specStates.empty());
    for (auto &ss: state.finishedSpecStates) {
        CacheState *cs = ((ExecutionState *)ss)-> cacheState;
        for (auto &t: cs->targets) {
            isSensitive = true;
            Target *tt = new Target(*(t.second));
            targets.insert(MapTarget(t.second->addr, tt));                
            //klee_message("Insert a target from %lu to %lu", ss->tag, state.tag);
        }
        delete ss;
    }
    state.finishedSpecStates.clear();
}


