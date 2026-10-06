// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00270190Free@@YAXXZ, retail 0x00270190, 24 bytes. Leaf lane.
// Frees global g_00DFEB78 (data 0x009FEB78) via rowed ??_V@YAXPAX@Z
// (operator delete[] in mem_ops.cpp) when nonzero, then zeroes it.
// /O1 gives and [m],0 and pop-ecx cleanup. Caller is unclaimed
// Catch@00630412 62B. Flags copied from next Rva002701F4Ctor.cpp (/O1).

// g_00DFEB78: matched references place it at VA 0xdfeb78 (retail .data initial value 0).
void * g_00DFEB78 = 0;
extern void __cdecl operator delete[](void *p);

void __cdecl Rva00270190Free()
{
	if (g_00DFEB78)
	{
		operator delete[](g_00DFEB78);
		g_00DFEB78 = 0;
	}
}
