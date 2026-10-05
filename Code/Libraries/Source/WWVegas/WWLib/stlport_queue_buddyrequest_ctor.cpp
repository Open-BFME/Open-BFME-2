// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0?$queue@VBuddyRequest@@V?$deque@VBuddyRequest@@V?$allocator@VBuddyRequest@@@_STL@@@_STL@@@_STL@@QAE@XZ 0x00551A06 21B retail queue<BuddyRequest> default ctor; caller GameSpyBuddyMessageQueue ctor at 0x00551ACE; callee _Deque_base ctor rowed in stlport_pod_large_bodies
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <queue>
class BuddyRequest { char m_bfmeBody[0x2B8]; };
template _STL::queue<BuddyRequest>::queue();
