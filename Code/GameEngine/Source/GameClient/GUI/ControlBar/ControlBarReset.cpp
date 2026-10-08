// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD
#include "ascii_string.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)


// ?reset@ControlBar@@QAEXXZ @0x0031E09E 448B: ControlBar reset.
// Target boundary: Ghidra FUN_0071e09e ends at 0x0031E25E (ret at E25D).
// Donor algorithm: Zero Hour ControlBar::reset as vendored by BFME1
// 6583b3c1ff21db4a561285717028fdafc780b7db in
// reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp,
// with BFME2 deltas read off retail: the window/video map teardown at
// +0x30 (Rva first/next helpers plus the pair erase), the +0xDC window
// array release through the rowed Rva00328518 helper, the +0x200
// animate-down destroy through the window-manager slot, and the
// ControlBarArrow transition remove. Member offsets (+0x2C list,
// +0x30 map, +0x74/+0x78/+0x7C, +0x1DC/+0x200, +0x20C/+0x210/+0x214,
// +0x26C/+0x27C/+0x278, +0x290/+0x294/+0x298, +0x2A4, +0xDC array) are
// all retail-measured; names for ZH-shared members follow the donor,
// BFME2-only ones are descriptive. Callee identities:
// hideSpecialPowerShortcut 0x0031AFCC, winEnable 0x00313BEC,
// clear 0x000AD6F4, rva002D370A, deleteOverrides 0x001E35ED,
// first 0x00427195, next 0x00411084, Rva00328518, StringBase ctor
// 0x00037BA0 are rowed; switchToContext (context switch),
// rva003A37DC (map pair erase) and the transition remove at 0x001DC42C
// are honest address-derived pins.

class GameWindow
{
public:
	int winEnable(bool enable);
};

class Rva000AD6F4
{
public:
	void clear();
private:
	void *m_ptr;
};

class RadarWindowOverrideSource
{
public:
	void rva002D370A();
};
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *m_nextOverride;
	bool m_isOverride;
	Overridable *deleteOverrides();
};

// Command-set/button node for the +0x2C list: next link at +0x18 and the
// reset-cleared word at +0xF8. Reached as Overridable only for the
// deleteOverrides call, which needs no this-adjustment.
struct BfmeResetNode
{
	unsigned char m_pad00[0x18];
	BfmeResetNode *m_next;			///< +0x18
	unsigned char m_pad1C[0xF8 - 0x1C];
	int m_resetCleared;			///< +0xF8
};

// Retail restores both iterator homes before next(). Volatile homes and the
// compiler barrier preserve those stores across the captured pair values.
struct VolIter
{
	volatile void *m_current;
	volatile void *m_owner;
};

class Rva000411084
{
public:
	void *next();

	void *m_current;
	void *m_owner;
};

// An explicit copy constructor makes the by-value erase argument reserve
// its stack space and copy its two words through the argument address.
struct VideoPair
{
	struct
	{
		void *first;
		void *second;
	} s;
	inline VideoPair(void *a, void *b) { s.first = a; s.second = b; }
	inline VideoPair(const VideoPair &other) { s.first = other.s.first; s.second = other.s.second; }
};

class Rva000427195
{
public:
	void *first(Rva000411084 *iter);
	void rva003A37DC(VideoPair p);
};

void Rva00328518(GameWindow *w, int x);

class GameWindowManager
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void winDestroy(GameWindow *w);
};
extern GameWindowManager *TheWindowManager;

class GameWindowTransitionsHandler;
extern GameWindowTransitionsHandler *TheTransitionHandler;

class GameWindowTransitionsHandler
{
public:
	void rva001DC42C(AsciiString groupName, bool skipPending);
};

class HasResetV
{
public:
	virtual void pad0();
	virtual void pad1();
	virtual void pad2();
	virtual void pad3();
	virtual void pad4();
	virtual void pad5();
	virtual void pad6();
	virtual void pad7();
	virtual void pad8();
	virtual void resetV();
};

class ControlBar
{
public:
	void hideSpecialPowerShortcut();
	void switchToContext(int a, void *b);
	void reset();

	unsigned char m_head00[0x0C];			///< +0x00..+0x0B opaque head (reset never touches it)
	HasResetV *m_resetMembers[4];			///< +0x0C..+0x18 virtual-reset members
	unsigned char m_pad1C[0x2C - 0x1C];
	BfmeResetNode *m_commandSets;			///< +0x2C
	Rva000427195 m_videoMap;			///< +0x30
	unsigned char m_pad31[0x74 - 0x31];
	volatile int m_radarAttackGlowOn;			///< +0x74
	float m_displayedConstructPercent;		///< +0x78
	int m_displayedOCLTimerSeconds;			///< +0x7C
	unsigned char m_pad80[0xDC - 0x80];
	GameWindow *m_disjointWindows[0x20];		///< +0xDC..+0x15C
	unsigned char m_pad15C[0x1DC - 0x15C];
	unsigned char m_sideSelectAnimateDown;			///< +0x1DC
	unsigned char m_pad1DD[0x200 - 0x1DD];
	GameWindow *m_animateDownWindow;			///< +0x200
	unsigned char m_pad204[0x20C - 0x204];
	unsigned char m_isObserverCommandBar;			///< +0x20C
	unsigned char m_pad20D[0x210 - 0x20D];
	void *m_observerLookAtPlayer;			///< +0x210
	unsigned char m_showBuildToolTipLayout;			///< +0x214
	unsigned char m_pad215[0x26C - 0x215];
	void *m_genArrow;				///< +0x26C
	unsigned char m_pad270[0x278 - 0x270];
	unsigned char m_genStarFlash;				///< +0x278
	unsigned char m_pad279[0x27C - 0x279];
	int m_lastFlashedAtPointValue;			///< +0x27C
	unsigned char m_pad280[0x290 - 0x280];
	unsigned char m_blinkFlag;				///< +0x290
	unsigned char m_pad291[0x294 - 0x291];
	int m_blinkCounter;				///< +0x294
	GameWindow *m_radarAttackGlowWindow;		///< +0x298
	unsigned char m_pad29C[0x2A4 - 0x29C];
	Rva000AD6F4 m_buildToolTipLayout;		///< +0x2A4
};

void ControlBar::reset()
{
	hideSpecialPowerShortcut();
	// do not destroy the rally drawable, it will get destroyed with everything else during a reset
	if ((m_radarAttackGlowOn = 0, m_radarAttackGlowWindow) != 0)
		m_radarAttackGlowWindow->winEnable(true);

	m_blinkFlag = false;
	m_blinkCounter = 0;

	m_displayedConstructPercent = -1.0f;
	m_displayedOCLTimerSeconds = 0;

	m_isObserverCommandBar = false; // reset us to use a normal command bar
	m_observerLookAtPlayer = 0;
	m_showBuildToolTipLayout = false;

	m_buildToolTipLayout.clear();

	if (theRadarWindowOverrideSource != 0)
		theRadarWindowOverrideSource->rva002D370A();

	if (m_resetMembers[1] != 0)
		m_resetMembers[1]->resetV();
	if (m_resetMembers[2] != 0)
		m_resetMembers[2]->resetV();
	if (m_resetMembers[3] != 0)
		m_resetMembers[3]->resetV();
	if (m_resetMembers[0] != 0)
		m_resetMembers[0]->resetV();

	// go back to default context
	switchToContext(0, 0);
	GameWindow **ppAnimateDown = &m_animateDownWindow;
	GameWindow *animateDown = *ppAnimateDown;
	if ((m_sideSelectAnimateDown = false, animateDown) != 0)
	{
		TheWindowManager->winDestroy(animateDown);
		*ppAnimateDown = 0;
	}

	// Teardown of the window/video map at +0x30.
	VolIter iter;
	m_videoMap.first((Rva000411084 *)&iter);
	void *first = (void *)iter.m_current;
	if (first != 0) {
		void *second = (void *)iter.m_owner;
		do {
			_ReadWriteBarrier();
			iter.m_current = first;
			iter.m_owner = second;
			((Rva000411084 *)&iter)->next();
			Overridable *overrides = *(Overridable **)((char *)first + 8);
			if (overrides->deleteOverrides() == 0) {
				m_videoMap.rva003A37DC(VideoPair(first, second));
			}
			first = (void *)iter.m_current;
			second = (void *)iter.m_owner;
		} while (first != 0);
	}

	// Remove any overridden sets.
	BfmeResetNode *set = (BfmeResetNode *)m_commandSets;
	while (set != 0) {
		volatile bool possibleAdjustment = false;
		BfmeResetNode *nextSet = set->m_next;
		if (set == (BfmeResetNode *)m_commandSets) {
			possibleAdjustment = true;
		}

		Overridable *stillValid = ((Overridable *)set)->deleteOverrides();
		if (stillValid == 0 && possibleAdjustment) {
			m_commandSets = nextSet;
		}

		set = nextSet;
	}

	// Remove any overridden command buttons.
	BfmeResetNode *button = (BfmeResetNode *)m_commandSets;
	{
		while (button != 0) {
			button->m_resetCleared = 0;
			button = button->m_next;
		}
	}

	// Clear the disjoint windows.
	GameWindow **slot = m_disjointWindows;
	int remaining = 0x20;
	do {
		if (*slot != 0)
			Rva00328518(*slot, 0);
		slot++;
		--remaining;
		_ReadWriteBarrier();
	} while (remaining != 0);

	if (TheTransitionHandler != 0)
		TheTransitionHandler->rva001DC42C(AsciiString("ControlBarArrow"), 0);
	m_genArrow = 0;

	m_lastFlashedAtPointValue |= -1;
	m_genStarFlash = true;
}
