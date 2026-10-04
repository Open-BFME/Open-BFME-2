// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva003F5BDB@Rva003F498A@@QAEXPAXPAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@Z @0x003F5BDB 116B: Rva003F498A filter via rva003F4DEE and pred 0x003F3F83 into ScienceType vector; callers at 0x00217116; erase and push_back rowed; size via sar 2 and unsigned jb loop
#include <vector>

enum ScienceType
{
	SCIENCE_0 = 0
};

struct Rva003F3F83
{
	int rva003F3F83();
};

struct Rva003F5BDBElem
{
	char m_pad00[0x20];
	ScienceType m_20;
	char m_pad24[0x78 - 0x24];
	Rva003F3F83 *m_78;
};

struct Rva003F5BDBRet
{
	void *m_00;
	_STL::vector<Rva003F5BDBElem *> m_04;
};

class Rva003F498A
{
public:
	void *rva003F4DEE(void *p);
	void rva003F5BDB(void *a, _STL::vector<ScienceType> *out);
};

void Rva003F498A::rva003F5BDB(void *a, _STL::vector<ScienceType> *out)
{
	out->erase(out->begin(), out->end());
	Rva003F5BDBRet *r = (Rva003F5BDBRet *)rva003F4DEE(a);
	if (r == 0)
		return;
	for (unsigned int i = 0; i < r->m_04.size(); ++i)
	{
		Rva003F5BDBElem *e = r->m_04[i];
		if ((char)e->m_78->rva003F3F83())
		{
			ScienceType tmp = e->m_20;
			out->push_back(tmp);
		}
	}
}
