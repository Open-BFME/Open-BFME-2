// cl: /O1 /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// ?rva000ABD19@Rva000ABD19@@QAE_NHH@Z @0x000ABD19 54B
// Unlock lane body after TileData::getRGBDataForWidth. Evidence: bounds-checked
// int-array presence test, ret 8 with two int args, offsets 0x8/0x20/0xa0/0x120e0/0x120e4.

class Rva000ABD19
{
public:
	unsigned char m_0[8];
	int m_8;
	unsigned char m_c[20];
	int m_20;
	unsigned char m_24[124];
	int *m_a0;
	unsigned char m_a4[73788];
	int m_120e0;
	int m_120e4;
	bool rva000ABD19(int a, int b);
};

bool Rva000ABD19::rva000ABD19(int a, int b)
{
	int idx = m_120e4 + b;
	idx *= m_8;
	idx += m_120e0;
	idx += a;
	if (idx >= 0) {
		if (idx < m_20)
			return m_a0[idx] != 0;
	}
	return false;
}
