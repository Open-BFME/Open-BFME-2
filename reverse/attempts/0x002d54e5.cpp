// ?init@AptPalantir@@QAEXXZ
// partial score=0.99 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// The palantir's Apt implementation (WorldBuilder: Palantir.cpp,
// Palantir::Impl; its Apt callbacks are rowed under AptPalantir, the class
// name the registration strings carry):
//
// - AptPalantir::AptPalantir, retail 0x002D57B6..0x002D628F (2777 bytes),
//   EH thiscall ret 8, WB twin 0x00F41A50 (assert line 941): the same member
//   order and the same 28 Apt registrations. The caller 0x002D638E
//   allocates 0x154 bytes and passes the owning Palantir subsystem and the
//   level its Apt\ load returned.
// - ~AptPalantir, retail 0x002D5380 (357 bytes; WB 0x00F43790).
// - init, retail 0x002D54E5 (229 bytes; WB 0x00F43B70), is banked: it is exact
//   but its playback constructor 0x00524C1B has no row or name yet.
// - the subsystem's reset of the palantir's flags, retail 0x002D55EF.
#include <map>
#include <list>

#include "ascii_string.h"
#include "Lib/Coord2D.h"
#include "../GameWindowManagerRecordView.h"

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

void *__cdecl operator new(unsigned int size);

// The holder constructor (row 0x0057BC63, Rva0057BC63FunctorHolder.cpp) is
// visible here as an inline, never-inlined definition, as in
// AptOptionsConstructor.cpp: retail's compiler knew it only reads the binding.
class Rva0057BC63FunctorHolder
{
public:
	__declspec(noinline) Rva0057BC63FunctorHolder(const FunctorBinding &binding)
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
class AptCustomRender;

class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

private:
	unsigned char m_names[0xC];
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);

private:
	unsigned char m_names[0xC];
};

class AptOverButtonHandlerAdder
{
public:
	void AddOverButtonHandler(int level, const AsciiString &name, AptRef<AptOverButtonHandler> handler);

private:
	unsigned char m_names[0x18];
};

class AptCustomRenderAdder
{
public:
	void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);

private:
	unsigned char m_names[0x24];
};

// The 0x58-byte Apt callback registry base (vtable 0x00C02A80): constructor
// 0x002D2C34 (pinned by address), destructor 0x005248D0. As in its other
// users (AptRowListConstructor.cpp and siblings) the view is novtable: the
// real constructor installs its own vtable, retail stores none before it.
class Rva002D2C34
{
public:
	void rva002D2C34();
};

class __declspec(novtable) Rva005248D0
{
public:
	__forceinline Rva005248D0() { ((Rva002D2C34 *)this)->rva002D2C34(); }
	virtual ~Rva005248D0();

	AptCommandMapAdder m_commandMaps;		// +0x04
	AptExternHandlerAdder m_externHandlers;		// +0x10
	AptOverButtonHandlerAdder m_overButtonHandlers;	// +0x1C
	AptCustomRenderAdder m_customRenders;		// +0x34
};

// Members with rowed constructors taking the Apt level.
class Rva00529FABClearForward
{
public:
	void clear();
};

class Rva005288B8
{
public:
	void rva005288B8();
};

class Rva0052AC0A
{
public:
	void rva0052AC0A();
};

class Rva00526F80
{
public:
	void rva00526F80();
};

class Rva0052A244
{
public:
	Rva0052A244(void *level);
	~Rva0052A244() { reinterpret_cast<Rva00529FABClearForward *>(this)->clear(); }

private:
	void *m_0;
};

class Rva00528AC3
{
public:
	Rva00528AC3(void *level);
	~Rva00528AC3() { reinterpret_cast<Rva005288B8 *>(this)->rva005288B8(); }

private:
	void *m_0;
};

class Rva0052AF1C
{
public:
	Rva0052AF1C(void *level);
	~Rva0052AF1C() { reinterpret_cast<Rva0052AC0A *>(this)->rva0052AC0A(); }

private:
	void *m_0;
};

class Rva002D5188ResourceBar
{
public:
	Rva002D5188ResourceBar();
	~Rva002D5188ResourceBar();

private:
	unsigned char m_pad[0x28];
};

// +0xC0: initialized by the rowed 0x00526F46.
class Rva00526F46
{
public:
	__forceinline Rva00526F46() { rva00526F46(); }
	~Rva00526F46() { reinterpret_cast<Rva00526F80 *>(this)->rva00526F80(); }
	Rva00526F46 *rva00526F46();

private:
	void *m_0;
};

// The three Apt sub-movie holders (rowed clears) and two more owned pointers.
class Rva002D3894
{
public:
	Rva002D3894() : m_movie(0) {}
	~Rva002D3894() { clear(); }
	void clear();

	void *m_movie;
};

class Rva002D38D1
{
public:
	Rva002D38D1() : m_movie(0) {}
	~Rva002D38D1() { clear(); }
	void clear();

	void *m_movie;
};

class Rva002D3931
{
public:
	Rva002D3931() : m_movie(0) {}
	~Rva002D3931() { clear(); }
	void clear();

	void *m_movie;
};

void __cdecl operator delete(void *pointer);

// An owned raw allocation, released and cleared on destruction.
class AptPalantirOwnedEC
{
public:
	AptPalantirOwnedEC() : m_ptr(0) {}
	~AptPalantirOwnedEC()
	{
		void *pointer = m_ptr;
		m_ptr = 0;
		delete pointer;
	}

	void *m_ptr;
};

// The radar view-box corners (ClipRadar takes PalantirPoint pointers): the
// array is built by `eh vector constructor iterator' with the shared empty
// constructor 0x0047A6A9 and destructor 0x000B3FD0, and zero-filled at the
// end through the STLport fill 0x000AD7E4.
struct PalantirPoint : public Coord2D
{
	PalantirPoint() {}
	~PalantirPoint() {}
};

struct AptPalantirSlot
{
	AptPalantirSlot() : m_0(0), m_4(false) {}

	int m_0;
	bool m_4;
};

class Rva002D3573;

// The +0x11C int map (STLport constructor 0x0033C432); its rowed destructor
// 0x002D50AD and clear 0x002D43C6 carry this address-derived name.
class Rva002D394B : public _STL::map<int, void *>
{
public:
	~Rva002D394B();
	void rva002D43C6();
};

// Palantir::Impl::init's window: a GadgetCreateView handed to the window
// manager's createFromView (vslot 34) and Zero Hour's WinInstanceData.
class WinInstanceData
{
public:
	WinInstanceData();
	virtual ~WinInstanceData();

private:
	unsigned char m_pad004[0x1A8 - 4];
};

class GameWindowManager
{
public:
#define V(n) virtual void unusedSlot##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33)
#undef V
	virtual GameWindow *createFromView(GadgetCreateView *view);	// vslot 34
	virtual void winDestroy(GameWindow *window);			// vslot 35
};
extern GameWindowManager *TheWindowManager;

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
WindowMsgHandledType LeftHUDInput(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2);

struct PalantirMovieWindow
{
	unsigned char m_pad000[0x1F4];
	int m_1f4;
};

// The 0x3C-byte movie playback the palantir drives: its constructor
// 0x00524C1B (pinned under the name of its bank, Rva00524BB4) takes the frame
// callback holder by value; vslot 1 starts it.
struct TreeHintRef00217D4C : public Rva0057BC63FunctorHolder
{
	TreeHintRef00217D4C(const FunctorBinding &binding) : Rva0057BC63FunctorHolder(binding) {}
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

class Rva00524BB4
{
public:
	Rva00524BB4(TreeHintRef00217D4C callback);
	virtual ~Rva00524BB4();
	virtual void start();

private:
	unsigned char m_pad004[0x3C - 4];
};

class Rva002D2E30
{
public:
	void rva002D2E30(int frame);
};

class AptPalantir : public Rva005248D0
{
public:
	AptPalantir(Rva002D3573 *owner, int level);
	virtual ~AptPalantir();
	void init();

	void OnInitialized(const char *unused);
	void OnClosed(const char *unused);
	void OnBttnSpellStore(const char *unused);
	void OnBttnOptions(const char *unused);
	void OnBttnObjectives(const char *unused);
	void OnBttnMovie(const char *unused);
	void OnBttnObserveNextPlayer(const char *unused);
	void OnBttnObservePriorPlayer(const char *unused);
	void OnBttnMessenger(const char *value);
	void OnHelpBoxLoaded(const char *path);
	void OnHelpBoxUnloaded(const char *unused);
	void OnHeroSelectLoaded(const char *path);
	void OnHeroSelectUnloaded(const char *unused);
	void OnPlanningModeUILoaded(const char *path);
	void OnPlanningModeUIUnloaded(const char *unused);
	void PalantirMinLOD(int query, char *result, bool skip);
	void rva002D3D61(const char *unused);
	void rva002D4DD0(const char *unused);
	void rva002D4E71(const char *unused);
	void rva002D3E29(const char *unused);
	void rva002D3E84(const char *unused);
	void ClipRadar(const PalantirPoint *, const PalantirPoint *, void *, void *);
	void RenderRadarViewBox(const PalantirPoint *, const PalantirPoint *, void *, void *);
	void RenderMovie(const PalantirPoint *, const PalantirPoint *, void *, void *);
	void RenderGlobe(const PalantirPoint *, const PalantirPoint *, void *, void *);

private:
	friend class RadarWindowOverrideSource;

	Rva002D3573 *m_owner;			// +0x58
	int m_level;				// +0x5C
	bool m_60b0 : 1;			// +0x60
	bool m_60b1 : 1;
	bool m_60b2 : 1;
	PalantirMovieWindow *m_movieWindow;	// +0x64
	int m_68;
	int m_6c;
	int m_70;
	int m_74;
	Rva00524BB4 *m_moviePlayback;		// +0x78
	bool m_7c;
	bool m_7d;
	bool m_7eb0 : 1;			// +0x7E
	bool m_7eb1 : 1;
	bool m_7eb2 : 1;
	bool m_7eb3 : 1;
	bool m_7eb4 : 1;
	bool m_7eb5 : 1;
	bool m_7eb6 : 1;
	bool m_7eb7 : 1;
	bool m_7fb0 : 1;			// +0x7F
	int m_80;
	int m_84;
	int m_88;
	Rva0052A244 m_8c;
	Rva00528AC3 m_90;
	Rva0052AF1C m_94;
	Rva002D5188ResourceBar m_resourceBar;	// +0x98
	Rva00526F46 m_c0;
	Rva002D3894 m_heroSelect;		// +0xC4
	Rva002D38D1 m_helpBox;			// +0xC8
	Rva002D3931 m_planningModeUI;		// +0xCC
	bool m_d0[20];				// +0xD0
	bool m_e4;
	bool m_e5;
	int m_e8;
	AptPalantirOwnedEC m_ec;
	int m_f0;
	bool m_f4;
	AsciiString m_f8;
	PalantirPoint m_viewBox[4];		// +0xFC
	Rva002D394B m_11c;
	bool m_128;
	AptPalantirSlot m_slots[3];		// +0x12C
	int m_144;
	_STL::list<int> m_148;
	int m_14c;
	bool m_150;
};

class Rva002D317C
{
public:
	void rva002D317C(const float *, const float *, int, int);
};

void __stdcall bfmeApplyYU(int);
void __stdcall rva0058C100ObserveNext(void *);

// Two over-button handlers are rowed as stdcall free functions (0x002D4F2D,
// 0x002D3DCE); their binding carries the plain code address with a zero
// adjustor, like every other member binding here.
struct AptPalantirRawMethod
{
	const void *m_function;
	int m_adjustor;
};

#pragma pointers_to_members(full_generality, multiple_inheritance)

#define APT_COMMAND(NAME, METHOD) \
	{ \
		FunctorMethod method = reinterpret_cast<FunctorMethod>(METHOD); \
		AsciiString name(NAME); \
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this)))); \
	}

#define APT_OVER_BUTTON(NAME, METHOD) \
	{ \
		FunctorMethod method = METHOD; \
		AsciiString name(NAME); \
		m_overButtonHandlers.AddOverButtonHandler(m_level, name, AptRef<AptOverButtonHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this)))); \
	}

#define APT_RENDER(NAME, METHOD) \
	{ \
		FunctorMethod method = reinterpret_cast<FunctorMethod>(METHOD); \
		AsciiString name(NAME); \
		m_customRenders.AddCustomRender(name, AptRef<AptCustomRender>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this)))); \
	}

__forceinline FunctorMethod StdcallMethod(const void *function)
{
	AptPalantirRawMethod raw = { function, 0 };
	return *reinterpret_cast<FunctorMethod *>(&raw);
}

AptPalantir::AptPalantir(Rva002D3573 *owner, int level)
	: m_owner(owner),
	  m_level(level),
	  m_60b0(false),
	  m_60b1(false),
	  m_60b2(true),
	  m_movieWindow(0),
	  m_moviePlayback(0),
	  m_7c(true),
	  m_7d(true),
	  m_7eb0(false),
	  m_7eb1(false),
	  m_7eb3(false),
	  m_7eb4(false),
	  m_7eb5(false),
	  m_7eb6(false),
	  m_7eb7(false),
	  m_7fb0(false),
	  m_80(-1),
	  m_84(0),
	  m_88(1),
	  m_8c(reinterpret_cast<void *>(level)),
	  m_90(reinterpret_cast<void *>(level)),
	  m_94(reinterpret_cast<void *>(level)),
	  m_e4(false),
	  m_e5(false),
	  m_e8(0),
	  m_f0(-1),
	  m_f4(false),
	  m_128(true),
	  m_144(0),
	  m_14c(0),
	  m_150(false)
{
	m_74 = 0;
	m_70 = 0;
	m_6c = 0;
	m_68 = 0;

	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptPalantir::PalantirMinLOD);
		AsciiString name("PalantirMinLOD");
		m_externHandlers.AddExternHandler(name, 0, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	APT_COMMAND("AptPalantir::OnInitialized", &AptPalantir::OnInitialized)
	APT_COMMAND("AptPalantir::OnClosed", &AptPalantir::OnClosed)
	APT_OVER_BUTTON("PalantirButtons/Buttons/PlayerMagic/ButtonClip/", reinterpret_cast<FunctorMethod>(&AptPalantir::rva002D4DD0))
	APT_OVER_BUTTON("PalantirButtons/Buttons/Options", StdcallMethod(&bfmeApplyYU))
	APT_OVER_BUTTON("PalantirButtons/Buttons/Objectives/ButtonClip/", reinterpret_cast<FunctorMethod>(&AptPalantir::rva002D4E71))
	APT_OVER_BUTTON("PalantirButtons/Buttons/PlayerPowerCap/", reinterpret_cast<FunctorMethod>(&AptPalantir::rva002D3D61))
	APT_OVER_BUTTON("ObserverStuff/NextPlayerBttn", StdcallMethod(&rva0058C100ObserveNext))
	APT_OVER_BUTTON("ObserverStuff/PriorPlayerBttn", reinterpret_cast<FunctorMethod>(&AptPalantir::rva002D3E29))
	APT_OVER_BUTTON("messengerButton/", reinterpret_cast<FunctorMethod>(&AptPalantir::rva002D3E84))
	APT_COMMAND("AptPalantir::OnBttnSpellStore", &AptPalantir::OnBttnSpellStore)
	APT_COMMAND("AptPalantir::OnBttnOptions", &AptPalantir::OnBttnOptions)
	APT_COMMAND("AptPalantir::OnBttnObjectives", &AptPalantir::OnBttnObjectives)
	APT_COMMAND("AptPalantir::OnBttnMovie", &AptPalantir::OnBttnMovie)
	APT_COMMAND("AptPalantir::OnBttnObserveNextPlayer", &AptPalantir::OnBttnObserveNextPlayer)
	APT_COMMAND("AptPalantir::OnBttnObservePriorPlayer", &AptPalantir::OnBttnObservePriorPlayer)
	APT_COMMAND("AptPalantir::OnBttnMessenger", &AptPalantir::OnBttnMessenger)
	APT_COMMAND("AptPalantir::OnHelpBoxLoaded", &AptPalantir::OnHelpBoxLoaded)
	APT_COMMAND("AptPalantir::OnHelpBoxUnloaded", &AptPalantir::OnHelpBoxUnloaded)
	APT_COMMAND("AptPalantir::OnHeroSelectLoaded", &AptPalantir::OnHeroSelectLoaded)
	APT_COMMAND("AptPalantir::OnHeroSelectUnloaded", &AptPalantir::OnHeroSelectUnloaded)
	APT_COMMAND("AptPalantir::OnPlanningModeUILoaded", &AptPalantir::OnPlanningModeUILoaded)
	APT_COMMAND("AptPalantir::OnPlanningModeUIUnloaded", &AptPalantir::OnPlanningModeUIUnloaded)
	APT_RENDER("AptPalantir::ClipRadar", &AptPalantir::ClipRadar)
	APT_RENDER("AptPalantir::RenderRadar", &Rva002D317C::rva002D317C)
	APT_RENDER("AptPalantir::RenderRadarViewBox", &AptPalantir::RenderRadarViewBox)
	APT_RENDER("AptPalantir::RenderMovie", &AptPalantir::RenderMovie)
	APT_RENDER("AptPalantir::RenderGlobe", &AptPalantir::RenderGlobe)

	_STL::fill(m_d0, m_d0 + 20, false);
	PalantirPoint origin;
	origin.x = 0.0f;
	origin.y = 0.0f;
	_STL::fill(m_viewBox, m_viewBox + 4, origin);
}


// The palantir subsystem (Rva002D3573; the owner AptPalantir keeps at +0x58)
// holds its implementation at +0x10.
class RadarWindowOverrideSource
{
public:
	void rva002D55EF();

private:
	AptPalantir *impl() const { return m_impl; }

	unsigned char m_pad000[0x10];
	AptPalantir *m_impl;			// +0x10
};

// Retail 0x002D55EF..0x002D563D (78 bytes; WB 0x00F48780): clear the
// palantir's 20 button flags, its +0xE4/+0xE5 flags and its +0x11C map
// (the rowed STLport clear 0x002D43C6).
void RadarWindowOverrideSource::rva002D55EF()
{
	_STL::fill(impl()->m_d0, impl()->m_d0 + 20, false);
	impl()->m_e4 = false;
	impl()->m_11c.rva002D43C6();
	impl()->m_e5 = false;
}

// Palantir::Impl::~Impl, retail 0x002D5380..0x002D54E5 (357 bytes; WB
// 0x00F43790): unload the palantir movie, destroy the movie playback and
// the input window, detach the listed observers, then the members in reverse.
class Rva00224B7DTarget
{
public:
	bool method(int level);
};

class Rva00224BC9Owner
{
public:
	bool check();
};

struct AptPalantirListener
{
	unsigned char m_pad00[0x08];
	AptPalantir *m_owner;			// +0x08
};

AptPalantir::~AptPalantir()
{
	reinterpret_cast<Rva00224B7DTarget *>(g_bfmeAptWindowManager)->method(m_level);
	reinterpret_cast<Rva00224BC9Owner *>(g_bfmeAptWindowManager)->check();
	::delete m_moviePlayback;
	m_moviePlayback = 0;
	TheWindowManager->winDestroy(reinterpret_cast<GameWindow *>(m_movieWindow));
	m_movieWindow = 0;
	_STL::list<int>::iterator end = m_148.end();
	for (_STL::list<int>::iterator it = m_148.begin(); it != end; ++it)
		reinterpret_cast<AptPalantirListener *>(*it)->m_owner = 0;
}
// Palantir::Impl::init, retail 0x002D54E5..0x002D55CA (229 bytes; WB
// 0x00F43B70, Palantir.cpp): with the Apt window manager up, create the
// palantir's input window (-128 bounds, LeftHUDInput) and its movie playback.
void AptPalantir::init()
{
	if (g_bfmeAptWindowManager)
	{
		WinInstanceData instData;
		GadgetCreateView view;
		view.status = 0x8000408;
		view.x = -128;
		view.y = -128;
		view.width = -128;
		view.height = -128;
		*reinterpret_cast<WindowMsgHandledType (**)(GameWindow *, unsigned int, unsigned int, unsigned int)>(view.unknown32) = LeftHUDInput;
		m_movieWindow = reinterpret_cast<PalantirMovieWindow *>(TheWindowManager->createFromView(&view));
		m_movieWindow->m_1f4 = 0;
		m_moviePlayback = new Rva00524BB4(TreeHintRef00217D4C(MakeBinding(reinterpret_cast<FunctorMethod>(&Rva002D2E30::rva002D2E30), reinterpret_cast<FunctorTarget *>(this))));
		m_moviePlayback->start();
	}
}
