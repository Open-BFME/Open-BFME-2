// Disp32 dword inc/dec: seven-byte __thiscall members with one shape:
//
//     inc dword ptr [ecx+<DISP32>] / ret     (FF 81 XX XX XX XX C3)
//     dec dword ptr [ecx+<DISP32>] / ret     (FF 89 XX XX XX XX C3)
//
// A dword counter at a fixed displacement from `this` is incremented (or
// decremented) in place. The displacements here do not fit in a signed
// byte, so MSVC 7.1 emits the disp32 form plus `ret`, for seven bytes
// total. This is the large-offset sibling of the disp8
// Disp8DwordFieldIncDec family (four bytes per body); the encoding itself
// is why the two families are kept in separate translation units. The
// accessed member is spelled as an `int` right after the lead array; the
// bytes cannot distinguish `int` from `unsigned int` or any other
// four-byte-wide incremented slot. Members before the accessed one are
// spelled as a lead array because their types are not witnessed here, only
// their total size.
// Identity is not recovered: every name is derived from its address (the
// disp8 dword-counter family pioneered the same opaque-holder pattern).
// No // cl: line (defaults match the frameless seven-byte shape).
#include "../../Include/Common/BfmeAccessorMacros.h"


BFME_DISP32_DWORD_INC(Rva002AA0BFDwordCounter, 0x6FC)
BFME_DISP32_DWORD_DEC(Rva002AA0C6DwordCounter, 0x6FC)
BFME_DISP32_DWORD_INC(Rva00050CE1DwordCounter, 0x80)
BFME_DISP32_DWORD_DEC(Rva00050CE8DwordCounter, 0x80)
BFME_DISP32_DWORD_INC(Rva000514DDDwordCounter, 0x684)
BFME_DISP32_DWORD_INC(Rva000514E4DwordCounter, 0x688)
BFME_DISP32_DWORD_INC(Rva0029A339DwordCounter, 0x568)
BFME_DISP32_DWORD_DEC(Rva0029A340DwordCounter, 0x568)
BFME_DISP32_DWORD_INC(Rva0008528DDwordCounter, 0xC4)
BFME_DISP32_DWORD_DEC(Rva00042212DwordCounter, 0x1B4)
