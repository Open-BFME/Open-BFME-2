// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// GameWindowTransitionsHandler construction and teardown (Zero Hour
// GameWindowTransitions.cpp, BFME 2 layout).
//
// Target evidence: the ctor 0x001DCBC3 installs vftable 0x00BDBC30 over the
// SubsystemInterface base 0x001B4E63; caller 0x002C0A30 stores the object
// in the global 0x00DFDC14, which INI::parseWindowTransitions (0x001DC66F)
// reads as TheTransitionHandler. The group list sits at +0x20 and the
// current/pending/draw/secondary groups at +0x24..+0x30 as in Zero Hour;
// BFME 2 adds the table at +0x0C, a critical section at +0x38 with its
// initialised flag at +0x50, and the fields up to +0x6C.
//
// Donor-carried: Open-BFME 1's handler types the table at its +0x08 as
// hash_map<NameKeyType, Transition *(*)(void), rts::hash, rts::equal_to>
// (its _M_insert/_M_initialize_buckets/operator[] are named that way from
// retail relocations there). BFME 2's table has the same shape (100-bucket
// ctor 0x001DCBA4 -> hashtable ctor 0x001DCB64 -> rts _M_initialize_buckets
// 0x00148DDF); the value type is carried from the donor, not proven here.
// Use the native 17-byte specialization at RVA 0x00013740 rather than
// emitting a separately optimized copy from this unit.
#include <stl/_algobase.h>
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

#include <hash_map>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include <cstddef>

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

namespace rts
{

template <typename T> struct hash
{
	size_t operator()(const T &value) const;
};

template <typename T> struct equal_to
{
	bool operator()(const T &a, const T &b) const;
};

}

class Transition;
typedef Transition *(*WindowTransitionFactory)( void );
typedef std::hash_map<NameKeyType, WindowTransitionFactory,
	rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > WindowTransitionMap;

extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void *cs);

// TransitionGroup (0x14 bytes) under its rowed address names: the dtor
// 0x001DC0EC (scalar deleting 0x001DC1E1) and the list walk rva001DBE17.
class Rva001DC0EC
{
public:
	~Rva001DC0EC();
};
class Rva001DBDA4
{
public:
	void rva001DBE17();
};
typedef Rva001DC0EC TransitionGroup;

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	unsigned char m_bfme04[8];
};

class GameWindowTransitionsHandler : public SubsystemInterface
{
public:
	GameWindowTransitionsHandler();
	virtual ~GameWindowTransitionsHandler();
	void init() { }
	void reset() { }
	void update() { }

private:
	typedef std::list<TransitionGroup *> TransitionGroupList;

	WindowTransitionMap m_transitionMap;        // +0x0C
	TransitionGroupList m_transitionGroupList;  // +0x20
	TransitionGroup *m_currentGroup;            // +0x24
	TransitionGroup *m_pendingGroup;            // +0x28
	TransitionGroup *m_drawGroup;               // +0x2C
	TransitionGroup *m_secondaryDrawGroup;      // +0x30
	int m_unk34;
	char m_lock[0x50 - 0x38];                   // +0x38 CRITICAL_SECTION
	unsigned char m_lockInitialized;            // +0x50
	unsigned char m_unk51;
	char m_pad52[0x64 - 0x52];
	int m_unk64;
	unsigned char m_unk68;
	unsigned char m_unk69;
	char m_pad6A[0x6C - 0x6A];
};

GameWindowTransitionsHandler::GameWindowTransitionsHandler()
{
	m_currentGroup = 0;
	m_pendingGroup = 0;
	m_drawGroup = 0;
	m_secondaryDrawGroup = 0;
	m_unk64 = 0x21;
	m_unk69 = 0;
	m_unk68 = 0;
	m_lockInitialized = 0;
	m_unk51 = 0;
	m_unk34 = 0;
	m_transitionGroupList.clear();
}

// Zero Hour's dtor plus BFME 2's group release (rva001DBE17 on each group
// pointer before clearing it) and DeleteCriticalSection under the +0x50
// flag; then every group is deleted and erased.
GameWindowTransitionsHandler::~GameWindowTransitionsHandler()
{
	if( m_currentGroup )
	{
		((Rva001DBDA4 *)m_currentGroup)->rva001DBE17();
		m_currentGroup = 0;
	}
	if( m_pendingGroup )
	{
		((Rva001DBDA4 *)m_pendingGroup)->rva001DBE17();
		m_pendingGroup = 0;
	}
	if( m_drawGroup )
	{
		((Rva001DBDA4 *)m_drawGroup)->rva001DBE17();
		m_drawGroup = 0;
	}
	if( m_secondaryDrawGroup )
	{
		((Rva001DBDA4 *)m_secondaryDrawGroup)->rva001DBE17();
		m_secondaryDrawGroup = 0;
	}
	if( m_lockInitialized )
	{
		DeleteCriticalSection( m_lock );
		m_lockInitialized = 0;
	}

	TransitionGroupList::iterator it = m_transitionGroupList.begin();
	while( it != m_transitionGroupList.end() )
	{
		TransitionGroup *g = *it;
		delete g;
		it = m_transitionGroupList.erase( it );
	}
}
