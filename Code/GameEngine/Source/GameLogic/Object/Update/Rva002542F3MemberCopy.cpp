// cl: /DNDEBUG /MD /GX-
// ??0Rva002542F3Member@@QAE@ABV0@@Z, retail 0x0043831C, 109 bytes.
// Copy ctor of Rva002542F3Member (default ctor rowed 0x002542F3, 0xB8 bytes).
// Layout per Rva002542F3MemberCtor.cpp: dword +0, BfmeObject872Header +4
// (rowed copy 0x002CF108), float +0x14, int +0x18, BfmeFixedStorage128 +0x1C
// (rowed copy 0x0004548B), ints +0x9C/+0xA0/+0xA4, BfmeObject872Header +0xA8.
// Callers 0x004383BA and 0x00438559. No donor: honest class name from ctor TU.
class BfmeObject872Header
{
public:
	BfmeObject872Header(const BfmeObject872Header &other);
private:
	char m_pad[0x10];
};

struct BfmeFixedStorage128
{
public:
	BfmeFixedStorage128(const struct BfmeFixedStorage128 &other);
private:
	char m_pad[0x80];
};

class Rva002542F3Member
{
public:
	Rva002542F3Member(const Rva002542F3Member &other);
private:
	int m_zero00;
	BfmeObject872Header m_bits04;
	float m_float14;
	int m_int18;
	BfmeFixedStorage128 m_buf1C;
	int m_zero9C;
	int m_zeroA0;
	int m_zeroA4;
	BfmeObject872Header m_bitsA8;
};

Rva002542F3Member::Rva002542F3Member(const Rva002542F3Member &other)
	: m_zero00(other.m_zero00)
	, m_bits04(other.m_bits04)
	, m_float14(other.m_float14)
	, m_int18(other.m_int18)
	, m_buf1C(other.m_buf1C)
	, m_zero9C(other.m_zero9C)
	, m_zeroA0(other.m_zeroA0)
	, m_zeroA4(other.m_zeroA4)
	, m_bitsA8(other.m_bitsA8)
{
}
