// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// InGameUI::reset (0x002A5EE6, vftable 0x7FD410 slot 9, SubsystemInterface's
// reset slot +0x24).
// Donors: ZH GameEngine/Source/GameClient/InGameUI.cpp InGameUI::reset and
// BFME 1's InGameUIReset.cpp (reference/open-bfme-1, retail 0x0044B3F0),
// whose order this body keeps: the subsystem resets, setScrolling, the
// selection helper and field clears, the +0x7F4 helper reset, the tactical
// view's default view, ResetInGameChat, stopMovie, setGUICommand,
// placeBuildAvailable, freeMessageResources, the superweapon and named timer
// teardown, removeMilitarySubtitle, the three clear helpers, resetIdleWorker,
// the move hints, the mode flags, the window layouts, the tooltip delay and
// UpdateDiplomacyBriefingText.
// Target evidence: the receivers are TheControlBar (0x00A01CFC), the global
// at 0x009FF028 and the banner UI init creates at 0x009FE32C, each through
// slot 9; BFME 2 adds the two singleton calls 0x0043CCC7 and 0x004E4317, the
// mouse tooltip reset (TheMouse 0x009FDCA0, 0x001EEBD5 with the empty
// UnicodeString and two null colors), the vector<ObjectID> at +0x548 cleared
// through the rowed erase 0x00532803, and the notification box at +0x9CC
// (0x004E7019). The superweapon infos go through ::delete with its null test
// (virtual dtor with flag 0, operator delete 0x0002FD60); the named timer
// infos are freed through TheDisplayStringManager (0x009FEAD8) slot 15 first.
// The per-name lists clear through the folded list clear 0x0023DAA5, the
// player maps through 0x002A47E1 and the timer map through 0x002A1B9D.
// Virtual slots on this: 24 removeMilitarySubtitle, 41 setScrolling,
// 47 setGUICommand, 55 placeBuildAvailable, 88 stopMovie (0x0029B4C4),
// 117 resetIdleWorker (0x0029D777).
#include <stdlib.h>
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include <list>
#include <map>
#include <vector>
#undef free
#include "ascii_string.h"
#include "unicode_string.h"
#include "../Common/GameLogicObjectLookupView.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

class SubsystemResetView
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08)
#undef SLOT
	virtual void reset();	// slot 9
};

class ControlBar : public SubsystemResetView {};
class RadarWindowOverrideSource : public SubsystemResetView {};
class BannerUI : public SubsystemResetView {};

extern ControlBar *TheControlBar;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
extern BannerUI *g_00DFE32C;

void Rva0043CCC7Set();
void rva004E4317();
void Rva004E84ABRun();	// BFME 1's ResetInGameChat
void Rva00433C75( const AsciiString &text, bool clear );	// BFME 1's UpdateDiplomacyBriefingText

struct _MouseSixteen { int v[4]; };

class Mouse
{
public:
	void rva001EEBD5( UnicodeString text, const _MouseSixteen *color, const _MouseSixteen *dropColor );
};
extern Mouse *TheMouse;

class View
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
	SLOT(56)
#undef SLOT
	virtual void setDefaultView( float pitch, float angle, float maxHeight );	// slot 57
};
extern View *TheTacticalView;

class DisplayString;

class DisplayStringManager
{
public:
#define SLOT(N) virtual void slot##N() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
#undef SLOT
	virtual DisplayString *newDisplayString() = 0;
	virtual void freeDisplayString( DisplayString *string ) = 0;	// slot 15
};
extern DisplayStringManager *TheDisplayStringManager;

// The helper at +0x7F4: slot 9 resets it, 0x004E5803 follows (the rowed
// forwarders 0x0029B17C and 0x0029B1A1 call the same two).
class Rva004E57E6
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08)
#undef SLOT
	virtual void reset();	// slot 9
	void rva004E5803();
};

class InGameNotificationBoxMovieClip
{
public:
	void rva004E7019();
};

// The InGameUI members reset calls by address (each rowed under its address).
class Rva0029C138 { public: void rva0029C138(); };
class Rva0029B380 { public: void rva0029B34B(); };	// freeMessageResources
class Rva0029D30A { public: void rva0029D30A(); };
class Rva0029D3FB { public: void rva0029D3FB(); };
class Rva0029D7CA { public: void rva0029D7CA(); };

class SuperweaponInfo
{
public:
	virtual ~SuperweaponInfo();
	__forceinline void deleteInstance() { ::delete this; }
};

class NamedTimerInfo
{
public:
	virtual ~NamedTimerInfo();
	__forceinline void deleteInstance() { ::delete this; }
	char m_opaque04[0xC - 0x4];
	DisplayString *displayString;			// +0x0C
};

class WindowLayout;

enum { MAX_PLAYER_COUNT = 20, MAX_MOVE_HINTS = 25 };

typedef _STL::list<SuperweaponInfo *> SuperweaponList;
typedef _STL::map<AsciiString, SuperweaponList> SuperweaponMap;
typedef _STL::map<AsciiString, NamedTimerInfo *> NamedTimerMap;

// Coord3D::zero, inline in ZH's BaseType.h; the canonical header lacks it.
inline void zeroCoord3D( Coord3D &pos )
{
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
}

struct MoveHint
{
	Coord3D pos;							// +0x00
	ObjectID sourceID;						// +0x0C
	bool flag;								// +0x10
};

class CommandButton;
class ThingTemplate;
class Drawable;

class InGameUI
{
public:
	virtual ~InGameUI();
#define SLOT(N) virtual void slot##N();
	SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08)
	virtual void reset();					// slot 9
	SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17)
	SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	virtual void removeMilitarySubtitle();	// slot 24
	SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31) SLOT(32)
	SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39) SLOT(40)
	virtual void setScrolling( bool isScrolling );	// slot 41
	SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46)
	virtual void setGUICommand( const CommandButton *command );	// slot 47
	SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54)
	virtual void placeBuildAvailable( const ThingTemplate *build, Drawable *buildDrawable );	// slot 55
	SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63)
	SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69) SLOT(70) SLOT(71)
	SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77) SLOT(78) SLOT(79)
	SLOT(80) SLOT(81) SLOT(82) SLOT(83) SLOT(84) SLOT(85) SLOT(86) SLOT(87)
	virtual void stopMovie();				// slot 88
	SLOT(89) SLOT(90) SLOT(91) SLOT(92) SLOT(93) SLOT(94) SLOT(95) SLOT(96)
	SLOT(97) SLOT(98) SLOT(99) SLOT(100) SLOT(101) SLOT(102) SLOT(103) SLOT(104)
	SLOT(105) SLOT(106) SLOT(107) SLOT(108) SLOT(109) SLOT(110) SLOT(111) SLOT(112)
	SLOT(113) SLOT(114) SLOT(115) SLOT(116)
	virtual void resetIdleWorker();			// slot 117
#undef SLOT

protected:
	char m_opaque004[0x14 - 0x4];
	bool m_superweaponHiddenByScript;		// +0x14
	bool m_engineInputEnabled;				// +0x15
	bool m_scriptInputEnabled;				// +0x16
	char m_opaque017[0x18 - 0x17];
	_STL::list<WindowLayout *> m_windowLayouts;	// +0x18
	char m_opaque01C[0x28 - 0x1C];
	bool m_isDragSelecting;					// +0x28
	char m_opaque029[0x40 - 0x29];
	MoveHint m_moveHint[MAX_MOVE_HINTS];	// +0x40
	char m_opaque234[0x548 - 0x234];
	_STL::vector<ObjectID> m_548;			// +0x548
	char m_opaque554[0x630 - 0x554];
	SuperweaponMap m_superweapons[MAX_PLAYER_COUNT];	// +0x630
	char m_opaque720[0x744 - 0x720];
	unsigned int m_superweaponLastFlashFrame;	// +0x744
	int m_superweaponFlashColor;			// +0x748
	bool m_superweaponUsedFlashColor;		// +0x74C
	char m_opaque74D[0x750 - 0x74D];
	NamedTimerMap m_namedTimers;			// +0x750
	char m_opaque75C[0x764 - 0x75C];
	float m_namedTimerLastFlashFrame;		// +0x764
	char m_opaque768[0x770 - 0x768];
	int m_770;								// +0x770
	char m_opaque774[0x778 - 0x774];
	bool m_namedTimerUsedFlashColor;		// +0x778
	bool m_showNamedTimers;					// +0x779
	char m_opaque77A[0x7EC - 0x77A];
	unsigned int m_tooltipsDisabledUntil;	// +0x7EC
	char m_opaque7F0[0x7F4 - 0x7F0];
	Rva004E57E6 *m_7F4;						// +0x7F4
	bool m_isScrolling;						// +0x7F8
	bool m_isSelecting;						// +0x7F9
	char m_opaque7FA[0x810 - 0x7FA];
	bool m_inputEnabled;					// +0x810, BFME 1's virtual setInputEnabled
	char m_opaque811[0x8B0 - 0x811];
	bool m_waypointMode;					// +0x8B0
	char m_opaque8B1[0x8B8 - 0x8B1];
	bool m_forceAttackMode;					// +0x8B8
	bool m_forceMoveToMode;					// +0x8B9
	bool m_attackMoveToMode;				// +0x8BA
	char m_opaque8BB[0x8C5 - 0x8BB];
	bool m_preferSelection;					// +0x8C5
	bool m_clientQuiet;						// +0x8C6
	char m_opaque8C7[0x914 - 0x8C7];
	int m_914[4];							// +0x914
	bool m_924;								// +0x924
	char m_opaque925[0x9CC - 0x925];
	InGameNotificationBoxMovieClip *m_notificationBox;	// +0x9CC
};

// ?reset@InGameUI@@UAEXXZ
void InGameUI::reset()
{
	m_inputEnabled = false;
	m_engineInputEnabled = true;
	m_scriptInputEnabled = true;

	TheControlBar->reset();
	theRadarWindowOverrideSource->reset();
	g_00DFE32C->reset();
	Rva0043CCC7Set();
	rva004E4317();

	setScrolling( false );
	TheMouse->rva001EEBD5( UnicodeString::TheEmptyString, 0, 0 );
	((Rva0029C138 *)this)->rva0029C138();
	m_924 = false;
	m_914[0] = 0;
	m_914[1] = 0;
	m_914[2] = 0;
	m_914[3] = 0;
	m_isSelecting = false;
	m_isDragSelecting = false;
	m_548.clear();
	m_7F4->reset();
	m_7F4->rva004E5803();

	TheTacticalView->setDefaultView( 0.0f, 0.0f, 1.0f );

	Rva004E84ABRun();

	// stop any movie currently playing
	stopMovie();

	// remove any pending GUI command
	setGUICommand( 0 );

	// remove any build available status
	placeBuildAvailable( 0, 0 );

	// free any message resources allocated
	((Rva0029B380 *)this)->rva0029B34B();

	int i;
	for( i = 0; i < MAX_PLAYER_COUNT; ++i )
	{
		for( SuperweaponMap::iterator mapIt = m_superweapons[i].begin(); mapIt != m_superweapons[i].end(); ++mapIt )
		{
			for( SuperweaponList::iterator listIt = mapIt->second.begin(); listIt != mapIt->second.end(); ++listIt )
			{
				SuperweaponInfo *info = *listIt;
				info->deleteInstance();
			}
			mapIt->second.clear();
		}
		m_superweapons[i].clear();
	}

	for( NamedTimerMap::iterator timerIt = m_namedTimers.begin(); timerIt != m_namedTimers.end(); ++timerIt )
	{
		NamedTimerInfo *info = timerIt->second;
		TheDisplayStringManager->freeDisplayString( info->displayString );
		info->deleteInstance();
	}
	m_namedTimers.clear();
	m_namedTimerLastFlashFrame = 0.0f;
	m_770 = 0;
	m_namedTimerUsedFlashColor = true; // so next one is false
	m_showNamedTimers = true;

	removeMilitarySubtitle();
	m_superweaponLastFlashFrame = 0;
	m_superweaponUsedFlashColor = true; // so next one is false
	m_superweaponHiddenByScript = false;

	((Rva0029D30A *)this)->rva0029D30A();
	((Rva0029D3FB *)this)->rva0029D3FB();
	((Rva0029D7CA *)this)->rva0029D7CA();
	resetIdleWorker();

	// clear hint lists
	for( i = 0; i < MAX_MOVE_HINTS; i++ )
	{
		zeroCoord3D( m_moveHint[ i ].pos );
		m_moveHint[ i ].sourceID = INVALID_OBJECT_ID;
		m_moveHint[ i ].flag = true;
	}

	m_waypointMode = false;
	m_forceAttackMode = false;
	m_forceMoveToMode = false;
	m_attackMoveToMode = false;
	m_preferSelection = false;
	m_clientQuiet = false;

	m_windowLayouts.clear();

	m_tooltipsDisabledUntil = 0;

	Rva00433C75( AsciiString::TheEmptyString, true );

	m_notificationBox->rva004E7019();
}
