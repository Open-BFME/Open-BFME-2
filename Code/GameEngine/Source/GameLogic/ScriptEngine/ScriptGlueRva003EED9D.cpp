// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
//
// ?rva003EED9D@Rva003EED9D@@QAEXXZ @0x003EED9D 57B (dump range 18).
// Guarded forward: bails when this+4 is set, otherwise copies the
// this+0x1C name through the rowed StringBase copy ctor into the pinned
// 0x003EEC63 (this+4, name, 0, 0) call (doSetTeamState argument idiom),
// then tail-jumps the pinned 0x004E3B78 member on this+8.
#include "ascii_string.h"

class Rva003EEC63
{
public:
	void rva003EEC63(void *p, AsciiString s, int a, int b);
};
class Rva004E3B78
{
public:
	void rva004E3B78();
};

class Rva003EED9D
{
public:
	void rva003EED9D();
private:
	char m_pad00[0x04];
	void *m_p04; // +0x04
	char m_pad08[0x14];
	AsciiString m_name1C; // +0x1C
};

void Rva003EED9D::rva003EED9D()
{
	if (m_p04 != 0)
		return;
	((Rva003EEC63 *)this)->rva003EEC63((char *)this + 4, m_name1C, 0, 0);
	((Rva004E3B78 *)((char *)this + 8))->rva004E3B78();
}
