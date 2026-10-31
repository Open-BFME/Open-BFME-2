// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b9040.md plus retail only. No
// decoder source was consulted.
//
// VP6_DeleteFragmentInfo retail 0x001B9040 (248 bytes): frees each raw
// allocation of the decoder instance when non-null, in the order 0x0, 0x14C,
// 0x118, 0x11C, 0x120, 0x6F8, 0x700, 0x6FC, zeroing the raw pointer and its
// aligned twin right after each free.

void bfmeFreeOneJT(void *block);                 // 0x001B6410 duck_free

struct FragmentInfoInstance
{
	void *m_00;
	void *m_04;
	unsigned char m_pad08[4];
	void *m_0c;
	void *m_10;
	unsigned char m_pad14[0xF8];
	void *m_10c;
	void *m_110;
	void *m_114;
	void *m_118;
	void *m_11c;
	void *m_120;
	unsigned char m_pad124[0x24];
	void *m_148;
	void *m_14c;
	unsigned char m_pad150[0x59C];
	void *m_6ec;
	void *m_6f0;
	void *m_6f4;
	void *m_6f8;
	void *m_6fc;
	void *m_700;
};

extern "C" void __cdecl VP6_DeleteFragmentInfo(void *fragmentInfo)
{
	FragmentInfoInstance *state = (FragmentInfoInstance *)fragmentInfo;

	if (state->m_00 != 0)
		bfmeFreeOneJT(state->m_00);
	state->m_00 = 0;
	state->m_04 = 0;

	if (state->m_14c != 0)
		bfmeFreeOneJT(state->m_14c);
	state->m_14c = 0;
	state->m_148 = 0;

	if (state->m_118 != 0)
		bfmeFreeOneJT(state->m_118);
	state->m_118 = 0;
	state->m_10c = 0;

	if (state->m_11c != 0)
		bfmeFreeOneJT(state->m_11c);
	state->m_11c = 0;
	state->m_110 = 0;

	if (state->m_120 != 0)
		bfmeFreeOneJT(state->m_120);
	state->m_120 = 0;
	state->m_114 = 0;

	if (state->m_6f8 != 0)
		bfmeFreeOneJT(state->m_6f8);
	state->m_6f8 = 0;
	state->m_6ec = 0;

	if (state->m_700 != 0)
		bfmeFreeOneJT(state->m_700);
	state->m_700 = 0;
	state->m_6f4 = 0;

	if (state->m_6fc != 0)
		bfmeFreeOneJT(state->m_6fc);
	state->m_6fc = 0;
	state->m_6f0 = 0;
}
