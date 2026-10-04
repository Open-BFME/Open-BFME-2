// ?rva0051E4B0@Rva0051E4B0@@QAEXXZ
// partial score=0.96 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva0051E4B0@Rva0051E4B0@@QAEXXZ @0x0051E4B0 97B
// Chain via 0x005BE264; neighbours Rva0051E458PowFloat and Rva0051E939Copy.
// Evidence: thiscall reads ecx first, string AptTimeLine::RenderGraph, TheRva00222A8BTarget via 0x002246B1, this+0x218 via 0x0052493F, this+0x280 guard for 0x005BE264.
#include "ascii_string.h"

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;

class Rva002246B1
{
public:
	int rva002246B1(const AsciiString *key);
};

class Rva0052493F
{
public:
	void rva0052493F();
};

void Rva005BE264Close();

class Rva0051E4B0
{
public:
	void rva0051E4B0();
	char m_pad[0x280];
	void *m_280;
};

// ?rva0051E4B0@Rva0051E4B0@@QAEXXZ present-unmatched
void Rva0051E4B0::rva0051E4B0()
{
	{
		AsciiString s("AptTimeLine::RenderGraph");
		((Rva002246B1 *)TheRva00222A8BTarget)->rva002246B1(&s);
	}
	((Rva0052493F *)((char *)this + 0x218))->rva0052493F();
	if (m_280)
		Rva005BE264Close();
}
