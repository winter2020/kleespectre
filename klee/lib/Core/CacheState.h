//===-- CacheState.h ------------------------------------------------------===//
//
//===----------------------------------------------------------------------===//
#ifndef KLEE_CACHESTATE_H
#define KLEE_CACHESTATE_H


#include "klee/ExecutionState.h"
#include "CacheUtil.h"
#include "../Expr/ArrayExprOptimizer.h"
#include "SpectreRecorder.h"


#include <vector> 
#include <set>
#include <map>
#include <unordered_map> 

namespace llvm {
    class Constant;
    class ConstantExpr;
    class SpectreRecorder;

}


namespace klee {
        class Expr;
        template<class T> class ref;
        typedef std::pair<ref<Expr>, ref<Expr>> PairExpr;
        typedef std::map<ref<Expr>, ref<Expr>> ExprMap;
        typedef std::set<ref<Expr>> ExprSet;
        typedef std::pair<ref<Expr>, ExprSet*> PairExprSet;
        typedef std::map<ref<Expr>, ExprSet*> ExprMapSet;
        
struct ConstantCache {
    int fullCount;
    std::vector<std::set<uint64_t> *> ccState;
    ConstantCache();
    void access(ref<Expr> &addr);
    bool isFull() { return (fullCount == 0? true: false);}
    ~ConstantCache();
};

struct Target {
    const InstructionInfo *info;
    ref<Expr> addr;
    ExprSet conf_addrs;
    ExprMap conf_constrs;
    ExprMapSet unique_constrs;
    ExprMapSet reloads;

    ConstantCache ccstate;

    Target() {};
    Target(Target& t);
    ~Target();

};

class CacheState {
    typedef std::pair<ref<Expr>, Target*> MapTarget;
public:
    std::map<ref<Expr>, Target*> targets;

private:
    ExecutionState &state;
    bool isSensitive;
    ExprOptimizer optimizer;
    //typedef std::unordered_set<ref<Expr>> CacheSet;
    //typedef std::vector<CacheSet*>  CacheSets;
    //static std::set<unsigned> found_vuls;
    static std::map<unsigned, int> found_vuls;
    SpectreRecorder *recorder;
    
    //std::unordered_map<ref<Expr>, Target*>  allTargets;

public:
    CacheState(ExecutionState &state);
    CacheState(ExecutionState &state, const CacheState &cs);
    ~CacheState();
    
    void mergeSpecCacheState();
    bool conflicConstr(ref<Expr> &addr1, ref<Expr> &addr2, ref<Expr> &result);
    bool uniqueConstr(ref<Expr> &addr1, ref<Expr> &addr2, ref<Expr> &result);
    bool reloadConstr(ref<Expr> &addr1, ref<Expr> &addr2, ref<Expr> &result);

    void handleAccess(ref<Expr> &addr, const InstructionInfo *info);
    void load(ref<Expr> &addr, const InstructionInfo *info);
    void store(ref<Expr> &addr, const InstructionInfo *info);
    void verifyCacheSideChannel(TimingSolver *solver);
    void setSpectreRecord(SpectreRecorder *sr);
    void recordResult(const InstructionInfo *temp, bool isVul);
    void dump();

}; // end calss CacheState

} // end namespace klee

#endif
