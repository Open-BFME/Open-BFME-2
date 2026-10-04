// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0057FECE@Rva0057FECE@@QAEXXZ @0x0057FECE 112B
// Evidence: unlock lane, caller 0x0043DE57 in 0x0043DE19 (ecx=esi+0x244 subobject), global g_Va00E06394, virtual slot 2 on +0x64 with delete, rowed clear 0x0052493F on this, literal AptMpChat::InitGadgets via pin 0x0041149A.
#include "ascii_string.h"

extern int g_Va00E06394;

class Rva0052493F
{
public:
	void rva0052493F();
};

class Rva0057FECE_P64
{
public:
	virtual ~Rva0057FECE_P64();
	virtual void f0();
	virtual void *f2(int x);
};

void operator delete(void *p);

void _bfme_closeAptScreen(const AsciiString &name);

class Rva0057FECE
{
public:
	void rva0057FECE();
private:
	char m_pad[100];
	Rva0057FECE_P64 *m_64;
	unsigned char m_68;
};

void Rva0057FECE::rva0057FECE()
{
	g_Va00E06394 = 0;
	void *p;
	if (m_64 != 0) {
		p = m_64->f2(0);
	} else {
		p = 0;
	}
	::operator delete(p);
	m_64 = 0;
	m_68 = 0;
	((Rva0052493F *)this)->rva0052493F();
	_bfme_closeAptScreen(AsciiString("AptMpChat::InitGadgets"));
}
