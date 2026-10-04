// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
//
// ??1Rva005E0DC0@@QAE@XZ @0x005E0DC0 93B
// Non-virtual dtor: explicit m_04->rva005C3209 call then member dtors for
// AsciiString +0xC plus three vector wrappers +0x10 +0x1C +0x28. Evidence:
// retail EH states 3/2/1/0 with releaseBuffer last, callees rowed 0x005C3209
// 0x005242D7 0x00524349 0x0052413E plus releaseBuffer 0x00036410, callers
// at 0x005E11EB 0x005E1252, neighbours 0x005E0D94 0x005E0EE1.
#include "ascii_string.h"

class Rva005C31FB
{
public:
	void rva005C3209();
};

class Rva005242D7
{
public:
	~Rva005242D7();
private:
	char m_pad[12];
};

class Rva00524349
{
public:
	~Rva00524349();
private:
	char m_pad[12];
};

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[12];
};

class Rva005E0DC0
{
public:
	~Rva005E0DC0();
private:
	int m_00;
	Rva005C31FB *m_04;
	int m_08;
	AsciiString m_0C;
	Rva0052413E m_10;
	Rva00524349 m_1C;
	Rva005242D7 m_28;
};

Rva005E0DC0::~Rva005E0DC0()
{
	m_04->rva005C3209();
}
