// cl: /O1 /MD
struct Coord3D;
#include "Thing/thing.h"
// Native 002763E6 is the existing Drawable position accessor.
class Drawable
{
public:
	const Coord3D *getPosition() const;
	bool calcPitchRoll(void *a, void *b, void *c, void *d, int e, int f);	// 0x00270276
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
				void *r1 = (void *)((const Drawable *)this)->getPosition();
				const Coord3D *r2 = ((const Thing *)this)->getUnitDirectionVector2D();
				return ((Drawable *)this)->calcPitchRoll(mid, s, r1, (void *)r2, a, b);
			}
		}
	}
	return false;
}
