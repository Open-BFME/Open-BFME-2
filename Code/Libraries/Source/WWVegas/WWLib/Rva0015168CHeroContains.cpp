// cl: /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva0015168C@Rva0015168C@@QAE_NPAVCreateAHeroData@@@Z at 0x0015168C (53B).
// Hero-registry contains via _STL::find over inner first/last at +0x18/+0x1c
// behind outer+0/inner+0x14 guards. Evidence: find row 0x20E873,
// callers 0x52A78/0x52B5C in 0x15288F, sibling outer+0/inner+0x14 shape.

#include <algorithm>

class CreateAHeroData;

struct HeroInner
{
	char m_pad00[0x18];
	CreateAHeroData **m_first;
	CreateAHeroData **m_last;
};

struct HeroObj
{
	char m_pad00[0x14];
	HeroInner * volatile m_inner;
};

class Rva0015168C
{
public:
	bool rva0015168C(CreateAHeroData *val);
private:
	HeroObj *m_ptr;
};

bool Rva0015168C::rva0015168C(CreateAHeroData *val)
{
	HeroObj *obj = m_ptr;
	if (obj == NULL || obj->m_inner == NULL)
		return false;
	HeroInner *inner = obj->m_inner;
	CreateAHeroData **found = _STL::find(inner->m_first, inner->m_last, val);
	return found != inner->m_last;
}
