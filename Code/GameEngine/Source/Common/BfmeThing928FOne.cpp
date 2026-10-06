// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
// ?bfmeOne928F@BfmeThing928F@@QAEXXZ, retail 0x0010C6C4 (193B). Ported from
// Open-BFME-1 game/GameEngine/Source/Common/BfmeConv928.cpp:159
// (BfmeThing928F::bfmeOne928F). Evidence: same two-list drain (this+8 then
// this+4), type filter 0x400/0x800 at +0x34, link at +0x114, 8-zero call to
// rowed 0x00330A37 plus slot-2 virtual, list<int> callees rowed.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


struct Rva007B4CD0Entry
{
	char m_pad00[0x34];
	int m_type; // +0x34
	char m_pad38[0x114 - 0x38];
	Rva007B4CD0Entry *m_next; // +0x114
};

class Rva00330A37
{
public:
	void rva00330A37(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
	virtual void v00();
	virtual void v01();
	virtual void v02();
};

class BfmeThing928F
{
public:
	void bfmeOne928F();
	void *m_pad00; // +0
	Rva007B4CD0Entry *m_list04; // +4
	Rva007B4CD0Entry *m_list08; // +8
};

void BfmeThing928F::bfmeOne928F()
{
	_STL::list<Rva007B4CD0Entry *> pending;
	int list;

	for (list = 0; list <= 1; ++list)
	{
		Rva007B4CD0Entry *entry = list ? m_list04 : m_list08;
		while (entry)
		{
			if (entry->m_type == 0x400 || entry->m_type == 0x800)
				pending.push_back(entry);
			entry = entry->m_next;
		}
	}

	for (_STL::list<Rva007B4CD0Entry *>::iterator it = pending.begin(); it != pending.end(); ++it)
	{
		((Rva00330A37 *)*it)->rva00330A37(0, 0, 0, 0, 0, 0, 0, 0);
		((Rva00330A37 *)*it)->v02();
	}
	pending.clear();
}
