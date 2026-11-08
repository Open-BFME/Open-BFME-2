// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001c0230.md 001c0450.md 001c0690.md 001c08b0.md plus retail only.
// No decoder source was consulted.
//
// FilteringHoriz_8_C (retail 0x001C0230, 535 bytes), FilteringVert_8_C
// (0x001C0450, 563), FilteringHoriz_12_C (0x001C0690, 535) and
// FilteringVert_12_C (0x001C08B0, 563): scalar loop filters over an 8 or 12
// line strip. The correction is the sum of the outer pixel difference and
// three times the inner difference plus 4, shifted right 3, then bounded
// (kept below the limit, folded back linearly up to twice the limit, zero
// beyond, sign preserved) with the limit read from the table behind
// g_bfmeFilterLimit (retail 0x00E22CE0). Both centre taps are written back
// through the saturating clamp table whose zero point is at 0x00E23100.

extern unsigned char g_bfmeClampTable[];		// retail 0x00E23100 (zero point)
// g_bfmeFilterLimit is defined in InitPostProcessing.cpp, which sets it.
extern int g_bfmeDeringModifiers[65];
#define g_bfmeFilterLimit (*(int **)(g_bfmeDeringModifiers + 64))

// g_bfmeClampTable: matched DIR32 references place this at VA 0x00E23100
// (RVA 0x00A23100), in .data's zero-filled tail. This 0x200-byte storage
// view ends at the next known global, g_bfmeSharedJX (VA 0x00E23300).
// P35 TEST-BRANCH-ONLY diagnostic: retail's table is writable and starts 0x100 bytes below the zero point.
unsigned char g_bfmeClampTableLow[0x100] = { 0 };
unsigned char g_bfmeClampTable[0x200] = { 0 };

#define BFME_LIMIT_ADJUST(v, t)		\
	{								\
		int s1 = (v) >> 31;			\
		int s2;						\
		(v) ^= s1;					\
		(v) -= s1;					\
		(v) *= (v) < 2 * (t);		\
		(v) -= (t);					\
		s2 = (v) >> 31;				\
		(v) ^= s2;					\
		(v) -= s2;					\
		(v) = (t) - (v);			\
		(v) += s1;					\
		(v) ^= s1;					\
	}

extern "C" void __cdecl FilteringHoriz_8_C(unsigned int index, unsigned char *ptr, int stride)
{
	int t = g_bfmeFilterLimit[index];

	for (int i = 0; i < 8; ++i) {
		int v = ((ptr[-2] - ptr[1]) + 3 * (ptr[0] - ptr[-1]) + 4) >> 3;
		BFME_LIMIT_ADJUST(v, t)
		ptr[-1] = g_bfmeClampTable[ptr[-1] + v];
		ptr[0] = g_bfmeClampTable[ptr[0] - v];
		ptr += stride;
	}
}

extern "C" void __cdecl FilteringVert_8_C(unsigned int index, unsigned char *ptr, int stride)
{
	int t = g_bfmeFilterLimit[index];
	int &s = stride;

	for (int i = 0; i < 8; ++i) {
		int v = ((*(const unsigned char *)((-2 * s) + (unsigned int)ptr) - ptr[stride])
			+ 3 * (ptr[0] - ptr[-stride]) + 4) >> 3;
		BFME_LIMIT_ADJUST(v, t)
		ptr[-stride] = g_bfmeClampTable[ptr[-stride] + v];
		ptr[0] = g_bfmeClampTable[ptr[0] - v];
		++ptr;
	}
}

extern "C" void __cdecl FilteringHoriz_12_C(unsigned int index, unsigned char *ptr, int stride)
{
	int t = g_bfmeFilterLimit[index];

	for (int i = 0; i < 12; ++i) {
		int v = ((ptr[-2] - ptr[1]) + 3 * (ptr[0] - ptr[-1]) + 4) >> 3;
		BFME_LIMIT_ADJUST(v, t)
		ptr[-1] = g_bfmeClampTable[ptr[-1] + v];
		ptr[0] = g_bfmeClampTable[ptr[0] - v];
		ptr += stride;
	}
}

extern "C" void __cdecl FilteringVert_12_C(unsigned int index, unsigned char *ptr, int stride)
{
	int t = g_bfmeFilterLimit[index];
	int &s = stride;

	for (int i = 0; i < 12; ++i) {
		int v = ((*(const unsigned char *)((-2 * s) + (unsigned int)ptr) - ptr[stride])
			+ 3 * (ptr[0] - ptr[-stride]) + 4) >> 3;
		BFME_LIMIT_ADJUST(v, t)
		ptr[-stride] = g_bfmeClampTable[ptr[-stride] + v];
		ptr[0] = g_bfmeClampTable[ptr[0] - v];
		++ptr;
	}
}
