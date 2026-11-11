// cl: /I. /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// AptPalantir::update, retail 0x002D65F6..0x002D6AE2 (1260 bytes, EH thiscall,
// the palantir's per-frame Apt update; WorldBuilder twin Palantir::Impl update
// 0x00F43EC0). Target evidence: the REL32 callees and data addresses, the field
// offsets and the call order are read from the retail bytes. The member
// holders below are private views for this unit: the unit carries only what
// update touches (the constructor view lives in AptPalantirConstructor.cpp).
// Structural inferences: the statement forms; the objective-change loop keeps
// its two byte flags (old/now) in 4-byte padded frame slots (Flag4), which is
// what places them at retail's int-aligned homes; one compiler barrier before
// the faction string block keeps retail's EBX/EDI roles.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <map>
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

#include "ascii_string.h"
#include "Code/Libraries/Include/Lib/Coord2D.h"
#include "Code/GameEngine/Source/GameClient/GUI/GameWindowManagerRecordView.h"

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

#include "../../../../Include/GameClient/FunctorBinding.h"

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
// defined here inline, as in AptOptionsConstructor.cpp: retail's compiler
// knew it only reads the binding. The inline body is a select-any COMDAT;
// all copies fold onto the single kept copy at link time.
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
class AptCustomRender;

#include "../../../../../Libraries/Source/Apt/AptCommandMapAdder.h"

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
// 0x002D2C34, destructor 0x005248D0. Use the matched constructor provider,
// as in AptPalantirConstructor.cpp; it installs the registry vtable itself.

class __declspec(novtable) Rva005248D0
{
public:
	Rva005248D0();
	virtual ~Rva005248D0();
 int rva002D2C21() const;

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
	void rva0052AC0F();

private:
	void *m_0;
};

class Rva002D5188ResourceBar
{
public:
	Rva002D5188ResourceBar();
	~Rva002D5188ResourceBar();
	void update();

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

// Native +C8 cleanup calls the existing rowed Rva002D38EB destructor
// folded with clear2D38D1. Use its neutral provider name; no claim of an
// original holder identity. The same4B pointer and zero construction remain.
class Rva002D38EB
{
public:
	Rva002D38EB() : m_movie(0) {}
	~Rva002D38EB();
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

// An owned raw allocation, released and cleared on destruction.
struct AptPalantirSpellPointCost
{
	int m_count;
	int m_amount;
};

class AptPalantirOwnedEC
{
public:
	AptPalantirOwnedEC() : m_ptr(0) {}
	~AptPalantirOwnedEC() { clear(); }
	void clear()
	{
		void *pointer = m_ptr;
		m_ptr = 0;
		delete pointer;
	}
	AptPalantirSpellPointCost *operator->() const { return m_ptr; }

	AptPalantirSpellPointCost *m_ptr;
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
#include "../../../../Include/GameClient/Bfme2WinInstanceData.h"

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
	void update();

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
	void HandleOverSpellStoreButton(const char *unused);
	void HandleOverObjectivesButton(const char *unused);
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
	Rva002D38EB m_helpBox;			// +0xC8
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

__declspec(noinline) inline AptPalantir::AptPalantir(Rva002D3573 *owner, int level)
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
	APT_OVER_BUTTON("PalantirButtons/Buttons/PlayerMagic/ButtonClip/", reinterpret_cast<FunctorMethod>(&AptPalantir::HandleOverSpellStoreButton))
	APT_OVER_BUTTON("PalantirButtons/Buttons/Options", StdcallMethod(&bfmeApplyYU))
	APT_OVER_BUTTON("PalantirButtons/Buttons/Objectives/ButtonClip/", reinterpret_cast<FunctorMethod>(&AptPalantir::HandleOverObjectivesButton))
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
	bool hasOverrideWindow() const;
	void rva002D4240(bool immediate);

private:
	AptPalantir *impl() const { return m_impl; }

	unsigned char m_pad000[0x10];
	AptPalantir *m_impl;			// +0x10
};

// Retail 0x002D55EF..0x002D563D (78 bytes; WB 0x00F48780): clear the
// palantir's 20 button flags, its +0xE4/+0xE5 flags and its +0x11C map
// (the rowed STLport clear 0x002D43C6).
__declspec(noinline) inline void RadarWindowOverrideSource::rva002D55EF()
{
	_STL::fill(impl()->m_d0, impl()->m_d0 + 20, false);
	impl()->m_e4 = false;
	impl()->m_11c.rva002D43C6();
	impl()->m_e5 = false;
}

// Palantir::Impl::~Impl, retail 0x002D5380..0x002D54E5 (357 bytes; WB
// 0x00F43790): unload the palantir movie, destroy the movie playback and
// the input window, detach the listed observers, then the members in reverse.
#include "../../../../../Libraries/Source/Apt/AptPlayerClass.h"

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

__declspec(noinline) inline AptPalantir::~AptPalantir()
{
	reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager)->RemoveLevel(m_level);
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
__declspec(noinline) inline void AptPalantir::init()
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
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

#include "../../../../Include/Common/BfmeSelectionState.h"
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva002E063B
{
public:
	int get() const;
};
struct AptPalantirLivingWorldView
{
	unsigned char m_pad000[0x98];
	Rva002E063B *m_98;			// +0x98
};

class Rva00E02D6C;
extern Rva00E02D6C *TheCampaignManager;
struct AptPalantirCampaignView
{
	unsigned char m_pad00[0x2C];
	bool m_2c;				// +0x2C
};

extern GameLogic *TheGameLogic;
#include "../../../../Include/Common/BfmeGlob939D.h"

class PlayerList;
extern PlayerList *ThePlayerList;
class Rva002A7DD0
{
public:
	bool rva002A7DD0();
};
struct AptPalantirFactionSource
{
	unsigned char m_pad000[0x18];
	AsciiString m_name;			// +0x18
	unsigned char m_pad01C[0x151 - 0x1C];
	bool m_151;				// +0x151
};
class BfmeMemberRV
{
public:
	unsigned char m_pad000[0x34];
	AptPalantirFactionSource *m_34;		// +0x34
	unsigned char m_pad038[0x74C - 0x38];
	AsciiString m_74c;			// +0x74C
};
#include "../../../../Include/GameClient/BfmeThingRV.h"

class AudioManager;
extern AudioManager *TheAudio;
class AptPalantirAudioView
{
public:
#define V(n) virtual void unusedSlot##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89)
	V(90) V(91) V(92) V(93) V(94) V(95) V(96) V(97) V(98)
#undef V
	virtual char slot99();			// +0x18C
};

#include "../../../../Include/Common/Radar.h"
extern Radar *TheRadar;

struct GlobalA04450;
extern GlobalA04450 *g_Va00A04450;
int Rva0050E9CDGet();

class Rva004266A1
{
public:
	unsigned char rva0042680D(int index);
	char m_pad00[4];
	int m_begin;
	int m_end;
};
struct Rva0039B95FHolder
{
	char m_pad00[0x10];
	Rva004266A1 *m_obj;
};
extern Rva0039B95FHolder *TheMissionObjectiveTracker;

namespace _STL {
template <> bool &map<int, bool, less<int>, allocator<pair<const int, bool> > >::operator[](const int &);
}
// The map<int,int> find path takes less<int> inline, as in retail; the
// imported specialization keeps this TU from emitting its own copy.
template <> __declspec(dllimport) __forceinline bool _STL::less<int>::operator()(const int &left, const int &right) const { return left < right; }

class MovieWindowPlayback
{
public:
#define V(n) virtual void unusedSlot##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8)
#undef V
	virtual void stop();			// +0x24
	virtual void advance();			// +0x28
	float rva00524A84();

	unsigned char m_pad004[0x24 - 4];
	bool m_b0 : 1;				// +0x24
	bool m_b1 : 1;
	bool m_b2 : 1;
};

class Rva00527F65PlanningUpdateForward
{
public:
	void update();
};
class Rva005258B2
{
public:
	void rva00526F0B();
	void rva005258B9(const AsciiString *faction);
};
class Rva00528FE0
{
public:
	bool rva00528FE0();
};
class Rva00529FB7
{
public:
	void rva00529FB7();
};
class PalantirCommandInterface
{
public:
	void rva00529FBE();
};
class AptInGameSideCommandBar
{
public:
	void Update();
};
#include "../../../../Include/Common/InGameHelpBoxMovieClip.h"
class Rva002D5711
{
public:
	void rva002D5711(const AsciiString &faction);
};
class Rva002D62AB
{
public:
	void updateButtonFlash();
};
class Palantir
{
public:
	class Impl
	{
	public:
		void UpdatePlayerStats();
		class RadarPing
		{
		public:
			void Update();
		};
	};
};

class Rva00222A8BTarget;
void Rva00516F21Invoke(Rva00222A8BTarget *, void *, const char *, const char *);

int ComputeFrameState();
void setPalantirFrameState(int state);
void setHideScroll();
void showMovieButton();
void hideMovieButton();
void fadePalantirButtonsZero();
void fadePalantirButtonsOne();
void showObserverStuff();
void hideObserverStuff();
void setFlashObjectivesButton(bool flash);
void setPlayerPowerCapState(bool capped);
void playPlayerSpellPointEffect();
void Rva003FF02EPowerCap(int points);
void Rva003FECCASetPlayerFaction(void **faction);

struct Flag4 { unsigned char v; unsigned char pad[3]; };
void AptPalantir::update()
{
	RadarWindowOverrideSource *owner = reinterpret_cast<RadarWindowOverrideSource *>(m_owner);
	if (owner->hasOverrideWindow() && TheLivingWorldLogic && reinterpret_cast<BfmeSelectionState *>(TheLivingWorldLogic)->isSelectionLocked())
		owner->rva002D4240(true);
	m_94.rva0052AC0F();
	if (m_heroSelect.m_movie)
		reinterpret_cast<Rva005258B2 *>(m_heroSelect.m_movie)->rva00526F0B();
	if (m_planningModeUI.m_movie)
		reinterpret_cast<Rva00527F65PlanningUpdateForward *>(m_planningModeUI.m_movie)->update();
	if (!reinterpret_cast<RadarWindowOverrideSource *>(m_owner)->hasOverrideWindow())
		return;

	int frameState = ComputeFrameState();
	if (frameState != m_e8)
	{
		setPalantirFrameState(frameState);
		m_80 = -1;
		m_7eb0 = false;
		m_7eb1 = false;
		m_7eb3 = false;
		m_7eb4 = false;
		m_7eb5 = false;
		m_88 = 1;
		m_e8 = frameState;
		if (reinterpret_cast<Rva00528FE0 *>(&m_8c)->rva00528FE0())
			reinterpret_cast<Rva00529FB7 *>(&m_8c)->rva00529FB7();
		return;
	}

	reinterpret_cast<PalantirCommandInterface *>(&m_8c)->rva00529FBE();
	reinterpret_cast<AptInGameSideCommandBar *>(&m_90)->Update();
	m_resourceBar.update();
	InGameHelpBoxMovieClip *helpBox = reinterpret_cast<InGameHelpBoxMovieClip *>(m_helpBox.m_movie);
	if (helpBox)
	{
		helpBox->Move(reinterpret_cast<AptPalantirAudioView *>(TheAudio)->slot99() != 0);
		reinterpret_cast<InGameHelpBoxMovieClip *>(m_helpBox.m_movie)->Update();
	}
	if (m_7d)
	{
		if (TheRadar)
			TheRadar->newMap();
		setHideScroll();
		m_7d = false;
	}

	bool showMovie = false;
	MovieWindowPlayback *playback = reinterpret_cast<MovieWindowPlayback *>(m_moviePlayback);
	if (playback->m_b0)
	{
		if (static_cast<unsigned char>(reinterpret_cast<Rva005248D0 *>(playback)->rva002D2C21()))
		{
			playback->stop();
		}
		else
		{
			playback->advance();
			if (!reinterpret_cast<MovieWindowPlayback *>(m_moviePlayback)->m_b2 && reinterpret_cast<MovieWindowPlayback *>(m_moviePlayback)->rva00524A84() > 0.5f)
				showMovie = true;
			else
				showMovie = false;
		}
	}
	if (m_7eb6 != showMovie)
	{
		if (showMovie)
		{
			showMovieButton();
			fadePalantirButtonsZero();
			m_movieWindow->m_1f4 = 1;
		}
		else
		{
			hideMovieButton();
			fadePalantirButtonsOne();
			m_movieWindow->m_1f4 = 0;
		}
		m_7eb6 = showMovie;
	}

	bool observing;
	if (TheGameLogic && reinterpret_cast<BfmeGlob939D *>(TheGameLogic)->rva0023C6C5() && reinterpret_cast<Rva002A7DD0 *>(ThePlayerList)->rva002A7DD0())
		observing = true;
	else
		observing = false;
	if (observing != m_7eb7)
	{
		if (observing)
			showObserverStuff();
		else
			hideObserverStuff();
		m_7eb7 = observing;
	}

	if (!m_e5)
	{
		if (TheLivingWorldLogic && !reinterpret_cast<BfmeSelectionState *>(TheLivingWorldLogic)->isSelectionLocked()
			&& !reinterpret_cast<BfmeGlob939D *>(TheGameLogic)->bfmeCall939D())
		{
			Rva004266A1 *objectives = TheMissionObjectiveTracker ? TheMissionObjectiveTracker->m_obj : 0;
			if (objectives)
			{
				int count = (objectives->m_end - objectives->m_begin) >> 3;
				for (int i = 0; i < count; ++i)
				{
					Flag4 old; old.v = 0;
					_STL::map<int, int>::iterator it = reinterpret_cast<_STL::map<int, int> &>(m_11c).find(i);
					// Node compare: the iterator operator!= has two flag variants across units.
					if (it._M_node != reinterpret_cast<_STL::map<int, int> &>(m_11c).end()._M_node)
						old.v = *reinterpret_cast<unsigned char *>(&(*it).second);
					Flag4 now; now.v = objectives->rva0042680D(i);
					if (now.v != old.v)
					{
						if (!old.v && now.v)
							m_e5 = true;
						reinterpret_cast<unsigned char &>(reinterpret_cast<_STL::map<int, bool> &>(m_11c)[i]) = now.v;
					}
				}
			}
		}
	}
	else if (g_Va00A04450 || Rva0050E9CDGet())
	{
		m_e5 = false;
	}
	if (m_7eb5 != m_e5)
	{
		setFlashObjectivesButton(m_e5);
		m_7eb5 = m_e5;
	}

	AsciiString faction;
	if (TheLivingWorldLogic && reinterpret_cast<BfmeSelectionState *>(TheLivingWorldLogic)->isSelectionLocked())
	{
		bool capped = reinterpret_cast<AptPalantirCampaignView *>(TheCampaignManager)->m_2c;
		if (capped != m_f4)
		{
			setPlayerPowerCapState(capped);
			m_f4 = capped;
		}
		AptPalantirLivingWorldView *livingWorld = reinterpret_cast<AptPalantirLivingWorldView *>(TheLivingWorldLogic);
		Rva002E063B *counter = livingWorld->m_98;
		int points = counter ? counter->get() : 0;
		AptPalantirSpellPointCost *cost0 = m_ec.m_ptr;
		if (cost0)
		{
			--cost0->m_count;
			_ReadWriteBarrier();
			if (cost0->m_count <= 0)
			{
				AptPalantirSpellPointCost *cost = m_ec.m_ptr;
				m_ec.m_ptr = 0;
				delete cost;
				playPlayerSpellPointEffect();
			}
			else
			{
				points -= m_ec.m_ptr->m_amount;
			}
		}
		if (points != m_f0)
		{
			Rva003FF02EPowerCap(points);
			m_f0 = points;
		}
	}
	else
	{
		m_ec.clear();
		reinterpret_cast<Palantir::Impl *>(this)->UpdatePlayerStats();
		BfmeMemberRV *player = reinterpret_cast<BfmeThingRV *>(ThePlayerList)->bfmePickRV();
		if (!reinterpret_cast<const StringBase<char> *>(&player->m_74c)->isEmpty())
			faction = player->m_74c;
		else if (player->m_34 && ((player->m_34->m_151) ? (player->m_34->m_151) : (player->m_34->m_151)))
			faction = player->m_34->m_name;
	}

	if (faction != m_f8)
	{
		reinterpret_cast<Rva002D5711 *>(&m_resourceBar)->rva002D5711(faction);
		Rva003FECCASetPlayerFaction(reinterpret_cast<void **>(&faction));
		if (m_heroSelect.m_movie)
			reinterpret_cast<Rva005258B2 *>(m_heroSelect.m_movie)->rva005258B9(&faction);
		m_f8 = faction;
	}

	if (TheGameLogic->isInMultiplayerGame())
	{
		if (!m_7fb0)
		{
			Rva00516F21Invoke(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager), reinterpret_cast<void *>(m_level), "SetMessengerButtonState", "_up");
			m_7fb0 = true;
		}
	}
	else if (m_7fb0)
	{
		Rva00516F21Invoke(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager), reinterpret_cast<void *>(m_level), "SetMessengerButtonState", "_unused");
		m_7fb0 = false;
	}

	reinterpret_cast<Rva002D62AB *>(this)->updateButtonFlash();
	_STL::list<int>::iterator end = m_148.end();
	for (_STL::list<int>::iterator it = m_148.begin(); it != end; ++it)
		reinterpret_cast<Palantir::Impl::RadarPing *>(*it)->Update();
}
