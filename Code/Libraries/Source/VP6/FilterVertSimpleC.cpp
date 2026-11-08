// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001c4010.md plus retail only. No decoder source was consulted.
// FilterVert_Simple_C, retail RVA 0x001C4010 (232 bytes).
// Deblocking loop filter run across a horizontal block edge, eight columns
// wide.  The four taps live at -2*stride .. +1*stride; the filter strength is
// looked up in a caller-supplied bounding-value table indexed by (f + 4) >> 3
// and every write goes through the saturating clamp table at 0x01356FE0.
//
// BFME 1's image carries two byte-identical copies of this routine; BFME 2's
// generic post-processing tier installs this one in its dispatch slot 25.

extern unsigned char g_bfmeClampTable[0x300];	// retail 0x00E23000
#define BFME_CLAMP_ZERO (g_bfmeClampTable + 0x100)	// retail 0x00E23100, the table's zero point

extern "C" void __cdecl FilterVert_Simple_C(void *, unsigned char *ptr, int stride, const int *bounding)
{
	int count, value, flag, diff, delta;

	for (count = 8; count != 0; --count) {
		value = 3 * (ptr[0] - ptr[-stride]);

		diff = ptr[-2 * stride] - ptr[-stride];
		if (diff > 0)
			diff = ptr[-2 * stride] - ptr[-stride];
		else
			diff = ptr[-stride] - ptr[-2 * stride];
		if (diff > 1)
			goto steep;

		diff = ptr[0] - ptr[stride];
		if (diff > 0)
			diff = ptr[0] - ptr[stride];
		else
			diff = ptr[stride] - ptr[0];
		if (diff <= 1) {
			flag = 0;
			goto filter;
		}

steep:
		flag = 1;
		value += ptr[-2 * stride] - ptr[stride];

filter:
		delta = bounding[(value + 4) >> 3];
		ptr[-stride] = BFME_CLAMP_ZERO[ptr[-stride] + delta];
		ptr[0] = BFME_CLAMP_ZERO[ptr[0] - delta];

		if (flag == 0) {
			int half = delta >> 1;
			ptr[-2 * stride] = BFME_CLAMP_ZERO[ptr[-2 * stride] + half];
			ptr[stride] = BFME_CLAMP_ZERO[ptr[stride] - half];
		}

		++ptr;
	}
}
