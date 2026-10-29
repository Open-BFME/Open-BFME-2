// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// Clean donor: reference/open-bfme-1 @575ba2b04743f190f069805fbdc59936123c45da
// game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarInitSpecialPowershortcutBar.cpp.
// Donor names the initialization workflow. WB C30790 keeps its literals and calls
// but exposes no name; existing GameLogic/Player refresh callers prove ControlBar.
// Retain the established address-derived method owner. Target31BAC3..31BD55 RET4
// independently proves five windowsA8/parentsBC/countD0/layoutD4/parentD8;
// Player template34 with name144/count148; window-manager slots80/F0.
// Target uses StringBase::isEmpty and pointer-format overload. Qualified global
// delete reproduces virtual destructor flag0 then global free rather than flag1.
typedef bool Bool;
#include "subsystem_interface.h"
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum { MAX_SPECIAL_POWER_SHORTCUTS = 5 };
enum { WIN_STATUS_USE_OVERLAY_STATES = 0x00200000 };
enum NameKeyType { NAMEKEY_INVALID = 0 };

// Target string text access is inlined: one Header pointer and text at+8,
// with the compiler empty literal when null. The emptiness test below instead
// calls the existing StringBase<char>::isEmpty worker as witnessed in retail.

static inline const char *inlineStr(const AsciiString &asciiString)
{
	const char *text = *reinterpret_cast<const char *const *>(&asciiString);
	return text ? text + 8 : "";
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

// BFME makes WindowLayout virtual: slot 1 is the deleting destructor, slot 4
// hide(Bool), slot 8 destroyWindows (ControlBarPrintPositions.cpp, Shell_doPush.cpp).
class WindowLayout
{
public:
	virtual void runInit(void *) = 0;
	virtual ~WindowLayout();
	virtual void runUpdate(void *) = 0;
	virtual void runShutdown(void *) = 0;
	virtual void hide(Bool hide) = 0;
	virtual void bringForward() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void destroyWindows() = 0;
};

class GameWindowManager
{
public:
	virtual void slot000();
	virtual void slot004();
	virtual void slot008();
	virtual void slot00C();
	virtual void slot010();
	virtual void slot014();
	virtual void slot018();
	virtual void slot01C();
	virtual void slot020();
	virtual void slot024();
	virtual void slot028();
	virtual void slot02C();
	virtual void slot030();
	virtual void slot034();
	virtual void slot038();
	virtual void slot03C();
	virtual void slot040();
	virtual void slot044();
	virtual void slot048();
	virtual void slot04C();
	virtual void slot050();
	virtual void slot054();
	virtual void slot058();
	virtual void slot05C();
	virtual void slot060();
	virtual void slot064();
	virtual void slot068();
	virtual void slot06C();
	virtual void slot070();
	virtual void slot074();
	virtual void slot078();
	virtual void slot07C();
	virtual WindowLayout *winCreateLayout(AsciiString filename); // target80
	virtual void slot084();
	virtual void slot088();
	virtual void slot08C();
	virtual void slot090();
	virtual void slot094();
	virtual void slot098();
	virtual void slot09C();
	virtual void slot0A0();
	virtual void slot0A4();
	virtual void slot0A8();
	virtual void slot0AC();
	virtual void slot0B0();
	virtual void slot0B4();
	virtual void slot0B8();
	virtual void slot0BC();
	virtual void slot0C0();
	virtual void slot0C4();
	virtual void slot0C8();
	virtual void slot0CC();
	virtual void slot0D0();
	virtual void slot0D4();
	virtual void slot0D8();
	virtual void slot0DC();
	virtual void slot0E0();
	virtual void slot0E4();
	virtual void slot0E8();
	virtual void slot0EC();
	virtual GameWindow *winGetWindowFromId(GameWindow *parent,NameKeyType id); // targetF0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *nameString);
	NameKeyType nameToKey(const AsciiString &nameString);
};

extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;

class PlayerTemplate
{
public:
	const AsciiString &getSpecialPowerShortcutWinName() const { return m_specialPowerShortcutWinName; }
	Int getSpecialPowerShortcutButtonCount() const { return m_specialPowerShortcutButtonCount; }

private:
	char m_unmodelled00[0x144];
	AsciiString m_specialPowerShortcutWinName;     // target+0x144
	Int m_specialPowerShortcutButtonCount;         // target+0x148
};

class Player
{
public:
	const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes);
	// the getPlayerTemplate copy loses to the first-in-order copy. No flags touched.
	const PlayerTemplate *bfme_player_template_scs() const { return m_playerTemplate; }
	Bool isLocalPlayer() const;
	Bool isPlayerActive() const;

private:
	char m_unmodelled00[0x34];
	const PlayerTemplate *m_playerTemplate;        // target+0x34
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
class CommandButton;
class CommandSet;
class INI;
class Object;
struct Coord3D;
class WindowVideoManager;
class AnimateWindowManager;
struct ICoord2D;
struct Rva0031DBFCElement;
class ControlBarSchemeManager;
class Drawable;
class vector;
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

void ControlBar::rva0031BAC3(Player *player)
{
	for (Int i = 0; i < MAX_SPECIAL_POWER_SHORTCUTS; ++i)
	{
		m_specialPowerShortcutButtonParents[i] = 0;
		m_specialPowerShortcutButtons[i] = 0;
	}

	if (m_specialPowerLayout)
	{
		m_specialPowerLayout->destroyWindows();
		::delete m_specialPowerLayout;
		m_specialPowerLayout = 0;
	}
	m_specialPowerShortcutParent = 0;
	m_currentlyUsedSpecialPowersButtons = 0;
	const PlayerTemplate *pt = player->bfme_player_template_scs();

	if (!pt || !player->isLocalPlayer()
			|| pt->getSpecialPowerShortcutButtonCount() == 0
			|| ((const StringBase<char> *)&pt->getSpecialPowerShortcutWinName())->isEmpty()
			|| !player->isPlayerActive())
		return;
	m_currentlyUsedSpecialPowersButtons = pt->getSpecialPowerShortcutButtonCount();
	AsciiString layoutName, tempName, windowName, parentName;
	layoutName = pt->getSpecialPowerShortcutWinName();
	m_specialPowerLayout = TheWindowManager->winCreateLayout(layoutName);
	m_specialPowerLayout->hide(true);

	tempName = layoutName;
	reinterpret_cast<StringBase<char> *>(&tempName)->concat(":GenPowersShortcutBarParent");
	NameKeyType id = TheNameKeyGenerator->nameToKey(tempName);
	m_specialPowerShortcutParent = TheWindowManager->winGetWindowFromId(0, id);

	tempName = layoutName;
	reinterpret_cast<StringBase<char> *>(&tempName)->concat(":ButtonCommand%d");
	parentName = layoutName;
	reinterpret_cast<StringBase<char> *>(&parentName)->concat(":ButtonParent%d");
	Int count = pt->getSpecialPowerShortcutButtonCount();
	m_currentlyUsedSpecialPowersButtons = count < MAX_SPECIAL_POWER_SHORTCUTS ? count : MAX_SPECIAL_POWER_SHORTCUTS;
	for (i = 0; i < m_currentlyUsedSpecialPowersButtons; i++)
	{
		windowName.format(&tempName, i + 1);
		id = TheNameKeyGenerator->nameToKey(inlineStr(windowName));
		m_specialPowerShortcutButtons[i] =
			TheWindowManager->winGetWindowFromId(m_specialPowerShortcutParent, id);
		m_specialPowerShortcutButtons[i]->winSetStatus(WIN_STATUS_USE_OVERLAY_STATES);

		windowName.format(&parentName, i + 1);
		id = TheNameKeyGenerator->nameToKey(inlineStr(windowName));
		m_specialPowerShortcutButtonParents[i] =
			TheWindowManager->winGetWindowFromId(m_specialPowerShortcutParent, id);
	}
}
