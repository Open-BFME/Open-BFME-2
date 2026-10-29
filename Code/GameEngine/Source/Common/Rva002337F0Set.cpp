// cl: /Ob0

struct Rva002337F0Blk
{
	int a;
	int b;
	int c;
	int d;
	char e;
	int f;
	int g;
};

class Rva002337F0
{
	Rva002337F0Blk m;

public:
	Rva002337F0 &set(const Rva002337F0Blk *p);
};

Rva002337F0 &Rva002337F0::set(const Rva002337F0Blk *p)
{
	m.a = p->a;
	m.b = p->b;
	m.c = p->c;
	m.d = p->d;
	m.e = p->e;
	m.f = p->f;
	m.g = p->g;
	return *this;
}

// StlSweepW4Rva00584405.cpp's vector element: the same 28-byte record, whose
// out-of-line copy constructor retail ICF-folded with set above (both copy
// the seven fields and return the receiver).
struct Rva00584405Element
{
	Rva002337F0Blk m;
	Rva00584405Element(const Rva00584405Element &other);
};

Rva00584405Element::Rva00584405Element(const Rva00584405Element &other)
{
	m.a = other.m.a;
	m.b = other.m.b;
	m.c = other.m.c;
	m.d = other.m.d;
	m.e = other.m.e;
	m.f = other.m.f;
	m.g = other.m.g;
}
