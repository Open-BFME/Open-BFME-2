// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva000B6AA9Build@@YAPAURva000B6AA9Rec@@PAU1@PAPAXH@Z @0x000B6AA9 76B:
// Build 12B rec at dest from srcpp plus Clamp 0x000B2B42 of word+4: local=0,
// w=srcpp?word else 0, Clamp(&local,&val,w), pack (srcpp,local,val) via tmp
// movsd x3 returning dest. Callers 0x000BDE09 0x001529B6 0x0021C171.
void __cdecl Rva000B2B42Clamp(int *a1, int *a2, int a3);
struct Rva000B6AA9Rec { void *p; int a; int b; };
Rva000B6AA9Rec *__cdecl Rva000B6AA9Build(Rva000B6AA9Rec *dest, void **srcpp, int val)
{
	int local = 0;
	void *p = *srcpp;
	int w = p ? *(unsigned short *)((char *)p + 4) : 0;
	Rva000B2B42Clamp(&local, &val, w);
	Rva000B6AA9Rec tmp;
	tmp.p = (void *)srcpp;
	tmp.a = local;
	tmp.b = val;
	*dest = tmp;
	return dest;
}
