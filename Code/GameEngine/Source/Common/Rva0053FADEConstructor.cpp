// ??0Rva0053FADE@@QAE@XZ
// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
//
// Retail 0x0053FAB7, 39 bytes: default constructor of the polymorphic class
// whose copy constructor is rowed at 0x0053FADE (Rva0053FADECopy.cpp; vtable
// 0x00C694DC). Base at +4 is the rowed Rva00330757Member default ctor
// 0x00330757; +0x14, the AsciiString at +0x18 and +0x20 start zero and +0x1C
// starts at 1. Identities are address-derived; the field meanings are unknown.

#include "ascii_string.h"

struct Rva00330757Member
{
	Rva00330757Member();
	~Rva00330757Member();

	char m_pad[0x10];
};

class Rva0053FADE : public Rva00330757Member
{
public:
	Rva0053FADE();
	virtual ~Rva0053FADE();

private:
	int m_14;
	AsciiString m_18;
	int m_1C;
	int m_20;
};

Rva0053FADE::Rva0053FADE() :
	m_14(0),
	m_1C(1),
	m_20(0)
{
}
