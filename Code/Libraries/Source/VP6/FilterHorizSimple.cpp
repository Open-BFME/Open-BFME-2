// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001c3f50.md plus retail only. No
// decoder source was consulted.
//
// FilterHoriz_Simple_C (retail 0x001C3F50): deblocking filter across a
// vertical block edge, eight lines tall (four pixels per line, two each side
// of the edge). A line is high activity when either same-side pixel pair
// differs by more than one. The correction (three times the step across the
// edge, plus the outer pixel difference for high activity lines), plus 4,
// shifted right 3, indexes the bounding array; the amount moves the
// edge-adjacent pixels, and half of it the outer pixels on non-high-activity
// lines, all through the saturating clamp table.

extern unsigned char g_bfmeClampTable[0x300];	// retail 0x00E23000
#define BFME_CLAMP_ZERO (g_bfmeClampTable + 0x100)	// retail 0x00E23100, the table's zero point

// RVA 0x001C3F50
extern "C" void __cdecl FilterHoriz_Simple_C(void *, unsigned char *ptr, int stride, const int *bounding)
{
	int p0, count, value, flag, diff, delta;

	for (count = 8; count != 0; --count) {
		int p2 = ptr[2];
		int p1 = ptr[1];
		p0 = ptr[0];
		value = 3 * (p2 - p1);

		diff = p0 - p1;
		if (diff > 0)
			diff = p0 - p1;
		else
			diff = p1 - p0;
		if (diff > 1)
			goto steep;

		{
			int p3 = ptr[3];
			diff = p2 - p3;
			if (diff > 0)
				diff = p2 - p3;
			else
				diff = p3 - p2;
			if (diff <= 1) {
				flag = 0;
				goto filter;
			}
		}

steep:
		flag = 1;
		value += p0 - ptr[3];

filter:
		delta = bounding[(value + 4) >> 3];
		ptr[1] = BFME_CLAMP_ZERO[ptr[1] + delta];
		ptr[2] = BFME_CLAMP_ZERO[ptr[2] - delta];

		if (flag == 0) {
			delta >>= 1;
			ptr[0] = BFME_CLAMP_ZERO[ptr[0] + delta];
			ptr[3] = BFME_CLAMP_ZERO[ptr[3] - delta];
		}

		ptr += stride;
	}
}
