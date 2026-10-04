// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva003F5DBD@Rva003F5DBD@@QAEXPAXH@Z @0x003F5DBD 130B: element science push_back via rowed 0x002E01C6 plus inner vector loop via rowed 0x002B7250 plus erase via rowed 0x003F5C72; callers at 0x003F5E7A; class from this+4 vector and this+10 ScienceType vector
#include <vector>

enum ScienceType
{
	SCIENCE_0 = 0
};

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

struct SciSrc
{
	char m_pad00[0x14];
	ScienceType m_14;
};

struct Gen_p48cd
{
	void *m_00;
	_STL::vector<void *> m_04;
	char m_pad10[0x30 - 4 - 12];
};

class Rva003F5DBD
{
	char m_pad00[4];
	_STL::vector<Gen_p48cd> m_04;
	_STL::vector<ScienceType> m_10;
public:
	void rva003F5DBD(void *a, int idx);
	void rva003F5E3F(void *a, void *key);
};

void Rva003F5DBD::rva003F5DBD(void *a, int idx)
{
	Gen_p48cd &e = m_04[idx];
	if (e.m_00 != 0)
	{
		ScienceType tmp = ((SciSrc *)e.m_00)->m_14;
		m_10.push_back(tmp);
	}
	int cnt = (int)e.m_04.size();
	CreateAHeroData *v;
	int i = 0;
	if (i < cnt)
	{
		v = a ? (CreateAHeroData *)((char *)a + 4) : 0;
		for (; i < cnt; ++i)
		{
			void *p = e.m_04[i];
			((Rva002B7250 *)((char *)p + 8))->rva002B7250(v);
		}
	}
	m_04.erase(m_04.begin() + idx);
}

void Rva003F5DBD::rva003F5E3F(void *a, void *key)
{
	for (unsigned int i = 0; i < m_04.size(); ++i)
	{
		if (m_04[i].m_00 == key)
		{
			rva003F5DBD(a, (int)i);
			return;
		}
	}
}
