// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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
#include "../../../../GameEngine/Include/Common/BfmeStringRecord000B94D2.h"
struct Rva00B6CF1 { Rva00B6CF1 &operator=(const Rva00B6CF1 &); };
struct Rva000C225DElement { Rva000C225DElement();Rva000C225DElement(const Rva000C225DElement&other) { new (this) BfmeStringRecord000B94D2(*(const BfmeStringRecord000B94D2 *)&other); }~Rva000C225DElement() { ((BfmeStringRecord000B94D2 *)this)->BfmeStringRecord000B94D2::~BfmeStringRecord000B94D2(); }Rva000C225DElement&operator=(const Rva000C225DElement&other) { ((Rva00B6CF1 *)this)->operator=(*(const Rva00B6CF1 *)&other); return *this; }char bytes[8]; bool operator<(const Rva000C225DElement&)const; bool operator==(const Rva000C225DElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva000C225DElement, _STL::allocator<Rva000C225DElement> >::_M_fill_insert(Rva000C225DElement *, unsigned int, Rva000C225DElement const &);
template void _STL::vector<Rva000C225DElement, _STL::allocator<Rva000C225DElement> >::insert(Rva000C225DElement *, unsigned int, Rva000C225DElement const &);
