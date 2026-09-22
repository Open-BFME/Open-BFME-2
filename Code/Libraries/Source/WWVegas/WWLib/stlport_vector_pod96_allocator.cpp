// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// BFME2's 96-byte Pod vector allocator at RVA 0x0046265E (28B: imul-0x60
// size computation plus the shared byte-allocator call). The home TU
// (stlport_pod_vector_bodies.cpp) compiles its allocators under /O1, which
// strength-reduces n*96 to lea+shl; retail keeps the imul, which this
// toolchain emits only under /G7 P4 tuning (probe-proven on the B9534 and
// Pod144 allocator precedents). Same-TU visibility and flag-split rules
// require a shard: flipping the home TU's flags would break its landed /O1
// bodies. Size-carrying body, so the BfmePod96 placeholder name is honest
// per the POD-PLACEHOLDER LAW (element construction never passes through
// here). The BfmePod96 layout mirrors the home TU declaration.
struct BfmePod96 { int a[24]; };
#include <memory>
template class _STL::allocator<BfmePod96>;
