// cl: /DNDEBUG /MD /EHsc
//
// Ported from Open-BFME-1's game/GameEngine/Source/Common/AddressTinyBodiesD0083FDF0.cpp
// (donor revision: reference/open-bfme-1 @ a38d345e) by tools/bfme1_sweep.py.
// The donor is a set of address-derived owners for small complete bodies, and
// it is held at copy-tier S: the sweep placed 3 of its bodies, so
// find_declared_unmatched refused the whole file. This TU carries those 3.
//
//   0x0073B490  32B  Rva008F8E40Quad::Rva008F8E40Quad(int, int, int, int)
//   0x006FBA50  32B  Rva008C44F0Body::body(int)
//   0x007095F0  20B  Rva008C4510Body::body(int) const
//
// The donor's own comments give the retail shape of each body ("0x008C44F0:
// set bit 9 of the dword at +0x1C from a flag", "0x008C4510: test bit n of the
// signed word at +0xA", "0x008F8E40: four-dword constructor; the second slot
// takes the last argument"). The member names stay as the donor wrote them
// because they describe what the bytes read and write, nothing more. No pin is
// needed: none of the three reaches a global or a callee.

// ?body@Rva008C4510Body@@QBEHH@Z -- 0x007095F0
class Rva008C4510Body
{
public:
	int body(int bitIndex) const;

private:
	char m_pad[0xA];
	short m_bits;
};

int Rva008C4510Body::body(int bitIndex) const
{
	return m_bits & (1 << bitIndex);
}

// ?body@Rva008C44F0Body@@QAEXH@Z -- 0x006FBA50
class Rva008C44F0Body
{
public:
	void body(int enable);

private:
	char m_pad[0x1C];
	unsigned int m_low9 : 9;
	unsigned int m_flag9 : 1;
};

void Rva008C44F0Body::body(int enable)
{
	m_flag9 = enable != 0;
}

// ??0Rva008F8E40Quad@@QAE@HHHH@Z -- 0x0073B490
class Rva008F8E40Quad
{
public:
	Rva008F8E40Quad(int a, int b, int c, int d);

private:
	int m_a;
	int m_d;
	int m_b;
	int m_c;
};

Rva008F8E40Quad::Rva008F8E40Quad(int a, int b, int c, int d)
	: m_a(a), m_d(d), m_b(b), m_c(c)
{
}
