// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// 0x00082B87 / 0x00082BB4 twins: same detach-key-and-clear manager shape as
// 0x000824C3 (branchless diff ternary, rowed Rva002B7250::rva002B7250, slot
// cleared), then the hint range at the sibling offset is dropped with the
// rowed vector<TreeHintRef00217D4C>::erase(first, last), reached through the
// Rva00082XXHintVec address view pinned at 0x000819EC. Host identities and
// the element layout are unproven; names are address-derived.

class CreateAHeroData;

struct TreeHintRef00217D4C;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

struct Rva00082XXHintVec
{
	TreeHintRef00217D4C *m_begin;
	TreeHintRef00217D4C *m_finish;
	TreeHintRef00217D4C *m_end;
};

// The range erase is the rowed STLport vector<TreeHintRef00217D4C>::erase.
namespace _STL
{
template <class T> class allocator;
template <class T, class A = allocator<T> > class vector
{
public:
	T *erase(T *first, T *last);
};
}

class Rva00082B87Host
{
public:
	void rva00082B87(int unused);
private:
	char m_pad[0x3C];
	Rva002B7250 *m_mgr; // +0x3C
	Rva00082XXHintVec m_hints; // +0x40
};

void Rva00082B87Host::rva00082B87(int unused)
{
	(void)unused;
	Rva002B7250 *mgr = m_mgr;
	char *diff = (char *)this - 0xC8;
	CreateAHeroData *key = (diff != 0) ? (CreateAHeroData *)this : 0;
	mgr->rva002B7250(key);
	Rva00082XXHintVec *hv = &m_hints;
	m_mgr = 0;
	((_STL::vector<TreeHintRef00217D4C> *)hv)->erase(hv->m_begin, hv->m_finish);
}

class Rva00082BB4Host
{
public:
	void rva00082BB4(int unused);
private:
	char m_pad[0x48];
	Rva002B7250 *m_mgr; // +0x48
	Rva00082XXHintVec m_hints; // +0x4C
};

void Rva00082BB4Host::rva00082BB4(int unused)
{
	(void)unused;
	Rva002B7250 *mgr = m_mgr;
	char *diff = (char *)this - 0xCC;
	CreateAHeroData *key = (diff != 0) ? (CreateAHeroData *)this : 0;
	mgr->rva002B7250(key);
	Rva00082XXHintVec *hv = &m_hints;
	m_mgr = 0;
	((_STL::vector<TreeHintRef00217D4C> *)hv)->erase(hv->m_begin, hv->m_finish);
}
