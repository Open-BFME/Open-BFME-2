// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: three small plain bodies near 0x167E5A (29/32/29B).
// 0x167E5A forwards (this+0xE4, int) to 0xD6A3F and returns the int;
// 0x167ED8 clamps a float at >= 0, clears a flag bit and stores it;
// 0x167EF8 copies a 12-byte record into +0xF0. Address-derived names.

class Rva000D6A3F
{
public:
	void rva000D6A3F(int n);
};
class Rva00167E5A
{
public:
	int rva00167E5A(int n);
};
class Rva00167ED8
{
public:
	void rva00167ED8(float f);
private:
	char m_pad[0x12];
	char m_flags;
	char m_pad13[0xD9];
	float m_val;
};
struct Rva00167EF8Rec
{
	int m_00;
	int m_04;
	int m_08;
};
class Rva00167EF8
{
public:
	void rva00167EF8(const Rva00167EF8Rec &src);
private:
	char m_pad[0xF0];
	Rva00167EF8Rec m_rec;
};

// ?rva00167ED8@Rva00167ED8@@QAEXM@Z
void Rva00167ED8::rva00167ED8(float f)
{
	float v = (f > 0.0f) ? f : 0.0f;
	m_flags &= ~2;
	m_val = v;
}

// ?rva00167EF8@Rva00167EF8@@QAEXABURva00167EF8Rec@@@Z
void Rva00167EF8::rva00167EF8(const Rva00167EF8Rec &src)
{
	Rva00167EF8Rec *dst = &m_rec;
	dst->m_00 = src.m_00;
	dst->m_04 = src.m_04;
	dst->m_08 = src.m_08;
}
