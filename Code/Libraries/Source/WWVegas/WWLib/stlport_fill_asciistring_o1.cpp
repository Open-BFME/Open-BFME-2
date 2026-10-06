// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$fill@PAVAsciiString@@V1@@_STL@@YAXPAVAsciiString@@0ABV1@@Z 0x000B4300 29B evidence: stride-4 loop calling rowed StringBase narrow copy set 0x000366F0; callers at 0x000C0719/0x000C075D in 0x000C0697; neighbour fill 0x000B431D same TU family
#include <vector>
#include "ascii_string.h"

template void _STL::fill<AsciiString *, AsciiString>(AsciiString *, AsciiString *, const AsciiString &);
