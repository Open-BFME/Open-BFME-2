// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <memory>

struct Rva0026F4F4Element { unsigned words[1];bool operator<(const Rva0026F4F4Element&)const;bool operator==(const Rva0026F4F4Element&)const; };
namespace _STL {template<>struct __type_traits<Rva0026F4F4Element> : __type_traits_aux<1> {};}

// Instantiate the recovered operation and its required template dependencies.
template _STL::vector<Rva0026F4F4Element, _STL::allocator<Rva0026F4F4Element> > & _STL::vector<Rva0026F4F4Element, _STL::allocator<Rva0026F4F4Element> >::operator=(_STL::vector<Rva0026F4F4Element, _STL::allocator<Rva0026F4F4Element> > const &);
