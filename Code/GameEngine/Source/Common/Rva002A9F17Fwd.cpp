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
};
extern Rva00421520 *g_00E03158;

class Rva002A9F17
{
public:
	void rva002A9F17(const StringBase<char> *name);
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

// g_00E03158: matched references place it at VA 0xe03158 (retail value 0).
class Rva00421520 *g_00E03158 = 0;
