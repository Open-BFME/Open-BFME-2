// cl: /MD /EHsc
// ?rva005C436E@Rva005C436E@@QAEXH@Z retail 0x005C436E 65B
// Evidence: callers 0x005C43BE 0x005C444D unblocks 0x005C4423 plus 0x005C43AF; rowed find 0x002B51F8 plus adds 0x002E07B9 0x002E07AC; chain [esi+4]+0x24+0x13c plus switch [esi+8]+8

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern "C" const void *const vtbl_00BBB554[];  // folded, 23 classes; via ??_7BfmeBaseVUQ@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBB554=??_7BfmeBaseVUQ@@6B@")

class Rva002E2903Player;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int v, unsigned int *p);
};

class Rva002E07B9
{
public:
	void add(int v);
};

class Rva002E07AC
{
public:
	void add(int v);
};

struct Inner13C
{
	char m_pad[0x13C];
	int m_val;
};

struct Inner24
{
	char m_pad[0x24];
	Inner13C *m_ptr;
};

struct Outer08
{
	char m_pad[8];
	int m_val;
	int m_0C;
};

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc();
	virtual void loadPostProcess();
	virtual void xfer();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(((unsigned int)vtbl_00BBB554));
}

class Rva005C436E : public Snapshot
{
public:
	virtual ~Rva005C436E();
	void rva005C436E(int v);
	void rva005C43AF();
private:
	Inner24 *m_04;
	Outer08 *m_08;
	bool m_0C;
};

void Rva005C436E::rva005C436E(int v)
{
	int idx = m_04->m_ptr->m_val;
	Rva002E2903Player *p = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(idx, 0);
	if (!p)
		return;
	switch (m_08->m_val) {
	case 0:
		((Rva002E07AC *)p)->add(v);
		break;
	case 1:
		((Rva002E07B9 *)p)->add(v);
		break;
	}
}

Rva005C436E::~Rva005C436E()
{
	if (m_0C) {
		rva005C436E(-m_08->m_0C);
		m_0C = 0;
	}
}

void Rva005C436E::rva005C43AF()
{
	if (!m_0C) {
		rva005C436E(m_08->m_0C);
		m_0C = 1;
	}
}
