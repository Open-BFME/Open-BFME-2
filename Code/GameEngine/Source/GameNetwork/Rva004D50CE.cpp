// ?rva004D50CE@Rva004D50CE@@QAEMXZ
// partial score=0.96 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc
// ?rva004D50CE@Rva004D50CE@@QAEMXZ @0x004D50CE 68B: averages up to 30
// unsigned ints at +0x41054 (count at +0x40E6C) via x87 fild with 2^32
// fixup plus final scale via globals 0x7C26EC/0x8601E0. Called once from
// 0x25DE2E float wrapper.

extern float g_008601E0;

class Rva004D50CE
{
public:
	float rva004D50CE();

private:
	char m_pad40E6C[0x40E6C];
	int m_count;
	char m_pad41054[0x41054 - 0x40E6C - 4];
	unsigned int m_array[30];
};

float Rva004D50CE::rva004D50CE()
{
	float sum = 0.0f;
	for (int i = 0; i < 30; ++i)
	{
		if (i == m_count)
			continue;
		sum += (float)m_array[i];
	}
	return sum * g_008601E0;
}
