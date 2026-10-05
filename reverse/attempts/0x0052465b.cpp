// ?rva0052465B@RvaOwner0052465B@@QAEXABVOpen2Elem063700@@PAURvaTarget00217D4C@@@Z
// partial score=0.45 date=2026-10-05
// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>

class Open2Elem063700
{
	int m_00;
};

struct RvaTarget00217D4C
{
	int m_00;
	int m_ref;
	void rva0007DEEF();
};

struct RvaHook0052465B
{
	void rva002244D2(const Open2Elem063700 &o);
};

extern RvaHook0052465B *g_hook0052465B;

class RvaGuard0052465B
{
	RvaTarget00217D4C *m_p;
public:
	RvaGuard0052465B(RvaTarget00217D4C *p) : m_p(p) {}
	~RvaGuard0052465B();
};

class RvaOwner0052465B : public _STL::vector<Open2Elem063700>
{
public:
	void rva0052465B(const Open2Elem063700 &o, RvaTarget00217D4C *t);
};

void RvaOwner0052465B::rva0052465B(const Open2Elem063700 &o, RvaTarget00217D4C *t)
{
	RvaGuard0052465B guard(t);
	if (g_hook0052465B != 0) {
		if (t != 0)
			++t->m_ref;
		g_hook0052465B->rva002244D2(o);
		this->push_back(o);
	}
	if (t != 0)
		t->rva0007DEEF();
}
