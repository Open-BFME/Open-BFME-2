// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include "../../../../../vendor/stlport/stl/_algobase.h"
#include "../../../../../vendor/stlport/stl/_uninitialized.h"
#include <vector>
struct TargetRef00217D4C { virtual void*destroy(unsigned); int references; };
struct Rva005F8F96 { ~Rva005F8F96(); TargetRef00217D4C *m_00; int m_04; };
struct Rva00153729 {
 Rva00153729(); Rva00153729(const Rva00153729&); Rva00153729&operator=(const Rva00153729&);
 // ?Rva00153729::~Rva00153729 present-unmatched
 ~Rva00153729() {}
 int key;
 _STL::vector<Rva005F8F96> fields[6];
};
class Rva00153E6FVector { Rva00153729*start,*finish,*end; public: void resize(unsigned,Rva00153729); void resize(unsigned); };
namespace _STL {
template<> Rva00153729*vector<Rva00153729>::erase(Rva00153729*,Rva00153729*);

}
void Rva00153E6FVector::resize(unsigned n) { resize(n,Rva00153729()); }
void Rva00153E6FVector::resize(unsigned n,Rva00153729 value) {
 _STL::vector<Rva00153729>*v=reinterpret_cast<_STL::vector<Rva00153729>*>(this);
 if(n<v->size()) v->erase(v->begin()+n,v->end());
 else v->insert(v->end(),n-v->size(),value);
}

template void _STL::vector<Rva00153729>::_M_fill_insert(Rva00153729*,unsigned,const Rva00153729&);

// Reference: pristine STLport4.5.3 fill_insert. Native 268B ret0C extent,
// 76B entry stride and constructor/helper calls establish this instantiation.
// Pristine algobase/uninitialized wrappers retain their native out-of-line
// reference-tag ABI; the bfmealloc allocator shim is still used.

// Reuse the kept providers proven by the native fill_insert REL32s. All
// pointer/reference words and the unused iterator metadata have identical ABI.
#pragma comment(linker, "/alternatename:??$__copy_backward_ptrs@PAURva00153729@@PAU1@@_STL@@YAPAURva00153729@@PAU1@00ABU__false_type@0@@Z=?Rva00153A5ERangeForward@@YAPAURva00153A5EOutput@@PAURva00153A5EInput@@0PAU1@ABURva00153A5EIteratorTag@@@Z")
#pragma comment(linker, "/alternatename:??$fill@PAURva00153729@@U1@@_STL@@YAXPAURva00153729@@0ABU1@@Z=?Rva00153A7BFill@@YAXPAVRva001539BC@@0ABV1@@Z")
