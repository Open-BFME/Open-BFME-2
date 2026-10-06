// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002C752F@Rva002C752F@@QAEXXZ @0x002C752F, 134B.
// Six-slot clear: zeroes bitset at +0x04 (0x10), tail bytes/dword at
// +0x35C/+0x35D/+0x360/+0x364, then per slot sets dword at +0x2C to -1
// and memsets 0x1C at +0x44, 0x1C at +0xEC, 0x4C at +0x194.
// Evidence: neighbour WeaponSetRva002C75D1 proves +0x2C autoChooseMask[6]
// and next array at +0x44; caller 0x0033A888 constructs the same three
// arrays (0x1C/0x1C/0x4C via 0x24C7B3/0x42526) then calls here.
#pragma function(memset)

extern "C" void *memset(void *dst, int value, unsigned int size);

struct Rva002C752F_1C
{
	unsigned char data[0x1C];
};

struct Rva002C752F_4C
{
	unsigned char data[0x4C];
};

class Rva002C752F
{
public:
	void rva002C752F();

private:
	char m_pad0[4];
	unsigned char m_04[0x10];
	const void *m_tmpl[6];
	int m_mask[6];
	Rva002C752F_1C m_a[6];
	Rva002C752F_1C m_b[6];
	Rva002C752F_4C m_c[6];
	unsigned char m_35C;
	unsigned char m_35D;
	char m_pad35E[2];
	int m_360;
	unsigned char m_364;
};

void Rva002C752F::rva002C752F()
{
	m_35C = 0;
	m_35D = 0;
	m_364 = 0;
	m_360 = 0;
	memset(m_04, 0, 0x10);
	for (int i = 0; i < 6; ++i) {
		m_tmpl[i] = 0;
		m_mask[i] = -1;
		memset(&m_a[i], 0, 0x1C);
		memset(&m_b[i], 0, 0x1C);
		memset(&m_c[i], 0, 0x4C);
	}
}
