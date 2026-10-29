// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/subsystem_bfme2
// stlport
typedef bool Bool;
#include "subsystem_interface.h"
#include "ascii_string.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)


// ?reset@ControlBar@@UAEXXZ @0x0031E09E 448B: ControlBar reset, the
// SubsystemInterface::reset override (retail vtable 0x00C0CC88 slot 9).
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

#include "ControlBarMemberTypes.h"

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
	void *m_current; // +0x00
	void *m_owner; // +0x04
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

// The +0x30 map as ControlBar's constructor spells it (its rowed hash_map
// constructor 0x0031E92D); begin and erase above are folded bodies reached
// through the Rva000427195 view.
#include <hash_map>

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
	void setGroup(AsciiString groupName, bool immediate);
	void remove(AsciiString groupName, bool skipPending);
};

class WindowVideoManager : public SubsystemInterface { public: WindowVideoManager(); virtual void init(); virtual void reset(); virtual void update(); private: char m_opaque[0x24 - 0x0C]; };

class AnimateWindowManager : public SubsystemInterface { public: AnimateWindowManager(); virtual void init(); virtual void reset(); virtual void update(); private: char m_opaque[0x38 - 0x0C]; };

enum CommandButtonMappedBorderType
{
    COMMAND_BUTTON_BORDER_NONE,
    COMMAND_BUTTON_BORDER_BUILD,
    COMMAND_BUTTON_BORDER_UPGRADE,
    COMMAND_BUTTON_BORDER_ACTION,
    COMMAND_BUTTON_BORDER_SYSTEM,
    COMMAND_BUTTON_BORDER_BFME5
};
enum CommandAvailability
{
	COMMAND_RESTRICTED = 0,
	COMMAND_AVAILABLE = 1,
	COMMAND_ACTIVE = 2,
	COMMAND_HIDDEN = 3,
	COMMAND_NOT_ALLOWED = 4,
	COMMAND_NOT_READY = 5,
	COMMAND_CANT_AFFORD = 6,
	COMMAND_LIMITED = 7,
	COMMAND_DONE = 8
};
class CommandButton;
class Image;
class Player;
class CommandSet;
class INI;
class Object;
struct Coord3D;
class PlayerTemplate;
struct ICoord2D;
class ControlBarSchemeManager;
class Drawable;
class WindowLayout;
class vector;
struct PlayerAITypeEntry;
class ControlBar : public SubsystemInterface
{
private:
	static const Image *m_rankVeteranIcon;
	static const Image *m_rankEliteIcon;
	static const Image *m_rankHeroicIcon;
public:
	virtual void init(void);
	void initObserverControls(void);
	void postProcessCommands(void);
	const CommandButton *findCommandButton(const AsciiString &name);
	void setControlCommand(GameWindow *button, const CommandButton *commandButton);
	void switchToContext(int context, void *draw);
	void GetPurchaseScienceStatus(Player *, int, const CommandButton **, bool *, bool *, bool *);
	bool rva0031E068(Player *, int);
	void setControlBarScheme(const AsciiString &schemeName);
	void switchControlBarStage(ControlBarStages stage);
	void hidePurchaseScience();
	void rva0031AD94();
	void showPurchaseScience();
	void rva0031D61E(const AsciiString *);
	void rva0031D64F();
	int rva0031AA86();
	void rva0031AB77SetFlag();
	void forgetStaleCommandSet(const AsciiString &);
	CommandSet *rva0031E8D5(const AsciiString &,int);
	CommandSet *rva0031B05B(CommandSet *);
	static void parseCommandSetDefinition(INI *);
	void setCommandBarBorder(GameWindow *button, CommandButtonMappedBorderType type);
	void setPortraitByImage(const Image *image);
	void rva0031AD14(int a, int b, int c, int d, int e);
	void rva0031AD48(bool hide);
	void rva0031ADAE();
protected:
	void setHiddenControlBar();
public:
	void rva0031AE13();
	void rva0031AE93(int *a, int *b);
	void rva0031AEAE(int *a, int *b);
	void rva0031AEC9();
	void hideSpecialPowerShortcut( void );
protected:
	void setLowControlBarConfig(void);
	void setDefaultControlBarConfig(void);
public:
	void rva0031B1BC(const Image *a250, const Image *a254, const Image *a258, const Image *a25c, const Image *a260, const Image *a264, const Image *a270, const Image *a274);
	void showSpecialPowerShortcut();
	void rva0031B210();
	// The target call and callee's ret 0x14 prove this five-argument ABI.
	// Const qualification follows the donor; the address name does not claim
	// the original return enum, access level or complete target declaration.
	CommandAvailability getCommandAvailability(const CommandButton *,GameWindow *,Object *,float *,bool) const;
	void rva0031B5A3(const Player *player);
	void showRallyPoint(const Coord3D *loc);
	void setControlCommand(const AsciiString &buttonWindowName, GameWindow *parent, const CommandButton *commandButton);
	void rva0031BAB1();
	void rva0031BAC3(Player *player);
	void populateCommand(Object *,bool);
protected:
	void populateStructureInventory(Object *,bool);
public:
	void populateBeacon(Object *);
protected:
	void populateUnderConstruction(Object *);
public:
	void populateOCLTimer(Object *);
protected:
	void populateMultiSelect();
public:
	void populateObserverList();
	void setControlBarSchemeByPlayer(Player *p);
	void setControlBarSchemeByPlayerTemplate(const PlayerTemplate *pt);
	void rva0031D230();
protected:
	void populateSpecialPowerShortcut(Player *player);
public:
	virtual void reset();
	virtual void update();
protected:
	void updateContextMultiSelect();
public:
	void rva0053E6E1();
protected:
	void updateContextCommand();
public:
	void rva0053E4B1();
	void updateContextContestedStructureInventory();
protected:
	void updateContextOCLTimer();
	// The home construction unit owns the exact149-byte provider at53EAEC.
	void updateContextStructureInventory();
public:
	ControlBar();
	WindowVideoManager *m_videoManager; // +0x0C
	AnimateWindowManager *m_animateWindowManager; // +0x10
	AnimateWindowManager *m_animateWindowManagerForGenShortcuts; // +0x14
	AnimateWindowManager *m_generalsScreenAnimate; // +0x18
private:
	ICoord2D m_defaultControlBarPosition; // +0x1C
	int m_currentControlBarStage; // +0x24
public:
	unsigned char m_UIDirty; // +0x28
	char m_pad29[0x3];
	CommandButton *m_commandButtons; // +0x2C +0x2C
	_STL::hash_map<int, Rva0031DBFCElement> m_videoMap; // +0x30 +0x30
private:
	ControlBarSchemeManager *m_controlBarSchemeManager; // +0x44
	// Nine slots: the constructor (0x0031E94C) clears +0x48..+0x6C with one
	// rep stosd. The last holds the command-button parent init creates; its
	// ContextParent name is unrecovered (Zero Hour's enum also has nine, with
	// CP_PURCHASE_SCIENCE at index 1).
	GameWindow *m_contextParent[NUM_CONTEXT_PARENTS + 1]; // +0x48
	Drawable *selectedDrawable; // +0x6C
	int context; // +0x70
public:
	int m_rallyPointDrawableID; // +0x74
	float m_displayedConstructPercent; // +0x78 +0x78
	int m_displayedOCLTimerSeconds; // +0x7C +0x7C
private:
	int m_0080; // +0x80
	GameWindow *m_rightHUDWindow; // +0x84
	GameWindow *m_rightHUDCameoWindow; // +0x88
	GameWindow *m_rightHUDUpgradeCameos[MAX_RIGHT_HUD_UPGRADE_CAMEOS]; // +0x8C
	GameWindow *m_rightHUDUnitSelectParent; // +0xA0
	GameWindow *m_communicatorButton; // +0xA4
	GameWindow *m_specialPowerShortcutButtons[5]; // +0xA8
	GameWindow *m_specialPowerShortcutButtonParents[5]; // +0xBC
	int m_currentlyUsedSpecialPowersButtons; // +0xD0
	WindowLayout *m_specialPowerLayout; // +0xD4 target+0xD4
public:
	GameWindow *m_specialPowerShortcutParent; // +0xD8 retail this+0xD8 (BFME1 header has this+0xFC)
	GameWindow *m_commandWindows[MAX_COMMANDS_PER_SET]; // +0xDC
private:
	void *m_015C[32]; // +0x15C
public:
	Bool m_sideSelectAnimateDown; // +0x1DC
	char m_pad1DD[0x3];
private:
	int m_01E0; // +0x1E0
	int m_01E4; // +0x1E4
	int m_01E8; // +0x1E8
	int m_01EC; // +0x1EC
	int m_01F0; // +0x1F0
	int m_01F4; // +0x1F4
	int m_01F8; // +0x1F8
	int m_01FC; // +0x1FC
public:
	GameWindow *m_animateDownWindow; // +0x200 +0x200
private:
	int m_0204; // +0x204
	unsigned int buildUpClockColor; // +0x208
public:
	bool m_isObserverCommandBar; // +0x20C
	char m_pad20D[0x3];
	void *m_observerLookAtPlayer; // +0x210 +0x210
	unsigned char m_showBuildToolTipLayout; // +0x214 +0x214
	char m_pad215[0x3];
private:
	int m_commandButtonBorderBuildColor; // +0x218 +0x218
	int m_commandButtonBorderActionColor; // +0x21C +0x21C
	int m_commandButtonBorderUpgradeColor; // +0x220 +0x220
	int m_commandButtonBorderSystemColor; // +0x224 +0x224
	int m_commandButtonBorderBfme5Color; // +0x228 +0x228
	unsigned int m_022C; // +0x22C
	_STL::vector<PlayerAITypeEntry> m_0230; // +0x230
	_STL::vector<PlayerAITypeEntry> m_023C; // +0x23C
	const Image *m_genStarOn; // +0x248
	const Image *m_genStarOff; // +0x24C
	const Image *m_p0250; // +0x250
	const Image *m_p0254; // +0x254
	const Image *m_p0258; // +0x258
	const Image *m_p025C; // +0x25C
	const Image *m_p0260; // +0x260
	const Image *m_p0264; // +0x264
	char m_pad268[0x4];
public:
	void *m_genArrow; // +0x26C +0x26C
private:
	const Image *m_p0270; // +0x270
	const Image *m_p0274; // +0x274
public:
	Bool m_genStarFlash; // +0x278
	char m_pad279[0x3];
	int m_lastFlashedAtPointValue; // +0x27C
private:
	ICoord2D m_controlBarForegroundMarkerPos; // +0x280
	ICoord2D m_controlBarBackgroundMarkerPos; // +0x288
public:
	unsigned char m_0290; // +0x290
	char m_pad291[0x3];
	int m_0294; // +0x294
	GameWindow *m_radarAttackGlowWindow; // +0x298
private:
	int m_rva0031C83D29C; // +0x29C
	void *m_commandWindowUserData; // +0x2A0
public:
	Rva000AD6F4 m_buildToolTipLayout; // +0x2A4 +0x2A4
private:
	_STL::vector<PlayerAITypeEntry> m_02A8; // +0x2A8
};

void ControlBar::reset()
{
	hideSpecialPowerShortcut();
	// do not destroy the rally drawable, it will get destroyed with everything else during a reset
	if ((m_rallyPointDrawableID = 0, m_radarAttackGlowWindow) != 0)
		m_radarAttackGlowWindow->winEnable(true);

	m_0290 = false;
	m_0294 = 0;

	m_displayedConstructPercent = -1.0f;
	m_displayedOCLTimerSeconds = 0;

	m_isObserverCommandBar = false; // reset us to use a normal command bar
	m_observerLookAtPlayer = 0;
	m_showBuildToolTipLayout = false;

	m_buildToolTipLayout.clear();

	if (theRadarWindowOverrideSource != 0)
		theRadarWindowOverrideSource->rva002D370A();

	if (m_animateWindowManager)
		m_animateWindowManager->reset();
	if (m_animateWindowManagerForGenShortcuts)
		m_animateWindowManagerForGenShortcuts->reset();
	if (m_generalsScreenAnimate)
		m_generalsScreenAnimate->reset();
	if (m_videoManager)
		m_videoManager->reset();

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
	((Rva000427195 *)&m_videoMap)->first((Rva000411084 *)&iter);
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
				((Rva000427195 *)&m_videoMap)->rva003A37DC(VideoPair(first, second));
			}
			first = (void *)iter.m_current;
			second = (void *)iter.m_owner;
		} while (first != 0);
	}

	// Remove any overridden sets.
	BfmeResetNode *set = (BfmeResetNode *)m_commandButtons;
	while (set != 0) {
		volatile bool possibleAdjustment = false;
		BfmeResetNode *nextSet = set->m_next;
		if (set == (BfmeResetNode *)m_commandButtons) {
			possibleAdjustment = true;
		}

		Overridable *stillValid = ((Overridable *)set)->deleteOverrides();
		if (stillValid == 0 && possibleAdjustment) {
			*(BfmeResetNode **)&m_commandButtons = nextSet;
		}

		set = nextSet;
	}

	// Remove any overridden command buttons.
	BfmeResetNode *button = (BfmeResetNode *)m_commandButtons;
	{
		while (button != 0) {
			button->m_resetCleared = 0;
			button = button->m_next;
		}
	}

	// Clear the disjoint windows.
	GameWindow **slot = m_commandWindows;
	int remaining = 0x20;
	do {
		if (*slot != 0)
			Rva00328518(*slot, 0);
		slot++;
		--remaining;
		_ReadWriteBarrier();
	} while (remaining != 0);

	if (TheTransitionHandler != 0)
		TheTransitionHandler->remove(AsciiString("ControlBarArrow"), 0);
	m_genArrow = 0;

	m_lastFlashedAtPointValue |= -1;
	m_genStarFlash = true;
}
