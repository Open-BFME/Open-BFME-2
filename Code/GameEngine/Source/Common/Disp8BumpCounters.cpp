// Disp8 increment-and-fetch counters: eleven-byte __thiscall members with
// one shape:
//
//     lea eax,[ecx+<DISP>] / inc dword [eax] / mov eax,[eax] / ret
//
// An int field at a fixed displacement from `this` is incremented and the
// new value returned. The reference-local source keeps the field address in
// eax across the increment and the reload. Every displacement here fits
// disp8 (every offset is below 0x80). Identity is not recovered: every name
// is derived from its address.
// cl: /MD /EHsc /DNDEBUG
#include "../../Include/Common/BfmeAccessorMacros.h"

BFME_DISP8_BUMP_COUNTER(Rva002B315BBumpCounter, 0xA0)
BFME_DISP8_BUMP_COUNTER(Rva002B3166BumpCounter, 0xA4)
BFME_DISP8_BUMP_COUNTER(Rva002B3171BumpCounter, 0xA8)
BFME_DISP8_BUMP_COUNTER(Rva002B317CBumpCounter, 0xAC)
