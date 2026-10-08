// ?rva001DF1A4@Rva001DF1A4@@QAEXXZ
// partial score=0.9 date=2026-10-08
// cl: /DNDEBUG /MD /EHsc
// ?rva001DF1A4@Rva001DF1A4@@QAEXXZ 0x001DF1A4 120B. Resets this object: two
// member calls on argument buffers, a count of 48-byte records, a call on the
// element vector at +0x5C with that count, one virtual-free call on +0x10,
// a per-element call over the 0x34-byte records, then the flag and value reset.
class Rva001DF1A4A
{
public:
	void rva001DEF89(void *arg);
	char *m_begin; // +0x00 (vector-like: begin, end)
	char *m_end; // +0x04
	char m_pad08[4];
};

class Rva001DF1A4B
{
public:
	void rva001DE3E3(void *arg);
	unsigned char m_pad00[0x14];
};

class Rva001DF1A4C
{
public:
	void rva001DEE92(int count);
	char *m_begin; // +0x00
	char *m_end; // +0x04
};

class Rva001DF1A4D
{
public:
	void rva001DD846();
	unsigned char m_pad00[0x0C];
};

class Rva001DF1A4E
{
public:
	void rva001DCD3C();
};

class Rva001DF1A4F
{
public:
	void rva0023DAA5();
	int m_value;
};

class Rva001DF1A4
{
public:
	void rva001DF1A4();
private:
	unsigned char m_pad00[0x10];
	Rva001DF1A4D m10; // +0x10
	Rva001DF1A4A m1C; // +0x1C
	unsigned char m28[0x0C]; // +0x28 argument buffer
	Rva001DF1A4B m34; // +0x34
	unsigned char m48[0x14]; // +0x48 argument buffer
	Rva001DF1A4C m5C; // +0x5C
	unsigned char m64[4];
	Rva001DF1A4F m68; // +0x68
	int m6C; // +0x6C
	int m70; // +0x70
	int m74; // +0x74
	int m78; // +0x78
	unsigned char m7C; // +0x7C
};

void Rva001DF1A4::rva001DF1A4()
{
	Rva001DF1A4A *a = &m1C;
	a->rva001DEF89(m28);
	m34.rva001DE3E3(m48);
	int count = (int)(a->m_end - a->m_begin) / 48;
	m5C.rva001DEE92(count);
	m10.rva001DD846();
	Rva001DF1A4C *c = &m5C;
	char *end = c->m_end;
	for (char *p = c->m_begin; p != end; p += 0x34)
		reinterpret_cast<Rva001DF1A4E *>(p)->rva001DCD3C();
	if (m78 == 0)
		m74 = 1;
	m7C = 1;
	m68.rva0023DAA5();
	m6C = m68.m_value;
	m70 = 0;
}
