// flags: region default (reverse/retail_inventory/flag_regions.csv)
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

class BfmeGridWM
{
public:
	void walk();
	void cell(int x, int y);
	unsigned char rva000AE18D(int x, int y);

private:
	int m_pad0;
	int m_pad1;
	int m_w;
	int m_h;
	char m_pad10[0x24];
	int m_34;
	char m_pad38[0x30];
	unsigned char *m_data;
	unsigned char *m_dataEnd;
};

void BfmeGridWM::walk()
{
	for (int x = 0; x < m_w - 1; ++x)
		for (int y = 0; y < m_h - 1; ++y)
			cell(x, y);
}

unsigned char BfmeGridWM::rva000AE18D(int x, int y)
{
	if (x < 0 || y < 0 || y >= m_h || x >= m_w)
		return 0;
	int byteIdx = m_34 * y + (x >> 3);
	if ((unsigned int)byteIdx >= (unsigned int)(m_dataEnd - m_data))
		return 0;
	_ReadWriteBarrier();
	unsigned int mask = 1u << (x & 7);
	return (m_data[byteIdx] & mask) != 0;
}
