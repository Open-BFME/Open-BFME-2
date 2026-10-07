// cl: /O1 /MD
struct Coord3D;
class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
};
class Rva002763E6Aux
{
public:
	int auxValue();
};
class Rva00270276Host
{
public:
	bool rva00270276(void *a, void *b, void *c, void *d, int e, int f);
};
struct Rva00276B32Inner
{
	unsigned char m_pad[0x74];
	int m_74;
};
struct Rva00276B32Elem
{
	unsigned char m_pad[4];
	Rva00276B32Inner *m_4;
	unsigned char m_tail[0x1F0 - 8];
	void *m_1F0holder;
};
// Actually +0x1F0 holds the elem pointer; +0x258 holds this struct.
struct Rva00276B32Mid
{
	unsigned char m_pad[0x258];
	Rva00276B32Elem *m_258;
};
class Rva00276B32Host
{
public:
	bool rva00276B32(int a, int b);
private:
	unsigned char m_pad[0xFC];
	Rva00276B32Mid *m_FC;
};
// ?rva00276B32@Rva00276B32Host@@QAE_NHH@Z
bool Rva00276B32Host::rva00276B32(int a, int b)
{
	Rva00276B32Mid *mid = m_FC;
	Rva00276B32Elem *e = (mid != 0) ? mid->m_258 : 0;
	if (e != 0)
	{
		Rva00276B32Elem *s = (Rva00276B32Elem *)e->m_1F0holder;
		if (s != 0)
		{
			if (s->m_4->m_74 == 1)
			{
				void *r1 = (void *)((Rva002763E6Aux *)this)->auxValue();
				const Coord3D *r2 = ((const Thing *)this)->getUnitDirectionVector2D();
				return ((Rva00270276Host *)this)->rva00270276(mid, s, r1, (void *)r2, a, b);
			}
		}
	}
	return false;
}
