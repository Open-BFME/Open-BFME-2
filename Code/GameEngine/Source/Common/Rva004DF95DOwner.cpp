// cl: /EHsc /DNDEBUG /MD
// ?rva004DF95D@Rva004DF95DOwner@@QAEXXZ @ 0x004DF95D (35B).
// Ghidra boundary 0x004DF95D..0x004DF97F ends with a tail jump; the next
// body starts at 0x004DF980. The instructions load pointer fields at +0, +4,
// +8 and +0xC into ECX and call their no-argument methods in that order.
// The first and final two callees are already rowed at 0x005962E7 and
// 0x0025C010. The middle call targets the 5-byte thunk at 0x00596074, whose
// retail bytes jump to rowed 0x0025C010. Owner and field identities remain
// unresolved; this layout view records only the pointer offsets in the body.

class Rva005962E7
{
public:
	void rva005962E7();
};

class Rva00596074
{
public:
	void rva00596074();
};

class Rva0025C010
{
public:
	void rva0025C010();
};

class Rva004DF95DOwner
{
public:
	void rva004DF95D();

private:
	Rva005962E7 *m_field0;
	Rva00596074 *m_field4;
	Rva0025C010 *m_field8;
	Rva0025C010 *m_fieldC;
};

void Rva004DF95DOwner::rva004DF95D()
{
	m_field0->rva005962E7();
	m_field4->rva00596074();
	m_field8->rva0025C010();
	m_fieldC->rva0025C010();
}
