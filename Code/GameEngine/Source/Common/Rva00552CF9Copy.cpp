// cl: /MD
// ?incorporate@PSPlayerAllStats@@QAEXPBV1@@Z 0x00552CF9 130B: thiscall copies fields and three sub-objects via virtuals slot 0x14 0x10 0x10; caller 0x0055941D
class Sub8
{
public:
	virtual void d0();
	virtual void d1();
	virtual void d2();
	virtual void d3();
	virtual void d4();
	virtual void copy(const Sub8 *src);
};
class Sub1B0
{
public:
	virtual void d0();
	virtual void d1();
	virtual void d2();
	virtual void d3();
	virtual void copy(const Sub1B0 *src);
};
class Sub340
{
public:
	virtual void d0();
	virtual void d1();
	virtual void d2();
	virtual void d3();
	virtual void copy(const Sub340 *src);
};
class Rva00552D7BSrc
{
public:
	Sub8 m_8_0;
	char m_pad4[0x144 - 4];
	unsigned short m_144;
	char m_pad146[0x150 - 0x146];
	int m_150;
};
class Rva00552DDASrc
{
public:
	Sub1B0 m_1B0_0;
	char m_pad4[0x144 - 4];
	unsigned short m_144;
	char m_pad146[0x150 - 0x146];
	int m_150;
};
class Rva00552E3CSrc
{
public:
	Sub340 m_340_0;
	char m_pad4[0x144 - 4];
	unsigned short m_144;
	char m_pad146[0x150 - 0x146];
	int m_150;
};
class PSPlayerAllStats
{
public:
	int m_0;
	int m_4;
	Sub8 m_8;
	char m_padC[0x14C - 0xC];
	unsigned short m_14C;
	char m_pad14E[0x158 - 0x14E];
	int m_158;
	char m_pad15C[0x1B0 - 0x15C];
	Sub1B0 m_1B0;
	char m_pad1B4[0x2F4 - 0x1B4];
	unsigned short m_2F4;
	char m_pad2F6[0x300 - 0x2F6];
	int m_300;
	char m_pad304[0x340 - 0x304];
	Sub340 m_340;
	char m_pad344[0x484 - 0x344];
	unsigned short m_484;
	char m_pad486[0x490 - 0x486];
	int m_490;
	void incorporate(const PSPlayerAllStats *src);
	void rva00552E9E(int v);
	void rva00552CB8();
	void setID(int v);
	void incorporate(const Rva00552D7BSrc *src);
	void incorporate(const Rva00552DDASrc *src);
	void incorporate(const Rva00552E3CSrc *src);
};

void PSPlayerAllStats::incorporate(const PSPlayerAllStats *src)
{
	if (m_0 && m_0 != src->m_0)
		return;
	int v = src->m_0;
	m_490 = v;
	m_300 = v;
	m_158 = v;
	m_0 = v;
	if (src->m_4 > 0)
	{
		unsigned short s = (unsigned short)src->m_4;
		m_484 = s;
		m_2F4 = s;
		m_14C = s;
		m_4 = s;
	}
	m_8.copy(&src->m_8);
	m_1B0.copy(&src->m_1B0);
	m_340.copy(&src->m_340);
}
void PSPlayerAllStats::rva00552E9E(int v)
{
	m_484 = (unsigned short)v;
	m_2F4 = (unsigned short)v;
	m_14C = (unsigned short)v;
	m_4 = (unsigned short)v;
}
void PSPlayerAllStats::rva00552CB8()
{
	m_0 = 0;
	m_4 = 0;
	m_8.d0();
	m_1B0.d0();
	m_340.d0();
}
void PSPlayerAllStats::incorporate(const Rva00552D7BSrc *src)
{
	if (m_0 && m_0 != src->m_150)
		return;
	int v = src->m_150;
	m_490 = v;
	m_300 = v;
	m_158 = v;
	m_0 = v;
	if (src->m_144 > 0)
	{
		unsigned short s = src->m_144;
		m_484 = s;
		m_2F4 = s;
		m_14C = s;
		m_4 = s;
	}
	m_8.copy(&src->m_8_0);
}
void PSPlayerAllStats::incorporate(const Rva00552DDASrc *src)
{
	if (m_0 && m_0 != src->m_150)
		return;
	int v = src->m_150;
	m_490 = v;
	m_300 = v;
	m_158 = v;
	m_0 = v;
	if (src->m_144 > 0)
	{
		unsigned short s = src->m_144;
		m_484 = s;
		m_2F4 = s;
		m_14C = s;
		m_4 = s;
	}
	m_1B0.copy(&src->m_1B0_0);
}
void PSPlayerAllStats::incorporate(const Rva00552E3CSrc *src)
{
	if (m_0 && m_0 != src->m_150)
		return;
	int v = src->m_150;
	m_490 = v;
	m_300 = v;
	m_158 = v;
	m_0 = v;
	if (src->m_144 > 0)
	{
		unsigned short s = src->m_144;
		m_484 = s;
		m_2F4 = s;
		m_14C = s;
		m_4 = s;
	}
	m_340.copy(&src->m_340_0);
}
