// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b6520.md plus retail only. No decoder source was consulted.
// InitPostProcessing, retail RVA 0x001B6520 (193 bytes).
// Retail RVA 0x009A5AA0, 193 bytes.  Rva009A4D00Init (0x009A4D00) calls it
// directly as cdecl with three table pointers (all its 64-entry int table
// 0x0134C6D8) and the tier constant 7.  The body builds the saturating clamp
// table read by the loop filters, publishes the three table pointers, copies
// the 64-entry source table, picks the tier's pair of tables and runs the CPU
// dispatch installer.

// Retail passes the tier on the stack; the installer never reads it.
extern "C" void __cdecl PostProcMachineSpecificConfig(int version);

extern unsigned char g_bfmeClampTable[0x300];	// retail 0x00E23000
#define BFME_CLAMP_ZERO (g_bfmeClampTable + 0x100)	// retail 0x00E23100, the table's zero point
extern const unsigned int *g_bfmeScaleTableV2;
// g_bfmeScaleTableV2: the V2 DC-quant scale table pointer (VA 0xe22cf0, zero-filled .bss), set here.
const unsigned int * g_bfmeScaleTableV2;
extern const unsigned int *g_bfmeScaleTableUV;
// g_bfmeScaleTableUV: the UV scale table pointer (VA 0xe22ce8, zero-filled .bss), set here.
const unsigned int * g_bfmeScaleTableUV;
extern const void *g_bfmeScaleTableV1;
// g_bfmeScaleTableV1: the V1 scale table pointer (VA 0xe22ce4, zero-filled .bss), set here.
const void * g_bfmeScaleTableV1;
// Storage view: the 64 native modifier dwords begin at VA E22BE0.
// Their end at E22CE0 is also the active loop-limit pointer slot. Keeping
// that slot in the same allocation preserves this observable adjacency.
// The first 64 cells remain the modifier table; cell 64 holds pointer bits.
// This view does not establish the original C++ aggregate type.
int g_bfmeDeringModifiers[65] = { 0 };
#define g_bfmeFilterLimit (*(int **)(g_bfmeDeringModifiers + 64))
// g_bfmeDeblockLimit: the deblock limit table pointer (VA 0x00E22CEC, zero-filled .bss);
// InitPostProcessing stores the version's table in it.
int *g_bfmeDeblockLimit;

// g_bfmeFilterLimitOld: the loop-filter limit table for codec versions below 5 (VA 0xdb7528, retail .data contents).
unsigned short g_bfmeFilterLimitOld[128] = {
	0x1eu, 0u, 0x19u, 0u, 0x14u, 0u, 0x14u, 0u,
	0xfu, 0u, 0xfu, 0u, 0xeu, 0u, 0xeu, 0u,
	0xdu, 0u, 0xdu, 0u, 0xcu, 0u, 0xcu, 0u,
	0xbu, 0u, 0xbu, 0u, 0xau, 0u, 0xau, 0u,
	9u, 0u, 9u, 0u, 8u, 0u, 8u, 0u,
	7u, 0u, 7u, 0u, 7u, 0u, 7u, 0u,
	6u, 0u, 6u, 0u, 6u, 0u, 6u, 0u,
	5u, 0u, 5u, 0u, 5u, 0u, 5u, 0u,
	4u, 0u, 4u, 0u, 4u, 0u, 4u, 0u,
	3u, 0u, 3u, 0u, 3u, 0u, 3u, 0u,
	2u, 0u, 2u, 0u, 2u, 0u, 2u, 0u,
	2u, 0u, 2u, 0u, 2u, 0u, 2u, 0u,
	2u, 0u, 2u, 0u, 2u, 0u, 2u, 0u,
	2u, 0u, 2u, 0u, 2u, 0u, 2u, 0u,
	1u, 0u, 1u, 0u, 1u, 0u, 1u, 0u,
	1u, 0u, 1u, 0u, 1u, 0u, 1u, 0u,
};
// g_bfmeFilterLimitV5: the loop-filter limit table for codec version 5 (VA 0xdb7628, retail .data contents).
unsigned short g_bfmeFilterLimitV5[128] = {
	0xeu, 0u, 0xeu, 0u, 0xdu, 0u, 0xdu, 0u,
	0xcu, 0u, 0xcu, 0u, 0xau, 0u, 0xau, 0u,
	0xau, 0u, 0xau, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	7u, 0u, 7u, 0u, 7u, 0u, 7u, 0u,
	7u, 0u, 7u, 0u, 6u, 0u, 6u, 0u,
	6u, 0u, 6u, 0u, 6u, 0u, 6u, 0u,
	5u, 0u, 5u, 0u, 5u, 0u, 5u, 0u,
	4u, 0u, 4u, 0u, 4u, 0u, 4u, 0u,
	4u, 0u, 4u, 0u, 4u, 0u, 3u, 0u,
	3u, 0u, 3u, 0u, 3u, 0u, 2u, 0u,
};
// g_bfmeFilterLimitV6: the loop-filter limit table for codec version 6 and up (VA 0xdb7728, retail .data contents).
unsigned short g_bfmeFilterLimitV6[128] = {
	0xeu, 0u, 0xeu, 0u, 0xdu, 0u, 0xdu, 0u,
	0xcu, 0u, 0xcu, 0u, 0xau, 0u, 0xau, 0u,
	0xau, 0u, 0xau, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	7u, 0u, 7u, 0u, 7u, 0u, 7u, 0u,
	7u, 0u, 7u, 0u, 6u, 0u, 6u, 0u,
	6u, 0u, 6u, 0u, 6u, 0u, 6u, 0u,
	5u, 0u, 5u, 0u, 5u, 0u, 5u, 0u,
	4u, 0u, 4u, 0u, 4u, 0u, 4u, 0u,
	4u, 0u, 4u, 0u, 4u, 0u, 3u, 0u,
	3u, 0u, 3u, 0u, 3u, 0u, 2u, 0u,
};
// g_bfmeDeblockLimitOld: the deblock limit table for codec versions below 5 (VA 0xdb7128, retail .data contents).
int g_bfmeDeblockLimitOld[64] = {
	0x1e, 0x19, 0x14, 0x14, 0xf, 0xf, 0xe, 0xe,
	0xd, 0xd, 0xc, 0xc, 0xb, 0xb, 0xa, 0xa,
	9, 9, 8, 8, 7, 7, 7, 7,
	6, 6, 6, 6, 5, 5, 5, 5,
	4, 4, 4, 4, 3, 3, 3, 3,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	1, 1, 1, 1, 1, 1, 1, 1,
};
// g_bfmeDeblockLimitV5: the deblock limit table for codec version 5 (VA 0xdb7228, retail .data contents).
int g_bfmeDeblockLimitV5[64] = {
	0xf, 0xf, 0xf, 0xf, 0xa, 0xa, 0xa, 0xa,
	0xa, 0xa, 0xa, 0xa, 0xa, 9, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8,
	8, 7, 7, 7, 7, 7, 7, 7,
	6, 6, 6, 6, 5, 5, 5, 5,
	5, 4, 4, 4, 4, 4, 4, 3,
	3, 3, 3, 3, 3, 2, 2, 2,
	2, 2, 1, 1, 1, 0, 0, 0,
};
// g_bfmeDeblockLimitV6: the deblock limit table for codec version 6 and up (VA 0xdb7328, retail .data contents).
int g_bfmeDeblockLimitV6[64] = {
	0xf, 0xf, 0xf, 0xf, 0xa, 0xa, 0xa, 0xa,
	0xa, 0xa, 0xa, 0xa, 0xa, 9, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8,
	8, 7, 7, 7, 7, 7, 7, 7,
	6, 6, 6, 6, 5, 5, 5, 5,
	5, 4, 4, 4, 4, 4, 4, 3,
	3, 3, 3, 3, 3, 2, 2, 2,
	2, 2, 1, 1, 1, 0, 0, 0,
};

extern "C" void __cdecl InitPostProcessing(void *firstTable, void *secondTable, void *sourceTable, int tier)
{
	unsigned char *clamp = BFME_CLAMP_ZERO;
	int i;
	for (i = -256; i < 512; ++i)
	{
		int value;
		if (i < 0)
			value = 0;
		else
		{
			value = i;
			if (value > 255)
				value = 255;
		}
		clamp[i] = (unsigned char)value;
	}

	g_bfmeScaleTableV2 = (const unsigned int *)firstTable;
	g_bfmeScaleTableUV = (const unsigned int *)secondTable;
	g_bfmeScaleTableV1 = sourceTable;
	for (i = 0; i < 64; ++i)
		g_bfmeDeringModifiers[i] = ((const int *)sourceTable)[i];

	if ((unsigned)tier >= 6)
	{
		g_bfmeFilterLimit = (int *)g_bfmeFilterLimitV6;
		g_bfmeDeblockLimit = g_bfmeDeblockLimitV6;
	}
	else if ((unsigned)tier >= 5)
	{
		g_bfmeFilterLimit = (int *)g_bfmeFilterLimitV5;
		g_bfmeDeblockLimit = g_bfmeDeblockLimitV5;
	}
	else
	{
		g_bfmeFilterLimit = (int *)g_bfmeFilterLimitOld;
		g_bfmeDeblockLimit = g_bfmeDeblockLimitOld;
	}
	PostProcMachineSpecificConfig(tier);
}

