// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva000B2BE5Get@@YAHPBURva000B2BE5Src@@H@Z @0x000B2BE5 26B:
// Flag getter (int,const-src*,int): return 2 if src and byte+0x114 bit 0x20
// else fallback. Callers 0x000BF33F 0x000BF4D2 0x000BF996 0x000C2ECC.
struct Rva000B2BE5Src { char pad[0x114]; unsigned char flag; };
int __cdecl Rva000B2BE5Get(const Rva000B2BE5Src *p, int fallback)
{
	if (p && (p->flag & 0x20))
		return 2;
	return fallback;
}
