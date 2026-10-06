// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva00053EE8Element {Rva00053EE8Element();Rva00053EE8Element(const Rva00053EE8Element&);Rva00053EE8Element&operator=(const Rva00053EE8Element&);~Rva00053EE8Element(){}char bytes[8]; bool operator==(const Rva00053EE8Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::hashtable<_STL::pair<int const, Rva00053EE8Element>, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva00053EE8Element> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva00053EE8Element> > >::_M_erase_bucket(unsigned int, _STL::_Hashtable_node<_STL::pair<int const, Rva00053EE8Element> > *);
