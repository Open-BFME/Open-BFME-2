// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva005F1295@@QAE@XZ retail 0x005F1295 105B
// Non-virtual dtor with an empty body: member dtors in reverse order under EH
// states 4..0 -- UnicodeString +0x40 (releaseBuffer 0x00036E70), the range
// holder +0x34 whose inline dtor runs the rowed
// ?rva005F11D0@Rva005F11D0@@QAEXXZ 0x005F11D0, three vector wrappers +0x28
// +0x1C +0x10 (rowed 0x00524265 0x005242D7 0x0052413E), then AsciiString +8
// (releaseBuffer 0x00036410). Same shape as Rva005E0DC0Dtor.cpp.
// Names address-derived.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[12];
};

class Rva005242D7
{
public:
	~Rva005242D7();
private:
	char m_pad[12];
};

class Rva00524265
{
public:
	~Rva00524265();
private:
	char m_pad[12];
};

class Rva005F11D0
{
public:
	~Rva005F11D0()
	{
		rva005F11D0();
	}
	void rva005F11D0();
private:
	char m_pad[12];
};

class Rva005F1295
{
public:
	~Rva005F1295();
private:
	int m_00;
	int m_04;
	AsciiString m_08;
	int m_0C;
	Rva0052413E m_10;
	Rva005242D7 m_1C;
	Rva00524265 m_28;
	Rva005F11D0 m_34;
	UnicodeString m_40;
};

Rva005F1295::~Rva005F1295()
{
}
