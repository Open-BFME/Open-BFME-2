// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// BFME2's 72-byte Pod vector allocator at RVA 0x000B4106 (28B: imul-0x48
// size computation plus the shared byte-allocator call). The home TU
// (stlport_pod_vector_bodies.cpp) compiles its allocators under /O1, which
// strength-reduces n*72 to lea+shl; retail keeps the imul, which this
// toolchain emits only under /G7 P4 tuning (probe-proven on the B9534 and
// Pod144 allocator precedents). Same-TU visibility and flag-split rules
// require a shard: flipping the home TU's flags would break its landed /O1
// bodies. Size-carrying body, so the BfmePod72 placeholder name is honest
// per the POD-PLACEHOLDER LAW (element construction never passes through
// here). No BfmePod72 declaration exists in-tree; the 18-int model matches
// the retail imul stride.
struct BfmePod72 { int a[18]; };
#include <memory>
template class _STL::allocator<BfmePod72>;
