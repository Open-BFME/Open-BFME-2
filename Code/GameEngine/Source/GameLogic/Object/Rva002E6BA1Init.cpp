// cl: /Oi
// ?rva002E6BA1@Rva002E6BA1@@QAEXHPAUIn002E6BA1@@@Z, retail 0x002E6BA1, 65 bytes.
// Initializer copying two dwords from input plus int arg at +0x30, zeroing
// +0x08/+0x0C/words/memset +0x14 x5, masking +0x2C, zeroing +0x28, inc global
// 0x00E049D4. Caller at 0x002E8B92.
#include <string.h>
struct In002E6BA1
{
	int m_00;
	int m_04;
};

extern int TheMixFileInfoCount;

class Rva002E6BA1
{
public:
	void rva002E6BA1(int a, In002E6BA1 *b);

private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	unsigned short m_10;
	unsigned short m_12;
	int m_14[5];
	int m_28;
	int m_2C;
	int m_30;
};

void Rva002E6BA1::rva002E6BA1(int a, In002E6BA1 *b)
{
	m_30 = a;
	m_00 = b->m_00;
	m_04 = b->m_04;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_12 = 0;
	memset(m_14, 0, 20);
	m_2C &= 0xffffffe0;
	m_28 = 0;
	++TheMixFileInfoCount;
}
