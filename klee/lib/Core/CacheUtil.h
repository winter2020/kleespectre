//===-- CacheUtil.h -------------------------------------------------------===//
//
//===----------------------------------------------------------------------===//
#ifndef __CACHE__UTIL__H__
#define __CACHE__UTIL__H__

#include "klee/ExecutionState.h"
#include "klee/Expr.h"

#include <map>


/* default cache configuration */
#define CACHE_WAYS (2)
#define CACHE_LINE_SIZE (64)
#define CACHE_SET_SIZE (512/ CACHE_WAYS)


namespace llvm {
    class Constant;
    class ConstantExpr;

}

namespace klee {
    class Expr;
    template<class T> class ref;

    typedef std::pair<ref<Expr>, ref<Expr>> PairExpr;
    typedef std::map<ref<Expr>, ref<Expr>> AddrMap;
    typedef std::map<PairExpr, ref<Expr>> AddrPairMap;

/* Cache configuration */
class CacheConfig { 
public:
    static unsigned int cache_ways;
    static unsigned int cache_line_size;
    static unsigned int cache_set_size;
};

class CacheUtil {

public:
    static AddrPairMap setPairBuffer;
    static AddrPairMap tagPairBuffer;
    static AddrMap setBuffer;
    static AddrMap tagBuffer;

    static uint64_t getSet(ConstantExpr *ce);
    static ref<Expr> getSet(ref<Expr> &addr);
    static uint64_t getTag(ConstantExpr *ce);
    static ref<Expr> getTag(ref<Expr> &addr);

    static int log_base2(int n) {
        int power = 0;  
        if (n <= 0 || (n & (n-1)) != 0) {
            assert(0 && "log2() only works for positive power of two values");
        }
        while (n >>= 1)
            power++;
        return power;
    }   

	static bool generateSetCnstrCC(ref<Expr>& addressI, ref<Expr>& addressJ);
    static bool generateTagCnstrCC(ref<Expr>& addressI, ref<Expr>& addressJ);
    static ref<Expr> generateSetCnstr(ref<Expr>& addressI, ref<Expr>& addressJ);
    static ref<Expr> generateTagCnstr(ref<Expr>& addressI, ref<Expr>& addressJ);

}; // End class CacheUtil

} // end namespace klee

#endif
