// ?rva002E6CD8@Rva002E6CD8Owner@@QAEXHEHEE@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
//
// ?rva002E6CD8@Rva002E6CD8Owner@@QAEXH0000@Z @0x002E6CD8 38B: five-field
// setter (thiscall, 5 args, void). Copies one dword + two bytes + one dword
// + one byte into +0x0/+0x4/+0x5/+0x8/+0xC in struct order. Honest
// address-derived names; field types unproven beyond byte/dword moves.

class Rva002E6CD8Owner
{
public:
	void rva002E6CD8(int a0, unsigned char a1, int a2, unsigned char a3, unsigned char a4);
private:
	int m_00;
	unsigned char m_04;
	unsigned char m_05;
	char m_pad06[2];
	int m_08;
	unsigned char m_0C;
};

// ?rva002E6CD8@Rva002E6CD8Owner@@QAEXH0000@Z
void Rva002E6CD8Owner::rva002E6CD8(int a0, unsigned char a1, int a2, unsigned char a3, unsigned char a4)
{
	m_00 = a0;
	m_04 = a1;
	m_05 = a3;
	m_08 = a2;
	m_0C = a4;
}
