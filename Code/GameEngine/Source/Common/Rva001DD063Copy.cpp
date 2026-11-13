// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva001DD063@@QAE@ABU0@@Z @0x001DD063 61B
// Copy ctor of 32-byte POD record. Evidence: retail mov sequence 1 dword then
// 2 bytes then 6 dwords with ret 4; called by 0x001DD1B3 and 0x001DD2BF as
// inner copy at +4; same shape as sibling Rva001DD0A0 copy ctor.
// Layout read from retail mov sequence: 1 dword 2 bytes 2 pad 6 dwords.
#include "../../Include/Common/Rva001DD063.h"
__declspec(noinline) inline Rva001DD063::Rva001DD063(const Rva001DD063 &o)
    : f00(o.f00),
      b04(o.b04), b05(o.b05),
      f08(o.f08), f0C(o.f0C),
      f10(o.f10), f14(o.f14), f18(o.f18), f1C(o.f1C)
{
}
// Select-any: Eva.cpp compiles an identical copy; the anchor keeps the rowed body emitted.
// ?bfmeAnchorRva001DD063Copy absent-from-retail
Rva001DD063 bfmeAnchorRva001DD063Copy(const Rva001DD063 &o) { return Rva001DD063(o); }
