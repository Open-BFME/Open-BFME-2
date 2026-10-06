// ?Rva00527827@Holder00527827@@QAEXHPAMHH@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /arch:SSE /MD
// Range-27 mode-dispatched float clamp.
// ?Rva00527827@Holder00527827@@QAEXHPAMHH@Z @0x00527827 87B
// Thiscall (a0, a1, a2, a3; only a0/a1 used): mode m_C == 1 converts
// *a1 plus g_00BC26F0 to int through the dead arg slots and clamps at
// least 1 into m_18; mode 3/4 runs the pinned 0x005CC208 slot forwarder
// (thiscall on m_1C with a0/a1, ecx flows through) when m_1C is set.
extern const float g_00BC26F0;

struct Obj00527827
{
	void Rva005CC208(int a0, int a1);
};

struct Holder00527827
{
	char m_pad[0xC];
	int m_C;
	int m_10;
	int m_14;
	int m_18;
	Obj00527827 *m_1C;
	void Rva00527827(int a0, float *a1, int a2, int a3);
};

void Holder00527827::Rva00527827(int a0, float *a1, int a2, int a3)
{
	int one = 1;
	if (m_C == one)
	{
		int one;
		int i = (int)(*a1 + g_00BC26F0);
		int *p;
		one = 1;
		p = &one;
		if (i >= one)
			p = &i;
		m_18 = *p;
	}
	else if (m_C == 3 || m_C == 4)
	{
		if (m_1C != 0)
			m_1C->Rva005CC208(a0, (int)a1);
	}
}
