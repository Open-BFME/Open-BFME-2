// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva004E9446@Rva004E94FB@@QAEXXZ @ 0x004E9446, 91 bytes.
// Predicate-gated erase walk over vector<void*> at +0x18 (end cached, refreshed
// after each erase): per element call rowed bool predicate 0x004E9378 ([+0x10]==2/3);
// when true delete (elem ? elem->v00(0) : 0) via rowed scalar delete 0x0002FD60 and
// erase via rowed vector<void*>::erase 0x001FF51F; when false call helper 0x00596B10
// if elem[+0x10]==1 then advance. Same this as caller 0x004E9710 (provisional pin class).
#include <vector>

class Rva004E9378
{
public:
	bool rva004E9378();
};

class Rva00596B10
{
public:
	void rva00596B10();
};

struct Rva004E9446Elem
{
	virtual void *v00(int arg);
	char m_pad[0x10 - 4];
	int m_10;
};

class Rva004E94FB
{
public:
	void rva004E9446();

private:
	char m_pad00[0x18];
	_STL::vector<void *> m_vec; // +0x18 (begin/end/capacity)
};

void Rva004E94FB::rva004E9446()
{
	_STL::vector<void *>::iterator end = m_vec.end();
	_STL::vector<void *>::iterator it = m_vec.begin();
	while (it != end)
	{
		Rva004E9446Elem *e = (Rva004E9446Elem *)*it;
		if (((Rva004E9378 *)e)->rva004E9378())
		{
			void *p = e ? e->v00(0) : (void *)0;
			delete p;
			it = m_vec.erase(it);
			end = m_vec.end();
		}
		else
		{
			if (e->m_10 == 1)
				((Rva00596B10 *)e)->rva00596B10();
			++it;
		}
	}
}
