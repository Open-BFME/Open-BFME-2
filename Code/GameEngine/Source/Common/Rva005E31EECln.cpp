// cl: /O1 /DNDEBUG /MD
// ?rva005E31EE@Rva005E31EE@@QAEXXZ @0x005E31EE 48B cleanup loop.
// If +0x2C != -1 calls pinned 0x005E31AA (this+int void) with it then sets -1.
// Then loops 3x over +0x1C members: if non-null calls virtual +0x0C (no args).
// Ret void, this only. Address-derived.
class Rva005E31AA
{
public:
	void rva005E31AA(int a);
};

class Rva005E31EELoop
{
public:
	virtual void _s0();
	virtual void _s1();
	virtual void _s2();
	virtual void rva005E31EESlot();
};

class Rva005E31EE
{
public:
	void rva005E31EE();
protected:
	unsigned char m_pad[0x1C];
	Rva005E31EELoop *m_1C[3];
	int m_28;
	int m_2C;
};

void Rva005E31EE::rva005E31EE()
{
	int v = m_2C;
	if (v != -1)
	{
		((Rva005E31AA *)this)->rva005E31AA(v);
		m_2C = -1;
	}
	for (int i = 0; i < 3; i++)
	{
		Rva005E31EELoop *o = m_1C[i];
		if (o)
			o->rva005E31EESlot();
	}
}
