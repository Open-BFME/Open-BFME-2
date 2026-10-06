// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?rva002227DF@Rva002227DF@@QAEXXZ @0x002227DF 85B
// Unnamed Apt loader init: builds "Apt\" and "Background.apt" in place as
// by-value pair plus flags (1, 0) for vtable slot 0x50 and keeps the result
// at +0x324. Owner unknown; honest-address class and method.
// Evidence: string literals 0x007E6D48 0x007E5880 slot 0x50 member 0x324
// StringBase PBD ctor 0x00037BA0 gap same dir unlock caller 0x0023A1BB.
#include "ascii_string.h"

class Rva002227DF
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void *v20(AsciiString dir, AsciiString file, int a, int b);
	void rva002227DF();
private:
	unsigned char m_pad[0x320];
	void *m_apt;
};

void Rva002227DF::rva002227DF()
{
	m_apt = v20(AsciiString("Apt\\"), AsciiString("Background.apt"), 1, 0);
}
