// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva001DD1B3@@QAE@ABU0@@Z @0x001DD1B3 29B
// Copy ctor of 36-byte record with int head and Rva001DD063 tail at +4.
// Evidence: retail copies [eax] then calls rowed 0x001DD063 with this+4;
// callers show outer returns this; same shape as sibling pod ctors.
#include "../../Include/Common/Rva001DD063.h"
#include "../../Include/Common/Rva001DD1B3.h"
Rva001DD1B3::Rva001DD1B3(const Rva001DD1B3 &other)
    : f00(other.f00), f04(other.f04)
{
}
