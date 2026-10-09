// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c2f20.md plus retail only.
// No decoder source was consulted.
// ?Rva009B2530@@YAXPAURva009A6130Context@@PAE1@Z retail 0x001C2F20..0x001C343D
// (1309 bytes) cdecl (post-processor instance / source frame / destination
// frame); the pinned address-derived name is kept. Progressive DeringFrame:
// the Y plane (line length = Y stride at 0x98) then U and V at half the
// block counts and half the line length. Version (field 0) 5 and up uses
// thresholds 384/2304/2880/5760 and the 0x00DB7928 scale table; versions 2
// to 4 use 2048/30720/92160/122880 with 0x00DB7828 and older ones the copy
// at 0x00E22BE0. A Y block whose variance (0x28) exceeds the third
// threshold at level (0x08) above 5 is strongly filtered once and twice
// more when the left / right / lower / upper neighbour exceeds the fourth;
// otherwise strong / weak / copy by the second and first thresholds. Chroma
// below version 5 takes its quality from the block's own Q index (0x24) and
// a block above the fourth threshold at level above 5 is filtered three
// times. Kernels are the dispatch slots 0x00E22FDC (strong) 0x00E22FBC
// (weak) and 0x00E22D0C (copy). The interlaced sibling at 0x001C3440 is
// Rva009B2A50DeringFrame.cpp and supplies the context view names.

struct Rva009A6130Context
{
	int m_mode;
	int m_04;
	int m_level;
	int m_tableIndex;
	unsigned char m_pad10[0x24 - 0x10];
	int *m_qIndex;
	int *m_metric;
	unsigned char m_pad2c[0x78 - 0x2c];
	unsigned int m_planeY;
	unsigned int m_planeU;
	unsigned int m_planeV;
	unsigned char m_pad84[0x90 - 0x84];
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_strideY;
};

typedef void (__cdecl *Rva009B2A50Dering)(Rva009A6130Context *, unsigned char *,
	unsigned char *, int, int, const int *);
typedef void (__cdecl *Rva009B2A50Copy)(unsigned char *, unsigned char *, int);

extern Rva009B2A50Dering g_rva01356EC0;
extern Rva009B2A50Dering g_rva01356EA0;
extern void *g_bfmeSlotB44;
extern int g_rva01356940[64];
extern int g_rva012D7F58[64];
extern int g_rva012D8058[64];

#define BLOCK_SRC (srcPtr + 8 * col)
#define BLOCK_DST (srcPtr + 8 * col + (dstPtr - srcPtr))

void __cdecl Rva009B2530(Rva009A6130Context *ctx, unsigned char *src, unsigned char *dst)
{
	int thresh1, thresh2, thresh3, thresh4;
	const int *table;
	int quality;
	unsigned char *srcPtr;
	unsigned char *dstPtr;
	unsigned int blocksAcross;
	unsigned int blocksDown;
	unsigned int index;
	unsigned int row;
	unsigned int col;
	unsigned int lineLength;

	quality = ctx->m_tableIndex;
	if (ctx->m_mode >= 5)
	{
		thresh1 = 0x180;
		thresh2 = 0x900;
		thresh3 = 0xb40;
		thresh4 = 0x1680;
	}
	else
	{
		thresh1 = 0x800;
		thresh2 = 0x7800;
		thresh3 = 0x16800;
		thresh4 = 0x1e000;
	}

	if (ctx->m_mode >= 5)
		table = g_rva012D8058;
	else if (ctx->m_mode >= 2)
		table = g_rva012D7F58;
	else
		table = g_rva01356940;

	// Y plane.
	blocksAcross = ctx->m_width;
	blocksDown = ctx->m_height;
	srcPtr = src + ctx->m_planeY;
	dstPtr = dst + ctx->m_planeY;
	lineLength = ctx->m_strideY;
	index = 0;

	for (row = 0; row < blocksDown; row++)
	{
		for (col = 0; col < blocksAcross; col++)
		{
			int variance = ctx->m_metric[index];
			if (ctx->m_level > 5 && variance > thresh3)
			{
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				if ((col > 0 && ctx->m_metric[index - 1] > thresh4) ||
					(col + 1 < blocksAcross && ctx->m_metric[index + 1] > thresh4) ||
					(row + 1 < blocksDown && ctx->m_metric[index + blocksAcross] > thresh4) ||
					(row > 0 && ctx->m_metric[index - blocksAcross] > thresh4))
				{
					g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
					g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				}
			}
			else if (variance > thresh2)
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else if (variance > thresh1)
				g_rva01356EA0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else
				((Rva009B2A50Copy)g_bfmeSlotB44)(BLOCK_SRC, BLOCK_DST, lineLength);
			++index;
		}
		srcPtr += 8 * lineLength;
		dstPtr += 8 * lineLength;
	}

	// U plane.
	blocksAcross >>= 1;
	blocksDown >>= 1;
	lineLength >>= 1;
	srcPtr = src + ctx->m_planeU;
	dstPtr = dst + ctx->m_planeU;

	for (row = 0; row < blocksDown; row++)
	{
		for (col = 0; col < blocksAcross; col++)
		{
			int variance = ctx->m_metric[index];
			if (ctx->m_mode < 5)
				quality = ctx->m_qIndex[index];
			if (ctx->m_level > 5 && variance > thresh4)
			{
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			}
			else if (variance > thresh2)
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else if (variance > thresh1)
				g_rva01356EA0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else
				((Rva009B2A50Copy)g_bfmeSlotB44)(BLOCK_SRC, BLOCK_DST, lineLength);
			++index;
		}
		srcPtr += 8 * lineLength;
		dstPtr += 8 * lineLength;
	}

	// V plane.
	srcPtr = src + ctx->m_planeV;
	dstPtr = dst + ctx->m_planeV;

	for (row = 0; row < blocksDown; row++)
	{
		for (col = 0; col < blocksAcross; col++)
		{
			int variance = ctx->m_metric[index];
			if (ctx->m_mode < 5)
				quality = ctx->m_qIndex[index];
			if (ctx->m_level > 5 && variance > thresh4)
			{
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			}
			else if (variance > thresh2)
				g_rva01356EC0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else if (variance > thresh1)
				g_rva01356EA0(ctx, BLOCK_SRC, BLOCK_DST, lineLength, quality, table);
			else
				((Rva009B2A50Copy)g_bfmeSlotB44)(BLOCK_SRC, BLOCK_DST, lineLength);
			++index;
		}
		srcPtr += 8 * lineLength;
		dstPtr += 8 * lineLength;
	}
}
