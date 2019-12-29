# KLEESpectre
KLEESpectre is a symbolic execution engine with speculation semantics and cache modelling. KLEESPectre built on top of the KLEE symbolic execution engine, can thus provide a testing engine to check for the data leakage through cache side channel as shown via Spectre attacks. Our symbolic cache model can verify whether the sensitive data leakage due to speculative execution can be observed by an attacker at a given program point.<br />

## Publication 

> Guanhua Wang, Sudipta Chattopadhyay, Arnab Kumar Biswas, Tulika Mitra, Abhik Roychoudhury. KLEESPECTRE: Detecting Information Leakage through Speculative Cache Attacks via Symbolic Execution.arXiv:1909.00647. 

Paper link: [kleespectre](https://arxiv.org/abs/1909.00647)

## Environment setting up. <br />
  KLEESpectre is based on the latest KLEE, which needs the support of LLVM-6.0.  <br />
  NOTE: Suggest to refer "https://klee.github.io/build-llvm60/" to install all dependencies. 
  ### Install all the dependencies of LLVM 
```
$sudo apt-get install build-essential curl libcap-dev git cmake libncurses5-dev python-minimal python-pip unzip libtcmalloc-minimal4 libgoogle-perftools-dev libsqlite3-dev doxygen 
$ pip3 install tabulate 
``` 
  ### Install LLVM-6.0 <br />
```
$ sudo apt-get install clang-6.0 llvm-6.0 llvm-6.0-dev llvm-6.0-tools 
``` 
## Build KLEEspectre. 
```
$ cd klee/build 
$ cp ../buid.sh . (or build_debug.sh for debug version) 
$ ./buid.sh 
$ make -j 10 
```    
## Options to enable speculative execution and cache modeling 
```
$ /PATH/TO/KLEE/ROOT/klee --help
...
Speculative execution options:
These options impact the speculative paths exploring and the cache modeling

  -cache-line-size=<uint>                                - Cache line size (default=64)
  -cache-sets=<uint>                                     - Cache sets (default=256)
  -cache-ways=<uint>                                     - Cache ways (default=2)
  -enable-cachemodel                                     - Enable Cache modeling (default=off).
  -enable-speculative                                    - Enable Speculative execuction modeling (default=off).
  -max-sew=<uint>                                        - Maximum SEW (default=10)
...
```
## Run a test without cache modelling: <br />
```
/PATH/TO/KLEE/ROOT/klee -check-div-zero=false -check-overshift=false --search=randomsp --output-istats=true --enable-speculative --max-sew=50 --env-file=/home/wgh/fineTest/test.env --run-in-dir=/tmp/sandbox --simplify-sym-indices --write-cvcs --write-cov --output-module --max-memory=8000 --disable-inlining --optimize --use-forked-solver --use-cex-cache --only-output-states-covering-new --max-instruction-time=30     --max-time=43200 --watchdog --max-memory-inhibit=false --max-static-fork-pct=1 --max-static-solve-pct=1 --max-static-cpfork-pct=1 switch-type=internal ./aes.bc" 
```   
"--enable-speculative" option enables the speculative paths exploring <br />
"--max-sew=#" set the Specualtive Execution Windows (SEW) to # (default is 10, 50 and 100 are used in the paper.) <br />
   
## Run a test with cache modelling: <br />
     Add "-enable-cachemodel" option to the command line

## Run KLEESpectre on an example code. 
```
#include <stdint.h>
#include <klee/klee.h>

unsigned int array1_size = 16; 
uint8_t array1[16];
uint8_t array2[256 * 64];
uint8_t temp = 0;


uint8_t victim_fun(int idx)  __attribute__ ((optnone)) 
{
    int y = 0;
    if (idx < array1_size) {    
        y = array1[idx];
        temp &= array2[y*64];
    }   

    /* This two lines disable the compiler optimization of array */
    array2[0] = 2;  
    array1[0] = 2;
    return temp;
}

int main() {
    int source = 20; 
    klee_make_symbolic(&source, sizeof(source), "source");
    victim_fun(source);
    return 0;
}
```
Compile above code to generate bitcode: 
```
clang -g -c -emit-llvm toy.c -o toy.bc
```
Run KLEESpectre with the generated bitcode:
```
/PATH/TO/KLEE/ROOT/klee -check-div-zero=false -check-overshift=false --search=randomsp --output-istats=true --enable-speculative --max-sew=50 --enable-cachemodel --env-file=/home/wgh/fineTest/test.env --run-in-dir=/tmp/sandbox --simplify-sym-indices --write-cvcs --write-cov --output-module --max-memory=8000 --disable-inlining --optimize --use-forked-solver --use-cex-cache --only-output-states-covering-new --max-instruction-time=30 --max-time=43200 --watchdog --max-memory-inhibit=false --max-static-fork-pct=1 --max-static-solve-pct=1 --max-static-cpfork-pct=1 --switch-type=internal ./toy.bc
```
The output of KLEESpectre: 
```
KLEE: WARNING: @Speculative execution modeling is enabled! maxSEW=50
Max instruction time: 30
KLEE: Using STP solver backend
KLEE: WARNING: 
@Start execution ==>

KLEE: WARNING ONCE: flushing 16384 bytes on read, may be slow and/or crash: MO8[16384] allocated at global:array2
KLEE: @CM: found a leakage: toy.c: 23, ASM line=33, time = 44000, WAYS: 2
KLEE: 
============ Spectre ================
KLEE: Spectre detection summary:
KLEE: Total Spectre found: 1
KLEE: 1BR: toy.c: 21, ASMLine: 20, UserControlled: 0
KLEE: 2RS: toy.c: 22, ASMLine: 26, isConst: 0
KLEE: 3LS: toy.c: 23, ASMLine: 33. kind: In Address, isConst: 0
KLEE: ===================================


KLEE: done: total instructions = 60
KLEE: done: completed paths = 2
KLEE: done: sp states = 2
KLEE: done: Completed sp states = 2
KLEE: done: Average instructions on speculative path = 10.5
KLEE: done: generated tests = 2
KLEE: done: loads: 10
KLEE: done: stores: 14
KLEE: done: constant loads: 6
KLEE: done: constant stores: 14
```
A description of the output: <br />
The line starts with `KLEE: @CM` denote there is a leakage found by the KLEESpectre with cache modeling. The lines between the "====" describe the potential leakage without the cache modeling. The line starts with `KLEE: 1BR` is the branch that misprediction causes cause data leakage. `KLEE: 2BS` denotes the code line loading the potentially sensitive data, finally the line `KLEE: 3LS` give the code line information for leaking the sensitive data to cache state. The rest part of the output is the statistic of this test including the numbers of the executed instructions, explored paths, explored speculative paths (`sp states = 2`) and so on. 

## Reproduce the data of Table 2 in KLEESpectre paper. 
```
git checkout tags/v1.0
cd benchmarks_original
./compile.sh
```
Then run the bitcode with KLEESpectre with the command mentioned above without the `--enable-cachemodel` option, the `--max-sew` set to 50 and 100. When you run original KLEE, remove the option `--enable-speculative --max-sew=#`, instead, you can add `--search=random-path --search=nurs:covnew` for the general path selection heuristic. The results are in [results_without_cache](results/kleespecrtre_without_cache.txt)

## Reproduce the data of Table 3 in KLEESpectre paper. 
```
git checkout tags/v1.0
cd benchmarks_cache
./compile.sh 
```
Then run the bitcode with KLEESpectre with the command mentioned above with the `--enable-cachemodel` option. You can run `klee-stats` to get the analysis time and the solver time. 
```
/PATH/TO/KLEE/ROOT/build/bin/klee-stats klee-out-0
```
Output: 
```
------------------------------------------------------------------------
|  Path   |  Instrs|  Time(s)|  ICov(%)|  BCov(%)|  ICount|  TSolver(%)|
------------------------------------------------------------------------
|klee-last| 1225894|    79.87|    88.77|   158.00|     552|        0.19|
------------------------------------------------------------------------
```

To test different cache configurations, the option `-cache-line-size=#` sets cache line size to #, the default value is 64. The Option `-cache-ways=#`  sets cache ways to #, default is 2. Option `-cache-sets=#` sets cache set to #, default value is 256. An example cache configuration is `-enable-cachemodel  -cache-ways=2 -cache-line-size=64 -cache-sets=256`. (Note that, the cache modeling only works with speculative path exploring enabled (`--enable-speculative`))
KLEESpectre must be recompiled after this change.  The results are in [results_cache](results/kleespecrtre_with_cache.txt)

# Using KLEESpectre with Docker
##Building the Docker image locally
```
$ git clone https://github.com/winter2020/kleespectre.git
$ cd klee
$ docker build -t kleespectre/kleespectre .
```
##Creating a KLEE Docker container
```
docker run --rm -ti --ulimit='stack=-1:-1' klee/klee
```
