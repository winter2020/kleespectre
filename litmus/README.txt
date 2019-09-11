1. Use ./compile.sh to compile all litmus tests. 
2. Use the following command to run each limus test. 
 /PATH/TO/KLEE/ROOT/klee --search=randomsp --output-istats --enable-speculative --simplify-sym-indices --write-cvcs --write-cov --output-module --max-memory=8000 --disable-inlining --use-cex-cache --only    -output-states-covering-new --max-instruction-time=30 --max-memory-inhibit=false --max-static-fork-pct=1 --max-static-solve-pct=1 --max-static-cpfork-pct=1 --switch-type=internal test.bc

3. For testing cache:
   $ cd litmus_cache
   A. Test 2-way cache:
   $ cd  way2
   $ ./run_way2.sh > out.txt 2>&1

   B. Test 4-way cache: 
   $ cd way4 
   $ ./run_way4.sh > out.txt 2>&1

   C. Test 8-way cache: 
   $ cd way8 
   $ ./run_way8.sh > out.txt 2>&1
