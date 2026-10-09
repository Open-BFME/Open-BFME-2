// ?rva006D2D90@@YAXXZ
// recovered 0x006D2D90 89B
// cl: /O2 /MD
// ?rva006D2D90@@YAXXZ @0x006D2D90 89B evidence byte table g_00CE8B70 plus globals
// E177E0-E177E8 plus caller 0x006CC380.
//
// Scans the 47-byte Apt eType table at 0x00CE8B70 (indices 1..46) for min/max,
// seeds three bytes to 0/4/8, stores the max dword and the min clamped to 12.
//
// Two source choices carry the whole body, and neither was in the bank:
//
// 1. The table read is VOLATILE. Read plainly, cl 13.10 strength-reduces the
//    loop induction -- it replaces `mov ecx,1 / movzx eax,[ecx+tbl] / inc ecx /
//    cmp ecx,0x2f` with a rotated table pointer, spends a register on it, and
//    then has to keep the zero seed live in a register too, which turns retail's
//    `mov BYTE [E2],0x0` into a register-indirect `mov BYTE [E2],cl`. Declaring
//    the table volatile forbids that: the read must go through the index, ecx
//    survives as a plain induction variable, and the zero seed is stored as a
//    direct immediate. That reproduces retail instruction for instruction from
//    0x006D2D90 through 0x006D2DD4 (`pop esi`) -- the three seed stores, the
//    xor esi,esi / mov edx,0xf4240 / mov ecx,1 trio, and the whole min/max loop
//    including both `cmp / jbe / mov` and `cmp / jae / mov` pairs.
//
// 2. The clamp is computed ONCE into a 32-bit local and stored once. Retail's
//    tail narrows a 32-bit register into an 8-bit store on both branches --
//    `mov eax,0xc / mov [E1],al / ret` against `mov [E1],dl / ret` -- which is
//    what `unsigned int c = minVal < 12 ? 12u : minVal; g_00E177E1 =
//    (unsigned char)c;` lowers to. The bank's early-return spelling instead
//    hoists a direct `mov BYTE [E1],0xc` above the branch and keeps only the
//    `dl` narrowing; same 8-bit stores, wrong constant placement. Writing the
//    clamp into minVal itself (`if (minVal < 12) minVal = 12;`) is
//    byte-identical to this form.
extern unsigned char g_00E177E0;
extern unsigned char g_00E177E1;
extern unsigned char g_00E177E2;
extern int g_00E177E4;
extern unsigned char g_00E177E8;
extern volatile unsigned char g_00CE8B70[];

// ?Rva006D2D90Init@@YAXXZ present-unmatched
void __cdecl rva006D2D90()
{
	g_00E177E2 = 0;
	g_00E177E0 = 4;
	g_00E177E8 = 8;
	int maxVal = 0;
	unsigned int minVal = 1000000;
	for (int i = 1; i < 0x2f; ++i) {
		unsigned int v = g_00CE8B70[i];
		if (v > (unsigned int)maxVal)
			maxVal = (int)v;
		if (v < minVal)
			minVal = v;
	}
	g_00E177E4 = maxVal;
	unsigned int c = minVal < 12 ? 12u : minVal;
	g_00E177E1 = (unsigned char)c;
}
// Native6CBC50 sized-free callback, independently exact6B.
// The startup6CC380 allocations and sized EH cleanup7A8050/5F establish roles.
extern void (__cdecl *g_bfmeAptFreeSizeAtE17730)(void *,unsigned int);
void rva006CBC50(void *storage,unsigned int size){g_bfmeAptFreeSizeAtE17730(storage,size);}
