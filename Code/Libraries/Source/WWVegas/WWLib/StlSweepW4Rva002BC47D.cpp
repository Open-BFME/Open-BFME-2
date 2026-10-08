// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva002BC47DElement { Rva002BC47DElement();Rva002BC47DElement(const Rva002BC47DElement&);~Rva002BC47DElement();Rva002BC47DElement&operator=(const Rva002BC47DElement&);char bytes[52]; bool operator<(const Rva002BC47DElement&)const; bool operator==(const Rva002BC47DElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva002BC47DElement, _STL::allocator<Rva002BC47DElement> >::_M_fill_insert(Rva002BC47DElement *, unsigned int, Rva002BC47DElement const &);

struct Rva002BBB96Element;
namespace _STL {
template<> Rva002BBB96Element* vector<Rva002BBB96Element>::erase(Rva002BBB96Element*,Rva002BBB96Element*);
}

// Native 0x002BC8C9..0x002BC935, ret56: resize with a 52-byte
// by-value element. Target accesses establish the vector's three pointers,
// element stride, range-erase 0x002BBB96, fill-insert 0x002BC47D and
// parameter destruction 0x002B707E. The separately rowed erase view has
// the same pointer ABI and stride; application and element names are unknown.
// STLport4.5.3 resize supplies the shrink/grow semantics, also verified in
// the recovered 76-byte-element sibling Rva00150C74Vector::resize.
class Rva002BC8C9Vector {
 Rva002BC47DElement *start,*finish,*end;
public:
 void resize(unsigned n,Rva002BC47DElement value);
};
void Rva002BC8C9Vector::resize(unsigned n,Rva002BC47DElement value) {
 if(n<(unsigned)(finish-start))
  reinterpret_cast<_STL::vector<Rva002BBB96Element>*>(this)->erase(reinterpret_cast<Rva002BBB96Element*>(start+n),reinterpret_cast<Rva002BBB96Element*>(finish));
 else {
  unsigned count=n-(finish-start);
  reinterpret_cast<_STL::vector<Rva002BC47DElement>*>(this)->_M_fill_insert(finish,count,value);
 }
}
