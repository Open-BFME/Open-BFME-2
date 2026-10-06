// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva00148B27Element {Rva00148B27Element();Rva00148B27Element(const Rva00148B27Element&);Rva00148B27Element&operator=(const Rva00148B27Element&);~Rva00148B27Element(){}char bytes[8]; bool operator==(const Rva00148B27Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Ht_iterator<_STL::pair<int const, Rva00148B27Element>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00148B27Element> >, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva00148B27Element> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva00148B27Element> > > _STL::hashtable<_STL::pair<int const, Rva00148B27Element>, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva00148B27Element> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva00148B27Element> > >::find<int>(int const &);
