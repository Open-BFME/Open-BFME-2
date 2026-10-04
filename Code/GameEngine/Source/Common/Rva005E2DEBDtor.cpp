// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva005E2DEB@@QAE@XZ @0x005E2DEB 79B
// Non-virtual dtor destroying AsciiString at +8, Rva0052413E at +0x10 and
// Rva005F8F96[3] at +0x1C via eh vector destructor. Layout from retail offsets:
// +8 releaseBuffer, +0x10 rowed Rva0052413E dtor (vector<AsciiString> holder),
// +0x1C array count 3 size 4 with rowed Rva005F8F96 dtor. Caller 0x005E30CE
// nulls [ecx] then calls here then operator delete, proving dtor.
// Evidence: unlock packet all callees rowed, prev/next same flags.
#include "ascii_string.h"

class Rva005F8F96
{
public:
	~Rva005F8F96();
private:
	void *m_00;
};

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[12];
};

class Rva005E2DEB
{
public:
	~Rva005E2DEB();
private:
	int m_00;
	int m_04;
	AsciiString m_08;
	int m_0C;
	Rva0052413E m_10;
	Rva005F8F96 m_1C[3];
};
Rva005E2DEB::~Rva005E2DEB()
{
}
