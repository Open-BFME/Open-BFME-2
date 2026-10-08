// ?rva002D4A69@Rva002D4A69@@QAEXXZ
// partial score=0.9 date=2026-10-08
// cl: /DNDEBUG /MD /EHsc
// ?rva002D4A69@Rva002D4A69@@QAEXXZ 0x002D4A69 134B. Sets two scaled float
// samples from the global window manager's slot-0x40 vec2 and calls the two
// manager helpers with the object's +0x5C value, once per object (flag at +0x14).
struct Rva002D4A69Vec
{
	float x;
	float y;
};

class BfmeAptWindowManager
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2C();
	virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3C();
	virtual Rva002D4A69Vec *slot40();
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva002D4A69Obj
{
public:
	unsigned char m_pad00[0x5C];
	int m5C; // +0x5C
};

void rva002D4420(BfmeAptWindowManager *manager, int value, unsigned int id, void *a, void *b);
void rva002D44E5(BfmeAptWindowManager *manager, int value, unsigned int id, void *a, float *x, float *y);

class Rva002D4A69
{
public:
	void rva002D4A69();
private:
	unsigned char m_pad00[8];
	Rva002D4A69Obj *m_obj; // +0x08
	unsigned char m_pad0C[4];
	int m10; // +0x10
	unsigned char m14; // +0x14
	unsigned char m_pad15[3];
	int m18; // +0x18
	float m1C; // +0x1C
	float m20; // +0x20
};

void Rva002D4A69::rva002D4A69()
{
	if (!m14)
	{
		if (m_obj)
		{
			rva002D4420(g_bfmeAptWindowManager, m_obj->m5C, 0x00C02CE8, &m18, &m10);
			Rva002D4A69Vec *v = g_bfmeAptWindowManager->slot40();
			float y = m20 * v->y;
			float x;
			rva002D44E5((x = m1C * v->x, g_bfmeAptWindowManager), m_obj->m5C, 0x00C02CD8, &m18, &x, &y);
		}
		m14 = 1;
	}
}
