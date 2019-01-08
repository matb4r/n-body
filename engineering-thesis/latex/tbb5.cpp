#include "tbb/tbb.h"
 
using namespace tbb;

void ParallelApplyFoo(float a[], size_t n) {
    parallel_for(size_t(0), n, [=](size_t i) {Foo(a[i]);});
}