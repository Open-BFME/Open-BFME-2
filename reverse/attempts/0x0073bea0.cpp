// ?rva073BEA0@Rva073BEA0Owner@@QAEXHH@Z
// partial score=0.4 date=2026-10-08
// cl: /O1 /MD /EHsc
// ?rva073BEA0@Rva073BEA0Owner@@QAEXHH@Z retail 0x0073BEA0 106B.
// Two x87 scale-and-truncate lanes (one per int argument) at the scale block
// +0x04 with a half-of-scale term, packed as a two-float point and passed to
// the object at +0x0C through its first virtual slot. Address-derived name;
// identity unproven.

typedef float Real;

struct Rva073BEA0Point
{
	Real x;
	Real y;
};

class Rva073BEA0Sink
{
public:
	virtual void slot00(const Rva073BEA0Point *p);
};

class Rva073BEA0Scale
{
public:
	char m_pad00[4];
	Real m_f04;
	Real m_f08;
	char m_pad0C[0x10];
	Real m_f1c;
};

class Rva073BEA0Owner
{
public:
	void rva073BEA0(int a, int b);

private:
	char m_pad00[4];
	Rva073BEA0Scale *m_scale; // +0x04
	char m_pad08[4];
	Rva073BEA0Sink *m_sink;   // +0x0C
};

void Rva073BEA0Owner::rva073BEA0(int a, int b)
{
	Rva073BEA0Scale *s = m_scale;
	int r1 = (int)((Real)b * s->m_f1c + s->m_f08 + s->m_f1c * 0.5);
	int r2 = (int)((Real)a * s->m_f1c + s->m_f04 + s->m_f1c * 0.5);
	Rva073BEA0Point pt;
	pt.x = (Real)r2;
	pt.y = (Real)r1;
	m_sink->slot00(&pt);
}
