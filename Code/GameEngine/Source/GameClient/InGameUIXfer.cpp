// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
//
// InGameUI's save-game snapshot: InGameUI::xfer (0x002A6AC2) and
// InGameUI::loadPostProcess (0x002A2184), the Snapshot slots 3 and 1 of the
// InGameUI tables, with the named timer helper addNamedTimer (0x002A5A50) the
// load calls and NamedTimerInfo's destructor (0x0029B8DD, deleting form
// 0x0029B8C1).
// Donors: ZH GameEngine/Source/GameClient/InGameUI.cpp (xfer,
// loadPostProcess, addNamedTimer) and BFME 1's InGameUIDoXfer.cpp
// (reference/open-bfme-1, retail 0x0044C250), whose control flow xfer keeps:
// the CRC tactical view float, the light-CRC exit, the named timers, the
// superweapon hidden flag and the per-player superweapon records.
// Target evidence: both Snapshot overrides receive Snapshot this (+0xC) and
// reach InGameUI members through it (addNamedTimer and findSWInfo through
// this - 0xC); the version pair is (1, 2); BFME 2 keeps twenty player maps at
// +0x630 and a superweapon record built by the 0x24-byte constructor 0x0029B74A
// (address-named, rowed in Rva0029B816Ctor.cpp); version 2 adds the placement
// icon drawables (+0x544, eight-byte entries, TheGlobalData +0xA94 of them)
// saved by DrawableID, which a load collects into the vector at +0x548 through
// the folded erase 0x00532803, reserve 0x002A1410 and push_back 0x002E01C6;
// loadPostProcess hides each one (Drawable::setDrawableHidden 0x00271601) and
// destroys it through TheGameClient (slot 16 finds it, slot 29 destroys it).
// addNamedTimer builds the 0x1C-byte NamedTimerInfo (vftable 0x007FD02C: name
// +4, text +8, display string +0xC, timestamp +0x10, color +0x14, countdown
// +0x18), removes any timer of that name (0x002A44D5, rowed address-named) and
// stores it through the AsciiString map subscript 0x002A57BD.
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

typedef int Color;

struct XferVersion
{
	unsigned char m_first;
	unsigned char m_version;
	unsigned char m_pad[2];
};

class Xfer
{
public:
	virtual void slot00();
	virtual bool isLoading();							// +0x04
	virtual bool isStoring();							// +0x08
	virtual bool isCRC();								// +0x0C
	virtual bool isLightCRC();							// +0x10
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void xferVersion( XferVersion *version );	// +0x28
#define SLOT(N) virtual void slot##N();
	SLOT(2C) SLOT(30) SLOT(34) SLOT(38) SLOT(3C) SLOT(40) SLOT(44) SLOT(48)
	SLOT(4C) SLOT(50) SLOT(54) SLOT(58) SLOT(5C) SLOT(60) SLOT(64)
#undef SLOT
	virtual void xferUnicodeString( UnicodeString *value );	// +0x68
	virtual void xferAsciiString( AsciiString *value );	// +0x6C
	virtual void xferReal( float *value );				// +0x70
	virtual void slot74();
	virtual void xferUnsignedInt( unsigned int *value );	// +0x78
	virtual void xferInt( int *value );					// +0x7C
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void xferBool( bool *value );				// +0x90
};

class XferException
{
public:
	XferException( int tag, const char *format, ... );
	XferException( const XferException &that );
	~XferException();

	char *text;
	int tag;
};

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *id );
void XferDrawableID( Xfer *xfer, int *id );

class Drawable
{
public:
	DrawableID getID() const;
	void setDrawableHidden( bool hidden );
};

class ClientFrameSubsystem
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
#undef SLOT
	virtual Drawable *findDrawableByID( ObjectID id );	// slot 16
#define SLOT(N) virtual void slot##N();
	SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24)
	SLOT(25) SLOT(26) SLOT(27) SLOT(28)
#undef SLOT
	virtual void destroyDrawable( Drawable *draw );		// slot 29
};
extern ClientFrameSubsystem *TheGameClient;

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
	SLOT(56) SLOT(57)
#undef SLOT
	virtual float slot58();	// +0xE8, BFME 1's CRC float
};
extern View *TheTacticalView;

class GlobalData
{
public:
	char m_opaque000[0xA94];
	int m_maxLineBuildObjects;				// +0xA94
};
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ((const GlobalData *)TheWritableGlobalData)

class GameFont;

class DisplayString
{
public:
	virtual void slot00() = 0;
	virtual void setText( UnicodeString text ) = 0;
	virtual UnicodeString getText() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void reset() = 0;
	virtual void setFont( GameFont *font ) = 0;
};

class DisplayStringManager
{
public:
#define SLOT(N) virtual void slot##N() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
#undef SLOT
	virtual DisplayString *newDisplayString() = 0;
	virtual void freeDisplayString( DisplayString *string ) = 0;
};
extern DisplayStringManager *TheDisplayStringManager;

class FontLibrary
{
public:
	GameFont *getFont( const AsciiString *name, float pointSize, bool bold );
};
extern FontLibrary *TheFontLibrary;

class GlobalLanguage
{
public:
	int adjustFontSize( int theFontSize );
};
extern GlobalLanguage *TheGlobalLanguageData;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
};

class SpecialPowerTemplate : public Overridable
{
public:
	const AsciiString &getName() const { return getFO()->m_name; }
private:
	const SpecialPowerTemplate *getFO() const { return (const SpecialPowerTemplate *)friend_getFinalOverride(); }
	char m_opaque000[0x10];
	AsciiString m_name;						// +0x10
};

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate( AsciiString name );
};
extern SpecialPowerStore *TheSpecialPowerStore;

class Player
{
public:
	int getPlayerColor() const { return m_color; }
private:
	char m_opaque000[0x280];
	int m_color;							// +0x280
};

class PlayerList
{
public:
	Player *getNthPlayer( int i );
};
extern PlayerList *ThePlayerList;

// The SuperweaponInfo ctor as rowed (Rva0029B816Ctor.cpp, address-named).
class Rva0029B816
{
public:
	Rva0029B816( int id, int timestamp, bool hiddenByScript, bool hiddenByScience, bool ready, const AsciiString &font, int pointSize, bool bold, int color, int powerTemplate );
private:
	char m_data[0x24];
};

class SuperweaponInfo
{
public:
	virtual ~SuperweaponInfo();
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_powerTemplate; }

	void *m_nameDisplayString;				// +0x04
	void *m_timeDisplayString;				// +0x08
	int m_color;							// +0x0C
	const SpecialPowerTemplate *m_powerTemplate;	// +0x10
	AsciiString m_powerName;				// +0x14
	ObjectID m_id;							// +0x18
	unsigned int m_timestamp;				// +0x1C
	bool m_hiddenByScript;					// +0x20
	bool m_hiddenByScience;					// +0x21
	bool m_ready;							// +0x22
	bool m_forceUpdateText;					// +0x23
};

class NamedTimerInfo
{
public:
	NamedTimerInfo() {}
	virtual ~NamedTimerInfo();

	AsciiString m_timerName;				// +0x04
	UnicodeString timerText;				// +0x08
	DisplayString *displayString;			// +0x0C
	unsigned int timestamp;					// +0x10
	Color color;							// +0x14
	bool isCountdown;						// +0x18
};

enum { MAX_PLAYER_COUNT = 20 };

typedef _STL::list<SuperweaponInfo *> SuperweaponList;
typedef _STL::map<AsciiString, SuperweaponList> SuperweaponMap;
typedef _STL::map<AsciiString, NamedTimerInfo *> NamedTimerMap;

// The map subscript 0x002A57BD is rowed under this AsciiString-keyed
// instantiation; its four-byte payload holds the timer pointer.
struct TreeHintPayload002A1D9D
{
	int m_val;
	TreeHintPayload002A1D9D() : m_val( 0 ) {}
	TreeHintPayload002A1D9D( const TreeHintPayload002A1D9D &o ) : m_val( o.m_val ) {}
};
typedef _STL::pair<const AsciiString, TreeHintPayload002A1D9D> TreeHintPair002A1D9D;
typedef _STL::map<AsciiString, TreeHintPayload002A1D9D, _STL::less<AsciiString>, _STL::allocator<TreeHintPair002A1D9D> > NamedTimerSubscriptMap;

// The folded four-byte vector reserve 0x002A1410 is rowed for ScienceType.
enum ScienceType { SCIENCE_INVALID = -1 };
typedef _STL::vector<ScienceType> FoldedReserveVector;

// InGameUI::removeNamedTimer, rowed address-named at 0x002A44D5.
class Rva002A44D5
{
public:
	void rva002A44D5( const AsciiString &timerName );
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	char m_opaque04[0xC - 0x4];
};

class InGameUIInterface10
{
public:
#define SLOT(N) virtual void slot##N() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04)
#undef SLOT
};

struct PlaceIconEntry
{
	Drawable *drawable;						// +0x00
	float m_04;								// +0x04
};

class InGameUI : public SubsystemInterface, public Snapshot, public InGameUIInterface10
{
public:
	virtual ~InGameUI();

	void addNamedTimer( const AsciiString &timerName, const UnicodeString &text, bool isCountdown );

protected:
	virtual void loadPostProcess();
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );

	SuperweaponInfo *findSWInfo( int playerIndex, const AsciiString &powerName, ObjectID id, const SpecialPowerTemplate *powerTemplate );

	bool m_superweaponHiddenByScript;		// +0x14
	char m_opaque015[0x544 - 0x15];
	PlaceIconEntry *m_placeIcon;			// +0x544
	_STL::vector<ObjectID> m_placeIconDrawableIDs;	// +0x548, filled by a load
	char m_opaque554[0x630 - 0x554];
	SuperweaponMap m_superweapons[MAX_PLAYER_COUNT];	// +0x630
	char m_opaque720[0x72C - 0x720];
	AsciiString m_superweaponNormalFont;	// +0x72C
	int m_superweaponNormalPointSize;		// +0x730
	bool m_superweaponNormalBold;			// +0x734
	char m_opaque735[0x750 - 0x735];
	NamedTimerMap m_namedTimers;			// +0x750
	char m_opaque75C[0x770 - 0x75C];
	int m_namedTimerLastFlashFrame;			// +0x770
	char m_opaque774[0x778 - 0x774];
	bool m_namedTimerUsedFlashColor;		// +0x778
	bool m_showNamedTimers;					// +0x779
	char m_opaque77A[0x77C - 0x77A];
	AsciiString m_namedTimerNormalFont;		// +0x77C
	int m_namedTimerNormalPointSize;		// +0x780
	bool m_namedTimerNormalBold;			// +0x784
	Color m_namedTimerNormalColor;			// +0x788
};

// ??1NamedTimerInfo@@UAE@XZ
NamedTimerInfo::~NamedTimerInfo()
{
}

// ?loadPostProcess@InGameUI@@MAEXXZ
void InGameUI::loadPostProcess()
{
	for( unsigned int i = 0; i < m_placeIconDrawableIDs.size(); ++i )
	{
		Drawable *draw = TheGameClient->findDrawableByID( m_placeIconDrawableIDs[ i ] );
		if( draw )
		{
			draw->setDrawableHidden( true );
			TheGameClient->destroyDrawable( draw );
		}
	}
	m_placeIconDrawableIDs.clear();
}

// ?addNamedTimer@InGameUI@@QAEXABVAsciiString@@ABVUnicodeString@@_N@Z
void InGameUI::addNamedTimer( const AsciiString &timerName, const UnicodeString &text, bool isCountdown )
{
	NamedTimerInfo *info = new NamedTimerInfo;
	info->m_timerName = timerName;
	info->color = m_namedTimerNormalColor;
	info->timerText = text;
	info->displayString = TheDisplayStringManager->newDisplayString();
	info->displayString->reset();
	info->displayString->setFont( TheFontLibrary->getFont( &m_namedTimerNormalFont,
		TheGlobalLanguageData->adjustFontSize( m_namedTimerNormalPointSize ),
		m_namedTimerNormalBold ) );
	info->displayString->setText( UnicodeString::TheEmptyString );
	info->timestamp = 0xffffffff;
	info->isCountdown = isCountdown;

	((Rva002A44D5 *)this)->rva002A44D5( timerName );
	(*(NamedTimerSubscriptMap *)&m_namedTimers)[ timerName ].m_val = (int)info;
}

// ?xfer@InGameUI@@MAEXPAVXfer@@@Z
void InGameUI::xfer( Xfer *xfer )
{
	if( xfer->isCRC() && TheTacticalView )
	{
		float value = TheTacticalView->slot58();
		xfer->xferReal( &value );
	}

	if( xfer->isLightCRC() )
		return;

	XferVersion version;
	version.m_first = 1;
	version.m_version = 2;
	xfer->xferVersion( &version );

	xfer->xferInt( &m_namedTimerLastFlashFrame );
	xfer->xferBool( &m_namedTimerUsedFlashColor );
	xfer->xferBool( &m_showNamedTimers );

	if( xfer->isStoring() )
	{
		int timerCount = m_namedTimers.size();
		xfer->xferInt( &timerCount );
		for( NamedTimerMap::iterator it = m_namedTimers.begin(); it != m_namedTimers.end(); ++it )
		{
			xfer->xferAsciiString( &it->second->m_timerName );
			xfer->xferUnicodeString( &it->second->timerText );
			xfer->xferBool( &it->second->isCountdown );
		}
	}
	else
	{
		int timerCount;
		xfer->xferInt( &timerCount );
		for( int timerIndex = 0; timerIndex < timerCount; ++timerIndex )
		{
			AsciiString timerName;
			UnicodeString timerText;
			bool isCountdown;
			xfer->xferAsciiString( &timerName );
			xfer->xferUnicodeString( &timerText );
			xfer->xferBool( &isCountdown );
			addNamedTimer( timerName, timerText, isCountdown );
		}
	}

	xfer->xferBool( &m_superweaponHiddenByScript );

	if( xfer->isStoring() )
	{
		for( int playerIndex = 0; playerIndex < MAX_PLAYER_COUNT; ++playerIndex )
		{
			for( SuperweaponMap::iterator mapIt = m_superweapons[ playerIndex ].begin(); mapIt != m_superweapons[ playerIndex ].end(); ++mapIt )
			{
				AsciiString powerName = mapIt->first;
				SuperweaponList &swList = mapIt->second;
				for( SuperweaponList::iterator listIt = swList.begin(); listIt != swList.end(); ++listIt )
				{
					SuperweaponInfo *swInfo = *listIt;
					xfer->xferInt( &playerIndex );
					AsciiString templateName = swInfo->getSpecialPowerTemplate()->getName();
					xfer->xferAsciiString( &templateName );
					xfer->xferAsciiString( &powerName );
					XferObjectID( xfer, &swInfo->m_id );
					xfer->xferUnsignedInt( &swInfo->m_timestamp );
					xfer->xferBool( &swInfo->m_hiddenByScript );
					xfer->xferBool( &swInfo->m_hiddenByScience );
					xfer->xferBool( &swInfo->m_ready );
				}
			}
		}
		int noMorePlayers = -1;
		xfer->xferInt( &noMorePlayers );
	}
	else
	{
		for( ;; )
		{
			int playerIndex;
			xfer->xferInt( &playerIndex );
			if( playerIndex == -1 )
				break;
			else if( playerIndex < 0 || playerIndex >= MAX_PLAYER_COUNT )
				throw XferException( 0, 0 );

			AsciiString templateName;
			xfer->xferAsciiString( &templateName );
			const SpecialPowerTemplate *powerTemplate = TheSpecialPowerStore->findSpecialPowerTemplate( templateName );
			if( powerTemplate == 0 )
				throw XferException( 0, 0 );

			AsciiString powerName;
			ObjectID id;
			unsigned int timestamp;
			bool hiddenByScript, hiddenByScience, ready;
			xfer->xferAsciiString( &powerName );
			XferObjectID( xfer, &id );
			xfer->xferUnsignedInt( &timestamp );
			xfer->xferBool( &hiddenByScript );
			xfer->xferBool( &hiddenByScience );
			xfer->xferBool( &ready );

			SuperweaponInfo *swInfo = findSWInfo( playerIndex, powerName, id, powerTemplate );
			if( swInfo == 0 )
			{
				const Player *player = ThePlayerList->getNthPlayer( playerIndex );
				swInfo = (SuperweaponInfo *)new Rva0029B816( id, timestamp, hiddenByScript, hiddenByScience, ready,
					m_superweaponNormalFont, m_superweaponNormalPointSize, m_superweaponNormalBold,
					player->getPlayerColor(), (int)powerTemplate );
				m_superweapons[ playerIndex ][ powerName ].push_back( swInfo );
			}
			else
			{
				swInfo->m_timestamp = timestamp;
				swInfo->m_hiddenByScript = hiddenByScript;
				swInfo->m_hiddenByScience = hiddenByScience;
				swInfo->m_ready = ready;
			}
			swInfo->m_forceUpdateText = true;
		}
	}

	if( version.m_version >= 2 )
	{
		if( xfer->isStoring() && !xfer->isCRC() )
		{
			int count = 0;
			for( int i = 0; i < TheGlobalData->m_maxLineBuildObjects; ++i )
			{
				if( m_placeIcon[ i ].drawable )
					++count;
			}
			xfer->xferInt( &count );
			for( int j = 0; j < TheGlobalData->m_maxLineBuildObjects; ++j )
			{
				if( m_placeIcon[ j ].drawable )
				{
					int drawableID = m_placeIcon[ j ].drawable->getID();
					XferDrawableID( xfer, &drawableID );
				}
			}
		}
		else if( xfer->isLoading() )
		{
			int count = 0;
			xfer->xferInt( &count );
			m_placeIconDrawableIDs.clear();
			((FoldedReserveVector *)&m_placeIconDrawableIDs)->reserve( count );
			ObjectID drawableID = (ObjectID)INVALID_DRAWABLE_ID;
			for( int i = 0; i < count; ++i )
			{
				XferDrawableID( xfer, (int *)&drawableID );
				m_placeIconDrawableIDs.push_back( drawableID );
			}
		}
	}
	else if( xfer->isLoading() )
	{
		m_placeIconDrawableIDs.clear();
	}
}
