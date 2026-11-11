// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva004E7B40@@YAXPAVRva004E7A76@@@Z @0x004E7B40 9B: cdecl one-pointer
// forward that loads the pointer into ecx and tail-jumps to the rowed
// Rva004E7A76::rva004E7A76 0x004E7A76 (null-checked slot-2 release through
// +8), the shape of an STLport _Destroy(T*) over a type whose destructor is
// that body (twin of rowed _Destroy<QueuedDownload> 0x005BC6F5). Its
// element type and name are not established.
#include "../../Include/Common/Rva004E7A76.h"

void Rva004E7B40(Rva004E7A76 *p)
{
	p->rva004E7A76();
}
