// cl: /MD
// ?rva003F7F30@Rva003F7F30@@QAEXXZ, retail 0x003F7F30 (27B).
// Evidence: unlock lane; caller 0x003F8090; callee ?clear@Rva002BED91@@QAEXXZ rowed; offsets 0xc=1 0x18=0 0x14 holder with clear at +0x1c.
class Rva002BED91
{
public:
	void clear();
};

struct Rva003F7F30Inner
{
	char m_00[0x1c];
	Rva002BED91 m_entry;
};

class Rva003F7F30
{
public:
	void rva003F7F30();
private:
	char m_00[0xc];
	int m_0c;
	char m_10[4];
	Rva003F7F30Inner *m_14;
	unsigned char m_18;
};

void Rva003F7F30::rva003F7F30()
{
	m_0c = 1;
	m_18 = 0;
	Rva003F7F30Inner *p = m_14;
	if (p)
		return p->m_entry.clear();
}
