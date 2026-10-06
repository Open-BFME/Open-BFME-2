// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>
#include <string>
#include <utility>

struct Rva00056BFEElement { char bytes[1]; Rva00056BFEElement();Rva00056BFEElement(const Rva00056BFEElement&);~Rva00056BFEElement();Rva00056BFEElement& operator=(const Rva00056BFEElement&); bool operator<(const Rva00056BFEElement&)const; bool operator==(const Rva00056BFEElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::hashtable<_STL::pair<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > const, Rva00056BFEElement>, _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >, _STL::hash<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > >, _STL::_Select1st<_STL::pair<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > const, Rva00056BFEElement> >, _STL::equal_to<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > >, _STL::allocator<_STL::pair<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > const, Rva00056BFEElement> > >::resize(unsigned int);
