// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G6 /arch:SSE
// stlport
//
// AptTimeLine::rva0051FCA2, retail 0x0051FCA2 (851 bytes).
//
// Identity (target evidence): slot 12 of the time line's primary vftable
// (pointer at 0x0086760C, between the shared Apt window slots and 0x0051E4B0);
// siblings override the same slot (AptSkirmish 0x00523303, AptLanLobby
// 0x004442DB). It refreshes the stats panel, binds the
// "AptTimeLine::OnInitialized/OnButtonContinue/OnButtonSaveReplay/
// CaHAwardNumber" commands, the "AptTimeLine::RenderGraph" custom renderer,
// six "TimeLine:..." status queries and the per-player
// "TimeLine:PlayerColor/PlayerFaction/GraphFocus:%d" queries, then collects
// the player name/faction-icon display (rowed native0x0051FA13).
// The weak WB CollectAllPlayerData name lead describes a larger body and
// is not the original name of this final callee. The binding idiom is the matched AptScoreScreen
// constructor's.
//
// Codegen note: WorldBuilder's twin builds each per-player binding inside
// the loop; retail hoists all three into the call-temporary area
// (-0x3C/-0x4C/-0x5C). cl does that only when it can see that the functor
// holder constructor (row 0x0057BC63) merely reads its binding, so that
// constructor is defined below inline (never inlined), mirroring
// Rva0057BC63FunctorHolder.cpp; `name` lives to the end of the function.

#include <vector>
#include "unicode_string.h"
#include "ascii_string.h"

class GameWindow
{
public:
	GameWindow();
protected:
	virtual ~GameWindow();
	char m_pad04[0x214];
};

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	FunctorBinding(FunctorMethod method, FunctorTarget *target) : m_target(target), m_method(method) {}
	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

class FunctorWrapperHead
{
public:
	FunctorWrapperHead() : m_refCount(0) {}
	virtual void anchor();
	int m_refCount; // +0x04
};

class Rva0057BC63FunctorWrapper : public FunctorWrapperHead
{
public:
	Rva0057BC63FunctorWrapper(const FunctorBinding &binding) : m_binding(binding) {}
	void invoke();
	FunctorBinding m_binding;
};

#include <new>

// The holder constructor (row 0x0057BC63, Rva0057BC63FunctorHolder.cpp) is
// defined here inline. Retail's compiler knew
// it only reads the binding: that is what keeps the per-player bindings
// below hoisted out of the loop across its calls (WorldBuilder's twin builds
// them inside the loop). Declared out of line, cl re-copies them every
// iteration and the frame grows by 0x10.
// The inline body is a select-any COMDAT; all copies fold onto the single
// kept copy (rows live in AptOptionsConstructor.cpp).
class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding)
	{
		m_ptr = new Rva0057BC63FunctorWrapper(binding);
		if (m_ptr != 0)
			m_ptr->m_refCount++;
	}
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}
	FunctorWrapperHead *m_ptr;
};

__forceinline FunctorBinding MakeBinding(FunctorMethod method, FunctorTarget *target)
{
	FunctorBinding binding(method, target);
	return binding;
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(const FunctorBinding &binding) : Rva0057BC63FunctorHolder(binding) {}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

class AptCommandMap;
class AptExternHandler;
class AptOverButtonHandler;

class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);
private:
	_STL::vector<AsciiString> m_names;
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);
private:
	_STL::vector<AsciiString> m_names;
};

class AptOverButtonHandlerAdder
{
public:
	void AddOverButtonHandler(const AsciiString &name, AptRef<AptOverButtonHandler> handler);
private:
	_STL::vector<AsciiString> m_names;
};

class Image;

// The image binder at +0x40 of the Apt window half (0x00524306 family), +0x258
// of the screen: window name to image name, with its rowed setter 0x00524725.
// The image binder at +0x40 of the Apt window half (0x00524306 family):
// window name to image name.
class Rva00524306
{
public:
	void rva00524725(const AsciiString &key, const Image *image);
	void rva00524767(const AsciiString &key, const AsciiString &image);
private:
	_STL::vector<AsciiString> m_names;
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10
	AptOverButtonHandlerAdder m_overButtonHandlers; // +0x1C
private:
	unsigned char m_pad028[0x40 - 0x28];
public:
	Rva00524306 m_imageAdder; // +0x40
private:
	unsigned char m_pad04C[0x58 - 0x4C];
};

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
private:
	AsciiString filename270; // +0x270
	int m_274; // +0x274
	char m_278; // +0x278
	char m_pad279[0x3];
};


class AptCustomRender;

class AptPlayer
{
public:
	void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);
};

// One native manager datum at VA DFE4CC; cast to this unit's receiver view.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class LivingWorldPlayer;
class Player;
class AptTimeLineStats
{
public:
	void rva005BF177();
	void CollectPlayerData(int index, LivingWorldPlayer *player);
	void CollectPlayerData(int index, class Player *player);
};

struct Pair0051E31A;

// The six status queries, by index (0x00C671A0).
static const char *s_statusQueries[] = {
	"TimeLine:StrategicEnd",
	"TimeLine:LocalPlayerIsObserver",
	"TimeLine:NumCahAwards",
	"TimeLine:NumOfPlayers",
	"TimeLine:ShowSaveReplay",
	"TimeLine:ScreenMode"
};

// Native callback words 0091E3A3 and 0091E766 already have rowed owners.
// Both bindings use the complete time-line receiver without adjustment.
class BfmeM1020
{
public:
	void bfmeGo1020M(int unused);
};
struct Rva0051E766Record;
class Rva0051E766
{
public:
	void rva0051E766(int which, char *buffer, bool probing);
	char m_pad00[0x284];
private:
	int m_mode; // +0x284
	_STL::vector<Rva0051E766Record> m_records; // +0x288
	bool m_294; // +0x294
	char m_pad295[0x3];
};

struct Rva0051F7ADRecord;
struct Rva0026F4F4Element;
class AptTimeLineStats;
class LivingWorldPlayer;
class Rva00520923Source;

// One player's row of the time line (0x50 bytes): name, color, faction name,
// status, and the score vectors; m_eventsA and m_eventsB hold the graph's event frames.
struct AptTimeLinePlayer
{
	unsigned char m_pad00[4];
	UnicodeString m_name;        // +0x04
	int m_color;                 // +0x08
	AsciiString m_faction;       // +0x0C, read by PlayerFaction 0x0051EC4E
	int m_side;                  // +0x10: 0 won, 1 dead, 2 left, 3 (0x002E1046)
	unsigned char m_pad14[0x20 - 0x14];
	_STL::vector<Rva0051F7ADRecord> m_20; // +0x20
	_STL::vector<Rva0026F4F4Element> m_eventsA; // +0x2C
	_STL::vector<Rva0026F4F4Element> m_eventsB; // +0x38
	_STL::vector<Rva0026F4F4Element> m_44; // +0x44
};

class AptTimeLine : public _bfme_AptGameWindow
{
public:
	virtual void rva0051FCA2();
	void OnButtonContinue(const char *unused);
	// Bound as "AptTimeLine::OnButtonSaveReplay" and "AptScoreScreen::Save":
	// one body or two folded, so it keeps its address.
	void rva0051E3C3(const char *unused);
	void GraphFocus(int index, const char *value, bool set);
	void PlayerColor(int index, char *value, bool set);
	void PlayerFaction(int index, char *value, bool set);
	void CaHAwardNumber(const char *value);
	void CollectAllPlayerData();
	void RenderGraph(const Pair0051E31A &position, const Pair0051E31A &size, int unused, const char *params);
	void CollectPlayerData(class Player *player, const class GameSlot *slot);
	void CollectPlayerData(LivingWorldPlayer *player, Rva00520923Source *source);
	void rva00520CD1();

	// Retail 0x0051ED7E (345 bytes), the continue action shared by two callbacks.
	void rva0051ED7E();

private:
	unsigned char m_pad27C[0x280 - 0x27C];
	AptTimeLineStats *m_stats;          // +0x280
	int m_gameType;                     // +0x284, 6 for a strategic single-player game
	_STL::vector<AptTimeLinePlayer> m_players; // +0x288
	bool m_observer;                    // +0x294
	unsigned char m_pad295[0x298 - 0x295];
	Image *m_sideImages[4];             // +0x298
	Image *m_eventImageA;               // +0x2A8
	Image *m_eventImageB;               // +0x2AC
	float m_lastMaximum;                // +0x2B0
	int m_lastFrames;                   // +0x2B4
	_STL::vector<float> m_focus;        // +0x2B8, one focus weight per player
	char m_extra[48];                   // +0x2C4
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
void AptTimeLine::rva0051FCA2()
{
	if (m_stats)
		m_stats->rva005BF177();
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&BfmeM1020::bfmeGo1020M);
		AsciiString name("AptTimeLine::OnInitialized");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptTimeLine::OnButtonContinue);
		AsciiString name("AptTimeLine::OnButtonContinue");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptTimeLine::rva0051E3C3);
		AsciiString name("AptTimeLine::OnButtonSaveReplay");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptTimeLine::CaHAwardNumber);
		AsciiString name("AptTimeLine::CaHAwardNumber");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptTimeLine::RenderGraph);
		AsciiString name("AptTimeLine::RenderGraph");
		reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager)->AddCustomRender(name, AptRef<AptCustomRender>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva0051E766::rva0051E766);
		for (int query = 0; query < 6; ++query)
		{
			AsciiString name(s_statusQueries[query]);
			m_externHandlers.AddExternHandler(name, query, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
		}
	}
	AsciiString name;
	for (int index = 0; index < 8; ++index)
	{
		name.format("TimeLine:PlayerColor:%d", index);
		m_externHandlers.AddExternHandler(name, index, AptRef<AptExternHandler>(MakeBinding(reinterpret_cast<FunctorMethod>(&AptTimeLine::PlayerColor), reinterpret_cast<FunctorTarget *>(this))));
		name.format("TimeLine:PlayerFaction:%d", index);
		m_externHandlers.AddExternHandler(name, index, AptRef<AptExternHandler>(MakeBinding(reinterpret_cast<FunctorMethod>(&AptTimeLine::PlayerFaction), reinterpret_cast<FunctorTarget *>(this))));
		name.format("TimeLine:GraphFocus:%d", index);
		m_externHandlers.AddExternHandler(name, index, AptRef<AptExternHandler>(MakeBinding(reinterpret_cast<FunctorMethod>(&AptTimeLine::GraphFocus), reinterpret_cast<FunctorTarget *>(this))));
	}
	CollectAllPlayerData();
}
