// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva005205DAElement { Rva005205DAElement();Rva005205DAElement(const Rva005205DAElement&);~Rva005205DAElement();Rva005205DAElement&operator=(const Rva005205DAElement&);char bytes[80]; bool operator<(const Rva005205DAElement&)const; bool operator==(const Rva005205DAElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva005205DAElement, _STL::allocator<Rva005205DAElement> >::_M_fill_insert(Rva005205DAElement *, unsigned int, Rva005205DAElement const &);

// Native520703..52076F takes the80B time-line record by value (RET84).
// It shrinks through the existing80B range erase or grows via the rowed
// fill-insert here, then destroys its value argument. STLport4.5.3 supplies
// the resize semantics; all call targets and stride are target evidence.
struct Rva00520211Element;
namespace _STL {
template<> Rva00520211Element* vector<Rva00520211Element>::erase(Rva00520211Element*,Rva00520211Element*);
}
class Rva00520703Vector {
 Rva005205DAElement *start,*finish,*end;
public: void resize(unsigned count,Rva005205DAElement value);
};
void Rva00520703Vector::resize(unsigned count,Rva005205DAElement value) {
 if(count<(unsigned)(finish-start))
  reinterpret_cast<_STL::vector<Rva00520211Element>*>(this)->erase(reinterpret_cast<Rva00520211Element*>(start+count),reinterpret_cast<Rva00520211Element*>(finish));
 else {
  unsigned added=count-(finish-start);
  reinterpret_cast<_STL::vector<Rva005205DAElement>*>(this)->_M_fill_insert(finish,added,value);
 }
}
