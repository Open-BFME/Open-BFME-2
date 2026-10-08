// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
//
// InGameUI::InGameUI (0x002A61A9) and the +0x8D4 holder's constructor
// (0x002A42D8).
// Donor: ZH GameEngine/Source/GameClient/InGameUI.cpp InGameUI::InGameUI and
// BFME 1's InGameUIConstructor.cpp (reference/open-bfme-1), whose order the
// body keeps: the input and selection flags, the movie name, the military
// subtitle, the message, military caption and tooltip settings, the move
// hints, the build progress slots, the pending GUI command, the placement
// icons and anchors, the video fields, the UI messages, the replay window, the
// superweapon and named timer displays, the floating text, the drawable
// caption and the mode flags.
// Target evidence: BFME 2 builds the +0x7F4 helper (new 0x34, 0x004E5A24) and
// initializes it through slot 1 right after the subtitle; the placement icon
// array holds 8-byte entries built by 0x00054EB0 through the vector
// constructor; the military caption fonts, the four "Albertus MT" caption
// groups, the 16 bytes at +0x5B4, the floating text timeout (the logic frame
// rate global 0x009BA4E8 over three), the selection helper 0x0029C138, the
// mouse tooltip reset (TheMouse 0x009FDCA0, 0x001EEBD5 with the empty
// UnicodeString and two null colors) and the resource entry list at
// 0x009FEDFC (0x004E551E) close the body. The members' constructors run
// first, EH states 3 to 0x2B, the notification box at +0x9CC built by
// new 0x54 (0x004E6C34) in the initializer list.
// Layout: InGameUIDtor.cpp's view, with the scalar members this body stores
// to filled in (the +0x874 table is 0x14 bytes, the radius decal 0x10, the
// +0x8D4 holder 0x3C and the idle worker lists STLport list<Object *>).
#include <stdlib.h>
#include <string.h>
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include <list>
#include <map>
#include <vector>
#undef free
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/Snapshot.h"
#include "../Common/GameLogicObjectLookupView.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	char m_opaque04[0xC - 0x4];
};

// The five-slot interface at +0x10: its table 0x00C078DC is all purecall.
class InGameUIInterface10
{
public:
	InGameUIInterface10() {}
	~InGameUIInterface10() {}
#define SLOT(N) virtual void slot##N() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04)
#undef SLOT
};

// The helper at +0x7F4: slot 1 initializes it.
class Rva004E57E6
{
public:
	virtual ~Rva004E57E6();
	virtual void init();
};

class Rva004E5A24 : public Rva004E57E6
{
public:
	Rva004E5A24();

private:
	char m_opaque04[0x34 - 0x4];
};

// The notification box the +0x9CC owner holds.
class Rva004E6C34
{
public:
	Rva004E6C34();

private:
	char m_opaque[0x54];
};

// The selection helper reset also calls by address.
class Rva0029C138 { public: void rva0029C138(); };

struct _MouseSixteen { int v[4]; };

class Mouse
{
public:
	void rva001EEBD5( UnicodeString text, const _MouseSixteen *color, const _MouseSixteen *dropColor );
};
extern Mouse *TheMouse;

class ResourceEntryCollector
{
public:
	void rva004E551E();

private:
	char m_opaque[0xC];
};
extern ResourceEntryCollector g_Va00DFEDFC;

struct GlobalData
{
	char m_opaque000[0xA94];
	int m_maxLineBuildObjects;				// +0xA94
};
extern GlobalData *TheGlobalData;

extern int g_009BA4E8;	// logic frames per second

class GameWindow;
extern GameWindow *m_replayWindow;

// The selected drawable lists: STLport list<Drawable *>, whose base
// constructor (0x00239BB0) takes its nodes from a pool of their own.
class Drawable;

typedef _STL::list<Drawable *> DrawableList;

enum { MAX_PLAYER_COUNT = 20, MAX_MOVE_HINTS = 25, MAX_BUILD_PROGRESS = 64, MAX_UI_MESSAGES = 6 };

// Coord3D::zero, inline in ZH's BaseType.h; the canonical header lacks it.
inline void zeroCoord3D( Coord3D &pos )
{
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
}

struct MoveHint
{
	MoveHint() {}
	~MoveHint() {}

	Coord3D pos;							// +0x00
	ObjectID sourceID;						// +0x0C
	bool flag;								// +0x10
};

class ThingTemplate;
class GameWindow;

struct BuildProgress
{
	const ThingTemplate *m_thingTemplate;	// +0x00
	float m_percentComplete;				// +0x04
	GameWindow *m_control;					// +0x08
};

// Placement icon entry (constructor 0x00054EB0).
struct PlaceIconEntry
{
	PlaceIconEntry() : drawable( 0 ), m_04( 0.0f ) {}

	Drawable *drawable;
	float m_04;
};

class DisplayString;
typedef int Color;

class SuperweaponInfo;
class NamedTimerInfo;
class WindowLayout;
class FloatingTextData;
class WorldAnimationData;
class Object;

typedef _STL::list<SuperweaponInfo *> SuperweaponList;
typedef _STL::map<AsciiString, SuperweaponList> SuperweaponMap;
typedef _STL::map<AsciiString, NamedTimerInfo *> NamedTimerMap;

// Camera marker list element (list base destructor 0x002A1BEB).
struct CameraMarker
{
	~CameraMarker();

	CameraMarker *m_next;
	AsciiString m_name;
};

struct Rva002A1B1DChunk
{
	Rva002A1B1DChunk() : a( 0 ), b( 0.0f ), c( 0.0f ) {}

	int a;
	float b;
	float c;
};

// Holder at +0x8D4: four 12-byte chunks, then the camera marker list at
// +0x30 and two ids.
class Rva002A1B1D
{
public:
	Rva002A1B1D();

private:
	Rva002A1B1DChunk m0;
	Rva002A1B1DChunk m1;
	Rva002A1B1DChunk m2;
	Rva002A1B1DChunk m3;
	_STL::list<CameraMarker> m_list;		// +0x30
	int m_34;
	int m_38;
};

// ??0Rva002A1B1D@@QAE@XZ
Rva002A1B1D::Rva002A1B1D()
{
	m_list.clear();
	m_34 = m_38 = -1;
}

// Record holder at +0x574 (constructor 0x004E63FC, destructor 0x0029E2A9).
class Rva0029E2A9
{
public:
	Rva0029E2A9();
	~Rva0029E2A9();

private:
	char m_opaque[0x14];
};

// Owning pointers: +0x588 and +0x9CC reset inline, +0x58C through 0x004E7F7E.
class Rva0029B5E3
{
public:
	Rva0029B5E3() : m_ptr( 0 ) {}
	~Rva0029B5E3() { clear(); }
	void clear();

private:
	void *m_ptr;
};

class Rva004E7F29
{
public:
	Rva004E7F29();
	~Rva004E7F29();

private:
	void *m_ptr;
};

class Rva0029B620
{
public:
	Rva0029B620( Rva004E6C34 *box ) : m_ptr( box ) {}
	~Rva0029B620() { clear(); }
	void clear();

private:
	Rva004E6C34 *m_ptr;
};

// Tree at +0x590 (constructor 0x00413727, destructor 0x0029FAB7).
class Rva0029B63A
{
public:
	Rva0029B63A();
	~Rva0029B63A();

private:
	char m_opaque[0x10];
};

// Bucket table at +0x874 (constructor 0x002A5876, destructor 0x002A4052).
class Rva002A1D02
{
public:
	Rva002A1D02();
	~Rva002A1D02();

private:
	char m_opaque[0x14];
};

class RadiusDecal
{
public:
	RadiusDecal();
	~RadiusDecal();

private:
	char m_opaque[0x10];
};

struct Rva0035C9A6Entry
{
	int a;
	int b;
};

class InGameUI : public SubsystemInterface, public Snapshot, public InGameUIInterface10
{
public:
	struct UIMessage
	{
		UnicodeString fullText;				// +0x00
		DisplayString *displayString;		// +0x04
		unsigned int timestamp;				// +0x08
		Color color;						// +0x0C
	};

	InGameUI();
	virtual ~InGameUI();

protected:
	bool m_superweaponHiddenByScript;		// +0x14
	bool m_engineInputEnabled;				// +0x15
	bool m_scriptInputEnabled;				// +0x16
	_STL::list<WindowLayout *> m_windowLayouts;	// +0x18
	AsciiString m_currentlyPlayingMovie;	// +0x1C
	DrawableList m_selectedDrawables;		// +0x20
	DrawableList m_selectedLocalDrawables;	// +0x24
	bool m_isDragSelecting;					// +0x28
	char m_opaque029[0x3C - 0x29];
	bool m_displayedMaxWarning;				// +0x3C
	MoveHint m_moveHint[MAX_MOVE_HINTS];	// +0x40
	int m_nextMoveHint;						// +0x234
	void *m_pendingGUICommand;				// +0x238
	BuildProgress m_buildProgress[MAX_BUILD_PROGRESS];	// +0x23C
	const ThingTemplate *m_pendingPlaceType;	// +0x53C
	ObjectID m_pendingPlaceSourceObjectID;	// +0x540
	PlaceIconEntry *m_placeIcon;			// +0x544
	_STL::vector<ObjectID> m_548;			// +0x548
	bool m_placeAnchorInProgress;			// +0x554
	int m_placeAnchorStartX;				// +0x558
	int m_placeAnchorStartY;				// +0x55C
	int m_placeAnchorEndX;					// +0x560
	int m_placeAnchorEndY;					// +0x564
	int m_selectCount;						// +0x568
	int m_maxSelectCount;					// +0x56C
	unsigned int m_frameSelectionChanged;	// +0x570
	Rva0029E2A9 m_574;						// +0x574
	Rva0029B5E3 m_588;						// +0x588
	Rva004E7F29 m_58C;						// +0x58C
	Rva0029B63A m_590;						// +0x590
	_STL::vector<int> m_5A0;				// +0x5A0
	int m_5AC;								// +0x5AC
	bool m_5B0;								// +0x5B0
	int m_5B4[4];							// +0x5B4
	void *m_videoStream;					// +0x5C4
	void *m_videoBuffer;					// +0x5C8
	void *m_5CC;							// +0x5CC
	UIMessage m_uiMessages[MAX_UI_MESSAGES];	// +0x5D0
	SuperweaponMap m_superweapons[MAX_PLAYER_COUNT];	// +0x630
	float m_superweaponPositionX;			// +0x720
	float m_superweaponPositionY;			// +0x724
	float m_superweaponFlashDuration;		// +0x728
	AsciiString m_superweaponNormalFont;	// +0x72C
	int m_superweaponNormalPointSize;		// +0x730
	bool m_superweaponNormalBold;			// +0x734
	AsciiString m_superweaponReadyFont;		// +0x738
	int m_superweaponReadyPointSize;		// +0x73C
	bool m_superweaponReadyBold;			// +0x740
	unsigned int m_superweaponLastFlashFrame;	// +0x744
	Color m_superweaponFlashColor;			// +0x748
	bool m_superweaponUsedFlashColor;		// +0x74C
	NamedTimerMap m_namedTimers;			// +0x750
	float m_namedTimerPositionX;			// +0x75C
	float m_namedTimerPositionY;			// +0x760
	float m_764;							// +0x764
	bool m_768;								// +0x768
	float m_namedTimerFlashDuration;		// +0x76C
	unsigned int m_namedTimerLastFlashFrame;	// +0x770
	Color m_namedTimerFlashColor;			// +0x774
	bool m_namedTimerUsedFlashColor;		// +0x778
	bool m_showNamedTimers;					// +0x779
	AsciiString m_namedTimerNormalFont;		// +0x77C
	int m_namedTimerNormalPointSize;		// +0x780
	bool m_namedTimerNormalBold;			// +0x784
	Color m_namedTimerNormalColor;			// +0x788
	AsciiString m_namedTimerReadyFont;		// +0x78C
	int m_namedTimerReadyPointSize;			// +0x790
	bool m_namedTimerReadyBold;				// +0x794
	Color m_namedTimerReadyColor;			// +0x798
	AsciiString m_drawableCaptionFont;		// +0x79C
	int m_drawableCaptionPointSize;			// +0x7A0
	bool m_drawableCaptionBold;				// +0x7A4
	Color m_drawableCaptionColor;			// +0x7A8
	AsciiString m_7AC;						// +0x7AC
	int m_7B0;
	bool m_7B4;
	Color m_7B8;
	AsciiString m_7BC;						// +0x7BC
	int m_7C0;
	bool m_7C4;
	Color m_7C8;
	AsciiString m_7CC;						// +0x7CC
	int m_7D0;
	bool m_7D4;
	Color m_7D8;
	AsciiString m_7DC;						// +0x7DC
	int m_7E0;
	bool m_7E4;
	Color m_7E8;
	unsigned int m_tooltipsDisabledUntil;	// +0x7EC
	void *m_militarySubtitle;				// +0x7F0
	Rva004E57E6 *m_7F4;						// +0x7F4
	bool m_isScrolling;						// +0x7F8
	bool m_isSelecting;						// +0x7F9
	int m_mouseMode;						// +0x7FC
	int m_mouseModeCursor;					// +0x800
	int m_mousedOverDrawableID;				// +0x804
	char m_opaque808[0x810 - 0x808];
	bool m_inputEnabled;					// +0x810
	bool m_messagesOn;						// +0x811
	int m_814;								// +0x814
	Color m_messageColor2;					// +0x818
	int m_messagePositionX;					// +0x81C
	int m_messagePositionY;					// +0x820
	int m_824;								// +0x824
	int m_828;								// +0x828
	AsciiString m_messageFont;				// +0x82C
	int m_messagePointSize;					// +0x830
	bool m_messageBold;						// +0x834
	int m_messageDelayMS;					// +0x838
	int m_militaryCaptionColorRed;			// +0x83C
	int m_militaryCaptionColorGreen;		// +0x840
	int m_militaryCaptionColorBlue;			// +0x844
	int m_militaryCaptionColorAlpha;		// +0x848
	float m_militaryCaptionPositionX;		// +0x84C
	float m_militaryCaptionPositionY;		// +0x850
	bool m_854;								// +0x854
	AsciiString m_militaryCaptionTitleFont;	// +0x858
	int m_militaryCaptionTitlePointSize;	// +0x85C
	bool m_militaryCaptionTitleBold;		// +0x860
	AsciiString m_militaryCaptionFont;		// +0x864
	int m_militaryCaptionPointSize;			// +0x868
	bool m_militaryCaptionBold;				// +0x86C
	int m_militaryCaptionDelayMS;			// +0x870
	Rva002A1D02 m_874;						// +0x874
	int m_curRcType;						// +0x888
	RadiusDecal m_curRadiusCursor;			// +0x88C
	int m_89C;								// +0x89C
	_STL::list<FloatingTextData *> m_floatingTextList;	// +0x8A0
	float m_floatingTextTimeOut;			// +0x8A4
	float m_floatingTextMoveUpSpeed;		// +0x8A8
	float m_floatingTextMoveVanishRate;		// +0x8AC
	bool m_waypointMode;					// +0x8B0
	char m_opaque8B1[0x8B8 - 0x8B1];
	bool m_forceAttackMode;					// +0x8B8
	bool m_forceMoveToMode;					// +0x8B9
	bool m_attackMoveToMode;				// +0x8BA
	bool m_8BB[4];							// +0x8BB
	bool m_8BF[4];							// +0x8BF
	bool m_drawRMBScrollAnchor;				// +0x8C3
	bool m_moveRMBScrollAnchor;				// +0x8C4
	bool m_preferSelection;					// +0x8C5
	bool m_clientQuiet;						// +0x8C6
	int m_8C8;								// +0x8C8
	_STL::list<WorldAnimationData *> m_worldAnimationList;	// +0x8CC
	_STL::list<int> m_8D0;					// +0x8D0
	Rva002A1B1D m_8D4;						// +0x8D4
	_STL::list<Rva0035C9A6Entry> m_910;		// +0x910
	int m_914[4];							// +0x914
	bool m_924;								// +0x924
	_STL::list<Object *> m_idleWorkers[MAX_PLAYER_COUNT];	// +0x928
	GameWindow *m_idleWorkerWin;			// +0x978
	int m_currentIdleWorkerDisplay;			// +0x97C
	int m_980;								// +0x980
	int m_984;								// +0x984
	char m_opaque988[0x98C - 0x988];
	bool m_98C;								// +0x98C
	bool m_98D;								// +0x98D
	char m_opaque98E[0x9B0 - 0x98E];
	int m_9B0;								// +0x9B0
	bool m_9B4;								// +0x9B4
	char m_opaque9B5[0x9C4 - 0x9B5];
	_STL::list<int> m_9C4;					// +0x9C4
	int m_9C8;								// +0x9C8
	Rva0029B620 m_notificationBox;			// +0x9CC
	AsciiString m_9D0;						// +0x9D0
	float m_9D4;
	AsciiString m_9D8;						// +0x9D8
	float m_9DC;
	AsciiString m_9E0;						// +0x9E0
	float m_9E4;
	AsciiString m_9E8;						// +0x9E8
	float m_9EC;
};

// ??0InGameUI@@QAE@XZ
InGameUI::InGameUI() :
	m_5AC( 0 ),
	m_5B0( false ),
	m_98C( false ),
	m_98D( false ),
	m_9B0( -1 ),
	m_9B4( false ),
	m_9C8( 0 ),
	m_notificationBox( new Rva004E6C34 ),
	m_9D4( 0.0f ),
	m_9DC( 0.0f ),
	m_9E4( 0.0f ),
	m_9EC( 0.0f )
{
	int i;

	m_engineInputEnabled = true;
	m_scriptInputEnabled = true;
	m_isDragSelecting = false;
	m_nextMoveHint = 0;
	m_selectCount = 0;
	m_frameSelectionChanged = 0;
	m_maxSelectCount = -1;
	m_isScrolling = false;
	m_isSelecting = false;
	m_mouseMode = 0;
	m_mouseModeCursor = 2;
	m_mousedOverDrawableID = 0;

	m_currentlyPlayingMovie.clear();
	m_militarySubtitle = 0;

	m_7F4 = new Rva004E5A24;
	m_7F4->init();

	m_814 = -1;
	m_waypointMode = false;
	m_preferSelection = false;
	m_clientQuiet = false;

	m_messageColor2 = 0xffb4b4b4;
	m_messagePositionX = 10;
	m_messagePositionY = 10;
	m_824 = 10;
	m_828 = 10;
	m_messageFont = "Arial";
	m_messagePointSize = 10;
	m_messageBold = false;
	m_messageDelayMS = 5000;

	m_militaryCaptionColorRed = 200;
	m_militaryCaptionColorGreen = 200;
	m_militaryCaptionColorBlue = 30;
	m_militaryCaptionColorAlpha = 255;
	m_militaryCaptionPositionX = 0.5f;
	m_militaryCaptionPositionY = 0.01f;
	m_854 = true;

	m_militaryCaptionTitleFont = "Courier";
	m_militaryCaptionTitlePointSize = 12;
	m_militaryCaptionTitleBold = true;

	m_militaryCaptionFont = "Courier";
	m_militaryCaptionPointSize = 12;
	m_militaryCaptionBold = false;
	m_militaryCaptionDelayMS = 750;

	m_tooltipsDisabledUntil = 0;

	memset( m_5B4, 0, sizeof( m_5B4 ) );

	// init hint lists
	for( i = 0; i < MAX_MOVE_HINTS; i++ )
	{
		zeroCoord3D( m_moveHint[ i ].pos );
		m_moveHint[ i ].sourceID = INVALID_OBJECT_ID;
		m_moveHint[ i ].flag = false;
	}

	for( i = 0; i < MAX_BUILD_PROGRESS; i++ )
	{
		m_buildProgress[ i ].m_thingTemplate = 0;
		m_buildProgress[ i ].m_percentComplete = 0.0f;
		m_buildProgress[ i ].m_control = 0;
	}

	m_pendingGUICommand = 0;

	// allocate an array for the placement icons
	m_placeIcon = new PlaceIconEntry[ TheGlobalData->m_maxLineBuildObjects ];
	for( i = 0; i < TheGlobalData->m_maxLineBuildObjects; i++ )
		m_placeIcon[ i ].drawable = 0;
	m_pendingPlaceType = 0;
	m_pendingPlaceSourceObjectID = INVALID_OBJECT_ID;
	m_placeAnchorStartX = m_placeAnchorStartY = 0;
	m_placeAnchorEndX = m_placeAnchorEndY = 0;
	m_placeAnchorInProgress = false;

	m_videoStream = 0;
	m_5CC = 0;

	// message info
	for( i = 0; i < MAX_UI_MESSAGES; i++ )
	{
		m_uiMessages[ i ].fullText.clear();
		m_uiMessages[ i ].displayString = 0;
		m_uiMessages[ i ].timestamp = 0;
		m_uiMessages[ i ].color = 0;
	}

	m_replayWindow = 0;
	m_messagesOn = true;

	m_superweaponPositionX = 0.7f;
	m_superweaponPositionY = 0.7f;
	m_superweaponFlashDuration = 1.0f;
	m_superweaponNormalFont = "Arial";
	m_superweaponNormalPointSize = 10;
	m_superweaponNormalBold = false;
	m_superweaponReadyFont = "Arial";
	m_superweaponReadyPointSize = 10;
	m_superweaponReadyBold = false;

	m_superweaponFlashColor = 0xffffffff;
	m_superweaponLastFlashFrame = 0;
	m_superweaponUsedFlashColor = true; // so next one is false
	m_superweaponHiddenByScript = false;

	m_namedTimerPositionX = 0.5f;
	m_namedTimerPositionY = 0.01f;
	m_764 = 0.0f;
	m_768 = false;
	m_namedTimerFlashDuration = 1.0f;
	m_namedTimerNormalFont = "Arial";
	m_namedTimerNormalPointSize = 10;
	m_namedTimerNormalBold = false;
	m_namedTimerReadyFont = "Arial";
	m_namedTimerReadyPointSize = 10;
	m_namedTimerReadyBold = false;

	m_namedTimerNormalColor = 0xffffff00;
	m_namedTimerReadyColor = 0xffff00ff;
	m_namedTimerFlashColor = 0xff00ffff;
	m_namedTimerLastFlashFrame = 0;
	m_namedTimerUsedFlashColor = true; // so next one is false
	m_showNamedTimers = true;

	m_floatingTextTimeOut = g_009BA4E8 / 3;
	m_floatingTextMoveUpSpeed = 1.0f;
	m_floatingTextMoveVanishRate = 0.1f;

	m_drawableCaptionFont = "Arial";
	m_drawableCaptionPointSize = 10;
	m_drawableCaptionBold = false;
	m_drawableCaptionColor = 0xffffffff;

	m_7AC = "Albertus MT";
	m_7B0 = 16;
	m_7B4 = false;
	m_7B8 = 0xffffffff;
	m_7BC = "Albertus MT";
	m_7C0 = 14;
	m_7C4 = false;
	m_7C8 = 0xffffcc00;
	m_7CC = "Albertus MT";
	m_7D0 = 14;
	m_7D4 = false;
	m_7D8 = 0xffffcc00;
	m_7DC = "Albertus MT";
	m_7E0 = 14;
	m_7E4 = false;
	m_7E8 = 0xffffcc00;

	m_drawRMBScrollAnchor = false;
	m_moveRMBScrollAnchor = false;
	m_displayedMaxWarning = false;

	m_idleWorkerWin = 0;
	m_currentIdleWorkerDisplay = -1;

	m_waypointMode = false;
	m_forceAttackMode = false;
	m_forceMoveToMode = false;
	m_attackMoveToMode = false;

	m_curRcType = 0;
	m_89C = 0;
	m_980 = 0;

	((Rva0029C138 *)this)->rva0029C138();
	m_924 = false;
	m_914[0] = 0;
	m_914[1] = 0;
	m_914[2] = 0;
	m_914[3] = 0;
	m_8BF[ 0 ] = false;
	m_8BF[ 1 ] = false;
	m_8BF[ 2 ] = false;
	m_8BF[ 3 ] = false;
	m_8BB[ 0 ] = false;
	m_8BB[ 1 ] = false;
	m_8BB[ 2 ] = false;
	m_8BB[ 3 ] = false;
	m_8C8 = 0;
	m_984 = 0;

	if( TheMouse )
		TheMouse->rva001EEBD5( UnicodeString::TheEmptyString, 0, 0 );

	g_Va00DFEDFC.rva004E551E();
}
