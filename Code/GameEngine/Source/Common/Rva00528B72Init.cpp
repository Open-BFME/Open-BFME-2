// cl: /MD
// ?rva00528B72@Rva00528B72@@QAEPAV1@PAX@Z retail 0x00528B72 38B
// Evidence: movss xmm0 [0x00BBB9AC -1.0f]; init +0 with ptr zeroes +4 +8 +0xC +0x10 float +0x14 returns this; caller 0x0052A00E
class Rva00528B72
{
public:
	Rva00528B72 *rva00528B72(void *p);
private:
	void *m_ptr;
	unsigned char m_04;
	int m_08;
	unsigned char m_0C;
	int m_10;
	float m_14;
};

Rva00528B72 *Rva00528B72::rva00528B72(void *p)
{
	m_ptr = p;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = -1.0f;
	return this;
}
