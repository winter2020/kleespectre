1. Use ./compile.sh to compile all litmus tests. 
2. Use the following command to run each limus test. 
 /PATH/TO/KLEE/ROOT/klee --search=randomsp --output-istats --enable-speculative --simplify-sym-indices --write-cvcs --write-cov --output-module --max-memory=8000 --disable-inlining --use-cex-cache --only    -output-states-covering-new --max-instruction-time=30 --max-memory-inhibit=false --max-static-fork-pct=1 --max-static-solve-pct=1 --max-static-cpfork-pct=1 --switch-type=internal test.bc

3. For testing cache, compile litmus_cache.c with: 
    clang-6.0 -g -c --emit-llvm litmus_cache.c -o litmus_cache.bc

   Run with command:
     /PATH/TO/KLEE/ROOT/klee --search=randomsp --output-istats --enable-speculative --enable-cachemodel --cache-ways=2 --cache-sets=256 --simplify-sym-indices --write-cvcs --write-cov --output-module --max-memory=8000 --disable-inlining --use-cex-cache --only    -    output-states-covering-new --max-instruction-time=30 --max-memory-inhibit=false --max-static-fork-pct=1 --max-static-solve-pct=1 --max-static-cpfork-pct=1 --switch-type=internal test.bc

   --cache-ways and --cache-sets can set to 4ways (128 sets) and 8 ways (64 sets)
   (*NOTE: the implementation changes after the submission, the results may be sightly different from the paper.)
