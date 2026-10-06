// cl: /DNDEBUG /MD /EHsc
//
// ?Rva00468F0FInRange@@YG_NPAVObject@@0@Z, retail 0x00468F0F 89B.
// SSE range check: dx dy from +0x38 +0x3C, null guard at +0x258,
// radius at +0x1F0 +0x3C, distSq vs radiusSq via comiss.
// Caller 0x47390E, prev 0x468E26 Get, next 0x469075 setter.

class Object
{
public:
	float m_38_unused[14];
	float m_38;
	float m_3C;
	char m_pad3C[0x258 - 0x40];
	void *m_258;
};

struct Rva00468F0FOuter
{
	char m_pad[0x1F0];
	void *m_1F0;
};

struct Rva00468F0FInner
{
	char m_pad[0x3C];
	float m_3C;
};

bool __stdcall Rva00468F0FInRange(Object *a, Object *b)
{
	float dx = a->m_38 - b->m_38;
	float dy = a->m_3C - b->m_3C;
	void *p = a->m_258;
	if (p == 0)
		return false;
	float r = ((Rva00468F0FInner *)((Rva00468F0FOuter *)p)->m_1F0)->m_3C;
	float distSq = dy * dy;
	distSq = distSq + dx * dx;
	float rSq = r * r;
	return distSq < rSq;
}
