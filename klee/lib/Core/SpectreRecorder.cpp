//===-- SpectreRecorder ------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "klee/Internal/Support/ErrorHandling.h"
#include "SpectreRecorder.h"
#include "klee/Internal/System/Time.h"


using namespace llvm;
using namespace klee;

namespace klee {

void SpectreRecorder::recordCacheResult(const InstructionInfo *temp, bool isVul) {

}

void SpectreRecorder::recordBR(const InstructionInfo *temp, bool isUserControlled) {
 
    InstructionInfo *br = const_cast<InstructionInfo *>(temp);
    std::map<InstructionInfo*, SpectreRecord*>::iterator it;

    if (tempRecord) {
        if (tempRecord->br == br) {
            return;
        } else {
             it = recordObjects.find(br);
             if (it != recordObjects.end()) {
                 tempRecord = it->second;
                 assert(tempRecord->br == br);
                 return;
               
             } else if (tempRecord->rs.empty()){
                 tempRecord->br = br;
                 tempRecord->isUserControlled = isUserControlled;
                 return;
             } 
        }

    } 

    it = recordObjects.find(br);
     if (it != recordObjects.end()) {
          tempRecord = it->second;
          return;
     }

    tempRecord = new SpectreRecord();
    tempRecord->br = br;
}

void SpectreRecorder::recordRS(const InstructionInfo *temp, bool isConst, bool isSecret) {
    assert(tempRecord && tempRecord->br);

    InstructionInfo *rs = const_cast<InstructionInfo *>(temp);

    std::set<InstructionInfo *>::iterator it;

    it = tempRecord->ii.find(rs);

    if (it == tempRecord->ii.end()) {
        if (tempRecord->rs.empty()) {
            recordObjects.insert(std::pair<InstructionInfo*, SpectreRecord*>(tempRecord->br, tempRecord));
        }
        if (tempRecord->rs.size() < 10000000) {
            LeakageInfo *li = new LeakageInfo(rs, LeakageKind::inExpression, isConst, isSecret);
            tempRecord->rs.insert(li);
            tempRecord->ii.insert(rs);
        }
    }

}

void SpectreRecorder::recordLS(const InstructionInfo *temp, enum LeakageKind lk, bool isConst) {
    assert(tempRecord && tempRecord->br);

    //if (tempRecord->ls.size() >= 100)
    //    return;
    uint64_t asm_line = temp->assemblyLine;
    auto al = ls_asm_lines.find(asm_line);

    if (al != ls_asm_lines.end()) {
        return; 
    }

    ls_asm_lines.insert(asm_line);

    //const auto seconds = time::getUserTime().toMicroseconds();
    //klee_message("@SR: Found a new leakage: %s: %d, ASMLine: %d, time=%lu", temp->file.c_str(), temp->line, temp->assemblyLine, seconds);

    InstructionInfo *ls = const_cast<InstructionInfo *>(temp);

    std::set<InstructionInfo*>::iterator it;

    it = tempRecord->ls_cache.find(ls);

    if (it == tempRecord->ls_cache.end()) {
        tempRecord->ls_cache.insert(ls);
        tempRecord->ls.insert(new LeakageInfo(ls, lk, isConst, false));
    }
}

void SpectreRecorder::dump(llvm::raw_ostream &os) {
    klee_message("\n============ Spectre ================");
    klee_message("Spectre detection summary:");
    klee_message("Total Spectre found: %ld", recordObjects.size());

    
    for (std::map<InstructionInfo*, SpectreRecord*>::iterator it = recordObjects.begin(); 
            it != recordObjects.end(); ++it)  {

        InstructionInfo* br = it->first;
        SpectreRecord *sr = it->second;
        //os << "1BR: " << br->file<< " : " << br->assemblyLine << "\n";
        klee_message("1BR: %s: %d, ASMLine: %d, UserControlled: %d", br->file.c_str(), br->line, br->assemblyLine, sr->isUserControlled);

        for (std::set<LeakageInfo*>::iterator rs_it=sr->rs.begin(); 
                rs_it != sr->rs.end(); ++rs_it) {

            //InstructionInfo * ii = (InstructionInfo *)rs_it;
            //os << "RS: " << ii->file<< " : " <<  br->line << "\n";
            //os << "2RS: " << (*rs_it)->file << " : " << (*rs_it)->assemblyLine << "\n";
            LeakageInfo *li = (LeakageInfo*)*rs_it;
            klee_message("2RS: %s: %d, ASMLine: %d, isConst: %d, isMarkedSecret: %d", li->ls->file.c_str(), li->ls->line, li->ls->assemblyLine, li->isConst, li->isMarkedSecret);
        }

        for (std::set<LeakageInfo *>::iterator li_it=sr->ls.begin(); 
                li_it != sr->ls.end(); ++li_it) {
            LeakageInfo const *li = (LeakageInfo*)*li_it;
            //os << "3LS: " << li->ls->file << " : " << li->ls->assemblyLine << ", kind: " << (li->kind == LeakageKind::inExpression ? "In Expression\n" : "In Constraint \n");
            //os << "3LS: " << li->ls->file << " : " << li->ls->assemblyLine << ", kind: " << (li->kind == LeakageKind::inExpression ? "In Expression\n" : "In Constraint \n");
            klee_message("3LS: %s: %d, ASMLine: %d. kind: %s, isConst: %d", li->ls->file.c_str(), li->ls->line, li->ls->assemblyLine, (li->kind == LeakageKind::inExpression ? "In Address" : "In Constraint"), li->isConst);
        }

        klee_message("===================================\n");

    }


}


} // end klee

