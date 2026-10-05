// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Target [5B09D8,5B09F5),29B cdecl wrapper. Native erase5B129F
// passes last/finish/first and an empty false_type by reference. STLport4.5.3
// __copy_ptrs is the semantic guide; the local shim changes its tag ABI.
// Preserve the retail const-reference tag and random-access category temporary.
// Record below is only the measured five-DWORD copy view, not an original name.
// Full rowed50B __copy at5B04D3 computes signed element distance with stride20
// and copies five DWORDs on each iteration. Its existing provider's type name
// is used solely to link that proven raw-copy ABI; no StringRecord identity
// or AsciiString ownership is inferred for this target vector.
#include <stl/_algobase.h>
struct Rva005B09D8Record { int words[5]; };
struct BfmeStringRecord002CF4C6;
namespace _STL {
template<> BfmeStringRecord002CF4C6* __copy<BfmeStringRecord002CF4C6*,BfmeStringRecord002CF4C6*,int>(BfmeStringRecord002CF4C6*,BfmeStringRecord002CF4C6*,BfmeStringRecord002CF4C6*,const random_access_iterator_tag&,int*);
}
Rva005B09D8Record* copyPointersRva005B09D8(Rva005B09D8Record*first,Rva005B09D8Record*last,Rva005B09D8Record*result,const _STL::__false_type&) {
return reinterpret_cast<Rva005B09D8Record*>(_STL::__copy(reinterpret_cast<BfmeStringRecord002CF4C6*>(first),reinterpret_cast<BfmeStringRecord002CF4C6*>(last),reinterpret_cast<BfmeStringRecord002CF4C6*>(result),_STL::random_access_iterator_tag(),(int*)0));
}
