// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// ?rva00087AC9@Rva00087AC9@@QAEXPAURva00087AC9Pair@@0@Z @ 0x00087AC9 (43B):
// __thiscall copy of two 8-byte float-plus-int pairs from +0xC8/+0xD0 to two
// out params. Evidence: callers 0x00087AF4/0x00087B81/0x00087C55 pass stack
// locals; x87 fld/fstp plus integer mov matches /O1.

struct Rva00087AC9Pair {
	float f;
	int i;
};

class Rva00087AC9 {
	char m_pad[0xC8];
	Rva00087AC9Pair m_a;
	Rva00087AC9Pair m_b;
public:
	void rva00087AC9(Rva00087AC9Pair *o1, Rva00087AC9Pair *o2);
};

void Rva00087AC9::rva00087AC9(Rva00087AC9Pair *o1, Rva00087AC9Pair *o2)
{
	Rva00087AC9Pair &d1 = *o1;
	Rva00087AC9Pair &s1 = m_a;
	d1.f = s1.f;
	d1.i = s1.i;
	Rva00087AC9Pair &d2 = *o2;
	Rva00087AC9Pair &s2 = m_b;
	d2.f = s2.f;
	d2.i = s2.i;
}
