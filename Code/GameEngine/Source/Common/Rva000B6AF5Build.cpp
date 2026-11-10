// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva000B6AF5Build@@YAPAURva000B6AF5Rec@@PAU1@PAPAXH@Z @0x000B6AF5 90B:
// Build 12B rec sibling of 0x000B6AA9: w1=movzx else 0, tmp=w1-val, w2=movzx,
// Clamp(&tmp,&val,w2), pack (srcpp,tmp,val) via tmp movsd x3 returning dest.
// Callers 0x000BDDF7 0x0021C025 0x0021C080 0x0021C0D7 0x0021C1C4 0x0021EED8.
void __cdecl Rva000B2B42Clamp(int *a1, int *a2, int a3);
#include "../../Include/Common/Rva000B6AF5Rec.h"
Rva000B6AF5Rec *__cdecl Rva000B6AF5Build(Rva000B6AF5Rec *dest, void **srcpp, int val)
{
	void *p = *srcpp;
	int baseCount = p ? *(unsigned short *)((char *)p + 4) : 0;
	int remaining = baseCount - val;
	void *record = *srcpp;
	int limit = record ? *(unsigned short *)((char *)record + 4) : 0;
	Rva000B2B42Clamp(&remaining, &val, limit);
	Rva000B6AF5Rec packedRec;
	packedRec.p = (void *)srcpp;
	packedRec.a = remaining;
	packedRec.b = val;
	*dest = packedRec;
	return dest;
}
