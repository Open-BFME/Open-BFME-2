// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva002C76B2Build@@YAPAVWeaponTemplateSetHead@@PAV1@HH@Z retail 0x002C76B2 204B
// Bitset builder returning out for WeaponTemplateSetHead 0x4C: memset 0 then set 1<<bit from four condition tables, copy-construct out. Evidence: calls memset import 0x6291AE and rowed copy ctor 0x45455; tables g_00DBC46C g_00C00960 g_00C00948 g_00C00930; callers 0x28DC8F 0x28FCB2 need unlock; free cdecl with EAX-out return per lever 31 and inline placement new precedent.
#include <string.h>
#include <new.h>
extern void *g_00DBC46C[];
extern int g_00C00960[];
// g_00C00960 and the per-b row table g_00DBC46C have this function as their
// only reader. Retail .rdata rows at VA 0xc008b8..0xc00918 (6 ints each, read
// only through g_00DBC46C's .data pointers at VA 0xdbc46c) and the image's
// contents follow; b selects rows 0xc00918, 0xc00900, 0xc008e8, 0xc008d0 and
// twice 0xc008b8.
int g_00C00960[6] = {
	123, 124, 125, 538, 539, -1,
};
static int g_00C00918[6] = { -1, -1, -1, -1, -1, -1, };
static int g_00C00900[6] = { 41, 47, 53, 530, 531, -1, };
static int g_00C008E8[6] = { 44, 50, 56, 532, 533, -1, };
static int g_00C008D0[6] = { 45, 51, 57, 534, 535, -1, };
static int g_00C008B8[6] = { 40, 46, 52, 536, 537, -1, };
void *g_00DBC46C[6] = {
	g_00C00918, g_00C00900, g_00C008E8, g_00C008D0, g_00C008B8, g_00C008B8,
};
// g_00C00948: matched references place it at VA 0xc00948; retail contents, sized to the
// 0x18-byte gap before the next known global there.
int FiringOrPreAttack[6] = {
	42, 48, 54, 540, 541, -1,
};
// g_00C00930: matched references place it at VA 0xc00930; retail contents, sized to the
// 0x18-byte gap before the next known global there.
int FiringOrReloading[6] = {
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
	WeaponTemplateSetHead &weaponTemplateSetHead = *(WeaponTemplateSetHead *)tmpBuf;
	memset(&weaponTemplateSetHead, 0, 0x4C);
	unsigned *bits = (unsigned *)&weaponTemplateSetHead;
	unsigned bit = 1;
	int v = ((int **)g_00DBC46C)[b][a];
	if (v != -1)
		bits[(unsigned)v >> 5] |= bit << ((unsigned)v & 31);
	int w = ((int *)g_00C00960)[a];
	if (w != -1 && b != 0)
		bits[(unsigned)w >> 5] |= bit << ((unsigned)w & 31);
	int firingOrPreAttackFlag = ((int *)FiringOrPreAttack)[a];
	if (firingOrPreAttackFlag != -1 && (b == 1 || b == 4 || b == 5))
		bits[(unsigned)firingOrPreAttackFlag >> 5] |= bit << ((unsigned)firingOrPreAttackFlag & 31);
	int firingOrReloadingFlag = ((int *)FiringOrReloading)[a];
	if (firingOrReloadingFlag != -1 && (b == 1 || b == 3))
		bits[(unsigned)firingOrReloadingFlag >> 5] |= bit << ((unsigned)firingOrReloadingFlag & 31);
	new (out) WeaponTemplateSetHead(weaponTemplateSetHead);
	return out;
}
