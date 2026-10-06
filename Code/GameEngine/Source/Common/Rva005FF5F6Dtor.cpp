// cl: /Ireference/shims/bfme2_ascii /MD /EHs
// ??1Rva005FF5F6@@QAE@XZ retail 0x005FF5F6 99B
// Non-virtual dtor with an empty body: member dtors in reverse order under EH
// states 3..0 -- the buffer +0x30 (inline CRT free of its block), UnicodeString
// +0x2C (releaseBuffer 0x00036E70), two vector wrappers +0x18 +0x0C (rowed
// 0x005242D7 0x0052413E), then AsciiString +8 (releaseBuffer 0x00036410).
// Same shape as Rva005F1295Dtor.cpp. Names address-derived.
#include "ascii_string.h"
#include "unicode_string.h"

extern "C" void __cdecl free(void *block);

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

class Rva005FF5F6Buffer
{
public:
	~Rva005FF5F6Buffer()
	{
		if (m_data)
			free(m_data);
	}
	void *m_data;
};

class Rva005FF5F6
{
public:
	~Rva005FF5F6();
private:
	int m_00;
	int m_04;
	AsciiString m_08;
	Rva0052413E m_0C;
	Rva005242D7 m_18;
	char m_pad24[8];
	UnicodeString m_2C;
	Rva005FF5F6Buffer m_30;
};

Rva005FF5F6::~Rva005FF5F6()
{
}
