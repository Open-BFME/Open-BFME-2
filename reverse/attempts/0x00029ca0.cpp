// ?_M_fill_insert@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEXPAPAXIABQAX@Z
// partial score=0.07809523809523809 date=2026-09-07
// cl: /Od /Ob1 /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Complete retail extent: RVA 0x29CA0..0x29EAD = 525 bytes, then 3 CC.
// The 522-byte attempt has a 3-byte sub esp,0x7c instead of retail's
// 6-byte sub esp,0x80. Prior later log's 522-byte retail size was incorrect.
// All instructions align after this prologue-length difference; an extra
// retail stack slot appears between the first copy chain and first fill loop.
// MSVC /FAs names the first changed scratch as the fill iterator ($T6756 in
// this build), after the backward-copy call. Earlier temporaries up through
// -36 are unchanged; later locals and this move downward by four in retail.
// Making __copy_trivial or __copy_trivial_backward visible noinline is inert
// under /Od. Exact primary 4.5.3 _vector.c equals vendor after CRLF conversion.
// Source remains reconstructible through the existing opt-in allocator shim;
// no padding local, assembly, invented pin or altered shared header is used.
#include <vector>

template class _STL::vector<void*,_STL::allocator<void*> >;
