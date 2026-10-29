// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/subsystem_bfme2
// stlport
// Target 0x0031E94C..0x0031EB7A, RET, 558 bytes.
// Ownership guide: BFME1 575ba2b047 ControlBarConstructor.cpp uses WeakPointer
// and OwnedPointer for its corresponding tail fields. Target stores establish
// +2A0/+2A4. +2A0 is a plain pointer cleared in member order: ControlBar::init hands it to
// winSetUserData, and a weak holder adds no cleanup. +2A4 is the holder
// ControlBar::reset and ControlBar::update release through clear (0x000AD6F4);
// the ctor nulls its pointer in member order (an inline default ctor). Its
// pointee type is unknown; the EH map stays exact (no member-dtor state).
// ??0ControlBar@@QAE@XZ @ 0x0031E94C 558B: ControlBar constructor.
// Evidence: pinned name; callers ?init@InGameUI@@UAEXXZ 0x0029E5D0 and
// ?recreateControlBar@InGameUI@@UAEXXZ 0x0029F890; vtable data 0x0080CC88;
// donor Zero Hour ControlBar::ControlBar plus BFME1 ControlBarConstructor.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <hash_map>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}
#include <vector>
#include "ascii_string.h"

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??1?$vector@UPlayerAITypeEntry@@V?$allocator@UPlayerAITypeEntry@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct PlayerAITypeEntry;
namespace _STL { template <> vector<PlayerAITypeEntry,allocator<PlayerAITypeEntry> >::~vector(); }
// Suppress this TU's non-retail copy of ??1?$_Vector_base@UPlayerAITypeEntry@@V?$allocator@UPlayerAITypeEntry@@@_STL@@@_STL@@QAE@X:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct PlayerAITypeEntry;
namespace _STL { template <> _Vector_base<PlayerAITypeEntry,allocator<PlayerAITypeEntry> >::~_Vector_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UPlayerAITypeEntry@@@_STL@@QBEXPAUPlayerAITypeEntry@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct PlayerAITypeEntry;
namespace _STL { template <> void allocator<PlayerAITypeEntry>::deallocate(PlayerAITypeEntry *,unsigned int) const; }

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}

typedef unsigned int UnsignedInt;
inline UnsignedInt GameMakeColor(int r, int g, int b, int a) { return (a << 24) | (r << 16) | (g << 8) | b; }

class GameWindow;

#include "ControlBarMemberTypes.h"  // the +0x30 map and the +0x2A4 holder

// The hash-map provider owns these helpers; its element view has eight bytes.
namespace _STL {
typedef hashtable<pair<const int, Rva0031DBFCElement>, int, hash<int>,
    _Select1st<pair<const int, Rva0031DBFCElement> >, equal_to<int>,
    allocator<pair<const int, Rva0031DBFCElement> > > ControlBarTable;
template <> void ControlBarTable::_M_initialize_buckets(size_t);
template <> void ControlBarTable::clear();
}

struct PlayerAITypeEntry
{
	AsciiString m_name;
	char m_unknown[12];
};

typedef bool Bool;
#include "subsystem_interface.h"

class WindowVideoManager : public SubsystemInterface { public: WindowVideoManager(); virtual void init(); virtual void reset(); virtual void update(); private: char m_opaque[0x24 - 0x0C]; };

class AnimateWindowManager : public SubsystemInterface { public: AnimateWindowManager(); virtual void init(); virtual void reset(); virtual void update(); private: char m_opaque[0x38 - 0x0C]; };

#include "../../../../../Libraries/Include/Lib/ICoord2D.h"

class ControlBarSchemeManager;
class Image;

class Rva0053B914
{
public:
	void rva0053B914();
};

class Rva0053ED1A
{
public:
	Rva0053ED1A();
private:
	char m_pad[0x5C];
};

class Rva0053ED1A_InitView
{
public:
	virtual void v00();
	virtual void v01();
};

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
class Player;
class CommandSet;
class INI;
class Object;
struct Coord3D;
class PlayerTemplate;
class Drawable;
class WindowLayout;
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

ControlBar::ControlBar() : m_showBuildToolTipLayout(false), m_commandWindowUserData(0)
{
	m_commandButtons = 0;
	m_controlBarSchemeManager = 0;
	m_isObserverCommandBar = false;
	m_observerLookAtPlayer = 0;
	m_01F4 = 0;
	m_01F0 = 0;
	m_01E4 = 0;
	m_01E0 = 0;
	m_01FC = 0;
	m_01F8 = 0;
	m_01EC = 0;
	m_01E8 = 0;
	m_animateDownWindow = 0;
	m_0204 = 0;
	for (int i = 0; i < 32; ++i)
		m_015C[i] = 0;
	UnsignedInt clock = GameMakeColor(0, 0, 0, 100);
	buildUpClockColor = clock;
	m_022C = clock;
	context = 0;
	m_defaultControlBarPosition.y = 0;
	m_defaultControlBarPosition.x = 0;
	m_genStarFlash = false;
	m_genStarOff = 0;
	m_genStarOn = 0;
	m_UIDirty = false;
	for (int i = 0; i < 9; ++i)
		m_contextParent[i] = 0;
	for (int i = 0; i < 32; ++i)
		m_commandWindows[i] = 0;
	for (int i = 0; i < 5; ++i)
	{
		m_specialPowerShortcutButtons[i] = 0;
		m_specialPowerShortcutButtonParents[i] = 0;
	}
	m_specialPowerShortcutParent = 0;
	m_specialPowerLayout = 0;
	m_rightHUDWindow = 0;
	m_rightHUDCameoWindow = 0;
	m_rightHUDUnitSelectParent = 0;
	m_communicatorButton = 0;
	selectedDrawable = 0;
	context = 0;
	m_rallyPointDrawableID = 0;
	m_displayedConstructPercent = -1.0f;
	m_displayedOCLTimerSeconds = 0;
	((Rva0053B914 *)this)->rva0053B914();
	int white = (int)GameMakeColor(255, 255, 255, 0);
	m_0080 = 0;
	m_videoManager = 0;
	m_animateWindowManager = 0;
	m_generalsScreenAnimate = 0;
	m_animateWindowManagerForGenShortcuts = 0;
	m_p0250 = 0;
	m_p0254 = 0;
	m_p0258 = 0;
	m_p025C = 0;
	m_p0260 = 0;
	m_p0264 = 0;
	m_p0270 = 0;
	m_p0274 = 0;
	m_genArrow = 0;
	m_sideSelectAnimateDown = false;
	rva0031AD14(white, white, white, white, white);
	m_0290 = false;
	m_0294 = 0;
	m_radarAttackGlowWindow = 0;
	m_rva0031C83D29C = 0;
	Rva0053ED1A *overlay = new Rva0053ED1A;
	m_commandWindowUserData = overlay;
	((Rva0053ED1A_InitView *)overlay)->v01();
	if (TheSubsystemList != 0)
		TheSubsystemList->rva001B5018(this);
}
