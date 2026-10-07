// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// @0x000EC9C6 135B. Early-out on the live dwords, clear the flag bytes,
// then forward this into the four rowed callees.

class Rva000EC9C6
{
public:
	void rva000EB40F();
	void rva000EB6BB();
	void rva000EBFD1();
	void rva000E663B(int arg);
	void rva000EC9C6(int arg);

	char m_pad0[0x28];
	int *m_at28;
	char m_pad2C[0x34 - 0x2C];
	int m_at34;
	int m_at38;
	char m_pad3C[0x44544 - 0x3C];
	unsigned char m_at44544;
	unsigned char m_at44545;
	char m_pad44546[0x44555 - 0x44546];
	unsigned char m_at44555;
	unsigned char m_at44556;
	char m_pad44557[0x45C5C - 0x44557];
	unsigned char m_at45C5C;
	char m_pad45C5D[0x45C64 - 0x45C5D];
	unsigned char m_at45C64;
};

void Rva000EC9C6::rva000EC9C6(int arg)
{
	if (m_at34 == 0)
		return;
	if (m_at44555 == 0)
		return;
	m_at44555 = 0;
	m_at45C5C = 0;
	if (m_at44556 != 0)
	{
		m_at44556 = 0;
		rva000EB40F();
	}
	if (m_at38 == 0)
		return;

	unsigned char *slot = &m_at44544;
	if (*slot != 0)
	{
		rva000EB6BB();
		*(volatile unsigned char *)((char *)this + 0x45C5C) = 1;
		*slot = 0;
	}
	else
	{
		slot = &m_at44545;
		if (*slot != 0 || m_at45C64 != 0)
		{
			rva000EBFD1();
			m_at45C64 = 0;
			*slot = 0;
		}
	}
	if (*m_at28 != 0)
		rva000E663B(arg);
}
