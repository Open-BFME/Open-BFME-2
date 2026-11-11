// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

// Retail's operation calls these rows for its element, spelled under separate placeholder
// names. The local element forwards to them, so the rows' own bodies run.
class Rva0051F87B { public: Rva0051F87B(const Rva0051F87B &); Rva0051F87B &operator=(const Rva0051F87B &); };
#include "Rva00520211Element.h"
struct Rva005205DAElement { Rva005205DAElement();Rva005205DAElement(const Rva005205DAElement&other) { new (this) Rva0051F87B(*(const Rva0051F87B *)&other); }~Rva005205DAElement() { ((Rva00520211Element *)this)->Rva00520211Element::~Rva00520211Element(); }Rva005205DAElement&operator=(const Rva005205DAElement&other) { ((Rva0051F87B *)this)->operator=(*(const Rva0051F87B *)&other); return *this; }char bytes[80]; bool operator<(const Rva005205DAElement&)const; bool operator==(const Rva005205DAElement&)const; };

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
class Rva00520703Vector
{
public:
	void resize(unsigned count,Rva005205DAElement value);
	void resize(unsigned count);
private:
	Rva005205DAElement *start; // +0x00
	Rva005205DAElement *finish; // +0x04
	Rva005205DAElement *end; // +0x08
};
void Rva00520703Vector::resize(unsigned count,Rva005205DAElement value) {
 if(count<(unsigned)(finish-start))
  reinterpret_cast<_STL::vector<Rva00520211Element>*>(this)->erase(reinterpret_cast<Rva00520211Element*>(start+count),reinterpret_cast<Rva00520211Element*>(finish));
 else {
  unsigned added=count-(finish-start);
  reinterpret_cast<_STL::vector<Rva005205DAElement>*>(this)->_M_fill_insert(finish,added,value);
 }
}
