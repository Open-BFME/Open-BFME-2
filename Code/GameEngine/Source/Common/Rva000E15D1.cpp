// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// @0x000E15D1 134B. Build a 16-byte record from the two counts, then
// walk y * cols + x through the 0xD4 stride.

struct Rva000E15D1Rec
{
	int m_a;
	int m_b;
	int m_c;
	int m_d;
};

class Rva00115044El
{
public:
	void rva00115044(Rva000E15D1Rec *rec, int value, int mode, unsigned char flag);
};

class Rva000E15D1
{
public:
	void rva000E153A();
	void rva000E15D1();

	char m_pad0[0x37C0];
	int m_at37C0;
	char m_pad37C4[0x37E0 - 0x37C4];
	unsigned char m_at37E0;
	char m_pad37E1[0x3888 - 0x37E1];
	char *m_base;
	char m_pad388C[4];
	int m_at3890;
	int m_at3894;
};

void Rva000E15D1::rva000E15D1()
{
	rva000E153A();
	int cols = m_at3890;
	Rva000E15D1Rec rec;
	rec.m_c = cols << 4;
	rec.m_a = 0;
	rec.m_b = 0;
	rec.m_d = m_at3894 << 4;
	if (cols <= 0)
		return;
	for (int x = 0; x < m_at3890; ++x)
	{
		for (int y = 0; y < m_at3894; ++y)
		{
			Rva00115044El *el =
				(Rva00115044El *)(m_base + (y * m_at3890 + x) * 0xD4);
			el->rva00115044(&rec, m_at37C0, 1, m_at37E0);
		}
	}
}
