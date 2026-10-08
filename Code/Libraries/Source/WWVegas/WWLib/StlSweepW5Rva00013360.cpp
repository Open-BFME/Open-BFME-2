// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O2 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

// Retail's shared __lg<int> is rowed at 0x78C9C. This /O2 instantiation
// emits a different copy; leave calls bound to the verified provider.
// The shared __gcd<int> is native at 0x23307C; this /O2 copy differs too.
namespace _STL {
	template <> int __lg<int>(int);
	template <> int __gcd<int>(int, int);
}

struct Rva00013360Element { Rva00013360Element();Rva00013360Element(const Rva00013360Element&);~Rva00013360Element();Rva00013360Element&operator=(const Rva00013360Element&);char bytes[1]; bool operator<(const Rva00013360Element&)const; bool operator==(const Rva00013360Element&)const; };
template void _STL::sort(Rva00013360Element*,Rva00013360Element*);
template void _STL::make_heap(Rva00013360Element*,Rva00013360Element*);
template void _STL::push_heap(Rva00013360Element*,Rva00013360Element*);
template void _STL::pop_heap(Rva00013360Element*,Rva00013360Element*);
template void _STL::sort_heap(Rva00013360Element*,Rva00013360Element*);
template void _STL::stable_sort(Rva00013360Element*,Rva00013360Element*);
template void _STL::nth_element(Rva00013360Element*,Rva00013360Element*,Rva00013360Element*);
template void _STL::partial_sort(Rva00013360Element*,Rva00013360Element*,Rva00013360Element*);
