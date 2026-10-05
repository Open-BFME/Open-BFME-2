// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
struct Rva00150D42Entry { Rva00150D42Entry(); Rva00150D42Entry(const Rva00150D42Entry&); ~Rva00150D42Entry(); unsigned int vptr; int index; char tail[68]; };
class Rva00150C74Vector { Rva00150D42Entry *start,*finish,*end; public: void resize(unsigned, Rva00150D42Entry); };
typedef _STL::vector<Rva00150D42Entry> Rva00150D42Vector;
namespace _STL { template<> void vector<Rva00150D42Entry>::resize(unsigned int); }
class Rva00150D42 { unsigned int vptr; Rva00150D42Vector values; public: void grow(int count); };
void Rva00150D42::grow(int count) {
 if ((unsigned)count >= values.size()) {
  int old=values.size();
  values.resize(count);
  for (;old<count;++old) values[old].index=old;
 }
}

// Target: Ghidra extent and native ret4 boundary; vector member +4;
// signed growth loop writes each new element index at +4. Storage stride
// 76 is established by native pointer arithmetic. Application identity unknown.
// STLport4.5.3 supplies size/operator[]; resize declaration targets the
// unique native wrapper 0x00150C74 decoded from this body.

// 0x00150C74: native ret4 wrapper allocates a 76B argument and invokes
// its constructor at 0x0014DB9F before forwarding to by-value resize.
namespace _STL { template<> void vector<Rva00150D42Entry>::resize(unsigned n) {
 reinterpret_cast<Rva00150C74Vector*>(this)->resize(n,Rva00150D42Entry());
} }
namespace _STL {
template<> Rva00150D42Entry* vector<Rva00150D42Entry>::erase(Rva00150D42Entry*,Rva00150D42Entry*);
template<> void vector<Rva00150D42Entry>::_M_fill_insert(Rva00150D42Entry*,unsigned,const Rva00150D42Entry&);
}
void Rva00150C74Vector::resize(unsigned n,Rva00150D42Entry value) {
 _STL::vector<Rva00150D42Entry>*v=reinterpret_cast<_STL::vector<Rva00150D42Entry>*>(this);
 if (n<v->size()) v->erase(v->begin()+n,v->end());
 else v->insert(v->end(),n-v->size(),value);
}
