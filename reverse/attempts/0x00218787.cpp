// ?rva00218787@Rva00218787@@QAEAAMABH@Z
// partial score=0.9 date=2026-10-04
// cl: /O1 /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00218787@Rva00218787@@QAEAAMABH@Z @ 0x00218787 124B: map int->float subscript with Rva temp; evidence lower_bound row stlport_map_int_int_os, insert row IntFloatMapSubscript, set row Rva004738A0Set, Release row TreeHintRefReleaseBFME2
// ?rva00218787@Rva00218787@@QAEAAMABH@Z present-unmatched
#include <map>

struct Rva004738A0Obj
{
	int m_00;
	int m_04;
};

struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva004738A0
{
public:
	int m_00;
	Rva004738A0Obj *m_04;
	Rva004738A0 *set(const int *a, Rva004738A0Obj *const *b);
	~Rva004738A0() { if (m_04) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_04); }
};

class Rva00218787 : public _STL::map<int, float, _STL::less<int>, _STL::allocator<_STL::pair<const int, float> > >
{
public:
	float &rva00218787(const int &key);
};

float &Rva00218787::rva00218787(const int &key)
{
	typedef _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > IntMap;
	IntMap *im = (IntMap *)(void *)this;
	IntMap::iterator it2 = im->lower_bound(key);
	iterator it = (iterator &)it2;
	if (it == end() || key < it->first)
	{
		int zero = 0;
		Rva004738A0 tmp;
		tmp.set(&key, (Rva004738A0Obj *const *)&zero);
		it = insert(it, *(const _STL::pair<const int, float> *)(void *)&tmp);
	}
	return it->second;
}
