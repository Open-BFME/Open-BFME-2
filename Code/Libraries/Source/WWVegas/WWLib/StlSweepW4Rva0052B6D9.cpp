// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva0052B6D9Element { char bytes[1]; bool operator<(const Rva0052B6D9Element&)const; bool operator==(const Rva0052B6D9Element&)const; };
namespace _STL {template<> struct hash<Rva0052B6D9Element> { unsigned operator()(const Rva0052B6D9Element&) const; };}

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Hashtable_node<_STL::pair<int const, Rva0052B6D9Element> > * _STL::hashtable<_STL::pair<int const, Rva0052B6D9Element>, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva0052B6D9Element> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva0052B6D9Element> > >::_M_new_node(_STL::pair<int const, Rva0052B6D9Element> const &);
