// cl: /Ob1 /GX- /GS
// ?rva00094B08@@YAXPAURva00094B08FloatBlock@@@Z @0x00094B08 95B.
// Zeroes twelve of a sixteen-float block and writes 1.0f into the remaining
// four (0, 5, 10, 15). Retail emits one `movss xmm0,[0x00BBB8D8]` after the
// twelve zero stores and reuses xmm0 for all four one stores, so 1.0f reaches
// the body as a memory constant in the shared .rdata literal pool rather than
// an immediate. That pool slot (0x00BBB8D8 == 1.0f, sitting between 0.25f at
// +0x7BB8D4 and FLT_MAX at +0x7BB8DC) is already load-bearing for matched
// bodies including ?RParabolicEase@@QBEMM@Z and ?rva0030E8DF@Rva0030E8DF@@QAEXXZ.
// The body itself was reconstructed from the BFME 1 donor
// game/GameEngine/Source/Common/S3FieldInitialisers.cpp
// @5cc75ddda6455c338a5068307e587a793f96d6b3 (blob
// 584d838f233b527410f172b70f9e5b20678e16a7), compiled with no includes.
// The original owner and method name are NOT established: there is no Ghidra
// function entry at this RVA and no independent call/jump/absolute reference
// into it. The preceding body tail-jumps to 0x0094AFD (94 bytes, ending
// 0x0094B07) and the following `ret` at 0x0094B66 is 94 bytes after this
// body starts, so this range is provably a self-contained 95-byte leaf. The
// address-derived name above is used rather than an invented one.
struct Rva00094B08FloatBlock {float values[16];};

// 1.0f as the shared .rdata literal at 0x00BBB8D8, not an immediate.
extern const float rva00094B08One;

void rva00094B08(Rva00094B08FloatBlock *p)
{
	p->values[1]=p->values[2]=p->values[3]=
	p->values[4]=p->values[6]=p->values[7]=
	p->values[8]=p->values[9]=p->values[11]=
	p->values[12]=p->values[13]=p->values[14]=0.0f;
	const float one = rva00094B08One;
	p->values[0]=p->values[5]=p->values[10]=p->values[15]=one;
}

// Retail global spelled differently by the unit that defines it (same
// address in reverse/data_ledger.csv); bind this unit's name to it.
#pragma comment(linker, "/alternatename:?rva00094B08One@@3MB=?g_Va00BBB8D8@@3MA")
