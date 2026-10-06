// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva0054883BElement {Rva0054883BElement();Rva0054883BElement(const Rva0054883BElement&);Rva0054883BElement&operator=(const Rva0054883BElement&);~Rva0054883BElement(){}char bytes[8]; bool operator==(const Rva0054883BElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template unsigned int _STL::hashtable<_STL::pair<int const, Rva0054883BElement>, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva0054883BElement> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva0054883BElement> > >::erase(int const &);
