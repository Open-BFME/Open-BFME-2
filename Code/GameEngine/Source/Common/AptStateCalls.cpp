// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// Apt panel state toggles: each calls the panel's Apt function through the
// rowed Rva005FB5E6AptCall wrapper. The arguments are TheRva00222A8BTarget,
// the panel's level and name fields, the function and "_show" or "_hide".
// A flag records the state. The value-setting halves defer to the rowed free
// setters Rva0057A5A8Set (TimeRemaining) and Rva005EF096Set (CommandPoints),
// which receive the name field's address as their team pointer slot.
// Function and argument names are the retail strings; class names are
// address-derived.
//
// ?DoShowTimeRemaining@ChecklistUIImpl@StrategicHUD@@QAEXH@Z  @0x0057A861 92B  SetTimeRemainingState _show + value
// ?DoHideTimeRemaining@ChecklistUIImpl@StrategicHUD@@QAEXXZ   @0x0057A8BD 60B  SetTimeRemainingState _hide
// ?ShowCommandPoints@Impl@RegionDetailsArmiesMovieClip@StrategicHUD@@QAEXHH@Z @0x005EF2BE 105B SetCommandPointsState value + _show
// ?HideCommandPoints@Impl@RegionDetailsArmiesMovieClip@StrategicHUD@@QAEXXZ   @0x005EF327 63B  SetCommandPointsState _hide
#include "ascii_string.h"
#include "unicode_string.h"

struct RGBColor { float red, green, blue; };

class Mouse
{
public:
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);
};

class GameTextInterface
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;
extern Mouse *TheMouse;

class Rva00222A8BTarget
{
public:
	bool rva0022277D(int level);	// 0x0022277D, WB AptPlayer::HideLevel
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;

int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

struct Rva0057A5A8Team;
void Rva0057A5A8Set(int level, Rva0057A5A8Team **ppTeam, int totalSeconds);

struct Rva005EF096Outer;
void Rva005EF096Set(int level, Rva005EF096Outer *outer, int a, int b);

namespace StrategicHUD {
class ChecklistUIImpl;
}

class StrategicHUD::ChecklistUIImpl
{
public:
	void DoShowTimeRemaining(int seconds);
	void DoHideTimeRemaining();
private:
	char m_pad00[8];
	unsigned int m_level;		// +0x08
	StringBase<char> m_name;	// +0x0C
	char m_pad10[0x34];
	int m_seconds;				// +0x44
	bool m_shown;				// +0x48
};

void StrategicHUD::ChecklistUIImpl::DoShowTimeRemaining(int seconds)
{
	if (!m_shown)
	{
		Rva005FB5E6AptCall(TheRva00222A8BTarget, (void *)m_level, m_name.str(), "SetTimeRemainingState", "_show");
		m_shown = true;
	}
	if (seconds != m_seconds)
	{
		Rva0057A5A8Set(m_level, (Rva0057A5A8Team **)&m_name, seconds);
		m_seconds = seconds;
	}
}

void StrategicHUD::ChecklistUIImpl::DoHideTimeRemaining()
{
	if (m_shown)
	{
		Rva005FB5E6AptCall(TheRva00222A8BTarget, (void *)m_level, m_name.str(), "SetTimeRemainingState", "_hide");
		m_shown = false;
	}
}

namespace StrategicHUD {
class RegionDetailsArmiesMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::RegionDetailsArmiesMovieClip::Impl
{
public:
	void ShowCommandPoints(int a, int b);
	void HideCommandPoints();
	void Update();
private:
	unsigned int m_level;		// +0x00
	StringBase<char> m_name;	// +0x04
	char m_pad08[0x2C];
	int m_a;					// +0x34
	int m_b;					// +0x38
	char m_pad3C;
	bool m_shown;				// +0x3D
	bool m_3E;					// +0x3E
};

void StrategicHUD::RegionDetailsArmiesMovieClip::Impl::ShowCommandPoints(int a, int b)
{
	if (a != m_a || b != m_b)
	{
		Rva005EF096Set(m_level, (Rva005EF096Outer *)&m_name, a, b);
		m_a = a;
		m_b = b;
	}
	if (!m_shown)
	{
		Rva005FB5E6AptCall(TheRva00222A8BTarget, (void *)m_level, m_name.str(), "SetCommandPointsState", "_show");
		m_shown = true;
	}
}

void StrategicHUD::RegionDetailsArmiesMovieClip::Impl::HideCommandPoints()
{
	if (m_shown)
	{
		Rva005FB5E6AptCall(TheRva00222A8BTarget, (void *)m_level, m_name.str(), "SetCommandPointsState", "_hide");
		m_shown = false;
		m_3E = false;
	}
}

// ?Update@Impl@RegionDetailsArmiesMovieClip@StrategicHUD@@QAEXXZ @0x005EF366 104B: flag +0x3E gates GameText fetch plus Mouse tooltip.
// Target evidence: byte [ecx+0x3E] je then TheGameText slot 0x3c fetch STRATEGICHUD:ArmyCurrentOverMaxCommandPointsTooltip then Mouse rva001EEA6D -1 0 1.0f; caller jmp 0x005EF3F9.
void StrategicHUD::RegionDetailsArmiesMovieClip::Impl::Update()
{
	if (!m_3E)
		return;
	UnicodeString msg = TheGameText->fetch("STRATEGICHUD:ArmyCurrentOverMaxCommandPointsTooltip");
	TheMouse->rva001EEA6D(msg, -1, 0, 1.0f);
}

// ?rva005FFC8B@Rva005FFC8B@@QAEXABUTreeHintRef00217D4C@@@Z @0x005FFC8B 64B:
// store the reference through its rowed assignment 0x002174A4, then
// CreateArmyPanel "garrison" through the same wrapper (level +4, name +8).
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	void *m_ref;
};

class Rva005FFC8B
{
public:
	void rva005FFC8B(const TreeHintRef00217D4C &ref);
private:
	char m_pad00[4];
	unsigned int m_level;		// +0x04
	StringBase<char> m_name;	// +0x08
	char m_pad0C[0x10];
	TreeHintRef00217D4C m_ref;	// +0x1C
};

void Rva005FFC8B::rva005FFC8B(const TreeHintRef00217D4C &ref)
{
	m_ref = ref;
	Rva005FB5E6AptCall(TheRva00222A8BTarget, (void *)m_level, m_name.str(), "CreateArmyPanel", "garrison");
}

// ?rva005779A0@Rva005779A0@@QBE?AVAsciiString@@XZ @0x005779A0 110B: the
// panel's Apt path "_level%d.%s" from level +4 and name +8, returned by value.
class Rva005779A0
{
public:
	AsciiString rva005779A0() const;
private:
	char m_pad00[4];
	unsigned int m_level;		// +0x04
	StringBase<char> m_name;	// +0x08
};

AsciiString Rva005779A0::rva005779A0() const
{
	AsciiString path;
	path.format("_level%d.%s", m_level, m_name.str());
	return path;
}

struct Rva00577A0EInner
{
	Rva005779A0 *m_00;
};

class Rva00577A0E
{
public:
	AsciiString rva00577A0E() const;
private:
	char m_pad00[0x40];
	Rva00577A0EInner *m_40;
};

AsciiString Rva00577A0E::rva00577A0E() const
{
	return m_40->m_00->rva005779A0();
}

// ?rva00525783@Rva00525783@@QAEXXZ @0x00525783 115B: leave the hero-select
// button state. When the flag at +0x45 is set, the pending record at +0x1C8 is
// first handed by value to 0x003591F4 (pinned) on the global at VA 0x00E01E28,
// if that global exists, and its flag at +0x1D8 is cleared.
// Then SetSelectAllHeroesButtonState "_unused" goes through the wrapper.
struct Rva003591F4Arg
{
	Rva003591F4Arg(const Rva003591F4Arg &other) : m_id(other.m_id), m_flag(other.m_flag) {}
	int m_id;
	bool m_flag;
};

class Rva00E01E28Owner
{
public:
	void rva003591F4(Rva003591F4Arg arg);
};

extern Rva00E01E28Owner *g_00E01E28;

class Rva00525783
{
public:
	void rva00525783();
private:
	char m_pad00[8];
	unsigned int m_level;		// +0x08
	StringBase<char> m_name;	// +0x0C
	char m_pad10[0x35];
	bool m_active;				// +0x45
	char m_pad46[0x182];
	Rva003591F4Arg m_pending;	// +0x1C8
	char m_pad1D0[8];
	bool m_hasPending;			// +0x1D8
};

void Rva00525783::rva00525783()
{
	if (!m_active)
		return;
	if (m_hasPending)
	{
		if (g_00E01E28)
			g_00E01E28->rva003591F4(m_pending);
		m_hasPending = false;
	}
	Rva005FB5E6AptCall(TheRva00222A8BTarget, (void *)m_level, m_name.str(), "SetSelectAllHeroesButtonState", "_unused");
	m_active = false;
}

// Apt window close requests: in the open states 2 and 3, run the window's
// Apt "Close" callback through the rowed Rva0043DB23 and move to state 4.
// ?rva004E67D0@InGameNotificationBoxMovieClip@@QAEXH@Z @0x004E67D0 49B (argument unused)
// ?DoClose@InGameNotificationBoxMovieClip@@QAEXXZ  @0x004E6B9B 55B (first clears the owned
//   pointer at +0x40 through the rowed Rva004E6A1D::clear)
void Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name);

class Rva004E6A1D
{
public:
	void clear();
	void *m_ptr;
};

class InGameNotificationBoxMovieClip
{
public:
	void rva004E67D0(int unused);
	void DoClose();
private:
	char m_pad00[4];
	void *m_owner;				// +0x04
	int m_state;				// +0x08
	char m_pad0C[0x34];
	Rva004E6A1D m_child;		// +0x40
};

void InGameNotificationBoxMovieClip::rva004E67D0(int unused)
{
	(void)unused;
	if (m_state == 2 || m_state == 3)
	{
		Rva0043DB23(TheRva00222A8BTarget, m_owner, "Close");
		m_state = 4;
	}
}

void InGameNotificationBoxMovieClip::DoClose()
{
	m_child.clear();
	if (m_state == 2 || m_state == 3)
	{
		Rva0043DB23(TheRva00222A8BTarget, m_owner, "Close");
		m_state = 4;
	}
}

// ?FadeOut@StrategicVeterancy@@QAEXXZ @0x005EC23E 74B: close the window record
// this points at. In state 1 it is released through the Apt target's
// 0x0022277D (pinned) and goes to state 0. In states 2 and 5 it runs
// "CloseWindow" and goes to state 3.
struct Rva005EC23EWindow
{
	char m_pad00[4];
	void *m_owner;				// +0x04
	int m_state;				// +0x08
};

class StrategicVeterancy
{
public:
	void FadeOut();
private:
	Rva005EC23EWindow *m_window;	// +0x00
};

void StrategicVeterancy::FadeOut()
{
	switch (m_window->m_state)
	{
	case 1:
		TheRva00222A8BTarget->rva0022277D((int)m_window->m_owner);
		m_window->m_state = 0;
		break;
	case 2:
	case 5:
		Rva0043DB23(TheRva00222A8BTarget, m_window->m_owner, "CloseWindow");
		m_window->m_state = 3;
		break;
	}
}

// ?rva005EF3F6@Rva005EF3F6@@QAEXXZ @0x005EF3F6 8B
// Target evidence: forwarder loads this+4 and tail-jumps to rowed
// ?Update@Impl@RegionDetailsArmiesMovieClip@StrategicHUD@@QAEXXZ @0x005EF366 in same TU.
class Rva005EF3F6
{
public:
	void rva005EF3F6();
private:
	int m_pad00;
	StrategicHUD::RegionDetailsArmiesMovieClip::Impl *m_ptr04;
};

void Rva005EF3F6::rva005EF3F6()
{
	return m_ptr04->Update();
}
