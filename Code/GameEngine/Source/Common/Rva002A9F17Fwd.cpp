// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva002A9F17@Rva002A9F17@@QAEXPBV?$StringBase@D@@@Z @0x002A9F17 30B forward to 0x00421520 via holder at +0x318 when global at 0x00E03158 is present
#include "ascii_string.h"

class Rva004210B0
{
public:
	char m_pad[4];
};
class Rva00421520
{
public:
	void rva00421520(Rva004210B0 *holder, const StringBase<char> *name);
	void rva00421292(Rva004210B0 *holder, const void *arg);
};
extern Rva00421520 *g_00E03158;

class Rva002A9F17
{
public:
	void rva002A9F17(const StringBase<char> *name);
	void rva002A9F35(const void *arg);
private:
	char m_pad[0x318];
	Rva004210B0 m_318;
};

void Rva002A9F17::rva002A9F17(const StringBase<char> *name)
{
	Rva00421520 *p = g_00E03158;
	if (p)
		p->rva00421520(&m_318, name);
}

// ?rva002A9F35@Rva002A9F17@@QAEXPBX@Z @0x002A9F35 30B sibling forwarder
// to 0x00421292 via holder at +0x318 when global at 0x00E03158 is
// present. Same shape as rowed 0x002A9F17; the forwarded arg is opaque
// (single push, no string evidence), so the callee pin keeps it void.
void Rva002A9F17::rva002A9F35(const void *arg)
{
	Rva00421520 *p = g_00E03158;
	if (p)
		p->rva00421292(&m_318, arg);
}

// g_00E03158: matched references place it at VA 0xe03158 (retail value 0).
class Rva00421520 *g_00E03158 = 0;
