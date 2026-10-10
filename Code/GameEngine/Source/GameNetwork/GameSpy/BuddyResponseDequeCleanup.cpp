// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Named Buddy queue getResponse/addResponse and ctor establish this deque.
// Target5508A5 advances0x864; target551910 copies0x219 words and allocates
// 0x864. BuddyResponse is trivially destroyed in its ZH definition; the same
// opaque byte storage already appears in BuddyResponseDequePushBackAux.cpp.
// Typed cleanup emissions are full-body twins of StlportDeque2148Cleanup.cpp;
// allocator/free calls are kept on their existing canonical providers.
#include <deque>
class BuddyResponse { char m_bfmeBody[0x864]; };
template _STL::deque<BuddyResponse>::~deque();
