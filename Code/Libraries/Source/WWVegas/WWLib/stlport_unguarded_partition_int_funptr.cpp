// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__unguarded_partition@PAHHP6A_NHH@Z@_STL@@YAPAHPAH0HP6A_NHH@Z@Z @0x002C529D 67B
// Quicksort partition over 4-byte int keys with a function-pointer comparator
// (indirect calls); scan up while comp(*first,pivot), scan down while
// comp(pivot,*last), swap on cross, return the split. Callers 0x0021DDC5
// 0x002C56E7 are the 123B introsort_loops.
#include <algorithm>

typedef bool (__cdecl *IntFunLess)(int a, int b);
template int* _STL::__unguarded_partition(int*, int*, int, IntFunLess);
