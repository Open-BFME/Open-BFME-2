// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva00501E3FElement@@QAE@ABU0@@Z @0x005007AA 37B: copy constructor of
// the 0x14-byte LivingWorld AI army record (GatherWorldInformation 0x0050366B
// builds one at [ebp-0x74] and push_backs it through 0x00501E3F): +0x00
// dword, +0x04 int-keyed tree copied through the pinned 0x004FFFF9, +0x10
// dword. Callers 0x00500856 (pair<const int, ...> copy), 0x00500873
// (_Construct), 0x0050366B and 0x0059DAC6. The tree member is only a call
// view of 0x004FFFF9; no other layout is claimed.

class Rva004FFFF9
{
public:
	void rva004FFFF9(const void *p);
};

struct Rva00501E3FElement
{
	Rva00501E3FElement(const Rva00501E3FElement &src);

	int m_00;		// +0x00
	Rva004FFFF9 m_04;	// +0x04
	char m_pad05[0x0B];	// +0x05..0x0F
	int m_10;		// +0x10
};

Rva00501E3FElement::Rva00501E3FElement(const Rva00501E3FElement &src)
{
	m_00 = src.m_00;
	m_04.rva004FFFF9(&src.m_04);
	m_10 = src.m_10;
}
