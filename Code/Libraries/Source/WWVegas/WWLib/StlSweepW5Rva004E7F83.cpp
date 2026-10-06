// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>
#include <memory>

struct Rva004E7F83Element { unsigned words[1];Rva004E7F83Element& operator=(const Rva004E7F83Element&b){words[0]=b.words[0];return *this;}bool operator<(const Rva004E7F83Element&)const;bool operator==(const Rva004E7F83Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva004E7F83Element & _STL::map<int, Rva004E7F83Element, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva004E7F83Element> > >::operator[](int const &);
