// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??0Rva00382FA7@@QAE@ABU0@@Z, retail 0x00382FA7, 295 bytes.
// Copy ctor with vptr, UnicodeString at +0x04, ints/bytes, two rep-movsd
// int blocks at +0x18[8] and +0x60[10], AsciiString at +0x40, ints, byte,
// nested Rva00382574 at +0x90 via its rowed copy, tail ints and 4-dword block
// at +0xcc. Identity from chain (calls 0x00382574 just landed) and caller
// 0x0038360A plus vtable 0xC193C8.
#include "ascii_string.h"


#include "unicode_string.h"

struct Rva00382574
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	AsciiString m_10;
	AsciiString m_14;
	AsciiString m_18;
	AsciiString m_1c;
	AsciiString m_20;
	AsciiString m_24;
	AsciiString m_28;
	bool m_2c;

	Rva00382574(const Rva00382574 &other);
};

struct IntBlock8 { int v[8]; };
struct IntBlock10 { int v[10]; };
struct IntBlock4 { int v[4]; };

class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};

struct Rva00382FA7 : public EmptyBase
{
	virtual ~Rva00382FA7();
	UnicodeString m_04;
	int m_08;
	int m_0c;
	unsigned char m_10;
	unsigned char m_11;
	unsigned char m_12;
	int m_14;
	IntBlock8 m_18;
	int m_38;
	int m_3c;
	AsciiString m_40;
	int m_44;
	int m_48;
	int m_4c;
	int m_50;
	int m_54;
	int m_58;
	int m_5c;
	IntBlock10 m_60;
	int m_88;
	unsigned char m_8c;
	Rva00382574 m_90;
	int m_c0;
	int m_c4;
	int m_c8;
	IntBlock4 m_cc;

	Rva00382FA7(const Rva00382FA7 &other);
};

Rva00382FA7::Rva00382FA7(const Rva00382FA7 &other)
	: EmptyBase()
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0c(other.m_0c)
	, m_10(other.m_10)
	, m_11(other.m_11)
	, m_12(other.m_12)
	, m_14(other.m_14)
	, m_18(other.m_18)
	, m_38(other.m_38)
	, m_3c(other.m_3c)
	, m_40(other.m_40)
	, m_44(other.m_44)
	, m_48(other.m_48)
	, m_4c(other.m_4c)
	, m_50(other.m_50)
	, m_54(other.m_54)
	, m_58(other.m_58)
	, m_5c(other.m_5c)
	, m_60(other.m_60)
	, m_88(other.m_88)
	, m_8c(other.m_8c)
	, m_90(other.m_90)
	, m_c0(other.m_c0)
	, m_c4(other.m_c4)
	, m_c8(other.m_c8)
	, m_cc(other.m_cc)
{
}
