// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /arch:SSE /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// StrategicInGameUI::DynamicAutoResolveDialog::Impl, the part of
// StrategicInGameUIDynamicAutoResolveDialog.cpp that WorldBuilder places
// after the player panel clip (WB 0x015E31E0..0x015E6080; asserts at lines
// 112..1202). Retail bodies:
//
//   0x005EAA44  _STL::vector<float>::vector(int, int, const allocator &)
//   0x005EAA9C  collectUnitCounts     (static; ESI = battle, 132 bytes)
//   0x005EAB20  collectMaxTotalHealth (static; ESI = battle, 185 bytes)
//   0x005EABD9  collectUnitHealths    (static; ESI = battle, 132 bytes)
//   0x005EACBD  WaitForBattleStepStateHandler::Update (498 bytes)
//   0x005EB481  Impl::Impl (645 bytes, vtable 0x00C78210)
//
// The three collectors are file-static and never have their address taken,
// so the compiler gives them a private convention (battle in ESI, the output
// vector on the stack; the float result in XMM0); WB passes both on the stack
// and asserts numPlayers > 0. Each walks the battle's units through
// LivingWorldAutoResolveBattle::enumerateCurrentUnits (0x004F6234) with a
// visitor whose base vtable is 0x00C1C780; the total-health one also walks
// every reinforcement round (first 0x004F81CC, enumerateReinforcementUnits
// 0x004F76EA, next 0x004F7B42). Those callees keep their address-derived
// ledger spellings, so the battle is cast to each one's receiver view.
#include "ascii_string.h"
#include <vector>
#include <map>

typedef int Int;
typedef float Real;
typedef bool Bool;

// ---- the battle and its players -----------------------------------------

struct Pred004F6234
{
	virtual ~Pred004F6234() {}
	virtual void visit(void *unit) = 0;
};
class Rva004F76EAPred;

struct DynamicAutoResolvePlayer;

// A battle player entry (0x34 bytes): the rounds in which it receives
// reinforcements (round -> count), then its player key at +0x30.
struct DynamicAutoResolveBattlePlayer
{
	_STL::map<Int, Int> m_reinforcementRounds;	// +0x00
	unsigned char m_pad0C[0x2C - 0x0C];
	Int m_2C;					// +0x2C
	Int m_key;					// +0x30
};

// The battle manager: its input data's player list leads (WB asserts
// getInputData().playerData[battlePlayerID]), the current round is at +0x7C.
struct DynamicAutoResolveBattlePlayers
{
	_STL::vector<DynamicAutoResolveBattlePlayer> m_playerData;	// +0x00
	unsigned char m_pad0C[0x78 - 0x0C];
	Int m_78;					// +0x78
	Int m_currentRound;				// +0x7C

	Int size() const { return m_playerData.size(); }
};

class Rva004F6234
{
public:
	void rva004F6234(Int side, Pred004F6234 *pred);
};
class Rva004F81CC
{
public:
	Int rva004F81CC(Int side);
};
class Rva004F76EA
{
public:
	void rva004F76EA(Int side, Int round, Rva004F76EAPred *pred);
};
class Rva004F7B42
{
public:
	Int rva004F7B42(Int side, Int round);
};
Real *Rva005EA09CFindMax(Real *first, Real *last);

// The three unit visitors (vtables 0x00C781B4, 0x00C780BC and the healths
// one); their visit bodies live elsewhere in the unit.
struct UnitCountCollector : public Pred004F6234
{
	UnitCountCollector(_STL::vector<Int> &counts) : m_counts(counts) {}
	virtual void visit(void *unit);

	_STL::vector<Int> &m_counts;
};

struct UnitHealthCollector : public Pred004F6234
{
	UnitHealthCollector(_STL::vector<Real> &healths) : m_healths(healths) {}
	virtual void visit(void *unit);

	_STL::vector<Real> &m_healths;
};

struct TotalHealthCollector : public Pred004F6234
{
	TotalHealthCollector(_STL::vector<Real> &healths) : m_healths(healths) {}
	virtual void visit(void *unit);

	_STL::vector<Real> &m_healths;
};

static __declspec(noinline) void collectUnitCounts(DynamicAutoResolveBattlePlayers *battle, _STL::vector<Int> &out)
{
	Int numPlayers = battle->size();
	_STL::vector<Int> counts(numPlayers, 0);
	UnitCountCollector collector(counts);
	for (Int side = 0; side < 2; ++side)
		reinterpret_cast<Rva004F6234 *>(battle)->rva004F6234(side, &collector);
	out.swap(counts);
}

static __declspec(noinline) Real collectMaxTotalHealth(DynamicAutoResolveBattlePlayers *battle)
{
	Int numPlayers = battle->size();
	_STL::vector<Real> healths(numPlayers, 0);
	TotalHealthCollector collector(healths);
	for (Int side = 0; side < 2; ++side)
	{
		reinterpret_cast<Rva004F6234 *>(battle)->rva004F6234(side, &collector);
		for (Int round = reinterpret_cast<Rva004F81CC *>(battle)->rva004F81CC(side); round >= 0;
			round = reinterpret_cast<Rva004F7B42 *>(battle)->rva004F7B42(side, round))
		{
			reinterpret_cast<Rva004F76EA *>(battle)->rva004F76EA(side, round, reinterpret_cast<Rva004F76EAPred *>(&collector));
		}
	}
	return *Rva005EA09CFindMax(healths.begin(), healths.end());
}

static __declspec(noinline) void collectUnitHealths(DynamicAutoResolveBattlePlayers *battle, _STL::vector<Real> &out)
{
	Int numPlayers = battle->size();
	_STL::vector<Real> healths(numPlayers, 0);
	UnitHealthCollector collector(healths);
	for (Int side = 0; side < 2; ++side)
		reinterpret_cast<Rva004F6234 *>(battle)->rva004F6234(side, &collector);
	out.swap(healths);
}

// ---- dialog collaborators ------------------------------------------------

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *pointer;
};

class __single_inheritance AptDelegateTarget;
typedef void (AptDelegateTarget::*AptDelegateMethod)(void);

struct DelegateDesc
{
	template <class T, class M> DelegateDesc(T *object, M method)
		: m_object(reinterpret_cast<AptDelegateTarget *>(object))
		, m_method(reinterpret_cast<AptDelegateMethod>(method))
	{
	}

	AptDelegateTarget *m_object;
	AptDelegateMethod m_method;
};

template <class T, class M> __forceinline DelegateDesc MakeDelegate(T *object, M method)
{
	DelegateDesc desc(object, method);
	return desc;
}

class Rva00579E47 : public TreeHintRef00217D4C
{
public:
	Rva00579E47(const DelegateDesc &desc);
	__forceinline ~Rva00579E47()
	{
		if (pointer) ReleaseTreeHintRef00217D4C(pointer);
	}
};

class Rva0057C2CC
{
public:
	void rva0057C2CC();
};

class Rva0057C394 : public Rva0057C2CC
{
public:
	void rva0057C394(const AsciiString &name, const TreeHintRef00217D4C &callback);
};

// The battle the dialog shows: sides of 0x1C bytes at +0x18, id at +0x34.
class Rva003F468D
{
public:
	Int rva003F468D(Int side, Int index);
	Int rva003F4DAE(Int side);

	unsigned char m_pad00[0x18];
	unsigned char *m_sidesStart;	// +0x18
	unsigned char *m_sidesFinish;	// +0x1C
	unsigned char m_pad20[0x34 - 0x20];
	Int m_id;			// +0x34
};

class Rva002E071E
{
public:
	bool rva002E071E(const Rva002E071E *other) const;
};

struct Rva002BA8F1Listener { char opaque[4]; };
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct LivingWorldLogicDialogView
{
	unsigned char m_pad00[0x2C];
	Rva005A0B4CList m_autoResolveObservers;	// +0x2C
	unsigned char m_pad30[0x98 - 0x30];
	Rva002E071E *m_localPlayer;		// +0x98
};

// The same observer list's rowed remover (its spelling carries an unrelated
// parameter type; the receiver is TheLivingWorldLogic + 0x2C).
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *observer);
};
struct LivingWorldLogicObserverView
{
	unsigned char m_pad00[0x2C];
	Rva002B7250 m_autoResolveObservers;	// +0x2C
};

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
};

// MessageStreamSubsystem (0x00A00950); appendMessage is vslot 18.
class MessageStream
{
public:
	virtual void m00();
	virtual void m01();
	virtual void m02();
	virtual void m03();
	virtual void m04();
	virtual void m05();
	virtual void m06();
	virtual void m07();
	virtual void m08();
	virtual void m09();
	virtual void m10();
	virtual void m11();
	virtual void m12();
	virtual void m13();
	virtual void m14();
	virtual void m15();
	virtual void m16();
	virtual void m17();
	virtual GameMessage *appendMessage(int type);
};
extern MessageStream *TheMessageStream;

// The frames between two reinforcement steps (0x00E06780).
extern Int g_DynamicAutoResolveStepFrames;

class Object;
class Rva00575674
{
public:
	void rva00575674(Object *p);
};
class Rva000AD6F4
{
public:
	__forceinline Rva000AD6F4() : m_ptr(0) {}
	~Rva000AD6F4();
	void clear();

	void *m_ptr;
};

// The dialog's movie clip (0x0C bytes, vtable 0x00C781DC); its constructor
// is rowed under an address-named class.
class Rva005EA85A
{
public:
	Rva005EA85A(void *impl, int level, const AsciiString &name);

	unsigned char m_pad00[0x0C];
};

// The dialog's own update step (0x005EA5BD), rowed under an address-named
// receiver.
class Rva005EA183
{
public:
	void rva005EA5BD();
};

// The handle at +0x20 of a player's data is an intrusive reference: copying
// it adds a reference (+0x04 of the target), destroying it releases one.
struct DynamicAutoResolvePlayerHandle
{
	DynamicAutoResolvePlayerHandle() : m_ptr(0) {}
	DynamicAutoResolvePlayerHandle(const DynamicAutoResolvePlayerHandle &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->references;
	}
	~DynamicAutoResolvePlayerHandle()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}

	TargetRef00217D4C *m_ptr;
};

class LivingWorldAutoResolveEventObserver
{
public:
	virtual ~LivingWorldAutoResolveEventObserver() {}
};

namespace StrategicInGameUI
{
	class DynamicAutoResolveDialog
	{
	public:
		class Impl : public LivingWorldAutoResolveEventObserver
		{
		public:
			struct PlayerData
			{
				PlayerData(const DynamicAutoResolvePlayer *player, const DynamicAutoResolveBattlePlayers *players);

				const DynamicAutoResolvePlayer *m_player;	// +0x00
				Int m_battlePlayerID;				// +0x04
				Real m_08;					// +0x08
				Real m_health;					// +0x0C
				Real m_finalHealth;				// +0x10
				Int m_unitCount;				// +0x14
				Int m_finalUnitCount;				// +0x18
				Int m_reinforcementRounds;			// +0x1C
				DynamicAutoResolvePlayerHandle m_20;		// +0x20
			};

			class StateHandler
			{
			public:
				StateHandler(Impl &owner) : m_owner(owner) {}
				virtual ~StateHandler() {}
				virtual void Startup() {}
				virtual void Update() {}

				Impl &m_owner;
			};

			class StartupStateHandler : public StateHandler
			{
			public:
				StartupStateHandler(Impl &owner, Int numPlayers) : StateHandler(owner), m_numPlayers(numPlayers) {}
				virtual void Startup();
				virtual void Update();

				Int m_numPlayers;
			};

			class WaitForBattleStepStateHandler : public StateHandler
			{
			public:
				virtual void Update();
			};

			Impl(void *dialog, Rva0057C394 *frame, Rva003F468D *battle, DynamicAutoResolveBattlePlayers *battlePlayers);
			virtual ~Impl();
			void OnClipLoaded(int, const AsciiString &);

			void *m_dialog;					// +0x04
			Rva0057C394 *m_frame;				// +0x08
			Rva003F468D *m_battle;				// +0x0C
			DynamicAutoResolveBattlePlayers *m_battlePlayers;	// +0x10
			Rva000AD6F4 m_state;				// +0x14
			Real m_maxTotalHealth;				// +0x18
			_STL::vector<PlayerData> m_playerData[2];	// +0x1C
			Rva000AD6F4 m_clip;				// +0x34
			Int m_step;					// +0x38
			Int m_lastStepRound;				// +0x3C
			Int m_nextStepRound;				// +0x40
			Bool m_44;					// +0x44
		};
	};
}

using StrategicInGameUI::DynamicAutoResolveDialog;

enum { SIDE_ALLY, SIDE_ENEMY };

DynamicAutoResolveDialog::Impl::Impl(void *dialog, Rva0057C394 *frame, Rva003F468D *battle, DynamicAutoResolveBattlePlayers *battlePlayers)
	: m_dialog(dialog),
	  m_frame(frame),
	  m_battle(battle),
	  m_battlePlayers(battlePlayers),
	  m_maxTotalHealth(collectMaxTotalHealth(battlePlayers)),
	  m_step(0),
	  m_lastStepRound(0),
	  m_nextStepRound(g_DynamicAutoResolveStepFrames),
	  m_44(true)
{
	{
		Rva00579E47 delegate(MakeDelegate(this, &Impl::OnClipLoaded));
		m_frame->rva0057C394(AsciiString("StrategicDynamicAutoResolve.swf"), delegate);
	}

	reinterpret_cast<LivingWorldLogicDialogView *>(TheLivingWorldLogic)->m_autoResolveObservers.append(reinterpret_cast<Rva002BA8F1Listener *>(this));

	_STL::vector<Real> playerHealths;
	collectUnitHealths(m_battlePlayers, playerHealths);
	_STL::vector<Int> playerUnitCounts;
	collectUnitCounts(m_battlePlayers, playerUnitCounts);

	Rva002E071E *localPlayer = reinterpret_cast<LivingWorldLogicDialogView *>(TheLivingWorldLogic)->m_localPlayer;
	Int numPlayers = 0;
	Int sideCount = (battle->m_sidesFinish - battle->m_sidesStart) / 0x1C;
	for (Int side = 0; side < sideCount; ++side)
	{
		Int count = battle->rva003F4DAE(side);
		for (Int i = 0; i < count; ++i)
		{
			Rva002E071E *player = reinterpret_cast<Rva002E071E *>(battle->rva003F468D(side, i));
			Int panelSide = (player == localPlayer || player->rva002E071E(localPlayer)) ? SIDE_ALLY : SIDE_ENEMY;
			PlayerData newPlayerData(reinterpret_cast<const DynamicAutoResolvePlayer *>(player), m_battlePlayers);
			Real health = playerHealths[newPlayerData.m_battlePlayerID];
			newPlayerData.m_unitCount = playerUnitCounts[newPlayerData.m_battlePlayerID];
			newPlayerData.m_health = health;
			m_playerData[panelSide].push_back(newPlayerData);
			++numPlayers;
		}
	}

	GameMessage *msg = TheMessageStream->appendMessage(0x6BD);
	msg->appendIntegerArgument(m_battle->m_id);
	msg->appendIntegerArgument(m_nextStepRound);

	reinterpret_cast<Rva00575674 *>(&m_state)->rva00575674(reinterpret_cast<Object *>(new StartupStateHandler(*this, numPlayers)));
}

// WB 0x015E63B0 (line 1222): the movie's load callback creates the dialog's
// movie clip once.
void DynamicAutoResolveDialog::Impl::OnClipLoaded(int level, const AsciiString &name)
{
	if (m_clip.m_ptr == 0)
		reinterpret_cast<Rva00575674 *>(&m_clip)->rva00575674(reinterpret_cast<Object *>(new Rva005EA85A(this, level, name)));
}

// Detaches from the living-world logic's auto-resolve observers (rowed
// 0x002B7250) and unloads the movie (rowed 0x0057C2CC); the members then
// destroy the clip, the two player-data vectors and the state.
DynamicAutoResolveDialog::Impl::~Impl()
{
	reinterpret_cast<LivingWorldLogicObserverView *>(TheLivingWorldLogic)->m_autoResolveObservers.rva002B7250(reinterpret_cast<CreateAHeroData *>(this));
	m_frame->rva0057C2CC();
}

// The reinforcement rounds of one battle player in [firstRound, lastRound)
// (WB 0x015E3580, inlined in retail; the bounds are its by-value copies).
static inline Int countReinforcementRounds(const DynamicAutoResolveBattlePlayers *battle, Int battlePlayerID, Int firstRound, Int lastRound)
{
	const _STL::map<Int, Int> &rounds = battle->m_playerData[battlePlayerID].m_reinforcementRounds;
	return _STL::distance(rounds.lower_bound(firstRound), rounds.lower_bound(lastRound));
}

void DynamicAutoResolveDialog::Impl::WaitForBattleStepStateHandler::Update()
{
	DynamicAutoResolveBattlePlayers *battle = m_owner.m_battlePlayers;
	if (battle == 0)
	{
		for (Int side = 0; side < 2; ++side)
		{
			_STL::vector<PlayerData> &players = m_owner.m_playerData[side];
			_STL::vector<PlayerData>::iterator end = players.end();
			for (_STL::vector<PlayerData>::iterator it = players.begin(); it != end; ++it)
				it->m_health = it->m_finalHealth;
		}
		reinterpret_cast<Rva005EA183 *>(&m_owner)->rva005EA5BD();
		return;
	}

	Int lastBattleRound = battle->m_currentRound;
	if (lastBattleRound >= m_owner.m_nextStepRound)
	{
		_STL::vector<Real> playerHealths;
		collectUnitHealths(m_owner.m_battlePlayers, playerHealths);
		_STL::vector<Int> playerUnitCounts;
		collectUnitCounts(m_owner.m_battlePlayers, playerUnitCounts);

		Int firstRound = _STL::max(m_owner.m_lastStepRound, 1);
		Int lastRound = m_owner.m_nextStepRound;
		for (Int side = 0; side < 2; ++side)
		{
			_STL::vector<PlayerData> &players = m_owner.m_playerData[side];
			_STL::vector<PlayerData>::iterator end = players.end();
			for (_STL::vector<PlayerData>::iterator it = players.begin(); it != end; ++it)
			{
				Real zero = 0.0f;
				it->m_health = _STL::max(playerHealths[it->m_battlePlayerID], zero);
				it->m_unitCount = playerUnitCounts[it->m_battlePlayerID];
				it->m_reinforcementRounds = countReinforcementRounds(m_owner.m_battlePlayers, it->m_battlePlayerID, firstRound, lastRound);
			}
		}

		++m_owner.m_step;
		m_owner.m_lastStepRound = m_owner.m_nextStepRound;
		m_owner.m_nextStepRound = lastBattleRound + g_DynamicAutoResolveStepFrames;

		GameMessage *msg = TheMessageStream->appendMessage(0x6BD);
		msg->appendIntegerArgument(m_owner.m_battle->m_id);
		msg->appendIntegerArgument(m_owner.m_nextStepRound);
		reinterpret_cast<Rva005EA183 *>(&m_owner)->rva005EA5BD();
	}
}

