// ?collectKeys@Rva00622290@@QAE?AURva00622290SetGroup@@XZ
// cl: /O2 /G6 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/sweep
// stlport
// Donor: Open-BFME-1 575ba2b04743 AssetRegistryKeySet009EF7D0.cpp.
// Donor supplies the lock/collect/copy algorithm; its original registry name
// and globals do not establish this target receiver's original identity.
// Native622290..6223BB RET4: lock+34; hash table+4C; iterator620A80;
// integer keys at node+4; insertion422047; returned tree copy620CA0.
// The local/returned group is20B, with count+0C=0 and flag+10=1.
// Existing pointer-set ABI serves the scalar-key insert/destruction callees;
// the return copies through the independently recovered set<int> tree.
// G6 preserves native hash bucket iteration loads and INC scheduling.

#define _STLP_USE_STATIC_LIB 1

#include <hash_map>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <windows.h>

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;
typedef _STL::_Rb_tree<Rva001408C0Key,Rva001408C0Key,_STL::_Identity<Rva001408C0Key>,_STL::less<Rva001408C0Key>,_STL::allocator<Rva001408C0Key> > PointerTree;
typedef _STL::_Rb_tree<int,int,_STL::_Identity<int>,_STL::less<int>,_STL::allocator<int> > IntSetTreeCopyView;
namespace _STL {
template<> PointerTree::~_Rb_tree();
template<> IntSetTreeCopyView::_Rb_tree(const IntSetTreeCopyView&);
}

struct Rva00622290SetGroup
{
	IntSetTreeCopyView m_tree;
	unsigned int m_count;
	bool m_active;
	unsigned char m_padding[3];

	explicit Rva00622290SetGroup(const IntSetTreeCopyView &tree)
		: m_tree(tree)
	{
		clear();
	}

	void clear()
	{
		m_count = 0;
		m_active = true;
	}
};

struct Rva00622290LocalSet
{
	Rva001408C0Set m_tree;
	unsigned int m_count;
	bool m_active;
	unsigned char m_padding[3];

	Rva00622290LocalSet() { clear(); }

	void clear()
	{
		m_count = 0;
		m_active = true;
	}
};

typedef _STL::hash_map<int, int> ScalarHashMap622290;

class Rva00622290Lock
{
public:
	explicit Rva00622290Lock(CRITICAL_SECTION *lock) : m_lock(lock)
	{
		EnterCriticalSection(m_lock);
	}
	~Rva00622290Lock()
	{
		LeaveCriticalSection(m_lock);
	}

	CRITICAL_SECTION *m_lock;
};

class Rva00622290
{
public:
	Rva00622290SetGroup collectKeys();

private:
	unsigned char m_unmodelled_000[0x34];
	CRITICAL_SECTION m_lock34;
	ScalarHashMap622290 m_map4c;
};

Rva00622290SetGroup Rva00622290::collectKeys()
{
	Rva00622290Lock lock(&m_lock34);
	Rva00622290LocalSet keys;
	ScalarHashMap622290::iterator it;
	for (it = m_map4c.begin(); it != m_map4c.end(); ++it)
	{
		keys.m_tree.insert(*(const Rva001408C0Key *)&(*it).first);
	}
	return Rva00622290SetGroup(
		*(const IntSetTreeCopyView *)&keys.m_tree);
}
