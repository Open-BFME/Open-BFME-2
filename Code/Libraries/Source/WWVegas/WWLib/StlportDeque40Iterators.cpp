// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport4.5.3 view of the target iterator stride; original element name and
// fields are unknown. Only the verified iterator or cleanup operations are claimed.
#include <deque>
struct BfmeOpaque40 { unsigned char bytes[40]; };
template class _STL::deque<BfmeOpaque40, _STL::allocator<BfmeOpaque40> >;
