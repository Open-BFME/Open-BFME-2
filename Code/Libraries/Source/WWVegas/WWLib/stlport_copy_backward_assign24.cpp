// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??$copy_backward@PAUBfmeAssignRecord24@@PAU1@@_STL@@YAPAUBfmeAssignRecord24@@PAU1@00@Z RVA 0x004286FB size 27
// Evidence: caller 0x0042875A in FUN_0082872d; callee rowed __copy_backward_ptrs at 0x00428421; shape matches E12 precedent 0x0051C94D.
// Uses STOCK vendor headers (no bfmealloc shim): the shim inlines to a 29B __copy_backward call; stock keeps the 27B ptrs call.
#include <vector>
#include "ascii_string.h"
struct BfmeAssignRecord24 { AsciiString s; int a[5]; };
template BfmeAssignRecord24 *_STL::copy_backward<BfmeAssignRecord24 *, BfmeAssignRecord24 *>(BfmeAssignRecord24 *, BfmeAssignRecord24 *, BfmeAssignRecord24 *);
