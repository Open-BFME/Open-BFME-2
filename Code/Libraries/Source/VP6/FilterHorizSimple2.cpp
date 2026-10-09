// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c3b70.md plus retail only.
// No decoder source was consulted.
// _FilterHoriz_Simple2_C retail 0x001C3B70..0x001C3F4C (989 bytes) cdecl
// (instance unused / pixel pointer at the first of four horizontally
// adjacent pixels / line length / bounding array centre); no retail caller.
// For eight lines (MSVC unrolls the loop fully) a line whose two edge-
// adjacent pixels are equal is skipped. Otherwise the bounding entry at
// (2 * edge step - left outer step + right outer step + 4) >> 3 is added
// to the left-adjacent pixel and subtracted from the right-adjacent one;
// half of it (arithmetic) moves the two outer pixels the same way only
// when both outer steps are zero. Every write goes through the saturating
// clamp table g_bfmeClampTable (zero point 0x00E23100). Retail advances
// the pointer by the line length only on a filtered line (the skip branch
// at 0x001C3B97 jumps past the add at 0x001C3BFC).
extern const unsigned char g_bfmeClampTable[];
extern "C" void FilterHoriz_Simple2_C(void *, unsigned char *ptr, int pitch, const int *bounding)
{
	int i, step, left, right, amount, half;
	for (i = 0; i < 8; i++) {
		step = ptr[2] - ptr[1];
		if (step != 0) {
			left = ptr[1] - ptr[0];
			right = ptr[3] - ptr[2];
			amount = bounding[(step * 2 - left + right + 4) >> 3];
			ptr[1] = g_bfmeClampTable[ptr[1] + amount];
			ptr[2] = g_bfmeClampTable[ptr[2] - amount];
			half = ((right | left) == 0) * (amount >> 1);
			ptr[0] = g_bfmeClampTable[ptr[0] + half];
			ptr[3] = g_bfmeClampTable[ptr[3] - half];
			ptr += pitch;
		}
	}
}
