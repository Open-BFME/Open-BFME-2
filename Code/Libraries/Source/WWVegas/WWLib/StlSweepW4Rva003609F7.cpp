// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva003609F7Element { char bytes[1]; bool operator<(const Rva003609F7Element&)const; bool operator==(const Rva003609F7Element&)const; };
namespace _STL {template<> struct hash<Rva003609F7Element> { unsigned operator()(const Rva003609F7Element&) const; };}

// Instantiate the recovered operation and its required template dependencies.
template _STL::pair<int const, Rva003609F7Element> & _STL::hashtable<_STL::pair<int const, Rva003609F7Element>, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva003609F7Element> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva003609F7Element> > >::_M_insert(_STL::pair<int const, Rva003609F7Element> const &);
