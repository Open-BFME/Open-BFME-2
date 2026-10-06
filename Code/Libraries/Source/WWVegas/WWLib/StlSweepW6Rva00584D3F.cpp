// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>
#include <utility>

struct Rva00584D3FElement { unsigned char words[1];bool operator<(const Rva00584D3FElement&)const;bool operator==(const Rva00584D3FElement&)const; };
template void _STL::sort(Rva00584D3FElement*,Rva00584D3FElement*);
template void _STL::stable_sort(Rva00584D3FElement*,Rva00584D3FElement*);
template void _STL::make_heap(Rva00584D3FElement*,Rva00584D3FElement*);
template void _STL::push_heap(Rva00584D3FElement*,Rva00584D3FElement*);
template void _STL::pop_heap(Rva00584D3FElement*,Rva00584D3FElement*);
template void _STL::sort_heap(Rva00584D3FElement*,Rva00584D3FElement*);
template void _STL::partial_sort(Rva00584D3FElement*,Rva00584D3FElement*,Rva00584D3FElement*);
template void _STL::nth_element(Rva00584D3FElement*,Rva00584D3FElement*,Rva00584D3FElement*);
template void _STL::inplace_merge(Rva00584D3FElement*,Rva00584D3FElement*,Rva00584D3FElement*);
