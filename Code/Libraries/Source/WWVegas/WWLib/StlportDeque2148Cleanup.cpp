// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport4.5.3 view of the target iterator stride; original element name and
// fields are unknown. Verified operations cover iteration, growth and cleanup.
#include <deque>
struct BfmeOpaque2148 { unsigned char bytes[0x864]; };
template class _STL::deque<BfmeOpaque2148, _STL::allocator<BfmeOpaque2148> >;
