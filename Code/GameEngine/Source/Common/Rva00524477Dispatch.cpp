// cl: /Ireference/shims/bfme2_ascii /MD
// Range-27 string-out-param dispatch.
// ?Rva00524477@Holder00524477@@QAEXHH@Z @0x00524477 101B
// Thiscall (a1, a2): bails when the 0x00DFE4CC singleton is null, else
// fills an 8-byte {int, AsciiString} out-block through pinned 0x0023FC23
// (AsciiString member rides uninitialized; destroyed explicitly through
// the shim inline dtor = rowed releaseBuffer 0x00036410), forwards the
// result triple through the int-returning spelling of rowed 0x005243FA
// (pinned; the body forwards 0x0052408B's eax), and on a changed m_10
// runs the singleton's pinned 0x002245FF plus m_C's pinned 0x00523EC8.
#include "ascii_string.h"

struct Out00524477
{
	int m_0;
	AsciiString m_4;
};

int Rva0023FC23(Out00524477 *out, int *a1, int a2);
int Rva005243FA(int a, int b, int c);

struct C00524477
{
	int m_0;
	void Rva00523EC8(int value);
};

struct G00524477
{
	void Rva002245FF(int a1, int a2);
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

struct Holder00524477
{
	char m_pad[0xC];
	C00524477 m_C;
	int m_10;
	void Rva00524477(int a1, int a2);
};

void Holder00524477::Rva00524477(int a1, int a2)
{
	if ((*(G00524477 **)&g_bfmeAptWindowManager) == 0)
		return;
	char buf[8];
	Out00524477 *out = (Out00524477 *)buf;
	int r = Rva0023FC23(out, &a1, a2);
	int b = m_10;
	int c = m_C.m_0;
	int rr = Rva005243FA(c, b, r);
	((AsciiString *)(buf + 4))->~AsciiString();
	if (rr == m_10)
		return;
	(*(G00524477 **)&g_bfmeAptWindowManager)->Rva002245FF(a1, a2);
	m_C.Rva00523EC8(rr);
}
