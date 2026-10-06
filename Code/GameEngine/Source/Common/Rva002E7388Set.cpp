// cl: /O1 /DNDEBUG /MD
//
// ?rva002E7388@Rva002E7388Owner@@QAEPAV1@HPAVRva0028CECFOwner@@HHHPAURva002E7388Pair@@HHH@Z
// @0x002E7388 76B: nine-arg setter returning this (thiscall). Stores p1..p8
// across +0x00..+0x28 (p6 pair struct dereferenced into +0x18/+0x1C, p2 kept
// for the tail call), invokes pinned 0x0028CECF on p2 into the +0x2C byte,
// returns this. The 9th arg is passed but unused (ret 0x24). Honest
// address-derived names; member identities unproven beyond the store/call
// shapes.

class Rva0028CECFOwner
{
public:
	bool rva0028CECF();
};

struct Rva002E7388Pair
{
	int m_a;
	int m_b;
};

class Rva002E7388Owner
{
public:
	Rva002E7388Owner *rva002E7388(int p1, Rva0028CECFOwner *p2, int p3, int p4,
		int p5, Rva002E7388Pair *p6, int p7, int p8, int p9);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	Rva0028CECFOwner *m_28;
	bool m_2C;
};

// ?rva002E7388@Rva002E7388Owner@@QAEPAV1@HPAVRva0028CECFOwner@@HHHPAURva002E7388Pair@@HHH@Z
Rva002E7388Owner *Rva002E7388Owner::rva002E7388(int p1, Rva0028CECFOwner *p2,
	int p3, int p4, int p5, Rva002E7388Pair *p6, int p7, int p8, int p9)
{
	m_00 = p1;
	m_04 = p3;
	m_10 = p4;
	m_14 = p5;
	m_18 = p6->m_a;
	m_1C = p6->m_b;
	m_20 = p7;
	m_24 = p8;
	m_28 = p2;
	m_2C = p2->rva0028CECF();
	return this;
}
