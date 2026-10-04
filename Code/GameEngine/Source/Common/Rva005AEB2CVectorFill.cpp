// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva005AEB2C@@QAE@XZ RVA 0x005AEB2C size 167 evidence TheGameSpyInfo virtuals 0x60/0x64 map iteration to vector push_back callers 0x005AEBD3 0x005AED3C
#include <vector>
#include <map>

struct BfmeE8
{
	void *p;
	unsigned char flag;
	char pad[3];
};

typedef _STL::map<int, int> IntMap;

class GameSpyInfoInterface
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual void d16();
	virtual void d17();
	virtual void d18();
	virtual void d19();
	virtual void d20();
	virtual void d21();
	virtual void d22();
	virtual void d23();
	virtual const IntMap *GetFirst() const;
	virtual const IntMap *GetSecond() const;
};

extern GameSpyInfoInterface *TheGameSpyInfo;

class Rva005AEB2C
{
public:
	Rva005AEB2C();
	_STL::vector<BfmeE8> m_vec;
};

Rva005AEB2C::Rva005AEB2C()
{
	if (TheGameSpyInfo)
	{
		const IntMap *a = TheGameSpyInfo->GetFirst();
		for (IntMap::const_iterator it = a->begin(); it != a->end(); ++it)
		{
			BfmeE8 e;
			e.p = (void *)&it->second;
			e.flag = 0;
			m_vec.push_back(e);
		}
		const IntMap *b = TheGameSpyInfo->GetSecond();
		for (IntMap::const_iterator it = b->begin(); it != b->end(); ++it)
		{
			BfmeE8 e;
			e.p = (void *)&it->second;
			e.flag = 1;
			m_vec.push_back(e);
		}
	}
}
