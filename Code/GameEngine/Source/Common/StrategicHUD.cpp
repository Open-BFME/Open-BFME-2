// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// StrategicHUD::HUD::Impl, the strategic HUD's Apt load/unload callbacks.
//
// The class is the one WorldBuilder names for the help-box callback 0x0042DB21
// (row ?OnHelpBoxLoaded@Impl@HUD@StrategicHUD@@): the constructor 0x0042E014
// binds "StrategicHUD::OnInitialized" and "StrategicHUD::OnClosed" delegates,
// then binds each callback below as a member pointer under "_level%u" plus a
// fixed suffix ("_OnHelpBoxLoaded", ...). The method names are those suffixes.
// HUD::Show 0x0042D5DD and HUD::FadeOut 0x0042D632 drive the same level (+4)
// and state (+8) through the HUD's pointer at +0, the one Rva0042DFF5 below
// owns.
//
// Layout from that constructor (it zeroes +0x18..+0x38) and the destructor
// 0x0042D92E, which tears the nine owning slots down in reverse through their
// rowed clears. Each slot is viewed through the rowed set/reset/clear it is
// passed to; where a slot's setter and clear are rowed under different class
// names, the clear is reached through a cast, as in Rva00578AC1.cpp.
//
// Every <X>Loaded builds its sub-movie object from the loaded movie's level
// and path (rowed BfmePathLeafAfterMarker.cpp helpers) only when the slot is
// empty; every <X>Unloaded clears the slot. The sub-movie constructors are
// unrowed and pinned by address under the class name the slot setter's own
// row gives the pointee; operator new sizes give the object sizes.
#include "ascii_string.h"

const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);

// "string + text", as rowed in RegistryAsciiPath.cpp: the 12-byte node the
// constructor converts into each "_level%u_On..." name.
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}

	const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	const AsciiString *m_string;
};

struct AsciiStringPlusText : AsciiStringRef
{
	operator AsciiString();

	Rva000B3F84Pair m_right;
};
AsciiStringPlusText __cdecl operator+(const AsciiString &left, const char *right);

// The pointees, with their constructors' addresses.
class Rva00527CCE
{
public:
	Rva00527CCE(int level, const AsciiString &name); // 0x00527C04

private:
	unsigned char m_pad[0x20];
};

class Rva00577DE1OwningCell
{
public:
	Rva00577DE1OwningCell(int level, const AsciiString &name); // 0x00577DFB

private:
	void *m_value;
};

// The Palantir: constructor 0x00578D22, methods in Rva00578AC1.cpp as
// StrategicHUD::Palantir.
class Rva00578C43
{
public:
	Rva00578C43(int level, const AsciiString &name); // 0x00578D22

private:
	unsigned char m_pad[0x58];
};

class Rva005794ED
{
public:
	Rva005794ED(int level, const AsciiString &name); // 0x00579575

private:
	unsigned char m_pad[0x20];
};

// The stats display: constructor 0x00579E82.
namespace StrategicHUD
{
class StatsDisplayImpl
{
public:
	StatsDisplayImpl(int level, const AsciiString &name); // 0x00579E82

private:
	unsigned char m_pad[0x40];
};
}

class Rva0057AD6E
{
public:
	Rva0057AD6E(int level, const AsciiString &name); // 0x0057B5AA

private:
	unsigned char m_pad[0x50];
};

class Rva0057BD01
{
public:
	Rva0057BD01(int level, const AsciiString &name); // 0x0057BD79

private:
	unsigned char m_pad[0x38];
};

// The load dialog frame: constructor 0x0057C499 (vtable 0x00C6F304, its +4
// a 0x1C object from 0x0057C3C4).
class Rva0057C499
{
public:
	Rva0057C499(int level, const AsciiString &name); // 0x0057C499

private:
	unsigned char m_pad[0x8];
};

class Rva0057C04F
{
public:
	Rva0057C04F(int level, const AsciiString &name); // 0x0057C152

private:
	unsigned char m_pad[0x1C];
};

// The help box is handed to the Palantir and the stats display, under the
// names those methods are rowed with.
namespace StrategicHUD
{
class Palantir
{
public:
	void rva005785A2(void *selection);
	void rva005785CD();
};

// The checklist (+0x30) and selection details (+0x34) by the class names
// their own rowed methods carry; each one's per-frame update is the method
// the HUD update reaches through the slot.
class ChecklistUIImpl
{
public:
	void rva0057B499();
};

class SelectionDetailsUIImpl
{
public:
	void rva0057BBBB();
};
}

// The help box's per-frame update, rowed at 0x005279DD.
class InGameHelpBoxMovieClip
{
public:
	void Update();
};

// The stats display and the new-turn indicator have empty updates, which
// fold onto the shared empty body 0x000B3FD0.
class Rva000B3FD0Nop
{
public:
	void noop();
};

class Rva005796B3
{
public:
	void rva005796B3(void *newObj);
};

// The slot holders. Each one's destructor is its rowed clear, which the
// Impl destructor calls once per slot, in reverse, under its own
// unwind state. Where the clear is rowed under another class name than the
// setter, it is reached through a cast, as in Rva00578AC1.cpp.
class Rva002D38D1
{
public:
	void clear();
};

class Rva002D38EB
{
public:
	Rva002D38EB() : m_ptr(0) {}
	~Rva002D38EB() { ((Rva002D38D1 *)this)->clear(); }
	void reset(Rva00527CCE *p);

	Rva00527CCE *m_ptr;
};

// The +0x1C slot's setter, rowed with an Object parameter; reached through
// a cast, as in AptRowListCallbacks.cpp.
class Object;

class Rva00575674
{
public:
	void rva00575674(Object *p);
};

class Rva000AD6F4
{
public:
	Rva000AD6F4() : m_ptr(0) {}
	~Rva000AD6F4() { clear(); }
	void clear();

	void *m_ptr;
};

class Rva0042D729
{
public:
	Rva0042D729() : m_ptr(0) {}
	~Rva0042D729() { rva0042D74C(); }
	void rva0042D729(Rva00577DE1OwningCell *p);
	void rva0042D74C();

	Rva00577DE1OwningCell *m_ptr;
};

class Rva0042D789
{
public:
	void clear();
};

class Rva0042D766
{
public:
	Rva0042D766() : m_ptr(0) {}
	~Rva0042D766() { ((Rva0042D789 *)this)->clear(); }
	void reset(Rva00578C43 *p);

	Rva00578C43 *m_ptr;
};

class Rva0042D7A3
{
public:
	Rva0042D7A3() : m_ptr(0) {}
	~Rva0042D7A3() { rva0042D7C6(); }
	void rva0042D7A3(Rva005794ED *p);
	void rva0042D7C6();

	Rva005794ED *m_ptr;
};

class Rva0042D7E0
{
public:
	Rva0042D7E0() : m_ptr(0) {}
	~Rva0042D7E0() { rva0042D803(); }
	void rva0042D7E0(StrategicHUD::StatsDisplayImpl *p);
	void rva0042D803();

	StrategicHUD::StatsDisplayImpl *m_ptr;
};

class Rva0042D81D
{
public:
	Rva0042D81D() : m_ptr(0) {}
	~Rva0042D81D() { rva0042D840(); }
	void rva0042D81D(Rva0057AD6E *p);
	void rva0042D840();

	Rva0057AD6E *m_ptr;
};

class Rva0042D87D
{
public:
	void clear();
};

class Rva0042D85A
{
public:
	Rva0042D85A() : m_ptr(0) {}
	~Rva0042D85A() { ((Rva0042D87D *)this)->clear(); }
	void reset(Rva0057BD01 *p);

	Rva0057BD01 *m_ptr;
};

class Rva0042D897
{
public:
	Rva0042D897() : m_ptr(0) {}
	~Rva0042D897() { rva0042D8BA(); }
	void rva0042D897(Rva0057C04F *p);
	void rva0042D8BA();

	Rva0057C04F *m_ptr;
};

// The bound callbacks are handed over as a by-value delegate the callee
// destroys, built in place from an {object, method} pair by the rowed
// constructor 0x00579E47 (the user-declared copy constructor is what makes
// cl build it in the argument slot rather than copy it there).
struct DelegateDesc;

class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc);
	Rva00579E47(const Rva00579E47 &other);
	~Rva00579E47();

private:
	void *m_ptr;
};

// The +0x0C member: 12 bytes, a vector of the bound names. Its constructor
// is the vector default constructor ICF-folded at 0x001F81BF (rowed there as
// ObjectCreationList's); 0x0052458E binds a delegate under a name through
// the Apt window manager and remembers the name; the rowed destructor
// 0x0052413E unbinds them.
// The by-value parameter type of 0x0052458E (definition below).
class Rva00579E47Delegate;

class Rva0052413E
{
public:
	Rva0052413E();
	~Rva0052413E();
	void rva0052458E(const AsciiString &name, Rva00579E47Delegate delegate);

private:
	unsigned char m_pad[0xC];
};

// The Apt window manager at 0x009FE4CC; the destructor unloads the movie
// through it. The unload is pinned under Rva00222A8BTarget, hence the cast.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00222A8BTarget
{
public:
	// Native provider compares the incoming 32-bit index with 14 and returns AL.
	bool rva0022277D(int index);
};

namespace StrategicHUD
{
class HUD
{
public:
	class Impl;

	void rva0042D5D6();

private:
	Impl *m_impl;
};
}

class StrategicHUD::HUD::Impl
{
public:
	Impl(int owner, unsigned int level);
	~Impl();

	void OnInitialized(const char *unused);
	void OnClosed(const char *unused);
	void OnChecklistLoaded(const char *name);
	void OnChecklistUnloaded(const char *name);
	void OnEndTurnButtonLoaded(const char *name);
	void OnEndTurnButtonUnloaded(const char *name);
	void OnHelpBoxLoaded(const char *name);
	void OnHelpBoxUnloaded(const char *name);
	void OnLoadDialogFrameLoaded(const char *name);
	void OnLoadDialogFrameUnloaded(const char *name);
	void OnNewTurnIndicatorLoaded(const char *name);
	void OnNewTurnIndicatorUnloaded(const char *name);
	void OnRadialMenuStageLoaded(const char *name);
	void OnRadialMenuStageUnloaded(const char *name);
	void OnPalantirLoaded(const char *name);
	void OnPalantirUnloaded(const char *name);
	void OnSelectionDetailsLoaded(const char *name);
	void OnSelectionDetailsUnloaded(const char *name);
	void OnStatsDisplayLoaded(const char *name);
	void OnStatsDisplayUnloaded(const char *name);

	void rva0042D577();

private:
	int m_00; // the constructor's first argument
	unsigned int m_level; // +0x04: the movie's level, "_level%u"
	int m_state; // +0x08: 0 until loaded; OnInitialized 1->2, OnClosed 3->4
	Rva0052413E m_0C; // +0x0C
	Rva002D38EB m_helpBox; // +0x18
	Rva000AD6F4 m_loadDialogFrame; // +0x1C
	Rva0042D729 m_radialMenuStage; // +0x20
	Rva0042D766 m_palantir; // +0x24
	Rva0042D7A3 m_endTurnButton; // +0x28
	Rva0042D7E0 m_statsDisplay; // +0x2C
	Rva0042D81D m_checklist; // +0x30
	Rva0042D85A m_selectionDetails; // +0x34
	Rva0042D897 m_newTurnIndicator; // +0x38
};

struct DelegateDesc
{
	DelegateDesc(StrategicHUD::HUD::Impl *object, void (StrategicHUD::HUD::Impl::*method)(const char *))
		: m_object(object), m_method(method) {}

	StrategicHUD::HUD::Impl *m_object;
	void (StrategicHUD::HUD::Impl::*m_method)(const char *);
};

// The one-pointer cell that owns the Impl: constructor 0x0042E71D (the owner
// passes its level by reference; the cell passes its own address as the
// Impl's first argument), clear 0x0042DFF5, and the destructor 0x0042E00F,
// which tail-jumps to the clear and is what the owner's unwind funclets call.
// The same shape as Rva00577DE1OwningCell. Its pointer at +0 is the one
// HUD::Show and HUD::FadeOut read, so this is likely StrategicHUD::HUD itself;
// kept under its address name until the constructor's own name is evidenced.
class Rva0042DFF5
{
public:
	Rva0042DFF5(const unsigned int &level);
	~Rva0042DFF5();
	__declspec(noinline) void clear();

private:
	StrategicHUD::HUD::Impl *m_ptr;
};

// The delegate as 0x0052458E takes it: an inline constructor taking the pair
// by value around the out-of-line 0x00579E47, the same shape as the functor
// banked for MpGameSetup 0x0044303D. Retail's order (the argument slot's
// address saved before ecx is loaded, the method through eax) needs both
// the inline wrapper and the by-value pair.
class Rva00579E47Delegate : public Rva00579E47
{
public:
	Rva00579E47Delegate(DelegateDesc desc) : Rva00579E47(desc) {}
};

// Retail 0x0042D493, 16 bytes: bound as the "StrategicHUD::OnInitialized"
// delegate.
void StrategicHUD::HUD::Impl::OnInitialized(const char *unused)
{
	if (m_state == 1)
		m_state = 2;
}

// Retail 0x0042D4A3, 16 bytes: bound as the "StrategicHUD::OnClosed" delegate.
void StrategicHUD::HUD::Impl::OnClosed(const char *unused)
{
	if (m_state == 3)
		m_state = 4;
}

// Retail 0x0042D5CB, 11 bytes: bound as "_level%u_OnLoadDialogFrameUnloaded".
void StrategicHUD::HUD::Impl::OnLoadDialogFrameUnloaded(const char *name)
{
	m_loadDialogFrame.clear();
}

// Retail 0x0042D577, 84 bytes: once the movie is loaded, updates the
// help box, the Palantir, the stats display, the checklist, the selection
// details and the new-turn indicator. HUD::rva0042D5D6 forwards to it.
void StrategicHUD::HUD::Impl::rva0042D577()
{
	if (m_state != 0)
	{
		if (m_helpBox.m_ptr != 0)
			((InGameHelpBoxMovieClip *)m_helpBox.m_ptr)->Update();
		if (m_palantir.m_ptr != 0)
			((StrategicHUD::Palantir *)m_palantir.m_ptr)->rva005785CD();
		if (m_statsDisplay.m_ptr != 0)
			((Rva000B3FD0Nop *)m_statsDisplay.m_ptr)->noop();
		if (m_checklist.m_ptr != 0)
			((StrategicHUD::ChecklistUIImpl *)m_checklist.m_ptr)->rva0057B499();
		if (m_selectionDetails.m_ptr != 0)
			((StrategicHUD::SelectionDetailsUIImpl *)m_selectionDetails.m_ptr)->rva0057BBBB();
		if (m_newTurnIndicator.m_ptr != 0)
			((Rva000B3FD0Nop *)m_newTurnIndicator.m_ptr)->noop();
	}
}

// Retail 0x0042D5D6, 7 bytes: the HUD's update, through its Impl.
void StrategicHUD::HUD::rva0042D5D6()
{
	m_impl->rva0042D577();
}

// Retail 0x0042D92E, 181 bytes.
StrategicHUD::HUD::Impl::~Impl()
{
	if (m_state != 0 && g_bfmeAptWindowManager != 0)
		((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva0022277D(reinterpret_cast<int>((void *)m_level));
}

// Retail 0x0042D9E3, 148 bytes: bound as "_level%u_OnChecklistLoaded".
void StrategicHUD::HUD::Impl::OnChecklistLoaded(const char *name)
{
	if (m_checklist.m_ptr == 0)
		m_checklist.rva0042D81D(new Rva0057AD6E(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
}

// Retail 0x0042DA77, 11 bytes: bound as "_level%u_OnChecklistUnloaded".
void StrategicHUD::HUD::Impl::OnChecklistUnloaded(const char *name)
{
	m_checklist.rva0042D840();
}

// Retail 0x0042DA82, 148 bytes: bound as "_level%u_OnEndTurnButtonLoaded".
void StrategicHUD::HUD::Impl::OnEndTurnButtonLoaded(const char *name)
{
	if (m_endTurnButton.m_ptr == 0)
		m_endTurnButton.rva0042D7A3(new Rva005794ED(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
}

// Retail 0x0042DB16, 11 bytes: bound as "_level%u_OnEndTurnButtonUnloaded".
void StrategicHUD::HUD::Impl::OnEndTurnButtonUnloaded(const char *name)
{
	m_endTurnButton.rva0042D7C6();
}

// Retail 0x0042DB21, 184 bytes: bound as "_level%u_OnHelpBoxLoaded".
void StrategicHUD::HUD::Impl::OnHelpBoxLoaded(const char *name)
{
	if (m_helpBox.m_ptr == 0)
	{
		m_helpBox.reset(new Rva00527CCE(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
		if (m_palantir.m_ptr != 0)
			((StrategicHUD::Palantir *)m_palantir.m_ptr)->rva005785A2(m_helpBox.m_ptr);
		if (m_statsDisplay.m_ptr != 0)
			((Rva005796B3 *)m_statsDisplay.m_ptr)->rva005796B3(m_helpBox.m_ptr);
	}
}

// Retail 0x0042DBD9, 43 bytes: bound as "_level%u_OnHelpBoxUnloaded".
void StrategicHUD::HUD::Impl::OnHelpBoxUnloaded(const char *name)
{
	((Rva002D38D1 *)&m_helpBox)->clear();
	if (m_palantir.m_ptr != 0)
		((StrategicHUD::Palantir *)m_palantir.m_ptr)->rva005785A2(0);
	if (m_statsDisplay.m_ptr != 0)
		((Rva005796B3 *)m_statsDisplay.m_ptr)->rva005796B3(0);
}

// Retail 0x0042DC04, 148 bytes: bound as "_level%u_OnLoadDialogFrameLoaded".
void StrategicHUD::HUD::Impl::OnLoadDialogFrameLoaded(const char *name)
{
	if (m_loadDialogFrame.m_ptr == 0)
		((Rva00575674 *)&m_loadDialogFrame)->rva00575674((Object *)new Rva0057C499(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
}

// Retail 0x0042DC98, 148 bytes: bound as "_level%u_OnNewTurnIndicatorLoaded".
void StrategicHUD::HUD::Impl::OnNewTurnIndicatorLoaded(const char *name)
{
	if (m_newTurnIndicator.m_ptr == 0)
		m_newTurnIndicator.rva0042D897(new Rva0057C04F(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
}

// Retail 0x0042DD2C, 11 bytes: bound as "_level%u_OnNewTurnIndicatorUnloaded".
void StrategicHUD::HUD::Impl::OnNewTurnIndicatorUnloaded(const char *name)
{
	m_newTurnIndicator.rva0042D8BA();
}

// Retail 0x0042DD37, 148 bytes: bound as "_level%u_OnRadialMenuStageLoaded".
void StrategicHUD::HUD::Impl::OnRadialMenuStageLoaded(const char *name)
{
	if (m_radialMenuStage.m_ptr == 0)
		m_radialMenuStage.rva0042D729(new Rva00577DE1OwningCell(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
}

// Retail 0x0042DDCB, 11 bytes: bound as "_level%u_OnRadialMenuStageUnloaded".
void StrategicHUD::HUD::Impl::OnRadialMenuStageUnloaded(const char *name)
{
	m_radialMenuStage.rva0042D74C();
}

// Retail 0x0042DDD6, 167 bytes: bound as "_level%u_OnPalantirLoaded"; also
// hands the new Palantir the help box.
void StrategicHUD::HUD::Impl::OnPalantirLoaded(const char *name)
{
	if (m_palantir.m_ptr == 0)
	{
		m_palantir.reset(new Rva00578C43(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
		if (m_helpBox.m_ptr != 0)
			((StrategicHUD::Palantir *)m_palantir.m_ptr)->rva005785A2(m_helpBox.m_ptr);
	}
}

// Retail 0x0042DE7D, 11 bytes: bound as "_level%u_OnPalantirUnloaded".
void StrategicHUD::HUD::Impl::OnPalantirUnloaded(const char *name)
{
	((Rva0042D789 *)&m_palantir)->clear();
}

// Retail 0x0042DE88, 148 bytes: bound as "_level%u_OnSelectionDetailsLoaded".
void StrategicHUD::HUD::Impl::OnSelectionDetailsLoaded(const char *name)
{
	if (m_selectionDetails.m_ptr == 0)
		m_selectionDetails.reset(new Rva0057BD01(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
}

// Retail 0x0042DF1C, 11 bytes: bound as "_level%u_OnSelectionDetailsUnloaded".
void StrategicHUD::HUD::Impl::OnSelectionDetailsUnloaded(const char *name)
{
	((Rva0042D87D *)&m_selectionDetails)->clear();
}

// Retail 0x0042DF27, 167 bytes: bound as "_level%u_OnStatsDisplayLoaded"; also
// hands the new stats display the help box.
void StrategicHUD::HUD::Impl::OnStatsDisplayLoaded(const char *name)
{
	if (m_statsDisplay.m_ptr == 0)
	{
		m_statsDisplay.rva0042D7E0(new StrategicHUD::StatsDisplayImpl(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
		if (m_helpBox.m_ptr != 0)
			((Rva005796B3 *)m_statsDisplay.m_ptr)->rva005796B3(m_helpBox.m_ptr);
	}
}

// Retail 0x0042DFCE, 11 bytes: bound as "_level%u_OnStatsDisplayUnloaded".
void StrategicHUD::HUD::Impl::OnStatsDisplayUnloaded(const char *name)
{
	m_statsDisplay.rva0042D803();
}

// Retail 0x0042DFF5, 26 bytes.
void Rva0042DFF5::clear()
{
	StrategicHUD::HUD::Impl *old = m_ptr;
	m_ptr = 0;
	if (old)
		delete old;
}

// Retail 0x0042E00F, 5 bytes.
Rva0042DFF5::~Rva0042DFF5()
{
	clear();
}

// Retail 0x0042E014, 1,801 bytes. Binds the two state delegates by their
// qualified names, then every load/unload callback above under
// "_level%u" plus its suffix.
StrategicHUD::HUD::Impl::Impl(int owner, unsigned int level)
	: m_00(owner), m_level(level), m_state(0)
{
	{
		AsciiString name("StrategicHUD::OnInitialized");
		m_0C.rva0052458E(name, Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnInitialized)));
	}
	{
		AsciiString name("StrategicHUD::OnClosed");
		m_0C.rva0052458E(name, Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnClosed)));
	}
	AsciiString prefix;
	prefix.format("_level%u", m_level);
	m_0C.rva0052458E(prefix + "_OnChecklistLoaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnChecklistLoaded)));
	m_0C.rva0052458E(prefix + "_OnChecklistUnloaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnChecklistUnloaded)));
	m_0C.rva0052458E(prefix + "_OnEndTurnButtonLoaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnEndTurnButtonLoaded)));
	m_0C.rva0052458E(prefix + "_OnEndTurnButtonUnloaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnEndTurnButtonUnloaded)));
	m_0C.rva0052458E(prefix + "_OnHelpBoxLoaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnHelpBoxLoaded)));
	m_0C.rva0052458E(prefix + "_OnHelpBoxUnloaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnHelpBoxUnloaded)));
	m_0C.rva0052458E(prefix + "_OnLoadDialogFrameLoaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnLoadDialogFrameLoaded)));
	m_0C.rva0052458E(prefix + "_OnLoadDialogFrameUnloaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnLoadDialogFrameUnloaded)));
	m_0C.rva0052458E(prefix + "_OnNewTurnIndicatorLoaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnNewTurnIndicatorLoaded)));
	m_0C.rva0052458E(prefix + "_OnNewTurnIndicatorUnloaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnNewTurnIndicatorUnloaded)));
	m_0C.rva0052458E(prefix + "_OnPalantirLoaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnPalantirLoaded)));
	m_0C.rva0052458E(prefix + "_OnPalantirUnloaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnPalantirUnloaded)));
	m_0C.rva0052458E(prefix + "_OnRadialMenuStageLoaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnRadialMenuStageLoaded)));
	m_0C.rva0052458E(prefix + "_OnRadialMenuStageUnloaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnRadialMenuStageUnloaded)));
	m_0C.rva0052458E(prefix + "_OnSelectionDetailsLoaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnSelectionDetailsLoaded)));
	m_0C.rva0052458E(prefix + "_OnSelectionDetailsUnloaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnSelectionDetailsUnloaded)));
	m_0C.rva0052458E(prefix + "_OnStatsDisplayLoaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnStatsDisplayLoaded)));
	m_0C.rva0052458E(prefix + "_OnStatsDisplayUnloaded", Rva00579E47Delegate(DelegateDesc(this, &StrategicHUD::HUD::Impl::OnStatsDisplayUnloaded)));
}

// Retail 0x0042E71D, 66 bytes.
Rva0042DFF5::Rva0042DFF5(const unsigned int &level)
{
	m_ptr = new StrategicHUD::HUD::Impl((int)this, level);
}
