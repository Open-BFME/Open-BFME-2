// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
struct TargetRef00217D4C { virtual void*destroy(unsigned); int references; };
struct Rva005F8F96 { ~Rva005F8F96(); TargetRef00217D4C *m_00; int m_04; };
struct Rva00153729 {
 Rva00153729(); Rva00153729(const Rva00153729&);
 // ?Rva00153729::~Rva00153729 present-unmatched
 ~Rva00153729() {}
 int key;
 _STL::vector<Rva005F8F96> fields[6];
};
class Rva00153E6FVector { Rva00153729*start,*finish,*end; public: void resize(unsigned,Rva00153729); void resize(unsigned); };
namespace _STL {
template<> Rva00153729*vector<Rva00153729>::erase(Rva00153729*,Rva00153729*);
template<> void vector<Rva00153729>::_M_fill_insert(Rva00153729*,unsigned,const Rva00153729&);
}
void Rva00153E6FVector::resize(unsigned n) { resize(n,Rva00153729()); }
void Rva00153E6FVector::resize(unsigned n,Rva00153729 value) {
 _STL::vector<Rva00153729>*v=reinterpret_cast<_STL::vector<Rva00153729>*>(this);
 if(n<v->size()) v->erase(v->begin()+n,v->end());
 else v->insert(v->end(),n-v->size(),value);
}

// Reference: STLport4.5.3 resize semantics. Target 00153E6F has ret50,
// 76B pointer stride and inline teardown of six 12B vector members at +4.
// The entry layout follows the verified ctor/dtor in Rva00153729Dtor.cpp;
// no application class identity is inferred. 00153EE5 default wrapper
// constructs its by-value argument directly through the existing ctor.
