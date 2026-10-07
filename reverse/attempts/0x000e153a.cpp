// ?rva000E153A@Rva000E15D1@@QAEXXZ
// partial score=0.98 date=2026-10-07
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

#include <algorithm>

class GameLODManager
{
public:
	char m_pad00[0x1780];
	int m_at1780;
};
extern GameLODManager *TheGameLODManager;

class GlobalData
{
public:
	char m_pad00[0x49];
	unsigned char m_at49;
};
extern GlobalData *TheWritableGlobalData;

class Rva00087A93
{
public:
	struct Data
	{
		virtual void slot();
		int ref;
	};
	Data *m_data;
	~Rva00087A93()
	{
		Data *d = m_data;
		if (d && --d->ref == 0)
			d->slot();
	}
};

Rva00087A93 __cdecl Rva00152C47Create(const char *first, const char *second,
	int mode, int value);

class Rva00072A94
{
public:
	Rva00072A94 &operator=(const Rva00072A94 &other);
private:
	void *m_ptr;
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
	char m_pad3898[0x3938 - 0x3898];
	Rva00072A94 m_at3938;
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

// ?rva000E153A@Rva000E15D1@@QAEXXZ present-unmatched
// Target 0x004E153A loads GameLODManager+0x1780, gates the tier through
// GlobalData+0x49, and indexes the integer table at VA 0x00DB5550. The helper
// call and return-holder cleanup are bounded by 0x00552C47 and matched
// Rva00087A93 destructor / Rva00072A94 assignment bodies. Class identities
// beyond those address-derived views remain unknown.
void Rva000E15D1::rva000E153A()
{
	int lod = TheGameLODManager->m_at1780;
	int value = TheWritableGlobalData->m_at49 ? 2 : std::min(lod, 1);
	((Rva00072A94 *)((char *)this + 0x3938))->operator=(
		reinterpret_cast<const Rva00072A94 &>(
		Rva00152C47Create("terrain.fx", "Default", 0,
			((const int *)0x00DB5550)[value])));
}
