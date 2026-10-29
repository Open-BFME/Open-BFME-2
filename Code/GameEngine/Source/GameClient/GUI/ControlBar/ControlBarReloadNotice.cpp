// cl: /O1 /EHsc /DNDEBUG /MD /Ireference/shims/subsystem_bfme2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// The "needs restart" byte at VA 0x00E01D0C and the bodies that touch it:
//
//   0x0031AB77  sets it (8 bytes).
//   0x0031E7F0  slot 4 of vftable 0x00C0CC88 (the class whose deleting
//               destructor is 0x0031EB7A), the INI reload notice: clear the
//               byte, and when the class's own slot 2 reports a reload put
//               "RIF: ControlBar ... reloaded" on screen through TheInGameUI (its
//               slot 16, cdecl), call 0x00409FCC on every value of the
//               AsciiString-keyed hash map at +0x30, walk the +0x2C
//               list (0x0031AC39), latch +0x28 and answer true; a byte set
//               meanwhile is passed out through the argument and cleared.
//
// Target evidence: the reload notice's codegen loads the vptr before it
// stores the byte, which MSVC 7.1 only does when the byte is a file-static
// it can prove `this` does not alias (an extern byte keeps the store first),
// so the byte is file-static here and its setter, which sits beside
// 0x0031AC39 in the same address range, lives in this unit too. The classes
// keep their address-derived names; the message and map meanings are
// inferred from the callees.

#include "ascii_string.h"
#include <list>
#include "unicode_string.h"
#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Imported inline: still inlined, never emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline void *&_STL::vector<void*>::operator[](size_t __n) { return *(this->_M_start + __n); }
}
// Suppress this TU's non-retail vector<void*> begin/end copies (family2-LK3 rows 6/9):
// the retail copies serve the link. Imported inline: still inlined, never emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline void **vector<void*>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline void **vector<void*>::end() { return this->_M_finish; }
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Imported inline: still inlined, never emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline size_t vector<void*>::size() const { return size_t(this->_M_finish - this->_M_start); }
}

// g_Va00E01D0C: VA 0x00E01D0C (.bss); retail initial byte 00.
static bool g_Va00E01D0C;

// WB 0x00C2D900 retains the receiver at entry; INICommandButton's native
// 0x001DAFEA loads TheControlBar before its call. The original method name
// remains unknown, but its thiscall ABI is established independently of the
// eight-byte optimized body, which does not need to read the receiver.
class INI;
class CommandSet;
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
class GameWindow;
class Image;
class Player;
class Object;
struct Coord3D;
class PlayerTemplate;
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

void ControlBar::rva0031AB77SetFlag()
{
	g_Va00E01D0C = 1;
}

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
extern InGameUI *TheInGameUI;	// VA 0x00DFEDF0

namespace rts
{
template <class T> struct hash
{
	unsigned int operator()(T value) const;
};
}

// The map's values: each gets refreshIfStale (0x00409FCC). The INI field
// table and button parser further down belong to the same class.
struct FieldParse;
class Overridable
{
public:
    virtual ~Overridable();
    const Overridable *getFinalOverride() const;
    Overridable *deleteOverrides();
    bool isOverride() const { return m_isOverride; }
    void markAsOverride() { m_isOverride = true; }
    void setNextOverride(Overridable *next) { m_nextOverride = next; }
    void clearStale() { m0C = 0; }
private:
    Overridable *m_nextOverride;
    bool m_isOverride;
    int m0C;
};
class CommandSet : public Overridable
{
public:
    CommandSet(const AsciiString &, int);
    virtual ~CommandSet();
    const AsciiString &getName() const { return m_name; }
    const class CommandButton *getCommandButton(int) const;
    void refreshIfStale();
    static const FieldParse m_commandSetFieldParseTable[];
    static void parseCommandButton(class INI *, void *, const class CommandButton **, int);
private:
    AsciiString m_name;
    void *m_buttons[32];
    int m_count;
    int m_mode98;
};

// Value view for the map below. Its iterator increment (0x00411084) and begin
// (0x00427195) are ICF-folded bodies whose addresses already carry other real
// names, so their pins keep this address-named value spelling; each value is
// a CommandSet, reached through this empty derived view at offset 0.
class Rva00409FFA : public CommandSet {};

// AsciiString-keyed: retail advances it with the iterator increment 0x00411084
// that the rts::hash<AsciiString> maps share (ICF); begin is the shared
// 0x00427195. The pointer value sits at node +8. The equality functor is not
// evidenced by these bytes.
typedef _STL::hash_map<AsciiString, Rva00409FFA *, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > Rva0031E7F0Map;

// ControlBar view (vftable 0x00C0CC88); polymorphic here so the derived
// class below shares its address.
class Rva0031AC39
{
public:
	virtual void v00();
	virtual void v01();
	virtual bool v02();	// 0x0031B53D in vftable 0x00C0CC88
};

class Rva0031DCF0 : public Rva0031AC39
{
public:
	bool rva0031E7F0(bool *needsRestart);
private:
	char m_unmodelled04[0x28 - 0x04];
	bool m_reloaded28;
	void *m_list2C;
	Rva0031E7F0Map m_map30;
};

bool Rva0031DCF0::rva0031E7F0(bool *needsRestart)
{
	bool result = false;
	g_Va00E01D0C = result;
	if (v02())
	{
		TheInGameUI->message(UnicodeString(L"RIF: ControlBar (CommandSet/CommandButton) reloaded. Changes effective immediately."));
		for (Rva0031E7F0Map::iterator it = m_map30.begin(); it != m_map30.end(); ++it)
		{
			(*it).second->refreshIfStale();
		}
		((ControlBar *)this)->postProcessCommands();
		m_reloaded28 = true;
		result = true;
	}
	if (g_Va00E01D0C)
	{
		*needsRestart = true;
		g_Va00E01D0C = false;
	}
	return result;
}

// WB 0x00C2D2B0 names ControlBar::parseCommandSetDefinition at ControlBar.cpp
// line 1525; native block registration 0x007AD120 binds CommandSet to this
// complete 0x0031EC03..0x0031ED00 body. BFME1 ba7ddda7 INICommandSet.cpp guides
// the find/create/override/duplicate behavior; native adds reload type 5.
// Keep the inline restart-byte store in the unit owning that file-static byte.
// The complete proposed TU retains exact 8B setter and 137B reload-notice bodies;
// the new parser is exact through its complete 253B retail boundary.
#include "Common/INIException.h"
class INI;
typedef void (*INIFieldParseProc)(INI *,void *,void *,const void *);
struct FieldParse {
    const char *token;
    INIFieldParseProc parse;
    const void *userData;
    int offset;
};
class INI {
public:
    const char *getNextToken(const char *separators=0);
    void initFromINI(void *,const FieldParse *);
    static void parseInt(INI *,void *,void *,const void *);
    char m_unknown00[8];
    int m_loadType;
};
class Rva0031D5F8 { public: void *rva0031D5F8(const AsciiString *); };
extern ControlBar *TheControlBar;
void ControlBar::parseCommandSetDefinition(INI *ini)
{
    AsciiString name;
    name=ini->getNextToken();
    CommandSet *set=(CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(&name);
    if(!set) {
        set=TheControlBar->rva0031E8D5(name,0);
        if(ini->m_loadType==2) set->markAsOverride();
    } else if(ini->m_loadType==2) {
        set=TheControlBar->rva0031B05B(set);
    } else if(ini->m_loadType==5) {
        if(set->isOverride()) g_Va00E01D0C=1;
        TheControlBar->forgetStaleCommandSet(name);
        set=TheControlBar->rva0031E8D5(name,0);
        set->clearStale();
    } else {
        throw INIException(3,"Duplicate commandset %s found!",name.str());
    }
    ini->initFromINI(set,CommandSet::m_commandSetFieldParseTable);
}

// Complete retail table at RVA 0x00838DD0: 32 command slots at object+0x14,
// followed by InitialVisible at +0x94 and the four-zero terminator. Callback
// 0x0040A092 already owns its address-derived name in the function ledger.

const FieldParse CommandSet::m_commandSetFieldParseTable[] =
{
    {"1",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)0,0x14},
    {"2",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)1,0x14},
    {"3",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)2,0x14},
    {"4",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)3,0x14},
    {"5",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)4,0x14},
    {"6",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)5,0x14},
    {"7",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)6,0x14},
    {"8",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)7,0x14},
    {"9",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)8,0x14},
    {"10",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)9,0x14},
    {"11",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)10,0x14},
    {"12",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)11,0x14},
    {"13",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)12,0x14},
    {"14",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)13,0x14},
    {"15",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)14,0x14},
    {"16",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)15,0x14},
    {"17",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)16,0x14},
    {"18",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)17,0x14},
    {"19",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)18,0x14},
    {"20",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)19,0x14},
    {"21",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)20,0x14},
    {"22",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)21,0x14},
    {"23",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)22,0x14},
    {"24",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)23,0x14},
    {"25",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)24,0x14},
    {"26",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)25,0x14},
    {"27",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)26,0x14},
    {"28",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)27,0x14},
    {"29",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)28,0x14},
    {"30",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)29,0x14},
    {"31",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)30,0x14},
    {"32",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)31,0x14},
    {"InitialVisible",INI::parseInt,0,0x94},
    {0,0,0,0}
};
