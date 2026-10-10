// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0?$queue@VBuddyResponse@@V?$deque@VBuddyResponse@@V?$allocator@VBuddyResponse@@@_STL@@@_STL@@@_STL@@QAE@XZ @0x00551A1B 21B retail queue<BuddyResponse> default ctor; caller GameSpyBuddyMessageQueue ctor at 0x00551ADA; callee _Deque_base ctor rowed for same-size BfmeOpaqueOwnedRecord2148 0x00550C06 via ICF. Evidence: pinned name plus sibling queue<BuddyRequest> 0x00551A06 21B same shape plus BuddyResponse 0x864 body from BuddyResponseDequePushBackAux.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <queue>
class BuddyResponse { char m_bfmeBody[0x864]; };
template _STL::queue<BuddyResponse>::queue();
