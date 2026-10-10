// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bf8d0.md plus retail only.
// No decoder source was consulted.
// ?copyPlane009AEEE0@@YAXPAURva009AF200Context@@HHH@Z retail
// 0x001BF8D0..0x001BFAB8 (488 bytes) cdecl (post-processor instance /
// source offset / destination offset / channel); the pinned name its
// matched caller Rva009AF200CopyPlanes (0x001BFBF0) uses is kept.
// DeblockPlane: version (field 0) 2 and up takes the non-filtered band
// routine from the slot at 0x00E22FB0 with DeblockVerticalEdgesInNonFilteredBand
// (0x001BE140) and older versions the loop-filtered slot at 0x00E22FA4 with
// the 0x001BD670 vertical-edge routine (both stored as addresses here).
// Channel 0 is the Y plane (Y stride 0x98 / fragments across 0x90 and down
// 0x94 / recon offset 0x78) and 1 / other the U / V planes (UV stride 0x9C /
// halved counts / first fragment after the Y (0x84) and U (0x88) fragments /
// recon offsets 0x7C and 0x80). The scale table is 0x00E22CF0 for Y and
// 0x00E22CE8 for chroma from version 2 and 0x00E22CE4 below it; retail's
// table switch compares the channel unsigned. The first four lines are
// copied then each band below runs the band routine and the last band's
// lines 4..7 are copied before the vertical-edge routine. Retail forms the
// source and destination pointers inside each channel case.

struct Rva009AF200Context
{
	int m_mode;
	unsigned char m_pad04[0x78 - 0x04];
	unsigned char *m_planeY;
	unsigned char *m_planeU;
	unsigned char *m_planeV;
	unsigned int m_fragmentsY;
	unsigned int m_fragmentsUV;
	unsigned int m_scratchCount;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_strideY;
	unsigned int m_strideUV;
};

typedef void (__cdecl *DeblockPlaneBand)(Rva009AF200Context *, unsigned char *,
	unsigned char *, unsigned int, unsigned int, int, const unsigned int *);

struct Rva009ACC80Context;
void __cdecl Rva009ACC80Filter(Rva009ACC80Context *, unsigned char *, unsigned char *,
	unsigned int, unsigned int, int, const unsigned int *);
struct Rva009AD750Context;
extern "C" void __cdecl DeblockVerticalEdgesInNonFilteredBand(Rva009AD750Context *,
	unsigned char *, unsigned char *, unsigned int, unsigned int, int, const unsigned int *);

extern DeblockPlaneBand g_00E22FA4;
extern DeblockPlaneBand g_00E22FB0;
extern const unsigned int *g_rva01356AA0;
extern const unsigned int *g_rva01356A98;
extern const void *g_rva01356A88;

void copyPlane009AEEE0(Rva009AF200Context *ctx, int sourceOffset, int destinationOffset, int channel)
{
	DeblockPlaneBand band;
	DeblockPlaneBand edges;
	const unsigned int *scale = 0;
	unsigned int stride;
	unsigned int across;
	unsigned int down;
	int first;
	unsigned char *source;
	unsigned char *destination;
	unsigned int row;
	unsigned int column;

	if (ctx->m_mode >= 2) {
		band = g_00E22FB0;
		edges = (DeblockPlaneBand)DeblockVerticalEdgesInNonFilteredBand;
	} else {
		band = g_00E22FA4;
		edges = (DeblockPlaneBand)Rva009ACC80Filter;
	}

	switch (channel) {
	case 0:
		stride = ctx->m_strideY;
		across = ctx->m_width;
		down = ctx->m_height;
		first = 0;
		source = ctx->m_planeY + sourceOffset;
		destination = ctx->m_planeY + destinationOffset;
		break;
	case 1:
		stride = ctx->m_strideUV;
		across = ctx->m_width >> 1;
		down = ctx->m_height >> 1;
		first = ctx->m_fragmentsY;
		source = ctx->m_planeU + sourceOffset;
		destination = ctx->m_planeU + destinationOffset;
		break;
	default:
		stride = ctx->m_strideUV;
		across = ctx->m_width >> 1;
		down = ctx->m_height >> 1;
		first = ctx->m_fragmentsY + ctx->m_fragmentsUV;
		source = ctx->m_planeV + sourceOffset;
		destination = ctx->m_planeV + destinationOffset;
		break;
	}

	if (ctx->m_mode >= 2) {
		switch ((unsigned int)channel) {
		case 0:
			scale = g_rva01356AA0;
			break;
		case 1:
		case 2:
			scale = g_rva01356A98;
			break;
		}
	} else {
		scale = (const unsigned int *)g_rva01356A88;
	}

	for (row = 0; row < 4; row++)
		for (column = 0; column < stride; column++)
			destination[row * stride + column] = source[row * stride + column];

	for (row = 1; row < down; row++) {
		source += stride * 8;
		destination += stride * 8;
		band(ctx, source, destination, stride, across, first, scale);
		first += across;
	}

	for (row = 4; row < 8; row++)
		for (column = 0; column < stride; column++)
			destination[row * stride + column] = source[row * stride + column];

	edges(ctx, source, destination, stride, across, first, scale);
}
