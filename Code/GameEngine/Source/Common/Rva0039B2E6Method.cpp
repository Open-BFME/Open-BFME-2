// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0039B2E6@Rva0039B2E6@@QAEXABURva0039B2E6Input@@@Z @0x0039B2E6 47B
// Evidence: chain from just-landed 0x39AF76; this+8/+0xC via rowed rva0039AF76 on input+0x10; +0x14/+0x18 from input+0x1C/+0x20; +0xFC via rowed rva0039B20C 0x39B20C; callers 0x420D5C 0x5DB1DD; unblocks 0x5DB145 0x420C8E.
#include "ascii_string.h"

class Rva0039AF76
{
public:
	void rva0039AF76(const AsciiString &name);
};

class Rva0039B20C
{
public:
	void rva0039B20C(void *src);
};

struct Rva0039B2E6Input
{
	char m_pad00[0x10];
	AsciiString m_str10;
	char m_pad14[0x1C - 0x14];
	int m_1C;
	int m_20;
	char m_pad24[0xFC - 0x24];
	void *m_FC;
};

class Rva0039B2E6
{
public:
	void rva0039B2E6(const Rva0039B2E6Input &input);
private:
	char m_pad00[8];
	AsciiString m_str08;
	int m_key0C;
	char m_pad10[0x14 - 0x10];
	int m_14;
	int m_18;
};

void Rva0039B2E6::rva0039B2E6(const Rva0039B2E6Input &input)
{
	((Rva0039AF76 *)this)->rva0039AF76(input.m_str10);
	m_14 = input.m_1C;
	m_18 = input.m_20;
	((Rva0039B20C *)this)->rva0039B20C(input.m_FC);
}
