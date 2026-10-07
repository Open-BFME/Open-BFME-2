// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00425CE2@@UAE@XZ, retail 0x00425CE2 (196B).
// Evidence: unlock lane; called by deleting dtor 0x00425DA6 28B; vtable store; base ??1GameEngineDeletingBase@@UAE@XZ rowed; member ??1Rva00360D26Member@@QAE@XZ rowed at +0x20; deque<LightPoint*> for_each 0x00425CBE plus deque<void*> clear 0x00422795 on g_00E03174; RB map at g_00E03168 with _M_increment 0x00024250 plus rva00421EEA 0x00421EEA; field +0xC zeroed.
#include <algorithm>
#include <deque>
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class LightPoint;

struct Rva00425B75Deleter
{
	void operator()(LightPoint *p) const;
};

class Rva00360D26Member
{
public:
	~Rva00360D26Member();
private:
	unsigned m_unknown;
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[8];
};

class Rva00421BF7
{
public:
	void rva00421EEA();
};

void __cdecl operator delete(void *p);

extern _STL::map<int, Rva00360D26Member *> g_00E03168;
extern _STL::deque<LightPoint *> g_00E03174;

class Rva00425CE2 : public GameEngineDeletingBase
{
public:
	virtual ~Rva00425CE2();
private:
	int m_0C;
	char m_pad10[0x20 - 0x0C - 4];
	Rva00360D26Member m_20;
};

Rva00425CE2::~Rva00425CE2()
{
	_STL::for_each(g_00E03174.begin(), g_00E03174.end(), Rva00425B75Deleter());
	(( _STL::deque<void *> *)(void *)&g_00E03174)->clear();
	for (_STL::map<int, Rva00360D26Member *>::iterator it = g_00E03168.begin(); it != g_00E03168.end(); ++it)
	{
		Rva00360D26Member *p = it->second;
		if (p)
		{
			Rva00360D26Member &r = *p;
			r.~Rva00360D26Member();
			::operator delete(p);
		}
	}
	((Rva00421BF7 *)(void *)&g_00E03168)->rva00421EEA();
	m_0C = 0;
}
