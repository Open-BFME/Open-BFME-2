// cl: /MD
//
// ?rva001F58D4@Rva001F58D4@@QAEXXZ, retail 0x001F58D4, 79 bytes.
// Reset/clear method: drains list at +0x4C via rowed rva001F4206 while +0x58
// nonzero, then zeroes +0x10..0x28 and +0x2C..0x44 plus +0x48/+0x50/+0x54/
// +0x58/+0x5C/+0x64/+0x74 and float +0x60. Callers at 0x001F637B/0x001F9DC1/
// 0x001F9ED6 pass this through. Honest Rva names; owner unknown.

class Rva001F4206
{
public:
	void rva001F4206();
};

class Rva001F58D4
{
public:
	void rva001F58D4();

private:
	char m_pad00[0x10];
	int m10[7];
	int m2c[7];
	int m48;
	void **m4c;
	int m50;
	int m54;
	int m58;
	int m5c;
	float m60;
	int m64;
	char m_pad68[12];
	int m74;
};

void Rva001F58D4::rva001F58D4()
{
	while (m58 != 0)
	{
		void **p = m4c;
		if (*p != (void *)p)
		{
			Rva001F4206 *obj = (Rva001F4206 *)((char *)m4c[0] + 8);
			obj->rva001F4206();
		}
	}
	for (int i = 0; i < 7; ++i)
	{
		m10[i] = 0;
		m2c[i] = 0;
	}
	m50 = 0;
	m54 = 0;
	m58 = 0;
	m5c = 0;
	m64 = 0;
	m74 = 0;
	m48 = 0;
	m60 = 0.0f;
}
