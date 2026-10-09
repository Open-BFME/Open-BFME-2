// _AnyRatioFrameScale
// partial score=0.96 date=2026-10-10
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001baf30.md plus retail only.
// No decoder source was consulted.
#include <string.h>
struct Rva009AA260Context;
int __cdecl Rva009AA260Scale(Rva009AA260Context *, const unsigned char *, int, unsigned, unsigned, unsigned char *, unsigned, unsigned, unsigned);

struct Vp6AnyRatioPostProc
{
	unsigned char pad00[0x40];
	unsigned int frameWidth;
	unsigned char pad44[0x58 - 0x44];
	int hScale;
	int hRatio;
	int vScale;
	int vRatio;
	unsigned char pad68[0x70 - 0x68];
	unsigned int expandedWidth;
	unsigned int expandedHeight;
	int reconY;
	int reconU;
	int reconV;
	unsigned char pad84[0xB4 - 0x84];
	int border;
};

struct Vp6AnyRatioYUVConfig
{
	int yWidth, yHeight, yStride, uvWidth, uvHeight, uvStride;
	unsigned char *y, *u, *v;
};

extern "C" int AnyRatioFrameScale(Vp6AnyRatioPostProc *pp, unsigned char *frame, Vp6AnyRatioYUVConfig *config, int yOffset, int uvOffset)
{
	int destWidth = pp->expandedWidth;
	int sourceWidth = (pp->expandedWidth * pp->hRatio + (pp->hScale - 1)) / pp->hScale;
	int destHeight = pp->expandedHeight;
	int sourceHeight = (pp->expandedHeight * pp->vRatio + (pp->vScale - 1)) / pp->vScale;
	int paddedWidth;
	int paddedHeight;
	int result;
	int i;
	if (pp->hRatio == 3)
		paddedWidth = (sourceWidth + 2) / 3 * 3 * pp->hScale / pp->hRatio;
	else
		paddedWidth = (sourceWidth + 7) / 8 * 8 * pp->hScale / pp->hRatio;
	if (pp->vRatio == 3)
		paddedHeight = (sourceHeight + 2) / 3 * 3 * pp->vScale / pp->vRatio;
	else
		paddedHeight = (sourceHeight + 7) / 8 * 8 * pp->vScale / pp->vRatio;
	result = Rva009AA260Scale((Rva009AA260Context *)pp, frame + pp->reconY, pp->frameWidth + pp->border * 2, sourceWidth, sourceHeight,
		config->y + yOffset, config->yStride, destWidth, destHeight);
	for (i = 0; i < paddedHeight; i++)
		memset(config->y + i * config->yStride + destWidth + yOffset, 0, paddedWidth - destWidth);
	for (i = destHeight; i < paddedHeight; i++)
		memset(config->y + i * config->yStride + yOffset, 0, paddedWidth);
	if (result == 0)
		return 0;
	sourceWidth = (sourceWidth + 1) >> 1;
	sourceHeight = (sourceHeight + 1) >> 1;
	destWidth = (destWidth + 1) >> 1;
	destHeight = (destHeight + 1) >> 1;
	Rva009AA260Scale((Rva009AA260Context *)pp, frame + pp->reconU, (pp->frameWidth >> 1) + pp->border, sourceWidth, sourceHeight,
		config->u + uvOffset, config->uvStride, destWidth, destHeight);
	Rva009AA260Scale((Rva009AA260Context *)pp, frame + pp->reconV, (pp->frameWidth >> 1) + pp->border, sourceWidth, sourceHeight,
		config->v + uvOffset, config->uvStride, destWidth, destHeight);
	return result;
}
