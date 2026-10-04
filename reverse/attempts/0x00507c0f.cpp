// ?_M_clear@?$vector@UBfmeStringRecord00426A5B@@V?$allocator@UBfmeStringRecord00426A5B@@@_STL@@@_STL@@IAEXXZ
// partial score=1.0 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ?_M_clear@?$vector@UBfmeStringRecord00426A5B@@V?$allocator@UBfmeStringRecord00426A5B@@@_STL@@@_STL@@IAEXXZ @0x00507C0F 30B
// retail vector<BfmeStringRecord00426A5B> _M_clear via rowed __destroy_aux 0x00507BB7 plus _free 0x00030830; caller 0x0050864C unblocks 0x005085B6
// prev 0x00507BB7 shares TU flags; element layout from Rva0042700FParse.cpp (AsciiString plus 3 flag bytes, stride 8)
#include <vector>
#include "ascii_string.h"
struct BfmeStringRecord00426A5B
{
	AsciiString text;
	unsigned char flag0;
	unsigned char flag1;
	unsigned char flag2;
	BfmeStringRecord00426A5B();
};
// ?_M_clear@?$vector@UBfmeStringRecord00426A5B@@V?$allocator@UBfmeStringRecord00426A5B@@@_STL@@@_STL@@IAEXXZ present-unmatched
template void _STL::vector<BfmeStringRecord00426A5B>::_M_clear();
