// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// Target node allocation at 0x002E0273 is 80 bytes: link + 4-byte key + 72-byte value.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva002E037FElement {Rva002E037FElement();Rva002E037FElement(const Rva002E037FElement&);Rva002E037FElement&operator=(const Rva002E037FElement&);~Rva002E037FElement(){}char bytes[72]; bool operator==(const Rva002E037FElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template _STL::pair<_STL::_Ht_iterator<_STL::pair<int const, Rva002E037FElement>, _STL::_Nonconst_traits<_STL::pair<int const, Rva002E037FElement> >, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva002E037FElement> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva002E037FElement> > >, bool> _STL::hashtable<_STL::pair<int const, Rva002E037FElement>, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva002E037FElement> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva002E037FElement> > >::insert_unique_noresize(_STL::pair<int const, Rva002E037FElement> const &);
