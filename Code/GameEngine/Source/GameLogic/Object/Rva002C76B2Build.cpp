// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva002C76B2Build@@YAPAVWeaponTemplateSetHead@@PAV1@HH@Z retail 0x002C76B2 204B
// Bitset builder returning out for WeaponTemplateSetHead 0x4C: memset 0 then set 1<<bit from four condition tables, copy-construct out. Evidence: calls memset import 0x6291AE and rowed copy ctor 0x45455; tables g_00DBC46C g_00C00960 g_00C00948 g_00C00930; callers 0x28DC8F 0x28FCB2 need unlock; free cdecl with EAX-out return per lever 31 and inline placement new precedent.
extern "C" void *memset(void *dst, int c, unsigned n);
typedef unsigned size_t;
inline void *operator new(size_t, void *place)
{
	return place;
}
extern void *g_00DBC46C[];
extern int g_00C00960[];
// g_00C00948: matched references place it at VA 0xc00948; retail contents, sized to the
// 0x18-byte gap before the next known global there.
int g_00C00948[6] = {
	42, 48, 54, 540, 541, -1,
};
// g_00C00930: matched references place it at VA 0xc00930; retail contents, sized to the
// 0x18-byte gap before the next known global there.
int g_00C00930[6] = {
	43, 49, 55, 542, 543, -1,
};
class WeaponTemplateSetHead
{
public:
	__declspec(nothrow) WeaponTemplateSetHead(const WeaponTemplateSetHead &that);
	char m_data[0x4C];
};
WeaponTemplateSetHead *__cdecl Rva002C76B2Build(WeaponTemplateSetHead *out, int a, int b)
{
	__assume(out != 0);
	char tmpBuf[0x4C];
	WeaponTemplateSetHead &tmp = *(WeaponTemplateSetHead *)tmpBuf;
	memset(&tmp, 0, 0x4C);
	unsigned *bits = (unsigned *)&tmp;
	unsigned bit = 1;
	int v = ((int **)g_00DBC46C)[b][a];
	if (v != -1)
		bits[(unsigned)v >> 5] |= bit << ((unsigned)v & 31);
	int w = ((int *)g_00C00960)[a];
	if (w != -1 && b != 0)
		bits[(unsigned)w >> 5] |= bit << ((unsigned)w & 31);
	int x = ((int *)g_00C00948)[a];
	if (x != -1 && (b == 1 || b == 4 || b == 5))
		bits[(unsigned)x >> 5] |= bit << ((unsigned)x & 31);
	int y = ((int *)g_00C00930)[a];
	if (y != -1 && (b == 1 || b == 3))
		bits[(unsigned)y >> 5] |= bit << ((unsigned)y & 31);
	new (out) WeaponTemplateSetHead(tmp);
	return out;
}
