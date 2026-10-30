// cl: /I. /G7 /O1 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?update@Player@@QAEXXZ, retail 0x002AE770 (351 bytes, RET0).
// Identity: existing pin (PlayerList's per-player update REL32 at
// 0x002A7AC0); WB C12FA0 is the same body by call graph. ZH Player.cpp
// Player::update supplies the shape: AI update, generic scripts of every
// owned team, local-player retaliation-mode message once a logic second.
// BFME2 deltas established from retail bytes:
//  - before the team walk, the +2BC name->int timer map is walked; each
//    nonzero entry is decremented and, on reaching zero, the +294 float
//    map entry for that name is reset from the +2A8 one (production-speed
//    bonus expiry; the writer is rowed PlayerProductionSpeed 0x002AE8CF);
//  - the team-prototype list (+0x32C) is walked through a local copy
//    (copy ctor 0x002AE577, nothrow base dtor 0x002ABB44);
//  - the energy sabotage and academy-stats updates are gone;
//  - LOGICFRAMES_PER_SECOND is the variable BfmeLogicFramesPerSecond;
//  - the tail calls rowed Player 0x002AD1FD and ScoreKeeper::updateFrame
//    on the +0x3BC score keeper.
// Field names for +2BC/+2A8/+294/+33E are donor inference; the map views
// keep their rowed address-derived owners.
#include <list>

// Retail compares typed list nodes inline, as in NetPacket.cpp.
namespace _STL {
template <class T, class L, class R>
static __forceinline bool operator!=(const _List_iterator<T, L> &a, const _List_iterator<T, R> &b)
{ return a._M_node != b._M_node; }
}

#include <vector>
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "reference/shims/moduledata/Common/Snapshot.h"
// bfme link decl-only begin
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
// bfme link decl-only end

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class AsciiString;
class TeamPrototype;
// The team-prototype list instantiation keeps the ledger's placeholder
// element name of its rowed copy constructor 0x002AE577.
struct Rva002AE577PointerTarget;

// The team list's nodes come from a pool and go back onto its free list
// (VA 0x00DBBD34, see Rva002AAC74PoolListClear.cpp), so its base clear
// (0x002AAC74) and destructor (0x002ABB44) are that pool's; retail calls the
// destructor with no EH state transition before it (see AIPlayerTeamBuild.cpp).
struct PoolNode002ABAC0;
extern PoolNode002ABAC0 *g_00DBBD34;
class FreelistPool { public: void *pop(); };
extern FreelistPool g_freelistPool009BBD2C;
namespace _STL {
// The copied team list has the same sentinel pool as its native owner
// Rva002AC026Member::init, not STLport's general-purpose node allocator.
template <> inline _List_base<Rva002AE577PointerTarget *, allocator<Rva002AE577PointerTarget *> >::_List_base(const allocator<Rva002AE577PointerTarget *> &a)
    : _M_node(_Node_allocator_type(a), (_Node *)0)
{
    _Node *node = (_Node *)g_freelistPool009BBD2C.pop();
    node->_M_next = node;
    node->_M_prev = node;
    _M_node._M_data = node;
}
template <> inline void _List_base<Rva002AE577PointerTarget *, allocator<Rva002AE577PointerTarget *> >::clear()
{
	void *head = _M_node._M_data;
	void *node = ((void **)head)[0];
	if (node != head) {
		do {
			void *freeHead = g_00DBBD34;
			void *current = node;
			node = ((void **)current)[0];
			((void **)current)[0] = freeHead;
			g_00DBBD34 = (PoolNode002ABAC0 *)current;
		} while (node != _M_node._M_data);
	}
	((void **)_M_node._M_data)[0] = _M_node._M_data;
	((void **)_M_node._M_data)[1] = _M_node._M_data;
}
template <> inline _List_base<Rva002AE577PointerTarget *, allocator<Rva002AE577PointerTarget *> >::~_List_base() throw()
{
	clear();
	void *head = _M_node._M_data;
	if (head != 0) {
		void *freeHead = g_00DBBD34;
		((void **)head)[0] = freeHead;
		g_00DBBD34 = (PoolNode002ABAC0 *)head;
	}
}
}
typedef _STL::list<Rva002AE577PointerTarget *> PlayerTeamList;

template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

#include "../../../Include/Common/MemoryPoolObject.h"

#include "../../../Include/Common/TeamBFME2.h"

class TeamPrototype
{
public:
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const
	{
		return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
	}
private:
	unsigned char m_pad[0x334];
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

// Rowed name-map helpers (AsciiStringTableSubscripts.cpp, MilesAudio views).
// The +2BC name->int timer table is an STLport hashtable (unused word, the
// bucket vector at +4, count) whose begin (0x00427195), iterator advance
// (0x00411084) and bucket skip (0x003F7925) keep their rowed address-derived
// owners. Their bodies are defined here as the retail TU saw them (template
// inlines that stay out of line): with them visible cl knows the iterator's
// address never escapes, so the timer walk keeps it.current in eax across the
// decrement as retail does; declared only, it reloaded it.current after the
// store through the node. The spellings follow the rowed bodies
// (AudioFileCacheDestructor.cpp, EvaMessageName.cpp, EvaBucketAdvance.cpp).
class Rva000411084;
struct NameTimerNode;
class Rva000427195
{
public:
	__declspec(noinline) void *first(Rva000411084 *iter);
	int bucketIndex(const AsciiString *name);
	void *m_unused00;
	// Player timers have native {next, AsciiString, Int} bucket nodes.
	// Use their actual pointer type so this helper sees its inline accessors
	// without emitting competing vector<void *> definitions.
	_STL::vector<NameTimerNode *> m_buckets;
};
class Rva000411084
{
public:
	__declspec(noinline) void *next()
	{
		void *node = *(void **)current;
		if (node == 0)
			node = advance();
		current = node;
		return this;
	}
	__declspec(noinline) void *advance()
	{
		struct Table
		{
			void *m_unused00;
			union {
				void **m_beginBuckets;
				void ** volatile m_beginBucketsVolatile;
			};
			void **m_endBuckets;
			int bucketIndex(const AsciiString *name);
		};
		Table *table = (Table *)owner;
		unsigned index = (unsigned)((Rva000427195 *)table)->bucketIndex((const AsciiString *)((char *)current + 4));
		unsigned count = (unsigned)(((char *)table->m_endBuckets - (char *)table->m_beginBuckets) >> 2);
		void *head = 0;
		do {
			++index;
			if (index >= count)
				break;
			head = table->m_beginBucketsVolatile[index];
		} while (head == 0);
		return head;
	}
	void *current, *owner;
};
inline void *Rva000427195::first(Rva000411084 *iter)
{
	for (unsigned n = 0; n < m_buckets.size(); ++n)
		if (m_buckets[n])
		{
			iter->current = m_buckets[n];
			iter->owner = this;
			return iter;
		}
	iter->current = 0;
	iter->owner = this;
	return iter;
}
class Rva001FDE3F
{
public:
	float &rva001FDE3F(const AsciiString &key);
};
struct NameTimerNode
{
	void *m_next;
	unsigned char m_key[4]; // AsciiString
	Int m_value;
};

class AIPlayerView
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void update();
};

class GameMessage
{
public:
	enum Type { MSG_ENABLE_RETALIATION_MODE = 0x462 };
	void appendIntegerArgument(Int arg);
	void appendBooleanArgument(Bool arg);
};
class MessageStream
{
public:
#define V(n) virtual void slot##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17)
#undef V
	virtual GameMessage *appendMessage(GameMessage::Type);
};
extern MessageStream *TheMessageStream;

class ScoreKeeper
{
public:
	void updateFrame(Int frame);
};

class Player;
class PlayerList
{
public:
	// Keep retail's inlined +0x10 access without a competing external copy.
	__declspec(dllimport) __forceinline Player *getLocalPlayer() { return m_local; }
private:
	unsigned char m_pad[0x10];
	Player *m_local; // +0x10
};
extern PlayerList *ThePlayerList;

extern GameLogic *TheGameLogic;

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct GlobalDataView
{
	unsigned char m_pad[0x11BC];
	Bool m_clientRetaliationModeEnabled; // +0x11BC
};
#define TheGlobalData ((const GlobalDataView *)TheWritableGlobalData)

extern Int BfmeLogicFramesPerSecond;

class Player
{
public:
	void update();
	void rva002AD1FD();
	Int getPlayerIndex() const { return m_playerIndex; }
	Bool isLogicalRetaliationModeEnabled() const { return m_logicalRetaliationModeEnabled; }
private:
	unsigned char m_pad0[0x54];
	Int m_playerIndex; // +0x54
	unsigned char m_pad58[0x294 - 0x58];
	Rva001FDE3F m_productionSpeedBonus; // +0x294
	unsigned char m_pad295[0x2A8 - 0x295];
	Rva001FDE3F m_startingProductionSpeedBonus; // +0x2A8
	unsigned char m_pad2A9[0x2BC - 0x2A9];
	Rva000427195 m_productionSpeedTimers; // +0x2BC
	unsigned char m_pad2CC[0x2DC - 0x2CC];
	AIPlayerView *m_ai; // +0x2DC
	unsigned char m_pad2E0[0x32C - 0x2E0];
	PlayerTeamList m_playerTeamPrototypes; // +0x32C
	unsigned char m_pad330[0x33E - 0x330];
	Bool m_logicalRetaliationModeEnabled; // +0x33E
	unsigned char m_pad33F[0x3BC - 0x33F];
	ScoreKeeper m_scoreKeeper; // +0x3BC
};

void Player::update()
{
	if (m_ai)
		m_ai->update();

	{
		Rva000411084 it;
		for (m_productionSpeedTimers.first(&it); it.current; it.next())
		{
			NameTimerNode *node = (NameTimerNode *)it.current;
			if (((NameTimerNode *)it.current)->m_value != 0)
			{
				((NameTimerNode *)it.current)->m_value--;
				// The test reads the count through the node local: through the
				// iterator cl folds it into the dec's flags (dec; jne), retail
				// re-reads it (dec; cmp [eax+8],0).
				if (node->m_value == 0)
				{
					const AsciiString &name = *(const AsciiString *)node->m_key;
					m_productionSpeedBonus.rva001FDE3F(name) = m_startingProductionSpeedBonus.rva001FDE3F(name);
				}
			}
		}
	}

	// Allow the teams this player owns to update themselves.
	PlayerTeamList teams(m_playerTeamPrototypes);
	PlayerTeamList::iterator end = teams.end();
	for (PlayerTeamList::iterator pit = teams.begin(); pit != end; ++pit)
	{
		for (DLINK_ITERATOR<Team> iter = ((TeamPrototype *)*pit)->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			team->updateGenericScripts();
		}
	}

	if (ThePlayerList->getLocalPlayer() == this)
	{
		UnsignedInt now = TheGameLogic->getFrame();
		if (now % BfmeLogicFramesPerSecond == 0)
		{
			if (TheGlobalData->m_clientRetaliationModeEnabled != isLogicalRetaliationModeEnabled())
			{
				GameMessage *msg = TheMessageStream->appendMessage(GameMessage::MSG_ENABLE_RETALIATION_MODE);
				if (msg)
				{
					msg->appendIntegerArgument(getPlayerIndex());
					msg->appendBooleanArgument(TheGlobalData->m_clientRetaliationModeEnabled);
				}
			}
		}
	}

	rva002AD1FD();
	m_scoreKeeper.updateFrame(TheGameLogic->getFrame());
}
