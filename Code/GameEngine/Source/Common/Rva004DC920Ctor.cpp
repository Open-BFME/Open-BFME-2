// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
//
// ?rva004DC920@Rva004DC920@@QAE@XZ @0x004DC920, 205B.
// Large record ctor with three AsciiStrings at +0x00/+0x3C/+0x188 from
// AsciiString::TheEmptyString via rowed StringBase copy 0x000365F0, two
// Rva0042526Member pairs at +0x54/+0xEC via rowed vector ctor 0x00001423,
// ints/bytes zeroed and -1 flags. Layout proven by sibling dtor
// Rva004DC9EDEntryDtor.cpp (same three strings) and member ctor
// Rva0042526MemberCtor.cpp. Callers 0x004B2142 0x004DCB5B 0x004DCBDA.
#include "ascii_string.h"

class Rva0042526Member
{
public:
	Rva0042526Member();

private:
	unsigned char m_pad[0x4C];
};

class Rva004DC920
{
public:
	Rva004DC920();
	void rva004DC788(const Rva004DC920 &other);

private:
	AsciiString m_00;
	int m_04;
	unsigned char m_08;
	unsigned char m_09;
	char m_pad0A[2];
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	unsigned char m_2C;
	unsigned char m_2D;
	char m_pad2E[2];
	int m_30;
	int m_34;
	int m_38;
	AsciiString m_3C;
	int m_40;
	unsigned char m_44;
	char m_pad45[3];
	int m_48;
	int m_4C;
	int m_50;
	Rva0042526Member m_54[2];
	Rva0042526Member m_EC[2];
	unsigned char m_184;
	char m_pad185[3];
	AsciiString m_188;
	unsigned char m_18C;
	unsigned char m_18D;
	char m_pad18E[2];
};

Rva004DC920::Rva004DC920()
	: m_00(AsciiString::TheEmptyString)
	, m_04(-1)
	, m_08(0)
	, m_09(0)
	, m_0C(0)
	, m_10(0)
	, m_14(0)
	, m_18(0)
	, m_2C(0)
	, m_2D(0)
	, m_30(0)
	, m_34(0)
	, m_38(0)
	, m_3C(AsciiString::TheEmptyString)
	, m_40(0)
	, m_44(0)
	, m_48(-1)
	, m_4C(-1)
	, m_50(0)
	, m_184(0)
	, m_188(AsciiString::TheEmptyString)
{
	m_28 = -1;
	m_20 = -1;
	m_18C = 0;
	m_18D = 0;
	m_24 = 0;
	m_1C = 0;
}

void Rva004DC920::rva004DC788(const Rva004DC920 &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_09 = other.m_09;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2C = other.m_2C;
	m_2D = other.m_2D;
	m_30 = other.m_30;
	m_34 = other.m_34;
	m_38 = other.m_38;
	m_3C = other.m_3C;
	m_40 = other.m_40;
	m_44 = other.m_44;
	m_48 = other.m_48;
	m_4C = other.m_4C;
	m_50 = other.m_50;
	m_54[0] = other.m_54[0];
	m_EC[0] = other.m_EC[0];
	m_54[1] = other.m_54[1];
	m_EC[1] = other.m_EC[1];
	m_184 = other.m_184;
	m_188 = other.m_188;
}
