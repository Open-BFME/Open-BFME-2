// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_CSTD_FUNCTION_IMPORTS /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// BFME1 semantic donor: ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f
// game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_populateSpecialPowerShortcut.cpp.
// WB 0x00C30C60 names the BFME2 method. Target boundary 0x0031D85D..0x0031DAF8
// is 667 bytes; every callee is resolved:
// 31B210 / 31DAF8 / 35B7D9 now have rowed providers and the 31B641 call is
// the established ControlBar::setControlCommand owner rather than a new pin.
// Retail retains the PlayerTemplate base in ESI through StringBase::isEmpty
// and adds 0x140 in place for the command-set lookup: the name's address is
// passed straight into findCommandSet's call (a pointer local for it is
// computed into EAX instead).
typedef bool Bool;
#include "subsystem_interface.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum { FALSE = 0, TRUE = 1 };

enum ScienceType
{
	SCIENCE_INVALID = -1
};

enum
{
	GUI_COMMAND_PURCHASE_SCIENCE = 0x19,
	NEED_SPECIAL_POWER_SCIENCE = 0x00000080
};

#include "ascii_string.h"
namespace _STL { void __cdecl free(void *); }
#include <vector>

// Match the established ScienceType vector cleanup's actual game allocator:
// _STL::free was only a pin spelling of this verified17-byte provider.
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template <> inline _Vector_base<ScienceType, allocator<ScienceType> >::~_Vector_base()
{ if (_M_start) Rva00030830GameFree(_M_start); }
}

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

class GadgetCreateView;
class Image;
class GameWindow;
class WinInstanceData;
typedef void (*GameWinTooltipFunc)(GameWindow *, WinInstanceData *, unsigned int);
class GameWindow
{
public:
	int winGetPosition(int *x, int *y);
	int winGetScreenPosition(int *x, int *y);
	void snapshotCreateView(GadgetCreateView *view, bool keepInstance);
	unsigned int winGetStatus();
	void winSetUserData(void *userData);
	unsigned int winSetStatus(unsigned int status);
	unsigned int winClearStatus(unsigned int status);
	int winSetSize(int width, int height);
	int winSetPosition(int x, int y);
	int winSetTooltipFunc(GameWinTooltipFunc tooltip);
	int winEnable(bool enable);
	int winHide(bool hide);
	int winSetEnabledImage(int index, const Image *image);
	void *winGetUserData();
	bool winIsHidden();
	virtual void unknown00();
	virtual void unknown01();
	virtual void unknown02();
	virtual void unknown03();
	virtual void unknown04();
	virtual void unknown05();
	virtual void unknown06();
	virtual void unknown07();
	virtual bool isPushButton() const;
};

class PlayerTemplate
{
	unsigned char m_unreconstructed_00[0x140];
	AsciiString m_specialPowerShortcutCommandSet;

public:
	const AsciiString &getSpecialPowerShortcutCommandSet() const
	{
		return m_specialPowerShortcutCommandSet;
	}
};

class Player
{
	unsigned char m_unreconstructed_00[0x34];
	PlayerTemplate *m_playerTemplate;

public:
	PlayerTemplate *getPlayerTemplate() const
	{
		return m_playerTemplate;
	}
	Bool isLocalPlayer(void) const;
	Bool hasScience(ScienceType science) const;
	Bool hasAnyRequiredSciences(const _STL::vector<ScienceType> &) const;
};

class Rva0029FCB4 { public: _STL::vector<ScienceType> rva0029FCB4(); };
class SpecialPowerTemplate {};

typedef _STL::vector<ScienceType> ScienceVec;

class CommandButton
{
	unsigned char m_unreconstructed_00[0x14];
	Int m_command;
	CommandButton *m_next;
	UnsignedInt m_options;
	unsigned char m_unreconstructed_1C[0x24];
	const SpecialPowerTemplate *m_specialPower;
	unsigned char m_unreconstructed_38[0x5C];
	ScienceVec m_science;

public:
	Int getCommandType(void) const
	{
		return m_command;
	}
	CommandButton *getNext(void) const
	{
		return m_next;
	}
	const SpecialPowerTemplate *getSpecialPowerTemplate(void) const
	{
		return m_specialPower;
	}
	const ScienceVec &getScienceVec(void) const
	{
		return m_science;
	}
	signed char getOptions(void) const
	{
		return static_cast<signed char>(m_options);
	}
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(Int index) const;
};

class Rva0035B7D9
{
public:
	void rva0035B7D9(Rva0035B7D9 *source, bool notify);
};

#include "ControlBarMemberTypes.h"
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
class INI;
class Object;
struct Coord3D;
class WindowVideoManager;
class AnimateWindowManager;
struct ICoord2D;
struct Rva0031DBFCElement;
class ControlBarSchemeManager;
class Drawable;
class WindowLayout;
struct PlayerAITypeEntry;
class Rva000AD6F4;
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

extern ControlBar *TheControlBar;
class Rva0031D5F8 { public: void *rva0031D5F8(const AsciiString *); };
class Rva0031AF54
{
public:
	void rva0031AF54(bool flag);
	char m_pad00[0x14];
	AnimateWindowManager *m_manager; // +0x14
	char m_pad18[0x90];
	GameWindow *m_list[10]; // +0xA8
	int m_count; // +0xD0
	char m_padD4[0x4];
	GameWindow *m_window; // +0xD8
};

void GadgetButtonSetAltSound(GameWindow *window, AsciiString sound);

void ControlBar::populateSpecialPowerShortcut(Player *player)
{
	const CommandSet *commandSet;
	Int i;
	Int currentButton = 0;
	const CommandButton *commandButton;
	if (!player || !player->getPlayerTemplate()
			|| !player->isLocalPlayer() || m_currentlyUsedSpecialPowersButtons == 0
			|| !m_specialPowerShortcutButtons || !m_specialPowerShortcutButtonParents)
		return;

	for (i = 0; i < m_currentlyUsedSpecialPowersButtons; ++i)
	{
		if (m_specialPowerShortcutButtons[i])
			m_specialPowerShortcutButtons[i]->winHide(true);
		if (m_specialPowerShortcutButtonParents[i])
			m_specialPowerShortcutButtonParents[i]->winHide(true);
	}

	PlayerTemplate *playerTemplate=player->getPlayerTemplate();
	if ((playerTemplate ? playerTemplate : playerTemplate)->getSpecialPowerShortcutCommandSet().isEmpty())
		return;
	commandSet = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(&playerTemplate->getSpecialPowerShortcutCommandSet());
	if (!commandSet)
		return;

	for (i = 0; i < m_currentlyUsedSpecialPowersButtons; ++i)
	{
		commandButton = commandSet->getCommandButton(i);
		if (!commandButton)
			continue;

		if (commandButton->getOptions() & NEED_SPECIAL_POWER_SCIENCE)
		{
			const SpecialPowerTemplate *power = commandButton->getSpecialPowerTemplate();
			if (power)
			{
                _STL::vector<ScienceType> required=((Rva0029FCB4 *)power)->rva0029FCB4();
                if (!required.empty()) {
				if (!player->hasAnyRequiredSciences(required))
					continue;

				Int bestIndex = -1;
				for (Int scienceIndex = 0;
					scienceIndex < commandButton->getScienceVec().size(); ++scienceIndex)
				{
					ScienceType science = commandButton->getScienceVec()[scienceIndex];
					if (player->hasScience(science))
						bestIndex = scienceIndex;
					else
						break;
				}

				if (bestIndex != -1)
				{
					ScienceType science = commandButton->getScienceVec()[bestIndex];
					for (CommandButton *purchase = m_commandButtons;
						purchase; purchase = purchase->getNext())
					{
						if (purchase->getCommandType() == GUI_COMMAND_PURCHASE_SCIENCE
								&& !purchase->getScienceVec().empty()
								&& purchase->getScienceVec()[0] == science)
							((Rva0035B7D9 *)commandButton)->rva0035B7D9(
								(Rva0035B7D9 *)purchase, true);
					}
				}
                }
			}
		}

		m_specialPowerShortcutButtons[currentButton]->winHide(false);
		m_specialPowerShortcutButtonParents[currentButton]->winHide(false);
		m_specialPowerShortcutButtons[currentButton]->winEnable(true);
		m_specialPowerShortcutButtonParents[currentButton]->winEnable(true);

		setControlCommand(m_specialPowerShortcutButtons[currentButton], commandButton);
		GadgetButtonSetAltSound(m_specialPowerShortcutButtons[currentButton],
			AsciiString("GUIGenShortcutClick"));
		++currentButton;
	}

	if (m_contextParent[0] && !m_contextParent[0]->winIsHidden()
			&& m_specialPowerShortcutParent->winIsHidden())
	{
		showSpecialPowerShortcut();
		((Rva0031AF54 *)this)->rva0031AF54(true);
	}
	rva0031B210();
}
