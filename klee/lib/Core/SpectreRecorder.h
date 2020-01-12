// Spectre Recorder.
//
//===----------------------------------------------------------------------===//
#ifndef KLEE_SPECRECORDER_H
#define KLEE_SPECRECORDER_H


#include "klee/Internal/Module/KInstruction.h"

#include <vector> 
#include <set>
#include <map>

namespace klee {
    struct InstructionInfo;

    enum LeakageKind {
        inExpression,
        inConstraint
    };

struct LeakageInfo {
    LeakageInfo(InstructionInfo *_ls, enum LeakageKind _lk, bool _isConst, bool _isSec) : 
        ls(_ls), kind(_lk), isConst(_isConst), isMarkedSecret(_isSec) {}
    InstructionInfo* ls;
    LeakageKind kind;
    bool isConst;
    bool isMarkedSecret;
    };

struct SpectreRecord{
    SpectreRecord(): br(0), isUserControlled(false) {}
    InstructionInfo *br;
    bool isUserControlled;
    std::set<InstructionInfo *> ii;
    std::set<LeakageInfo *> rs;
    std::set<LeakageInfo *> ls;
    std::set<InstructionInfo*> ls_cache;
};

class SpectreRecorder {
private:
    std::map<InstructionInfo*, SpectreRecord*> recordObjects;
    SpectreRecord *tempRecord;
    std::set<uint64_t> ls_asm_lines;

public: 
    SpectreRecorder(): tempRecord(0){}

    void recordBR(const InstructionInfo *br, bool isUserControlled);
    void recordRS(const InstructionInfo *rs, bool isConst, bool isSecret);
    void recordLS(const InstructionInfo *ls, enum LeakageKind lk, bool isConst);
    void recordCacheResult(const InstructionInfo *temp, bool isVul);
    void dump(llvm::raw_ostream &os);

}; // end calss SpecRecoder

} // end namespace klee

#endif
