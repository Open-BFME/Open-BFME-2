// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>
#include <string>
#include <utility>

struct Rva0029FBC9Element { char bytes[1]; Rva0029FBC9Element();Rva0029FBC9Element(const Rva0029FBC9Element&);~Rva0029FBC9Element();Rva0029FBC9Element& operator=(const Rva0029FBC9Element&); };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree_iterator<_STL::pair<void *const, Rva0029FBC9Element>, _STL::_Nonconst_traits<_STL::pair<void *const, Rva0029FBC9Element> > > _STL::_Rb_tree<void *, _STL::pair<void *const, Rva0029FBC9Element>, _STL::_Select1st<_STL::pair<void *const, Rva0029FBC9Element> >, _STL::less<void *>, _STL::allocator<_STL::pair<void *const, Rva0029FBC9Element> > >::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, _STL::pair<void *const, Rva0029FBC9Element> const &, _STL::_Rb_tree_node_base *);
