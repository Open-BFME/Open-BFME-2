// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
//
// ??1Rva0029D3B0@@UAE@XZ @0x0029D3B0 75B.
// Dtor storing vtable 0x007FD1C0, releasing DisplayString slot via
// TheDisplayStringManager slot 15 when +0xC is set, then wide releaseBuffer
// on the UnicodeString at +8. Evidence: vtable store, rowed slot 15 target
// via TheDisplayStringManager, rowed wide releaseBuffer 0x00036E70.

#include "unicode_string.h"

class DisplayStringManager
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void slot15(void *p);
};

extern DisplayStringManager *TheDisplayStringManager;

class Rva0029D3B0
{
public:
	virtual ~Rva0029D3B0();
	unsigned char m_pad04[0x8 - 4];
	UnicodeString m_08; // +8
	void *m_0C; // +0xC
};

Rva0029D3B0::~Rva0029D3B0()
{
	if (m_0C != 0)
		TheDisplayStringManager->slot15(m_0C);
	m_0C = 0;
}
