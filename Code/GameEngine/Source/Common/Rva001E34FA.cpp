// cl: /MD
//
// ?rva001E34FA@Rva001E34FA@@QAEHXZ, retail 0x001E34FA, 23 bytes.
// Guarded two-level field reader: eax=[this]; if null return 1;
// ecx=[eax+8]; if null return [eax+0x18] else return [ecx+0x18].
// Called at 0x001E74A5/0x001E74B7 and 0x0026A7AE/0x0026ACCC.
// Owner identity unproven, honest Rva name.

struct Rva001E34FAInner
{
	int m_pad00[6]; // +0x00..+0x17
	int m_val18; // +0x18
};

struct Rva001E34FAOuter
{
	int m_pad00[2]; // +0x00..+0x07
	Rva001E34FAInner *m_p08; // +0x08
	int m_pad0C[3]; // +0x0C..+0x17
	int m_val18; // +0x18
};

class Rva001E34FA
{
public:
	int rva001E34FA();
private:
	Rva001E34FAOuter *m_p00;
};

int Rva001E34FA::rva001E34FA()
{
	Rva001E34FAOuter *p = m_p00;
	if (!p)
		return 1;
	Rva001E34FAInner *q = p->m_p08;
	if (q)
		return q->m_val18;
	return p->m_val18;
}

// ?rva001E3511@Rva001E3511@@QAEHXZ, retail 0x001E3511, 27 bytes.
// Sibling of 0x001E34FA: null returns 0x7fffffff, level offset 0x20.
// Called at 0x001E74C0/0x001E753A plus 10 more. Honest Rva name.

struct Rva001E3511Inner
{
	int m_pad00[8]; // +0x00..+0x1F
	int m_val20; // +0x20
};

struct Rva001E3511Outer
{
	int m_pad00[2]; // +0x00..+0x07
	Rva001E3511Inner *m_p08; // +0x08
	int m_pad0C[5]; // +0x0C..+0x1F
	int m_val20; // +0x20
};

class Rva001E3511
{
public:
	int rva001E3511();
private:
	Rva001E3511Outer *m_p00;
};

int Rva001E3511::rva001E3511()
{
	Rva001E3511Outer *p = m_p00;
	if (!p)
		return 0x7fffffff;
	Rva001E3511Inner *q = p->m_p08;
	if (q)
		return q->m_val20;
	return p->m_val20;
}
