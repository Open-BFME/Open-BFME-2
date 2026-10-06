// ?rva005FFF17Update@@YIXPAVRva005FFF17@@HHH@Z
// partial score=0.85 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// ?rva005FFF17Update@@YIXPAVRva005FFF17@@HHH@Z @0x005FFF17 75B evidence:
// fastcall updater (this, fwd-dead-in-edx, a, b): e = &m_arr[a] (stride-2
// bytes at +0x4C); if (char)b == e->m_00 return; p = m_08 else global
// 0x00BBAC1C with +8 on live path; calls pinned __cdecl-6
// ?rva00977C23@@YAXPAHPAHHPAXHH@Z @0x00977C23(&b, &a, 0x00C7A58C, p, m_04,
// g_00DFE4CC); e->m_00 = (char)b; ret 8. Same callee shape as 0x005FBAFE.
// TU-local view only.
struct Rva005FFF17Elem
{
	char m_00;
	char m_01;
};

extern int g_00DFE4CC;	// VA 0x00DFE4CC

void __cdecl rva00977C23(int *pb, int *pa, int c, void *p, int m, int g);

class Rva005FFF17
{
public:
	int m_00;
	int m_04;
	int m_08;
	char m_pad[0x4C - 0xC];
	Rva005FFF17Elem m_arr[1];
};

// ?rva005FFF17Update@@YIXPAVRva005FFF17@@HHH@Z present-unmatched
void __fastcall rva005FFF17Update(Rva005FFF17 *o, int fwd, int a, int b)
{
	int ai = a;
	int bc = b;
	Rva005FFF17Elem *e = &o->m_arr[ai];
	if ((char)bc == e->m_00)
		return;
	void *p = (void *)o->m_08;
	if (!p)
		p = (void *)0x00BBAC1C;
	else
		p = (char *)p + 8;
	rva00977C23(&b, &a, 0x00C7A58C, p, o->m_04, g_00DFE4CC);
	e->m_00 = (char)bc;
}
