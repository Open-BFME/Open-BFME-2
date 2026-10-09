// cl: /O2 /G6 /MD
// Clean-room: reverse/vp6_cleanroom/specs/001d7620.md.
// Native1D7620..1D7623 is EMMS followed by RET; the reviewed spec
// identifies the cdecl state-clear routine installed for MMX/SSE2 paths.
// The compiler intrinsic implements that hardware operation directly.
// No external decoder source was consulted.
#include <mmintrin.h>

extern "C" void __cdecl ClearMmx()
{
    _mm_empty();
}
