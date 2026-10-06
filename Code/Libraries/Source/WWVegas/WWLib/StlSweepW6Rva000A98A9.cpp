// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>
#include <memory>
#include <utility>

struct Rva000A98A9Element { unsigned char words[1];bool operator<(const Rva000A98A9Element&)const;bool operator==(const Rva000A98A9Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template unsigned int _STL::hashtable<_STL::pair<unsigned int const, Rva000A98A9Element>, unsigned int, _STL::hash<unsigned int>, _STL::_Select1st<_STL::pair<unsigned int const, Rva000A98A9Element> >, _STL::equal_to<unsigned int>, _STL::allocator<_STL::pair<unsigned int const, Rva000A98A9Element> > >::_M_bkt_num_key(unsigned int const &, unsigned int) const;
