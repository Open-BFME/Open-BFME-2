// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002E0BEB@Rva002E0BEB@@QAEXPAX@Z @0x002E0BEB 64B copy two-wide then conditional add
// Evidence: callees rowed 0x002E077F operator= and 0x0020E250 six-int add; callers 0x0020E68A 0x0020F538; neighbours 0x002E0A0A copy ctor and 0x002E0CD4 getter share /O1
class Rva002E077F
{
public:
	Rva002E077F &operator=(const Rva002E077F &src);
	virtual ~Rva002E077F();
private:
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
};

class Rva0020E449
{
public:
	void rva0020E250(const Rva0020E449 &other);
private:
	char m_pad[4];
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
};

struct Rva002E0BEBInner
{
	char m_pad[0x8c];
	Rva0020E449 m_8c;
	char m_pad2[0x94];
	int m_13c;
};

struct Rva002E0BEBArg
{
	char m_pad[0x24];
	Rva002E0BEBInner *m_24;
};

class Rva002E0BEB
{
public:
	void rva002E0BEB(void *arg);
private:
	char m_pad0[0x14];
	int m_14;
	char m_pad1[0x240];
	Rva002E077F m_258;
	Rva002E077F m_274;
};

void Rva002E0BEB::rva002E0BEB(void *arg)
{
	m_274 = m_258;
	Rva002E0BEBArg *p = (Rva002E0BEBArg *)arg;
	if (p == 0)
		return;
	Rva002E0BEBInner *inner = p->m_24;
	if (inner->m_13c != m_14)
		return;
	((Rva0020E449 *)&m_274)->rva0020E250(inner->m_8c);
}
