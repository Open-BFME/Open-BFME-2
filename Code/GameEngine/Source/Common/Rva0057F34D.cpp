// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0057F34D@Rva0057F34D@@QAEXXZ @0x0057F34D 92B
// Evidence: unlock lane, caller 0x0043DE4C in 0x0043DE19 (ecx=esi+0x190 subobject), rowed clear 0x0052493F on this, literal AptMpClans::InitGadgets via pin 0x0041149A, stores +0xA8 +0xA0 +0xA4.
#include "ascii_string.h"

class Rva0052493F
{
public:
	void rva0052493F();
};

void _bfme_closeAptScreen(const AsciiString &name);

class Rva0057F34D
{
public:
	void rva0057F34D();
private:
	char m_pad[160];
	int m_a0;
	int m_a4;
	unsigned char m_a8;
};

void Rva0057F34D::rva0057F34D()
{
	m_a8 = 0;
	((Rva0052493F *)this)->rva0052493F();
	_bfme_closeAptScreen(AsciiString("AptMpClans::InitGadgets"));
	m_a0 = 0;
	m_a4 = 0;
}
