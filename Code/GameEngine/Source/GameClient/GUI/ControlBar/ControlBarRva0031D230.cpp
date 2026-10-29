// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/subsystem_bfme2
//
// ?rva0031D230@ControlBar@@QAEXXZ -- retail 0x0031D230..0x0031D5F8 (968 bytes).
// ControlBar context evaluation (Zero Hour ControlBar::evaluateContextUI): clears
// the dirty byte at +0x28 / refreshes the purchase science window / reads the
// selection through TheInGameUI slots 0x118 0x124 0x130 and the controllable
// check 0x0029C752 / uncontrolled selections pick the beacon (5) structure
// inventory (4) or 3 contexts from the contain interface at Object +0x250
// (slots 0x70 0xD8 0xE0 0x4C) / multi-select through TheGameClient slot 0x40 /
// then the object context: status 0x13 / OCLUpdate module key / kind bit 150
// with 0x0028C15E / kind 0xDB / status 2 with the 0x0028BD17 interface slots
// 0x38 and 0x2C / garrison inventory (2) / OCL timer (10) / command (1) /
// beacon (5) / none (0). Identity: Zero Hour evaluateContextUI and the
// WorldBuilder twin at 0x00C2C270 share this call graph and order; the beacon
// test compares PlayerTemplate +0x17C with the template name at +0x64.
// The selection is Zero Hour's STLport std::list<Drawable *> (DrawableList).
// stlport
typedef bool Bool;
#include "subsystem_interface.h"
#include "ascii_string.h"
#include <list>

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
enum KindOfType { KINDOF_INVALID = -1 };
enum Relationship { REL_ENEMIES = 0, REL_NEUTRAL = 1, REL_ALLIES = 2 };

class Object;
class Team;
class Module;

class AsciiString;
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *nameString);
	NameKeyType nameToKey(const AsciiString &nameString);
};

class PlayerTemplate
{
public:
	char pad000[0x17C];
	AsciiString m_beaconTemplate;	// +0x17C
	const AsciiString &getBeaconTemplate() const { return m_beaconTemplate; }
};

class Player
{
public:
	Relationship getRelationship(const Team *that) const;

	char pad00[0x34];
	PlayerTemplate *m_playerTemplate;	// +0x34
	const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }
};

class PlayerList
{
public:
	char unknown00[0x10]; // +0x00
	Player *local; // +0x10
};

class ThingTemplate
{
public:
	__forceinline unsigned int isKindOf(int bit) const { return m_kindOf[bit >> 5] & (1u << (bit & 31)); }

	char pad000[0x64];
	AsciiString m_name;	// +0x64
	const AsciiString &getName() const { return m_name; }
	char pad068[0x108 - 0x68];
	unsigned int m_kindOf[7];	// +0x108
};

class ContainModuleInterface
{
public:
	virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
	virtual bool isGarrisonable() const;	// +0x10
	virtual void vf14(); virtual void vf18(); virtual void vf1C();
	virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
	virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C();
	virtual void vf40(); virtual void vf44(); virtual void vf48();
	virtual const Player *getApparentControllingPlayer(const Player *observingPlayer) const;	// +0x4C
	virtual void vf50(); virtual void vf54(); virtual void vf58(); virtual void vf5C();
	virtual void vf60(); virtual void vf64(); virtual void vf68(); virtual void vf6C();
	virtual int getContainMax() const;	// +0x70
	virtual void vf74(); virtual void vf78(); virtual void vf7C();
	virtual void vf80(); virtual void vf84(); virtual void vf88(); virtual void vf8C();
	virtual void vf90(); virtual void vf94(); virtual void vf98(); virtual void vf9C();
	virtual void vfA0(); virtual void vfA4(); virtual void vfA8(); virtual void vfAC();
	virtual void vfB0(); virtual void vfB4(); virtual void vfB8(); virtual void vfBC();
	virtual void vfC0(); virtual void vfC4(); virtual void vfC8(); virtual void vfCC();
	virtual void vfD0(); virtual void vfD4();
	virtual bool vfD8() const;	// +0xD8
	virtual void vfDC();
	virtual const Player *vfE0() const;	// +0xE0
};

class Rva0028BD17Interface
{
public:
	virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
	virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
	virtual void vf20(); virtual void vf24(); virtual void vf28();
	virtual bool vf2C() const;	// +0x2C
	virtual void vf30(); virtual void vf34();
	virtual bool vf38() const;	// +0x38
};

class Object
{
	friend class ControlBar;

public:
	bool testStatus(ObjectStatusTypes status) const;
	Player *getControllingPlayer() const;
	bool isKindOf(KindOfType kind) const;
	bool rva0028C15E(int a1, float *value, int a3, int a4);
	void *rva0028BD17() const;
	const AsciiString *rva00290E67() const;
	bool isLocallyControlled() const;
	const ThingTemplate *getTemplate() const { return m_template; }

protected:
	Module *findModule(NameKeyType key) const;

public:
	void *m_vtbl;	// +0x00
	const ThingTemplate *m_template;	// +0x04
	char pad008[0x250 - 0x08];
	ContainModuleInterface *m_contain;	// +0x250
	char pad254[0x304 - 0x254];
	Team *m_team;	// +0x304
};

struct Coord3D;
class Drawable
{
public:
	void setPosition(const Coord3D *loc);
	void setIndicatorColor(int color);
	char m_pad00[0xFC];
	Object *m_object; // +0xFC +0xFC
};

class Drawable;
class UnicodeString;
typedef std::list<Drawable *> DrawableList;
class InGameUI
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void __cdecl message(UnicodeString format, ...);	// +0x40
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void notify();	// +0x110
	virtual void v69();
	virtual int getSelectCount();	// +0x118
	virtual void v71();
	virtual void v72();
	virtual const DrawableList *getAllSelectedDrawables() const;	// +0x124
	virtual void v74();
	virtual void v75();
	virtual int getSoloNexusSelectedDrawableID();	// +0x130
	bool areSelectedObjectsControllable() const;	// 0x0029C752
	char m_pad04[0x11];
	unsigned char m_15;
	unsigned char m_16;
};

class GameClient
{
public:
	virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
	virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
	virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
	virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C();
	virtual Drawable *findDrawableByID(int id);	// +0x40
};

extern InGameUI *TheInGameUI;
extern GameClient *TheGameClient;
extern PlayerList *ThePlayerList;
extern NameKeyGenerator *TheNameKeyGenerator;

int Rva0043C99AGet();

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
class GameWindow;
class Image;
class CommandSet;
class INI;
class WindowVideoManager;
class AnimateWindowManager;
struct ICoord2D;
struct Rva0031DBFCElement;
class ControlBarSchemeManager;
class WindowLayout;
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

void ControlBar::rva0031D230()
{

	//
	// the UI has been "evaluated" and is now displaying the most current and correct
	// information to the player
	//
	m_UIDirty = false;

	// if our purchase science window is up, we will want to update it by repopulating it.
	if ((unsigned char)Rva0043C99AGet())
		showPurchaseScience();

	// sanity, nothing selected
	if (TheInGameUI->getSelectCount() == 0)
	{
		switchToContext(0, 0);
		return;
	}

	// get the list of drawable IDs from the in game UI
	const DrawableList *selectedDrawables = TheInGameUI->getAllSelectedDrawables();

	// sanity
	if (selectedDrawables->empty() == true)
	{
		switchToContext(0, 0);
		return;
	}

	//Make sure the selected objects are in fact, controllable! If not, then
	//we don't show any GUI commands for them!!!
	//This is used when we select enemy objects or objects on another team.
	//@todo we may want to show their portrait
	if (!TheInGameUI->areSelectedObjectsControllable())
	{
		//Also make sure the unit isn't a garrisonable neutral civ team building!
		Drawable *draw = selectedDrawables->front();

		//sanity
		if (!draw)
		{
			switchToContext(0, 0);
			return;
		}
		Object *obj = draw->m_object;
		if (!obj)
		{
			switchToContext(0, 0);
			return;
		}

		if (obj->getControllingPlayer()
			&& obj->getControllingPlayer()->getPlayerTemplate()
			&& obj->getControllingPlayer()->getPlayerTemplate()->getBeaconTemplate().compare(obj->getTemplate()->getName()) == 0)
		{
			switchToContext(5, draw);
		}
		else
		{
			//Check for a contain interface and a enemy relationship and reject that!
			ContainModuleInterface *contain = obj->m_contain;
			if (contain && contain->getContainMax() > 0)
			{
				switchToContext(4, draw);
				Player *localPlayer = ThePlayerList->local;
				if (contain && contain->vfD8() && contain->vfE0() == localPlayer)
				{
					switchToContext(3, draw);
					return;
				}
				const Player *otherPlayer = contain->getApparentControllingPlayer(localPlayer);
				if (!otherPlayer)
					otherPlayer = obj->getControllingPlayer();
				Player *player = ThePlayerList->local;
				bool playersKnown = player && otherPlayer;
				if (!playersKnown)
				{
					//Sanity.
					switchToContext(0, 0);
					return;
				}
			}
		}
	}

	//
	// when we have multiple things selected, we will only display the common commands
	// in the center command bar that can be displayed with multi-units selected
	//

	Drawable *drawToEvaluateFor = 0;
	bool multiSelect = false;
	if (TheInGameUI->getSelectCount() > 1)
	{
		// Attempt to isolate a Drawable here to evaluate
		// The need arises when selected is an AngryMob,
		// whose selection actually consists of varied units
		// but is represented in the UI as a single unit,
		// so we must isolate and evaluate only the Nexus
		drawToEvaluateFor = TheGameClient->findDrawableByID(TheInGameUI->getSoloNexusSelectedDrawableID());
		multiSelect = (drawToEvaluateFor == 0);
	}
	else // get the first and only drawble in the selection list
		drawToEvaluateFor = selectedDrawables->front();

	if (multiSelect)
	{
		switchToContext(7, 0);
	}
	else if (drawToEvaluateFor)// either we have exactly one drawable, or we have isolated one to evaluate for...
	{
		// get object
		Object *obj = drawToEvaluateFor->m_object;

		// we show no interface for objects being sold
		if (!obj || obj->testStatus((ObjectStatusTypes)0x13)
			|| !obj->getControllingPlayer() || !obj->getControllingPlayer()->getPlayerTemplate())
		{
			switchToContext(0, 0);
			return;
		}

		static const NameKeyType key_OCLUpdate = TheNameKeyGenerator->nameToKey("OCLUpdate");
		Module *update = obj->findModule(key_OCLUpdate);

		bool emptyAmount = false;
		if (obj->getTemplate()->isKindOf(150))
		{
			float amount = 0.0f;
			if (obj->rva0028C15E(3, &amount, 0, 1))
				emptyAmount = (amount == 0.0f);
		}

		bool contextSelected = false;
		bool special = false;
		if (emptyAmount || obj->isKindOf((KindOfType)0xDB))
		{
			special = true;
		}
		else if (obj->testStatus((ObjectStatusTypes)2))
		{
			Rva0028BD17Interface *iface = (Rva0028BD17Interface *)obj->rva0028BD17();
			special = iface && (iface->vf38() || iface->vf2C());
		}
		else
		{
			Rva0028BD17Interface *iface = (Rva0028BD17Interface *)obj->rva0028BD17();
			special = iface && iface->vf2C();
		}
		if (special)
		{
			switchToContext(6, drawToEvaluateFor);
			contextSelected = true;
		}

		// check for a regular switch to the appropriate context
		if (!contextSelected)
		{
			ContainModuleInterface *cmi = obj->m_contain;
			if (cmi && cmi->isGarrisonable() && ((const StringBase<char> *)obj->rva00290E67())->isEmpty())
			{
				//Kris: This is a convenient section to graft an inventory commandset for
				//garrisoned troops. However, we only want to use this if we DON'T have
				//a commandset defined. If we do, then trust that the commandset will
				//handle it!

				Player *localPlayer = ThePlayerList->local;

				// we cannot select objects that are controlled by our enemies
				Relationship relationship = localPlayer->getRelationship(obj->m_team);
				if (obj->isLocallyControlled() == true || relationship == REL_NEUTRAL)
					switchToContext(2, drawToEvaluateFor);
			}
			else if (update)
			{
				switchToContext(10, drawToEvaluateFor);
			}
			else if (((const StringBase<char> *)obj->rva00290E67())->isEmpty() == false)
			{
				switchToContext(1, drawToEvaluateFor);
			}
			else if (obj->getControllingPlayer()
				&& obj->getControllingPlayer()->getPlayerTemplate()
				&& obj->getControllingPlayer()->getPlayerTemplate()->getBeaconTemplate().compare(obj->getTemplate()->getName()) == 0)
			{
				switchToContext(5, drawToEvaluateFor);
			}
			else
				switchToContext(0, drawToEvaluateFor);
		}
	}
	else
	{
		switchToContext(0, 0);
	}
}
