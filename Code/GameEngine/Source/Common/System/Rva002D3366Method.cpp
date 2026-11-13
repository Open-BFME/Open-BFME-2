// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002D3366@Rva002D3366@@QAEXMM@Z retail 0x002D3366 25 bytes. Thiscall wrapper forwarding two float stack args to virtual slot [eax+8]. Evidence: callers 0x0004E6BE and 0x0004F56E pass two floats from stack with ecx from [edi+0x20]; x87 fld/fstp copy matches /O1 without SSE like neighbour Rva002D337FThunk.
#include "../../../Include/Common/Rva002D3366.h"

void Rva002D3366::rva002D3366(float a, float b)
{
	m_slot8(a, b);
}
