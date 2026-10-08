// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0055A91A@ScoredKillTracker@@QAEXXZ @ 0x0055A91A 34B
// Evidence: LINK BONUS via 0x0039C09C; inner Rva0039BCF8 at +0x10 via rowed rva0039BCF8 0x0039BCF8; flag +0x14 set -1; list<int> at +0x18 via rowed clear 0x0023DAA5; count +0x1C set 0; callers 0x0039C0CA 0x0041453E 0x0055A93F 0x0055AC2D 0x0055A993; layout like Rva0055AA06 list/count.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


class Rva0039BCF8
{
public:
	void **rva0039BCF8(void *val);
	char m_pad00[0x100];
	int m_100; // +0x100
};

class ModuleData;

class Rva0039C7A5Holder
{
public:
	void add(const ModuleData *data);
};

class ScoredKillTracker
{
public:
	void rva0055A91A();
	void hookToKeeper(Rva0039BCF8 *p);
	void LoadPostProcess();
private:
	char m_pad00[0x10];
	Rva0039BCF8 *m_10; // +0x10
	int m_14; // +0x14
	_STL::list<int, _STL::allocator<int> > m_list; // +0x18
	int m_1c; // +0x1C
};

class Player
{
public:
	char m_pad00[0x3BC];
	Rva0039BCF8 m_3BC; // +0x3BC
};

class PlayerList
{
public:
	Player *getNthPlayer(int i);
};

extern PlayerList *ThePlayerList;

void ScoredKillTracker::rva0055A91A()
{
	if (m_10 == 0)
		return;
	m_10->rva0039BCF8(this);
	m_14 = -1;
	m_list.clear();
	m_1c = 0;
}

void ScoredKillTracker::hookToKeeper(Rva0039BCF8 *p)
{
	rva0055A91A();
	if (p == 0)
		return;
	m_10 = p;
	m_14 = p->m_100;
	((Rva0039C7A5Holder *)p)->add((const ModuleData *)this);
}

void ScoredKillTracker::LoadPostProcess()
{
	if (m_14 == -1 || m_14 < 0)
		return rva0055A91A();
	Player *player = ThePlayerList->getNthPlayer(m_14);
	if (player == 0)
		return rva0055A91A();
	hookToKeeper(&player->m_3BC);
}

struct BfmeAssignExtra
{
	int v0;
	int v1;
	int v2;
};

struct BfmeAssignRecord44
{
	BfmeAssignRecord44 &operator=(const BfmeAssignRecord44 &other);
	char m_00[4]; // +0x00
	int m_04; // +0x04
	int m_08; // +0x08
	int m_0c; // +0x0C
	Rva0039BCF8 *m_10; // +0x10
	int m_14; // +0x14
	_STL::list<int, _STL::allocator<int> > m_list; // +0x18
	int m_1c; // +0x1C
	BfmeAssignExtra m_20; // +0x20 (12B via movsd x3)
};

BfmeAssignRecord44 &BfmeAssignRecord44::operator=(const BfmeAssignRecord44 &other)
{
	if (this == &other)
		return *this;
	((ScoredKillTracker *)this)->rva0055A91A();
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0c = other.m_0c;
	m_list = other.m_list;
	m_1c = other.m_1c;
	m_20 = other.m_20;
	if (other.m_10 != 0)
		((ScoredKillTracker *)this)->hookToKeeper(other.m_10);
	return *this;
}
