// ?rva0051FCA2@AptTimeLine@@UAEXXZ
// partial score=0.99 date=2026-10-09
// ?rva0051FCA2@AptTimeLine@@UAEXXZ
// partial score=0.99 date=2026-10-09
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

#include <vector>
#include "unicode_string.h"
#include "ascii_string.h"

class GameWindow
{
protected:
	virtual ~GameWindow();
private:
	unsigned char m_pad004[0x218 - 4];
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
	void *m_vtbl;
	int m_refCount; // +0x04
};

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
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

// The image binder at +0x40 of the Apt window half (0x00524306 family):
// window name to image name.
class Rva00524306
{
public:
	void rva00524767(const AsciiString &name, const AsciiString &image);
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
	AsciiString m_filename; // +0x270
	int m_274;
	char m_278;
};


class AptCustomRender;

class AptPlayer
{
public:
	void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);
};

extern AptPlayer *TheAptPlayer;

class AptTimeLineStats
{
public:
	void rva005BF177();
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

class AptTimeLine : public _bfme_AptGameWindow
{
public:
	virtual void rva0051FCA2();
	void OnInitialized(const char *unused);
	void OnButtonContinue(const char *unused);
	// Bound as "AptTimeLine::OnButtonSaveReplay" and "AptScoreScreen::Save".
	void rva0051E3C3(const char *unused);
	void CaHAwardNumber(const char *value);
	void RenderGraph(const Pair0051E31A &a, const Pair0051E31A &b, int c, const char *d);
	void rva0051E766(int query, char *value, bool set);
	void PlayerColor(int index, char *value, bool set);
	void PlayerFaction(int index, char *value, bool set);
	void GraphFocus(int index, const char *value, bool set);
	void rva0051FA13();
private:
	unsigned char m_pad27C[0x280 - 0x27C];
	AptTimeLineStats *m_stats; // +0x280
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
void AptTimeLine::rva0051FCA2()
{
	if (m_stats)
		m_stats->rva005BF177();
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptTimeLine::OnInitialized);
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
		TheAptPlayer->AddCustomRender(name, AptRef<AptCustomRender>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptTimeLine::rva0051E766);
		int query = 0;
		FunctorBinding binding = MakeBinding(method, reinterpret_cast<FunctorTarget *>(this));
		for (; query < 6; ++query)
		{
			AsciiString name(s_statusQueries[query]);
			m_externHandlers.AddExternHandler(name, query, AptRef<AptExternHandler>(binding));
		}
	}
	AsciiString name;
	{
		int index = 0;
		FunctorMethod colorMethod = reinterpret_cast<FunctorMethod>(&AptTimeLine::PlayerColor);
		FunctorBinding colorBinding = MakeBinding(colorMethod, reinterpret_cast<FunctorTarget *>(this));
		FunctorMethod factionMethod = reinterpret_cast<FunctorMethod>(&AptTimeLine::PlayerFaction);
		FunctorBinding factionBinding = MakeBinding(factionMethod, reinterpret_cast<FunctorTarget *>(this));
		FunctorMethod focusMethod = reinterpret_cast<FunctorMethod>(&AptTimeLine::GraphFocus);
		FunctorBinding focusBinding = MakeBinding(focusMethod, reinterpret_cast<FunctorTarget *>(this));
		for (; index < 8; ++index)
		{
			name.format("TimeLine:PlayerColor:%d", index);
			m_externHandlers.AddExternHandler(name, index, AptRef<AptExternHandler>(colorBinding));
			name.format("TimeLine:PlayerFaction:%d", index);
			m_externHandlers.AddExternHandler(name, index, AptRef<AptExternHandler>(factionBinding));
			name.format("TimeLine:GraphFocus:%d", index);
			m_externHandlers.AddExternHandler(name, index, AptRef<AptExternHandler>(focusBinding));
		}
	}
	rva0051FA13();
}
