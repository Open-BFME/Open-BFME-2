// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// BFME1 ba7ddda7 ControlBar.cpp supplies the context-selection workflow.
// WB 0x00C2DCC0 names switchToContext. Native 0x0031BF64..0x0031C3E2
// supplies the complete 1150B instruction body, context values and offsets.
// The row also covers its immediately following 44B eleven-case jump table.
// Four new address-derived ControlBar callees have named WB counterparts:
// command 0x01117000, multiselect 0x01124EB0, construction 0x01123660,
// observer 0x0111D290. Beacon 0x01123A30 is unnamed. Native boundaries and
// argument cleanup establish each ABI, without recovering these bodies.
// Rally-point 0x00C2F300 names the Coord3D-pointer workflow, with retail
// 0x0031B892..0x0031B99A supplying its complete one-argument boundary.
#include <vector>
#include "../../../Common/GameLogicObjectLookupView.h"
class Drawable;
class Object;
class GameWindow { public: int winHide(bool); unsigned int winClearStatus(unsigned int); };
class GameWindowManager;
class InGameUI;
class Rva00E01E28Owner;
extern GameWindowManager *TheWindowManager;
extern InGameUI *TheInGameUI;
class HotKeyManager;
extern HotKeyManager *TheHotKeyManager;
extern int g_Va00E04478;
// Retail E01D14 stores the prior selected drawable; original identifier unknown.
Drawable *BfmeControlBarPreviousDrawable = 0;
extern GameLogic *TheGameLogic;
int Rva0043C969Get();
class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
class Rva002D368E { public: void rva002D368E(); };
// This existing folded setter copies Object+0x74 to receiver+0x58. Using its
// owned binding does not identify the context overlay as PhysicsBehavior.
class PhysicsBehavior { public: void setIgnoreCollisionsWith(const Object *); };
struct BfmePod8 { int a[2]; };
namespace _STL {
template <> BfmePod8 *vector<BfmePod8, allocator<BfmePod8> >::erase(BfmePod8 *, BfmePod8 *);
}
class ContextResetView {
public:
    virtual void slot00()=0;
    virtual void slot01()=0;
    virtual void slot02()=0;
    virtual void slot03()=0;
    virtual void slot04()=0;
    virtual void slot05()=0;
    virtual void slot06()=0;
    virtual void slot07()=0;
    virtual void slot08()=0;
    virtual void reset()=0;
};
class ContextRadiusView {
public:
    virtual void slot00()=0;
    virtual void slot01()=0;
    virtual void slot02()=0;
    virtual void slot03()=0;
    virtual void slot04()=0;
    virtual void slot05()=0;
    virtual void slot06()=0;
    virtual void slot07()=0;
    virtual void slot08()=0;
    virtual void slot09()=0;
    virtual void slot10()=0;
    virtual void slot11()=0;
    virtual void slot12()=0;
    virtual void slot13()=0;
    virtual void slot14()=0;
    virtual void slot15()=0;
    virtual void slot16()=0;
    virtual void slot17()=0;
    virtual void slot18()=0;
    virtual void slot19()=0;
    virtual void slot20()=0;
    virtual void slot21()=0;
    virtual void slot22()=0;
    virtual void slot23()=0;
    virtual void slot24()=0;
    virtual void slot25()=0;
    virtual void slot26()=0;
    virtual void slot27()=0;
    virtual void slot28()=0;
    virtual void slot29()=0;
    virtual void slot30()=0;
    virtual void slot31()=0;
    virtual void slot32()=0;
    virtual void slot33()=0;
    virtual void slot34()=0;
    virtual void slot35()=0;
    virtual void slot36()=0;
    virtual void slot37()=0;
    virtual void slot38()=0;
    virtual void slot39()=0;
    virtual void slot40()=0;
    virtual void slot41()=0;
    virtual void slot42()=0;
    virtual void slot43()=0;
    virtual void slot44()=0;
    virtual void slot45()=0;
    virtual void slot46()=0;
    virtual void slot47()=0;
    virtual void slot48()=0;
    virtual void slot49()=0;
    virtual void slot50()=0;
    virtual void slot51()=0;
    virtual void slot52()=0;
    virtual void slot53()=0;
    virtual void slot54()=0;
    virtual void slot55()=0;
    virtual void slot56()=0;
    virtual void slot57()=0;
    virtual void slot58()=0;
    virtual void slot59()=0;
    virtual void slot60()=0;
    virtual void slot61()=0;
    virtual void slot62()=0;
    virtual void slot63()=0;
    virtual void slot64()=0;
    virtual void slot65()=0;
    virtual void slot66()=0;
    virtual void slot67()=0;
    virtual void slot68()=0;
    virtual void slot69()=0;
    virtual void slot70()=0;
    virtual void slot71()=0;
    virtual void slot72()=0;
    virtual void slot73()=0;
    virtual void slot74()=0;
    virtual void slot75()=0;
    virtual void slot76()=0;
    virtual void slot77()=0;
    virtual void slot78()=0;
    virtual void slot79()=0;
    virtual void slot80()=0;
    virtual void clearRadius()=0;
};
class ContextFocusView {
public:
    virtual void slot00()=0;
    virtual void slot01()=0;
    virtual void slot02()=0;
    virtual void slot03()=0;
    virtual void slot04()=0;
    virtual void slot05()=0;
    virtual void slot06()=0;
    virtual void slot07()=0;
    virtual void slot08()=0;
    virtual void slot09()=0;
    virtual void slot10()=0;
    virtual void slot11()=0;
    virtual void slot12()=0;
    virtual void slot13()=0;
    virtual void slot14()=0;
    virtual void slot15()=0;
    virtual void slot16()=0;
    virtual void slot17()=0;
    virtual void slot18()=0;
    virtual void slot19()=0;
    virtual void slot20()=0;
    virtual void slot21()=0;
    virtual void slot22()=0;
    virtual void slot23()=0;
    virtual void slot24()=0;
    virtual void slot25()=0;
    virtual void slot26()=0;
    virtual void slot27()=0;
    virtual void slot28()=0;
    virtual void slot29()=0;
    virtual void slot30()=0;
    virtual void slot31()=0;
    virtual void slot32()=0;
    virtual void slot33()=0;
    virtual void slot34()=0;
    virtual void slot35()=0;
    virtual void slot36()=0;
    virtual void slot37()=0;
    virtual void slot38()=0;
    virtual void slot39()=0;
    virtual void slot40()=0;
    virtual void slot41()=0;
    virtual void slot42()=0;
    virtual void slot43()=0;
    virtual void slot44()=0;
    virtual void slot45()=0;
    virtual void slot46()=0;
    virtual void slot47()=0;
    virtual void slot48()=0;
    virtual int setFocus(GameWindow *)=0;
};
class ContextRebuildView {
public:
    virtual void slot00()=0;
    virtual void slot01()=0;
    virtual void slot02()=0;
    virtual void selected()=0;
};
class RebuildHoleBehaviorInterface;
class RebuildHoleBehavior { public: static RebuildHoleBehaviorInterface *getRebuildHoleBehaviorInterfaceFromObject(Object *); };
struct ContextDrawableView { char unknown00[0xFC]; Object *object; Object *getObject() { return object; } };
struct ContextTemplateView { char unknown00[0x10C]; unsigned char flags; };
struct ContextObjectView { char unknown00[4]; ContextTemplateView *objectTemplate; bool hasRebuildFlag() const { return (objectTemplate->flags&0x40)!=0; } };
struct ContextControlBarView {
    char unknown00[0x44];
    GameWindow *parent[10];
    Drawable *selected;
    int context;
    char unknown74[0x68];
    GameWindow *commandWindows[32];
    char unknown15C[0x144];
    ContextResetView *overlay;
    void *unknown2A4;
    _STL::vector<BfmePod8> selections;
};
struct Coord3D;
typedef bool Bool;
#include "subsystem_interface.h"
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
class AsciiString;
class Image;
class Player;
class CommandSet;
class INI;
class PlayerTemplate;
class WindowVideoManager;
class AnimateWindowManager;
struct ICoord2D;
struct Rva0031DBFCElement;
class ControlBarSchemeManager;
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
// Each arm follows the independently read native call order.
#define HIDE_PARENTS(a,b,c,d,e,f,g,h) \
    self->parent[2]->winHide(a); self->parent[9]->winHide(b); \
    self->parent[3]->winHide(c); self->parent[4]->winHide(d); \
    self->parent[5]->winHide(e); self->parent[8]->winHide(f); \
    self->parent[6]->winHide(g); self->parent[7]->winHide(h)
void ControlBar::switchToContext(int context,void *draw)
{
    ContextControlBarView *self=(ContextControlBarView *)this;
    Drawable *incomingDraw=(Drawable *)draw;
    bool changed=context!=self->context || incomingDraw!=self->selected;
    if (changed) {
        self->selections.clear();
        if (theRadarWindowOverrideSource)
            ((Rva002D368E *)theRadarWindowOverrideSource)->rva002D368E();
    }
    Object *drawObject=incomingDraw ? ((ContextDrawableView *)incomingDraw)->getObject() : 0;
    if (TheHotKeyManager) ((ContextResetView *)TheHotKeyManager)->reset();
    ((ContextRadiusView *)TheInGameUI)->clearRadius();
    if (incomingDraw!=BfmeControlBarPreviousDrawable && incomingDraw!=self->selected)
        self->overlay->reset();
    Drawable *oldSelected=self->selected;
    self->selected=incomingDraw;
    BfmeControlBarPreviousDrawable=oldSelected;
    if (!g_Va00E04478 && !Rva0043C969Get() && TheGameLogic && TheGameLogic->rva0042219())
        ((ContextFocusView *)TheWindowManager)->setFocus(0);
    ((PhysicsBehavior *)self->overlay)->setIgnoreCollisionsWith(drawObject);
    showRallyPoint(0);
    switch (context) {
    case 0:
    case 4:
        HIDE_PARENTS(true,true,true,true,true,true,true,true);
        {
            GameWindow **window=self->commandWindows;
            int count=32;
            do { if (*window) (*window)->winClearStatus(0x800000); ++window; --count; } while (count!=0);
        }
        if (incomingDraw && ((ContextDrawableView *)incomingDraw)->getObject()
            && ((ContextObjectView *)((ContextDrawableView *)incomingDraw)->getObject())->hasRebuildFlag()) {
            RebuildHoleBehaviorInterface *rebuild=RebuildHoleBehavior::getRebuildHoleBehaviorInterfaceFromObject(((ContextDrawableView *)incomingDraw)->getObject());
            if (rebuild) ((ContextRebuildView *)rebuild)->selected();
        }
        break;
    case 1:
        HIDE_PARENTS(false,false,true,true,true,true,true,true);
        populateCommand(((ContextDrawableView *)incomingDraw)->getObject(),changed);
        break;
    case 2:
        HIDE_PARENTS(false,false,true,true,true,true,true,true);
        populateStructureInventory(((ContextDrawableView *)incomingDraw)->getObject(),false);
        break;
    case 3:
        if (theRadarWindowOverrideSource) ((Rva002D368E *)theRadarWindowOverrideSource)->rva002D368E();
        HIDE_PARENTS(false,false,true,true,true,true,true,true);
        populateStructureInventory(((ContextDrawableView *)incomingDraw)->getObject(),true);
        break;
    case 5:
        HIDE_PARENTS(true,true,true,false,true,true,true,true);
        populateBeacon(((ContextDrawableView *)incomingDraw)->getObject());
        break;
    case 6:
        HIDE_PARENTS(true,false,true,true,true,true,true,true);
        populateUnderConstruction(((ContextDrawableView *)incomingDraw)->getObject());
        break;
    case 10:
        HIDE_PARENTS(true,true,true,true,true,false,true,true);
        populateOCLTimer(((ContextDrawableView *)incomingDraw)->getObject());
        break;
    case 7:
        HIDE_PARENTS(false,false,true,true,true,true,true,true);
        populateMultiSelect();
        break;
    case 9:
        HIDE_PARENTS(true,true,true,true,true,true,true,false);
        populateObserverList();
        break;
    }
    self->context=context;
}
#undef HIDE_PARENTS
