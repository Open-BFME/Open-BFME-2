// ??1?$vector@UBfmeStringRecord00426A5B@@V?$allocator@UBfmeStringRecord00426A5B@@@_STL@@@_STL@@QAE@XZ
// partial score=0.93 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ??1?$vector@UBfmeStringRecord00426A5B@@V?$allocator@UBfmeStringRecord00426A5B@@@_STL@@@_STL@@QAE@XZ @0x00507BD0 63B
// retail vector<BfmeStringRecord00426A5B> dtor via rowed __destroy_aux 0x00507BB7 plus _free 0x00030830 with EH prolog handler 0x007941D3
// caller 0x005086B1 unblocks 0x00508684; prev 0x00507BB7 shares TU flags; next 0x00507C2D Made ctor
#include <vector>
#include "ascii_string.h"
struct BfmeStringRecord00426A5B
{
	AsciiString text;
	unsigned char flag0;
	unsigned char flag1;
	unsigned char flag2;
};
// ??1?$vector@UBfmeStringRecord00426A5B@@V?$allocator@UBfmeStringRecord00426A5B@@@_STL@@@_STL@@QAE@XZ present-unmatched
template _STL::vector<BfmeStringRecord00426A5B>::~vector();
