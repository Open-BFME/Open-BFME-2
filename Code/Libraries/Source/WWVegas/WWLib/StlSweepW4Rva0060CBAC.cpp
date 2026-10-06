// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>
#include <string>
#include <utility>

struct Rva0060CBACElement { char bytes[1]; Rva0060CBACElement();Rva0060CBACElement(const Rva0060CBACElement&);~Rva0060CBACElement();Rva0060CBACElement& operator=(const Rva0060CBACElement&); bool operator<(const Rva0060CBACElement&)const; bool operator==(const Rva0060CBACElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::hashtable<_STL::pair<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > const, Rva0060CBACElement>, _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >, _STL::hash<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > >, _STL::_Select1st<_STL::pair<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > const, Rva0060CBACElement> >, _STL::equal_to<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > >, _STL::allocator<_STL::pair<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > const, Rva0060CBACElement> > >::resize(unsigned int);
