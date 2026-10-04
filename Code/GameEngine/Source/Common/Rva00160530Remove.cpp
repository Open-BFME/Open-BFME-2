// cl: /O1 /Ob0
// ?rva004F0372@Rva00160530@@QAEXPAPAV1@@Z @0x004F0372 48B. Doubly-linked remove with head update.
// Evidence: prev/next list nodes with +4/+8 plus set() insert twin plus caller 0x004F0426 plus unblocks 0x004F040F.
class Rva00160530
{
	Rva00160530 *m_00;
	Rva00160530 *m_04;
	Rva00160530 *m_08;

public:
	void rva004F0372(Rva00160530 **p);
};

void Rva00160530::rva004F0372(Rva00160530 **p)
{
	if (m_08)
		m_08->m_04 = m_04;
	if (m_04)
		m_04->m_08 = m_08;
	else
		*p = m_08;
	m_04 = 0;
	m_08 = 0;
}
