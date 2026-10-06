// ??0Rva00540D94@@QAE@ABURva00540E9DSrc@@MMH@Z
// cl: /Ob0
//
// ??0Rva00540D94@@QAE@ABURva00540E9DSrc@@MMH@Z, retail 0x00540D94, 54 bytes.
// Constructor: int at +0 = v; the 12-byte Rva00540E9DSrc at +4..+0xC copied
// field-by-field; floats at +0x10 +0x14 = f1/f2. Evidence: sibling ctors in
// Rva00540E82Init.cpp (same 12-byte src at +4, same float pair), callers at
// 0x00540FFE/0x00542351.
//
// The explicit int-pointer copy is load-bearing: spelling the three fields as
// `m_04.a = src.a; m_04.b = src.b; m_04.c = src.c;` lets MSVC sink the final
// word load past the +0x10 float store (target keeps the +0xC store before the
// +0x10 store), while writing them through int lvalues keeps the source and
// destination words in one contiguous run. `m_04 = src` instead emits a
// `movs` 12-byte block copy and loses the shape.

struct Rva00540E9DSrc
{
	int a;
	int b;
	int c;
};

class Rva00540D94
{
public:
	Rva00540D94(const Rva00540E9DSrc &src, float f1, float f2, int v);
	int m_00;
	Rva00540E9DSrc m_04;
	float m_10;
	float m_14;
};

Rva00540D94::Rva00540D94(const Rva00540E9DSrc &src, float f1, float f2, int v)
{
	m_00 = v;
	int *dst = &m_04.a;
	const int *s = &src.a;
	dst[0] = s[0];
	dst[1] = s[1];
	dst[2] = s[2];
	m_10 = f1;
	m_14 = f2;
}
