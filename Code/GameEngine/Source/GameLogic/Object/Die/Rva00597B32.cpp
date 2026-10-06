// cl: /GX-
// ?shutdown@AIUpgradeScienceBuilder@@QAEXXZ @0x00597B32 162B: vslot2 of 0x00870C18 clearing two voidptr vectors with slot0+delete then hero remove via g_00DFEEF8 and ScienceType clear; callers 0x00597BFE
class Player;
class CreateAHeroData;

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
};

class Rva004DFB55
{
public:
	void rva004DFB55(CreateAHeroData *p);
};

extern Rva002A8F24 *g_00DFEEF8;

enum ScienceType
{
	SCIENCE_INVALID = 0
};

namespace _STL
{

template <class _Tp> class allocator
{
};

template <class _Tp, class _Alloc> class vector
{
public:
	_Tp *erase(_Tp *first, _Tp *last);
	_Tp *m_start;
	_Tp *m_finish;
	_Tp *m_end;
};

}

class Elem
{
public:
	virtual void *slot0(int x);
};

void __cdecl operator delete(void *p);

class AIUpgradeScienceBuilder
{
public:
	void shutdown();
private:
	char m_pad00[8];
	Player *m_player08;
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > m_sci0c;
	_STL::vector<void *, _STL::allocator<void *> > m_vec18;
	_STL::vector<void *, _STL::allocator<void *> > m_vec24;
	int m_tail30;
};

void AIUpgradeScienceBuilder::shutdown()
{
	void **it = m_vec18.m_start;
	void **finish = m_vec18.m_finish;
	while (it != finish)
	{
		void *p = *it;
		void *q = 0;
		if (p != 0)
			q = ((Elem *)p)->slot0(0);
		::operator delete(q);
		++it;
	}
	{
		_STL::vector<void *, _STL::allocator<void *> > &r1 = m_vec18;
		r1.erase(r1.m_start, r1.m_finish);
	}

	it = m_vec24.m_start;
	finish = m_vec24.m_finish;
	while (it != finish)
	{
		void *p = *it;
		void *q = 0;
		if (p != 0)
			q = ((Elem *)p)->slot0(0);
		::operator delete(q);
		++it;
	}
	{
		_STL::vector<void *, _STL::allocator<void *> > &r2 = m_vec24;
		r2.erase(r2.m_start, r2.m_finish);
	}

	Player *pl = m_player08;
	void *store = g_00DFEEF8->rva002A8F24(pl);
	((Rva004DFB55 *)store)->rva004DFB55((CreateAHeroData *)((char *)this - 0xc));
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > *vs = &m_sci0c;
	vs->erase(vs->m_start, vs->m_finish);
}
