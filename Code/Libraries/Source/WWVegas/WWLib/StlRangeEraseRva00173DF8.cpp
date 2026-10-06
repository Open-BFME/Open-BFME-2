// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include "../../../../../vendor/stlport/stl/_algobase.h"
#include <vector>
#include "StlRecordRva0017341B.h"
namespace _STL {
template<> Rva0017341BWords* __copy(Rva0017341BWords*,Rva0017341BWords*,Rva0017341BWords*,const random_access_iterator_tag&,int*);
}
template Rva0017341BWords* _STL::__copy_ptrs(Rva0017341BWords*,Rva0017341BWords*,Rva0017341BWords*,const _STL::__false_type&);
template Rva0017341BWords* _STL::vector<Rva0017341BWords>::erase(Rva0017341BWords*,Rva0017341BWords*);

// Target 00173714 plain-ret29B calls the native126B forward-copy loop
// 0017341B with three range pointers, a local iterator tag and null distance.
// Its matched caller00173DF8 uses the four-argument reference-tag ABI,
// copies [last,finish) into first, stores the new finish and returns first.
// Native126B helper proves48B stride and twelve scalar word copies; no
// application record identity or deeper layout is inferred. The loop's
// matching helper now shares StlRecordRva0017341B.h with these callers.
