// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Retail allocate-and-copy [8A1D0,8A1FD),45B RET12 allocates through
// receiver+8 then copies a range with the full38B helper at8A185.
// Its loop stride24 and full35B copy ctor89822 establish an opaque24B
// record view; application type and individual field identities are unknown.
// The full ctor reaches only primitive31B set87A74; throw() follows that
// target call graph. The full18B guarded constructor is bound below.
// STLport4.5.3 provides the vector algorithm and three-pointer storage view;
// these reference semantics are independently checked against retail bytes.
// G7 reproduces the target allocator's multiply-by24 compiler shape.
#include <stl/_algobase.h>
namespace _STL {static inline const unsigned int&max(const unsigned int&a,const unsigned int&b){return a<b?b:a;}}
#include <vector>
struct Rva0008B5B5Record { unsigned int unknown[6]; Rva0008B5B5Record(const Rva0008B5B5Record&) throw(); };
namespace _STL {template<> __declspec(nothrow) void _Construct<Rva0008B5B5Record,Rva0008B5B5Record>(Rva0008B5B5Record*,const Rva0008B5B5Record&);}
template Rva0008B5B5Record* _STL::vector<Rva0008B5B5Record>::_M_allocate_and_copy<Rva0008B5B5Record*>(unsigned int,Rva0008B5B5Record*,Rva0008B5B5Record*);
#pragma comment(linker, "/alternatename:??$_Construct@URva0008B5B5Record@@U1@@_STL@@YAXPAURva0008B5B5Record@@ABU1@@Z=?Rva0008A173Copy@@YAXPAVRva00089822@@ABV1@@Z")

// Retail reserve [8B5B5,8B630),125B RET4 preserves size at stride24;
// growth uses the full45B helper above then frees old storage at30830.
template void _STL::vector<Rva0008B5B5Record>::reserve(unsigned int);
