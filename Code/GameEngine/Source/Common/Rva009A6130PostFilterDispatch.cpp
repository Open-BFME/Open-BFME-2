// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?Rva009A6130PostFilterDispatch@@YAXPAURva009A6130Context@@HHHHPAE11HH@Z
// BFME 2 RVA 0x001B6BA0: 1155 code bytes, followed by a nine-entry switch table.
// Clean C++ donor: Open-BFME-1 10af19f44a89ab7ecc23195bb9a842ceafbc02c9,
// game/GameEngine/Source/Common/Rva009A6130PostFilterDispatch.cpp (B1 0x009A6130).
// The VP6 post-filter interpretation and field labels come from that donor;
// the original symbol is unknown, so retain its address-derived name.
//
// Native evidence: Ghidra starts FUN_005b6ba0 here; the body reads ten cdecl
// arguments, stores nine at context +0x00..+0x20, then dispatches levels 0..8.
// Its loads independently establish the offsets declared below. The pointer
// and dimension interpretations follow the donor and the native copy calls;
// these are a scoped view, not a claim about the codec's original class name.
// Native call 0x001B6D08 reaches 0x001B96A0 with (context, frame). Reuse the
// existing d_009a8c50 pin via its witnessed two-argument ABI, as the matched
// Rva009A5800Forward.cpp caller does. Calls at 0x001B6D13 and 0x001B7016
// reach 0x001C2F20 with (context, source, destination), caller stack cleanup.
// That helper reads those three stack arguments and ends in a plain ret at
// 0x001C343C; Ghidra's 1299-byte span omits the final loop branch and epilogue.
// The Rva009B2530 label comes from the corresponding donor call, not symbols.
//
// Native indirect calls use VA 0x00E22F88 (five-argument Y copy) and
// 0x00E22F7C (five-argument noise). The matched CPU table installer establishes
// its table base at 0x00E22F7C at every slot assignment. Share its definition:
// Y copy is slot 3 and noise is slot 0. Neither callback gets a private global.
// Field reloads after calls and the separate m_c0 tails preserve retail codegen.

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

struct BfmeGridZJ;
struct Rva009AF200Context;
struct Rva009AF320Context;
struct Rva009B3800Context;
void __cdecl bfmeFillZJ(BfmeGridZJ *);
void __cdecl Rva009AF200CopyPlanes(Rva009AF200Context *, int, int);
void __cdecl Rva009AF320CopyPlanes(Rva009AF320Context *, int, int);
void __cdecl Rva009B3800PlaneCopy(Rva009B3800Context *, int, int);

struct Rva009A6130Context;
void __cdecl d_009a8c50(void);
#define Rva009A8C50(c, f) ((void (__cdecl *)(Rva009A6130Context *, unsigned char *))d_009a8c50)((c), (f))
void __cdecl Rva009B2530(Rva009A6130Context *, unsigned char *, unsigned char *);
void __cdecl Rva009B2A50(Rva009A6130Context *, unsigned char *, unsigned char *);

typedef void (__cdecl *Rva009A6130CopyY)(unsigned char *, unsigned char *,
	unsigned int, unsigned int, unsigned int);
typedef void (__cdecl *Rva009A6130Noise)(unsigned char *, unsigned int,
	unsigned int, unsigned int, int);
typedef void (__cdecl *BfmeDispatchFn)();
struct BfmeCodecDispatchTable
{
	BfmeDispatchFn slot[26];
};
extern BfmeCodecDispatchTable g_bfmeCodecDispatch;
#define COPY_Y ((Rva009A6130CopyY)g_bfmeCodecDispatch.slot[3])
#define NOISE ((Rva009A6130Noise)g_bfmeCodecDispatch.slot[0])

struct Rva009A6130Context
{
	int m_mode;
	int m_04;
	int m_level;
	int m_tableIndex;
	unsigned char *m_source;
	unsigned char *m_destination;
	unsigned char *m_18;
	int m_1c;
	int m_20;
	unsigned char m_pad24[0x6c - 0x24];
	void *m_6c;
	unsigned char m_pad70[0x78 - 0x70];
	unsigned int m_planeY;
	unsigned int m_planeU;
	unsigned int m_planeV;
	unsigned char m_pad84[0x90 - 0x84];
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_strideY;
	unsigned char m_pad9c[0xbc - 0x9c];
	unsigned char *m_bc;
	void *m_c0;
	void *m_c4;
};

// The landed helpers each declare their own view of this context.
#define FILL(c) bfmeFillZJ((BfmeGridZJ *)(c))
#define AF200(c, a, b) Rva009AF200CopyPlanes((Rva009AF200Context *)(c), (int)(a), (int)(b))
#define AF320(c, a, b) Rva009AF320CopyPlanes((Rva009AF320Context *)(c), (int)(a), (int)(b))
#define B3800(c, a, b) Rva009B3800PlaneCopy((Rva009B3800Context *)(c), (int)(a), (int)(b))

void __cdecl Rva009A6130PostFilterDispatch(Rva009A6130Context *ctx, int mode, int a3,
	int level, int tableIndex, unsigned char *source, unsigned char *destination,
	unsigned char *a8, int a9, int a10)
{
	ctx->m_mode = mode;
	ctx->m_04 = a3;
	ctx->m_level = level;
	ctx->m_tableIndex = tableIndex;
	ctx->m_source = source;
	ctx->m_destination = destination;
	ctx->m_18 = a8;
	ctx->m_1c = a9;
	ctx->m_20 = a10;

	switch (ctx->m_level)
	{
	case 8:
		FILL(ctx);
		if (ctx->m_mode < 2)
		{
			AF200(ctx, ctx->m_source, ctx->m_destination);
		}
		else if (ctx->m_6c && ctx->m_c0)
		{
			B3800(ctx, ctx->m_source, ctx->m_bc);
			unsigned int bytes = ctx->m_height * ctx->m_strideY * 2;
			memcpy(ctx->m_destination + ctx->m_planeU, ctx->m_bc + ctx->m_planeU, bytes);
			memcpy(ctx->m_destination + ctx->m_planeV, ctx->m_bc + ctx->m_planeV, bytes);
			COPY_Y(ctx->m_bc + ctx->m_planeY, ctx->m_destination + ctx->m_planeY,
				ctx->m_width << 3, ctx->m_height << 3, ctx->m_strideY);
		}
		else
		{
			B3800(ctx, ctx->m_source, ctx->m_destination);
		}
		break;

	case 6:
	case 5:
		if (ctx->m_mode < 5)
			FILL(ctx);
		else if (ctx->m_6c)
		{
			if (!ctx->m_c0)
			{
				AF320(ctx, ctx->m_source, ctx->m_destination);
				Rva009A8C50(ctx, ctx->m_destination);
				Rva009B2A50(ctx, ctx->m_destination, ctx->m_destination);
			}
			else
			{
				AF320(ctx, ctx->m_source, ctx->m_bc);
				Rva009A8C50(ctx, ctx->m_bc);
				Rva009B2A50(ctx, ctx->m_bc, ctx->m_bc);
				unsigned int bytes = ctx->m_height * ctx->m_strideY * 2;
				memcpy(ctx->m_destination + ctx->m_planeU, ctx->m_bc + ctx->m_planeU, bytes);
				memcpy(ctx->m_destination + ctx->m_planeV, ctx->m_bc + ctx->m_planeV, bytes);
				COPY_Y(ctx->m_bc + ctx->m_planeY, ctx->m_destination + ctx->m_planeY,
					ctx->m_width << 3, ctx->m_height << 3, ctx->m_strideY);
			}
			break;
		}
		AF200(ctx, ctx->m_source, ctx->m_destination);
		Rva009A8C50(ctx, ctx->m_destination);
		Rva009B2530(ctx, ctx->m_destination, ctx->m_destination);
		if (ctx->m_c4)
			NOISE(ctx->m_destination + ctx->m_planeY, ctx->m_width << 3,
				ctx->m_height << 3, ctx->m_strideY, tableIndex);
		break;

	case 7:
		if (ctx->m_mode >= 5)
		{
			if (ctx->m_6c)
			{
				if (!ctx->m_c0)
				{
					AF320(ctx, ctx->m_source, ctx->m_destination);
				}
				else
				{
					AF320(ctx, ctx->m_source, ctx->m_bc);
					unsigned int bytes = ctx->m_height * ctx->m_strideY * 2;
					memcpy(ctx->m_destination + ctx->m_planeU, ctx->m_bc + ctx->m_planeU, bytes);
					memcpy(ctx->m_destination + ctx->m_planeV, ctx->m_bc + ctx->m_planeV, bytes);
					COPY_Y(ctx->m_bc + ctx->m_planeY, ctx->m_destination + ctx->m_planeY,
						ctx->m_width << 3, ctx->m_height << 3, ctx->m_strideY);
				}
				break;
			}
		}
		else
			FILL(ctx);
		AF200(ctx, ctx->m_source, ctx->m_destination);
		Rva009A8C50(ctx, ctx->m_destination);
		Rva009B2530(ctx, ctx->m_destination, ctx->m_destination);
		break;

	case 4:
		if (ctx->m_mode >= 5)
		{
			if (ctx->m_6c)
			{
				if (!ctx->m_c0)
				{
					AF320(ctx, ctx->m_source, ctx->m_destination);
				}
				else
				{
					AF320(ctx, ctx->m_source, ctx->m_bc);
					unsigned int bytes = ctx->m_height * ctx->m_strideY * 2;
					memcpy(ctx->m_destination + ctx->m_planeU, ctx->m_bc + ctx->m_planeU, bytes);
					memcpy(ctx->m_destination + ctx->m_planeV, ctx->m_bc + ctx->m_planeV, bytes);
					COPY_Y(ctx->m_bc + ctx->m_planeY, ctx->m_destination + ctx->m_planeY,
						ctx->m_width << 3, ctx->m_height << 3, ctx->m_strideY);
				}
				break;
			}
		}
		else
			FILL(ctx);
		AF200(ctx, ctx->m_source, ctx->m_destination);
		break;

	case 1:
		FILL(ctx);
		break;

	case 0:
		if (ctx->m_6c && ctx->m_c0)
		{
			unsigned int bytes = ctx->m_height * ctx->m_strideY * 2;
			memcpy(ctx->m_destination + ctx->m_planeU, ctx->m_source + ctx->m_planeU, bytes);
			memcpy(ctx->m_destination + ctx->m_planeV, ctx->m_source + ctx->m_planeV, bytes);
			COPY_Y(ctx->m_source + ctx->m_planeY, ctx->m_destination + ctx->m_planeY,
				ctx->m_width << 3, ctx->m_height << 3, ctx->m_strideY);
		}
		break;

	case 2:
	case 3:
	default:
		AF200(ctx, ctx->m_source, ctx->m_destination);
		Rva009A8C50(ctx, ctx->m_destination);
		Rva009B2530(ctx, ctx->m_destination, ctx->m_destination);
		break;
	}
}
