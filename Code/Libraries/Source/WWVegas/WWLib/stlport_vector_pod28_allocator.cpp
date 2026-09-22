// cl: /O2 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// BFME2's 28-byte Pod vector allocator at RVA 0x00689290 (28B: imul-0x1C
// size computation plus the shared byte-allocator call, add-esp cleanup).
// Unlike the pop/pop imul family (Pod40/72/144, /G7 shards), retail cleans
// the two pushed dwords with add esp,8 — the /O2 call-epilogue form — while
// keeping the imul. Probe whether /O2 alone reproduces both.
struct BfmePod28 { int a[7]; };
#include <memory>
template class _STL::allocator<BfmePod28>;
