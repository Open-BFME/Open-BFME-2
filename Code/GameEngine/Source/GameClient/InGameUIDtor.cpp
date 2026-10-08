// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
//
// InGameUI::~InGameUI (0x002A5B30, vftable 0x7FD410 slot 0's destructor).
// Donor: ZH GameEngine/Source/GameClient/InGameUI.cpp InGameUI::~InGameUI,
// whose order the explicit body keeps: delete TheControlBar, then
// removeMilitarySubtitle, stopMovie, stopCameoMovie, placeBuildAvailable,
// setRadiusCursorNone, freeMessageResources, delete[] m_placeIcon,
// clearFloatingText, clearWorldAnimations and resetIdleWorker.
// Target evidence: BFME 2 also deletes the radar override source (0x009FF028)
// and the banner UI (0x009FE32C) after TheControlBar, each through ::delete's
// shape (virtual dtor with flag 0, operator delete 0x0002FD60) and nulled;
// deletes the +0x7F4 helper the same way after removeMilitarySubtitle; calls
// 0x0029D7CA after clearWorldAnimations and clears the +0x874 table
// (0x002A1D02) last. The direct calls name the virtual slots of 0x7FD410:
// 24 removeMilitarySubtitle (0x002A0C87), 55 placeBuildAvailable
// (0x0029BB8B), 81 setRadiusCursorNone (0x0029A64A), 88 stopMovie
// (0x0029B4C4), 91 stopCameoMovie (0x0029F4AB), 117 resetIdleWorker
// (0x0029D777).
// Layout: three bases, SubsystemInterface (0x00, out-of-line dtor 0x001B4E74),
// Snapshot (0x0C, inline dtor storing 0x00BBB554) and a five-slot interface
// at 0x10 (inline dtor storing the folded purecall table 0x00C078DC). The
// member destructors run in reverse from +0x9E8 down to +0x18, EH states 0x29
// to 2, the two DrawableLists' throw() destructors without state stores.
#include <stdlib.h>
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
	virtual ~SubsystemInterface();

private:
	char m_opaque04[0xC - 0x4];
};

class ControlBar : public SubsystemInterface {};
class RadarWindowOverrideSource : public SubsystemInterface {};
class BannerUI : public SubsystemInterface {};

extern ControlBar *TheControlBar;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
extern BannerUI *g_00DFE32C;

// The five-slot interface at +0x10: its table 0x00C078DC is all purecall.
class InGameUIInterface10
{
public:
	~InGameUIInterface10() {}
#define SLOT(N) virtual void slot##N() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04)
#undef SLOT
};

// The helper at +0x7F4 (reset through slot 9 by InGameUI::reset).
class Rva004E57E6
{
public:
	virtual ~Rva004E57E6();
};

// The InGameUI members the destructor calls by address (each rowed under its
// address): freeMessageResources, clearFloatingText, clearWorldAnimations.
class Rva0029B380 { public: void rva0029B34B(); };
class Rva0029D30A { public: void rva0029D30A(); };
class Rva0029D3FB { public: void rva0029D3FB(); };
class Rva0029D7CA { public: void rva0029D7CA(); };

// DrawableList's destructor 0x00239AF4 is throw(): no state store before it.
class Drawable;
class DrawableList
{
public:
	~DrawableList() throw();

private:
	void *m_node;
};

enum { MAX_PLAYER_COUNT = 20, MAX_MOVE_HINTS = 25, MAX_UI_MESSAGES = 6 };

struct MoveHint
{
	Coord3D pos;							// +0x00
	ObjectID sourceID;						// +0x0C
	bool flag;								// +0x10

	~MoveHint() {}
};

class DisplayString;
typedef int Color;

class SuperweaponInfo;
class NamedTimerInfo;
class WindowLayout;
class FloatingTextData;
class WorldAnimationData;
class Object;
class GameWindow;
class ThingTemplate;

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

// Holder at +0x8D4: four 12-byte chunks, then the camera marker list at
// +0x30. Its implicit destructor inlines here; the unwind funclet calls the
// out-of-line copy 0x002A4355.
struct Rva002A1B1DChunk
{
	int a;
	int b;
	int c;
};

class Rva002A1B1D
{
	Rva002A1B1DChunk m0;
	Rva002A1B1DChunk m1;
	Rva002A1B1DChunk m2;
	Rva002A1B1DChunk m3;
	_STL::list<CameraMarker> m_list;		// +0x30
};

// Record holder at +0x574 (destructor 0x0029E2A9, two AsciiStrings).
class Rva0029E2A9
{
public:
	~Rva0029E2A9();

private:
	char m_opaque[0x14];
};

// Owning pointers: +0x588 and +0x9CC reset inline, +0x58C through 0x004E7F7E.
class Rva0029B5E3
{
public:
	~Rva0029B5E3() { clear(); }
	void clear();

private:
	void *m_ptr;
};

class Rva004E7F29
{
public:
	~Rva004E7F29();

private:
	void *m_ptr;
};

class Rva0029B620
{
public:
	~Rva0029B620() { clear(); }
	void clear();

private:
	void *m_ptr;
};

// Tree at +0x590 (destructor 0x0029FAB7).
class Rva0029B63A
{
public:
	~Rva0029B63A();

private:
	char m_opaque[0x10];
};

// Bucket table at +0x874 (clear 0x002A1D02, destructor 0x002A4052).
class Rva002A1D02
{
public:
	~Rva002A1D02();
	void clear();

private:
	char m_opaque[0x18];
};

class RadiusDecal
{
public:
	~RadiusDecal();

private:
	char m_opaque[0x14];
};

// Per-player idle worker lists (destructor 0x001EB940).
class Rva001EB940
{
public:
	~Rva001EB940();

private:
	void *m_node;
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

	virtual ~InGameUI();
	virtual void removeMilitarySubtitle();	// slot 24
	virtual void placeBuildAvailable( const ThingTemplate *build, Drawable *buildDrawable );	// slot 55
	virtual void setRadiusCursorNone();		// slot 81
	virtual void stopMovie();				// slot 88
	virtual void stopCameoMovie();			// slot 91
	virtual void resetIdleWorker();			// slot 117

protected:
	char m_opaque014[0x18 - 0x14];
	_STL::list<WindowLayout *> m_windowLayouts;	// +0x18
	AsciiString m_currentlyPlayingMovie;	// +0x1C
	DrawableList m_selectedDrawables;		// +0x20
	DrawableList m_selectedLocalDrawables;	// +0x24
	char m_opaque028[0x40 - 0x28];
	MoveHint m_moveHint[MAX_MOVE_HINTS];	// +0x40
	char m_opaque234[0x544 - 0x234];
	Drawable **m_placeIcon;					// +0x544
	_STL::vector<ObjectID> m_548;			// +0x548
	char m_opaque554[0x574 - 0x554];
	Rva0029E2A9 m_574;						// +0x574
	Rva0029B5E3 m_588;						// +0x588
	Rva004E7F29 m_58C;						// +0x58C
	Rva0029B63A m_590;						// +0x590
	_STL::vector<int> m_5A0;				// +0x5A0
	char m_opaque5AC[0x5D0 - 0x5AC];
	UIMessage m_uiMessages[MAX_UI_MESSAGES];	// +0x5D0
	SuperweaponMap m_superweapons[MAX_PLAYER_COUNT];	// +0x630
	char m_opaque720[0x72C - 0x720];
	AsciiString m_superweaponNormalFont;	// +0x72C
	char m_opaque730[0x738 - 0x730];
	AsciiString m_superweaponReadyFont;		// +0x738
	char m_opaque73C[0x750 - 0x73C];
	NamedTimerMap m_namedTimers;			// +0x750
	char m_opaque75C[0x77C - 0x75C];
	AsciiString m_namedTimerNormalFont;		// +0x77C
	char m_opaque780[0x78C - 0x780];
	AsciiString m_namedTimerReadyFont;		// +0x78C
	char m_opaque790[0x79C - 0x790];
	AsciiString m_drawableCaptionFont;		// +0x79C
	char m_opaque7A0[0x7AC - 0x7A0];
	AsciiString m_7AC;						// +0x7AC
	char m_opaque7B0[0x7BC - 0x7B0];
	AsciiString m_7BC;						// +0x7BC
	char m_opaque7C0[0x7CC - 0x7C0];
	AsciiString m_7CC;						// +0x7CC
	char m_opaque7D0[0x7DC - 0x7D0];
	AsciiString m_7DC;						// +0x7DC
	char m_opaque7E0[0x7F4 - 0x7E0];
	Rva004E57E6 *m_7F4;						// +0x7F4
	char m_opaque7F8[0x82C - 0x7F8];
	AsciiString m_messageFont;				// +0x82C
	char m_opaque830[0x858 - 0x830];
	AsciiString m_militaryCaptionTitleFont;	// +0x858
	char m_opaque85C[0x864 - 0x85C];
	AsciiString m_militaryCaptionFont;		// +0x864
	char m_opaque868[0x874 - 0x868];
	Rva002A1D02 m_874;						// +0x874
	RadiusDecal m_curRadiusCursor;			// +0x88C
	_STL::list<FloatingTextData *> m_floatingTextList;	// +0x8A0
	char m_opaque8A4[0x8CC - 0x8A4];
	_STL::list<WorldAnimationData *> m_worldAnimationList;	// +0x8CC
	_STL::list<int> m_8D0;					// +0x8D0
	Rva002A1B1D m_8D4;						// +0x8D4
	char m_opaque908[0x910 - 0x908];
	_STL::list<int> m_910;					// +0x910
	char m_opaque914[0x928 - 0x914];
	Rva001EB940 m_idleWorkers[MAX_PLAYER_COUNT];	// +0x928
	GameWindow *m_idleWorkerWin;			// +0x978
	char m_opaque97C[0x9C4 - 0x97C];
	_STL::list<int> m_9C4;					// +0x9C4
	char m_opaque9C8[0x9CC - 0x9C8];
	Rva0029B620 m_notificationBox;			// +0x9CC
	AsciiString m_9D0;						// +0x9D0
	int m_9D4;
	AsciiString m_9D8;						// +0x9D8
	int m_9DC;
	AsciiString m_9E0;						// +0x9E0
	int m_9E4;
	AsciiString m_9E8;						// +0x9E8
	int m_9EC;
};

// ??1InGameUI@@UAE@XZ
InGameUI::~InGameUI()
{
	::delete TheControlBar;
	TheControlBar = 0;
	::delete theRadarWindowOverrideSource;
	theRadarWindowOverrideSource = 0;
	::delete g_00DFE32C;
	g_00DFE32C = 0;

	// free all the display strings if we're
	removeMilitarySubtitle();

	::delete m_7F4;
	m_7F4 = 0;

	stopMovie();
	stopCameoMovie();

	// remove any build available status
	placeBuildAvailable( 0, 0 );
	setRadiusCursorNone();

	// delete the message resources
	((Rva0029B380 *)this)->rva0029B34B();

	// delete the array for the drawbles
	delete [] m_placeIcon;
	m_placeIcon = 0;

	// clear floating text
	((Rva0029D30A *)this)->rva0029D30A();

	// clear world animations
	((Rva0029D3FB *)this)->rva0029D3FB();
	((Rva0029D7CA *)this)->rva0029D7CA();
	resetIdleWorker();
	m_874.clear();
}
