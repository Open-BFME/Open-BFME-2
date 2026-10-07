// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// @0x000E127B 177B. Same 0xD4 walk as 0x000E15D1. The incoming byte
// picks the element call, and +0x37C0 gates the whole walk.

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
	void rva00112259();
};

class Rva00068441
{
public:
	void rva00068441(int arg);
};

class Rva000E127B
{
public:
	void rva000E127B(int arg);

	char m_pad0[0x37C0];
	int m_at37C0;
	char m_pad37C4[0x37E0 - 0x37C4];
	unsigned char m_at37E0;
	char m_pad37E1[0x3888 - 0x37E1];
	char *m_base;
	char m_pad388C[4];
	int m_at3890;
	int m_at3894;
	char m_pad3898[0x3930 - 0x3898];
	unsigned char m_at3930;
};

void Rva000E127B::rva000E127B(int arg)
{
	((Rva00068441 *)this)->rva00068441(arg);
	if (m_at37C0 == 0)
		return;
	int cols = m_at3890;
	Rva000E15D1Rec rec;
	rec.m_c = cols << 4;
	rec.m_a = 0;
	rec.m_b = 0;
	rec.m_d = m_at3894 << 4;
	int x = 0;
	if (cols > 0)
	{
		for (; x < m_at3890; ++x)
		{
			for (int y = 0; y < m_at3894; ++y)
			{
				Rva00115044El *el =
					(Rva00115044El *)(m_base + (y * m_at3890 + x) * 0xD4);
				if ((unsigned char)arg != 0)
					el->rva00115044(&rec, m_at37C0, 0, m_at37E0);
				else
					el->rva00112259();
			}
		}
	}
	m_at3930 = 0;
}
