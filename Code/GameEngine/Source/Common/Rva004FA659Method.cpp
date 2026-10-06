// cl: /MD
// ?rva004FA659@Rva004FA659@@QAEXXZ @0x004FA659 19B: thiscall, compares dwords
// at +0x20/+0x24, forwards (m_20 != m_24) as unsigned char to member at +4
// via rowed Rva004E060C::rva004E060C. Callers at 0x004FAA52/0x004FABC2/
// 0x004FAEF7 unclaimed so owner is honest-address Rva004FA659. Neighbour
// Rva004FA830Ctor.cpp carries // cl: /O1 /MD.
class Rva004E060C
{
public:
	void rva004E060C(unsigned char v);
};

class Rva004FA659
{
public:
	void rva004FA659();

private:
	char m_pad0[4];
	Rva004E060C *m_4;
	char m_pad8[0x20 - 8];
	int m_20;
	int m_24;
};

void Rva004FA659::rva004FA659()
{
	m_4->rva004E060C(m_20 != m_24);
}
