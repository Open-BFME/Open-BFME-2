// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva001DD1B3@@QAE@ABHABURva001DD063@@@Z @0x001DD2BF 29B
// Two-arg ctor of 36-byte record: int head plus Rva001DD063 tail at +4.
// Evidence: chain lane every callee rowed; retail copies [eax] then calls rowed 0x001DD063 with this+4 and returns this; caller 0x001DE3A5.
#include "../../Include/Common/Rva001DD063.h"
struct Rva001DD1B3 {
    int f00;
    Rva001DD063 f04;
    Rva001DD1B3(const int &key, const Rva001DD063 &tail);
};
__declspec(noinline) inline Rva001DD1B3::Rva001DD1B3(const int &key, const Rva001DD063 &tail)
    : f00(key), f04(tail)
{
}
// Select-any: Eva.cpp compiles an identical copy; the anchor keeps the rowed body emitted.
// ?bfmeAnchorRva001DD1B3Ctor absent-from-retail
Rva001DD1B3 bfmeAnchorRva001DD1B3Ctor(const int &key, const Rva001DD063 &tail) { return Rva001DD1B3(key, tail); }
