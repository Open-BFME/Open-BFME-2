// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001c0090.md plus retail only.
// No decoder source was consulted.
//
// FilterVert_Generic (retail 0x001C0090, 341 bytes): loop filter across a
// horizontal edge, eight columns. With pixels a (two lines up), b (one line
// up), c (this row) and d (one line down) the filter value is a - 3b + 3c - d,
// mapped through the bounding array at (value + 4) >> 3; pixel b gains it and
// pixel c loses it through the clamp table (zero point at image 0x00E23100).

extern unsigned char g_bfmeClampTable[];

// RVA 0x001C0090
extern "C" void __cdecl FilterVert_Generic(void *, unsigned char *ptr, int lineLength, const int *bounding)
{
	for (int i = 0; i < 8; ++i) {
		int value = (ptr[-2 * lineLength] - ptr[lineLength]) + 3 * (ptr[0] - ptr[-lineLength]);
		int delta = bounding[(value + 4) >> 3];
		ptr[-lineLength] = g_bfmeClampTable[ptr[-lineLength] + delta];
		ptr[0] = g_bfmeClampTable[ptr[0] - delta];
		++ptr;
	}
}
