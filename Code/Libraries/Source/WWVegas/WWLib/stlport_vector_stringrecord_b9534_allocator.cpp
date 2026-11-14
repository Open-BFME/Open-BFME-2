// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfmealloc
// stlport
// BFME2's shared 24-byte vector allocator at RVA 0x395944.
// The home TU (stlport_vector_stringrecord_b9534_allocate_copy.cpp) compiles
// this allocator with lea+shl strength reduction under /O1; retail keeps the
// imul, which this toolchain emits only under /G7 P4 tuning (probe-proven).
// Same-TU visibility and flag-split rules require a shard: flipping the home
// TU's flags would break its five landed /O1 bodies. The allocator is an
// imul-0x18 size fold shared image-wide (23 raw callers, including the rowed
// B9534 allocate_and_copy at 0xBBCEF and the Pod24 pin); it is rowed under the
// B9534 spelling by caller evidence, the Pod24 pin standing as fold candidate.
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "BfmeStringRecord000B9534.h"
#include <memory>
template class _STL::allocator<BfmeStringRecord000B9534>;
