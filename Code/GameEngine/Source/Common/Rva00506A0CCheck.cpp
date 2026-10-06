// cl: /MD
// ?rva00506A0C@Rva00506A0C@@QAE_NPBURva00506A0COther@@@Z @0x00506A0C 40B:
// search pointer range [+4 begin +8 end] for element whose dword at +4 equals
// arg dword at +0x74; true on first hit else false. Caller 0x00506A99 tests al.
// Prev Disp getter no flags next Rva00506B1B /O1 /MD. Honest address-derived
// class plus Elem/Other views; offsets only.

struct Rva00506A0CElem
{
	int m_00;
	int m_04;
};

struct Rva00506A0COther
{
	char m_pad[0x74];
	int m_74;
};

class Rva00506A0C
{
public:
	bool rva00506A0C(const Rva00506A0COther *other);
private:
	char m_00[4];
	Rva00506A0CElem **m_04;
	Rva00506A0CElem **m_08;
};

bool Rva00506A0C::rva00506A0C(const Rva00506A0COther *other)
{
	int key = other->m_74;
	for (Rva00506A0CElem **p = m_04; p != m_08; ++p) {
		if ((*p)->m_04 == key)
			return true;
	}
	return false;
}
