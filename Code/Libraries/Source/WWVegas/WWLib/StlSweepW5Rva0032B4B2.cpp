// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>

struct Rva0032B4B2Element {Rva0032B4B2Element();Rva0032B4B2Element(const Rva0032B4B2Element&);Rva0032B4B2Element&operator=(const Rva0032B4B2Element&);virtual void slot0();virtual void slot1();virtual ~Rva0032B4B2Element();char bytes[4]; bool operator==(const Rva0032B4B2Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::_Rb_tree<int, _STL::pair<int const, Rva0032B4B2Element>, _STL::_Select1st<_STL::pair<int const, Rva0032B4B2Element> >, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva0032B4B2Element> > >::erase(_STL::_Rb_tree_iterator<_STL::pair<int const, Rva0032B4B2Element>, _STL::_Nonconst_traits<_STL::pair<int const, Rva0032B4B2Element> > >);
