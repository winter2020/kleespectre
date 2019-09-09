//===-- CacheUtil.cpp  -----------------------------------------------------===//
// 
//
//===----------------------------------------------------------------------===//

#include "CacheUtil.h"
#include "klee/Expr.h"

#include <map>
#include <utility>

#define CACHE_SET(x,nset,line) (((x) >> log_base2(line)) & (nset - 1))
#define CACHE_TAG(x,nset,line) ((x) >> (log_base2(line) + log_base2(nset)))


using namespace llvm;
using namespace klee;

// static class members initilization
//
AddrPairMap CacheUtil::setPairBuffer;
AddrPairMap CacheUtil::tagPairBuffer;
AddrMap CacheUtil::setBuffer;
AddrMap CacheUtil::tagBuffer;

unsigned int CacheConfig::cache_ways = CACHE_WAYS;
unsigned int CacheConfig::cache_line_size = CACHE_LINE_SIZE;
unsigned int CacheConfig::cache_set_size = CACHE_SET_SIZE;


// Calculate set for Constant expression
uint64_t CacheUtil::getSet(ConstantExpr *ce)  {
    uint64_t addrRaw = ce->getZExtValue();
    uint64_t set = CACHE_SET(addrRaw, CacheConfig::cache_set_size, CacheConfig::cache_line_size);
    return set;
}

// Caculate set for symbolic expression
ref<Expr> CacheUtil::getSet(ref<Expr> &addr)  {
    ref<Expr> set;

    assert(addr->getKind() != Expr::Constant);

    if (setBuffer.count(addr)) {
        set = setBuffer[addr];
    } else {
        ref<Expr> blAddr = LShrExpr::create(addr, ConstantExpr::alloc(log_base2(CacheConfig::cache_line_size), addr->getWidth()));
        set = AndExpr::create(blAddr, ConstantExpr::alloc(CacheConfig::cache_set_size - 1, addr->getWidth()));
        setBuffer[addr] = set;
    }
    return set;
}

// Calculate tag for Constant expression
uint64_t CacheUtil::getTag(ConstantExpr *ce) {
    uint64_t addrRaw = ce->getZExtValue();
    uint64_t tag =  CACHE_TAG(addrRaw, CacheConfig::cache_set_size, CacheConfig::cache_line_size);
    return tag;
}

// Calculate tag for symbolic expression
ref<Expr> CacheUtil::getTag(ref<Expr> &addr) {
    ref<Expr> tag;

    assert(addr->getKind() != Expr::Constant);

    if (tagBuffer.count(addr)) {
        return tagBuffer[addr];
    }
    tag = LShrExpr::create(addr, ConstantExpr::alloc(log_base2(CacheConfig::cache_line_size)+log_base2(CacheConfig::cache_set_size), addr->getWidth()));
    tagBuffer[addr] = tag;
    return tag;
}

/* generate tag inequality constraints for constant address pairs */
bool CacheUtil::generateTagCnstrCC(ref<Expr>& addressI, ref<Expr>& addressJ) {
    ConstantExpr *ce1 = dyn_cast<ConstantExpr>(addressI);
    ConstantExpr *ce2 = dyn_cast<ConstantExpr>(addressJ);

    return (getTag(ce1) ==  getTag(ce2));
}

/* generate set equality constraints for constant address pairs */
bool CacheUtil::generateSetCnstrCC(ref<Expr>& addressI, ref<Expr>& addressJ) {

	ConstantExpr* ce1 = dyn_cast<ConstantExpr>(addressI);
	ConstantExpr* ce2 = dyn_cast<ConstantExpr>(addressJ);

	return (getSet(ce1) == getSet(ce2));
}


/* generate set equality constraints for <symbolic,c|s> <c|s, symbolic>address pairs */
ref<Expr> CacheUtil::generateSetCnstr(ref<Expr>& addressI, ref<Expr>& addressJ) {
    uint64_t set; 
    bool hasConst = false;
    ref<Expr> sSet;
    ref<Expr> cAddr = addressI;
    ref<Expr> sAddr1 = addressJ;
    ref<Expr> sAddr2 = addressI;
    ref<Expr> result;


    if (addressI->getKind() == Expr::Constant) {
        hasConst = true;
    } else if (addressJ->getKind() == Expr::Constant) {
        cAddr = addressJ;
        sAddr1 = addressI;
        hasConst = true;
    }

    if (hasConst) {

        assert(sAddr1->getKind() != Expr::Constant);

        PairExpr setPair(cAddr, sAddr1);

        if(setPairBuffer.count(setPair)) {
            return setPairBuffer[setPair];
        }
        
        ConstantExpr *ce = dyn_cast<ConstantExpr>(cAddr);
        set = getSet(ce);
        sSet = getSet(sAddr1);
        result = EqExpr::create(sSet, ConstantExpr::alloc(set, sSet->getWidth()));
        setPairBuffer[setPair] = result;
    } else {
        assert(sAddr1->getKind() != Expr::Constant);
        assert(sAddr2->getKind() != Expr::Constant);
        
        PairExpr sp1(sAddr1, sAddr2);
        PairExpr sp2(sAddr2, sAddr1);

        if (setPairBuffer.count(sp1)) {
            return setPairBuffer[sp1];
        } else if (setPairBuffer.count(sp2)) {
            return setPairBuffer[sp2];
        }
        ref<Expr> s1 = getSet(sAddr1);
        ref<Expr> s2 = getSet(sAddr2);
        result = EqExpr::create(s1, s2);
        setPairBuffer[sp1] = result;
    }

    return result;
}

/* generate tag equality constraints for <symbolic,c/s>, <c|s, symbolic> address pairs */
ref<Expr> CacheUtil::generateTagCnstr(ref<Expr>& addressI, ref<Expr>& addressJ) {
    uint64_t tag; 
    ref<Expr> sTag;
    bool hasConst = false;
    ref<Expr> cAddr = addressI;
    ref<Expr> sAddr1 = addressJ;
    ref<Expr> sAddr2 = addressI;
    ref<Expr> result;


    if (addressI->getKind() == Expr::Constant) {
        hasConst = true;
    } else if (addressJ->getKind() == Expr::Constant) {
        cAddr = addressJ;
        sAddr1 = addressI;
        hasConst = true;
    }

    if (hasConst) {
        assert(sAddr1->getKind() != Expr::Constant);
 
        PairExpr addrPair(cAddr, sAddr1);

        if(tagPairBuffer.count(addrPair)) {
            return tagPairBuffer[addrPair];
        }
        
        ConstantExpr *ce = dyn_cast<ConstantExpr>(cAddr);
        tag = getTag(ce);
        sTag = getTag(sAddr1);
        result = EqExpr::create(sTag, ConstantExpr::alloc(tag, sTag->getWidth()));
        tagPairBuffer[addrPair] = result;
    } else {

        assert(sAddr1->getKind() != Expr::Constant);
        assert(sAddr2->getKind() != Expr::Constant);
 
        PairExpr sp1(sAddr1, sAddr2);
        PairExpr sp2(sAddr2, sAddr1);

        if (tagPairBuffer.count(sp1)) {
            return tagPairBuffer[sp1];
        } else if (tagPairBuffer.count(sp2)) {
            return tagPairBuffer[sp2];
        }
        ref<Expr> s1 = getTag(sAddr1);
        ref<Expr> s2 = getTag(sAddr2);
        result = EqExpr::create(s1, s2);
        tagPairBuffer[sp1] = result;
    }
    return result;
}
