// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001bff60.md plus retail only.
// No decoder source was consulted.
//
// FilterHoriz_Generic (retail 0x001BFF60, 290 bytes): loop filter across a
// vertical edge, eight rows. With the four pixels a, b, c, d at offsets 0..3
// the filter value is a - 3b + 3c - d, mapped through the bounding array at
// (value + 4) >> 3; pixel b gains it and pixel c loses it through the clamp
// table (zero point at image 0x00E23100).

extern unsigned char g_bfmeClampTable[0x300];	// retail 0x00E23000
#define BFME_CLAMP_ZERO (g_bfmeClampTable + 0x100)	// retail 0x00E23100, the table's zero point

// RVA 0x001BFF60
extern "C" void __cdecl FilterHoriz_Generic(void *, unsigned char *ptr, int lineLength, const int *bounding)
{
	for (int i = 0; i < 8; ++i) {
		int value = (ptr[0] - ptr[3]) + 3 * (ptr[2] - ptr[1]);
		int delta = bounding[(value + 4) >> 3];
		ptr[1] = BFME_CLAMP_ZERO[ptr[1] + delta];
		ptr[2] = BFME_CLAMP_ZERO[ptr[2] - delta];
		ptr += lineLength;
	}
}
