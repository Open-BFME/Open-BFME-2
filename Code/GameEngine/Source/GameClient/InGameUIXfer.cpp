// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
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
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <stdlib.h>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base
// wrapper (_List_iterator_base::operator!=, retail's copy is 0x006CFE40).
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
// Retail's map subscript (0x002A6A2D) builds the default list with T(), not
// through an out-of-line __default_constructed call.
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(T) T()
#include <map>
// Keep typed node comparisons local; no competing external tree-base copy.
namespace _STL {
template <class Value, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<Value, LeftTraits>& a,
                              const _Rb_tree_iterator<Value, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/Snapshot.h"
#include "../Common/GameLogicObjectLookupView.h"
// bfme link decl-only begin
namespace _STL { template <> ObjectID * vector<ObjectID, allocator<ObjectID> >::erase(ObjectID *, ObjectID *); }
// bfme link decl-only end

typedef int Color;

struct XferVersion
{
	unsigned char m_first;
	unsigned char m_version;
	unsigned char m_pad[2];
};

#include "../Common/System/XferVectorTypes.h"
#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/Common/XferException.h"

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *id );
void XferDrawableID( Xfer *xfer, int *id );

#include "../../Include/GameClient/Drawable.h"


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
// TheGameClient is only an alias of the owned global TheGameClient (ledger names column); this unit reads the owner through its own view type.
extern class GameClient *TheGameClient;
#define TheGameClient (*(ClientFrameSubsystem * *)&TheGameClient)

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

#include "../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ((const GlobalData *)TheWritableGlobalData)

class GameFont;

#include "../../Include/GameClient/DisplayString.h"

#include "../../Include/GameClient/DisplayStringManager.h"
extern DisplayStringManager *TheDisplayStringManager;

#include "../../Include/GameClient/FontLibrary.h"
extern FontLibrary *TheFontLibrary;

#include "../../Include/Common/GlobalLanguageClass.h"
extern GlobalLanguage *TheGlobalLanguageData;

#include "../../Include/Common/Overridable.h"
#include "../../Include/Common/SpecialPower.h"

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate( AsciiString name );
};
extern SpecialPowerStore *TheSpecialPowerStore;

#include "../../Include/Common/Player.h"

#include "../../Include/Common/PlayerList.h"
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
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void _Construct<pair<AsciiString const ,list<SuperweaponInfo *,allocator<SuperweaponInfo *> > >,pair<AsciiString const ,list<SuperweaponInfo *,allocator<SuperweaponInfo *> > > >(pair<AsciiString const ,list<SuperweaponInfo *,allocator<SuperweaponInfo *> > > *,pair<AsciiString const ,list<SuperweaponInfo *,allocator<SuperweaponInfo *> > > const &); }

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

// The superweapon map subscript 0x002A6A2D is rowed under this opaque
// four-byte list view (stlport_rb_tree_subscript_002a6a2d.cpp).
struct TreeHintOpaque002A484A : public _STL::list<int> {};
typedef _STL::pair<const AsciiString, TreeHintOpaque002A484A> TreeHintPair002A484A;
typedef _STL::map<AsciiString, TreeHintOpaque002A484A, _STL::less<AsciiString>, _STL::allocator<TreeHintPair002A484A> > SuperweaponSubscriptMap;
template <> TreeHintOpaque002A484A &SuperweaponSubscriptMap::operator[](const AsciiString &);

// The map subscript 0x002A57BD is rowed under this AsciiString-keyed
// instantiation; its four-byte payload holds the timer pointer.
struct TreeHintPayload002A1D9D
{
	int m_val;
	TreeHintPayload002A1D9D() : m_val( 0 ) {}
	TreeHintPayload002A1D9D( const TreeHintPayload002A1D9D &other ) : m_val( other.m_val ) {}
};
typedef _STL::pair<const AsciiString, TreeHintPayload002A1D9D> TreeHintPair002A1D9D;
typedef _STL::map<AsciiString, TreeHintPayload002A1D9D, _STL::less<AsciiString>, _STL::allocator<TreeHintPair002A1D9D> > NamedTimerSubscriptMap;

// Use the rowed ordinary insertion provider instead of emitting its
// differently configured inline tree copy in this snapshot unit.
typedef _STL::_Rb_tree<AsciiString, TreeHintPair002A1D9D, _STL::_Select1st<TreeHintPair002A1D9D>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair002A1D9D> > TimerInsertTree;
template <> _STL::pair<TimerInsertTree::iterator, bool> TimerInsertTree::insert_unique(const TreeHintPair002A1D9D &);

// The folded four-byte vector reserve 0x002A1410 is rowed for ScienceType.
enum ScienceType { SCIENCE_INVALID = -1 };
// Nothing here calls the science vector's deallocation helpers out of line;
// their unreferenced copies differed from the first ones in link order.
// Declared imported and force-inlined, they are not emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<ScienceType>::deallocate(ScienceType *__p, size_t) const
{ if (__p != 0) ::free((void *)__p); }
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<ScienceType *, ScienceType, allocator<ScienceType> >::deallocate(ScienceType *__p, size_t __n)
{ __stl_alloc_rebind(__STATIC_CAST(_Base&, *this),(ScienceType*)0).deallocate(__p, __n); }
template <> __declspec(dllimport) __forceinline
void vector<ScienceType, allocator<ScienceType> >::_M_clear() {
    _Destroy(this->_M_start, this->_M_finish);
    this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start);
}
}
typedef _STL::vector<ScienceType> FoldedReserveVector;

// InGameUI::removeNamedTimer, rowed address-named at 0x002A44D5.
class Rva002A44D5
{
public:
	void rva002A44D5( const AsciiString &timerName );
};

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

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
	if( xfer->IsCRC() && TheTacticalView )
	{
		float value = TheTacticalView->slot58();
		*xfer == value;
	}

	if( xfer->IsLightCRC() )
		return;

	XferVersion version;
	version.m_first = 1;
	version.m_version = 2;
	*xfer == reinterpret_cast<Xfer::Version &>(version);

	*xfer == m_namedTimerLastFlashFrame;
	*xfer == m_namedTimerUsedFlashColor;
	*xfer == m_showNamedTimers;

	if( xfer->IsStoring() )
	{
		int timerCount = m_namedTimers.size();
		*xfer == timerCount;
		for( NamedTimerMap::iterator it = m_namedTimers.begin(); it != m_namedTimers.end(); ++it )
		{
			*xfer == it->second->m_timerName;
			*xfer == it->second->timerText;
			*xfer == it->second->isCountdown;
		}
	}
	else
	{
		int timerCount;
		*xfer == timerCount;
		for( int timerIndex = 0; timerIndex < timerCount; ++timerIndex )
		{
			AsciiString timerName;
			UnicodeString timerText;
			bool isCountdown;
			*xfer == timerName;
			*xfer == timerText;
			*xfer == isCountdown;
			addNamedTimer( timerName, timerText, isCountdown );
		}
	}

	*xfer == m_superweaponHiddenByScript;

	if( xfer->IsStoring() )
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
					*xfer == playerIndex;
					AsciiString templateName = swInfo->getSpecialPowerTemplate()->getName();
					*xfer == templateName;
					*xfer == powerName;
					XferObjectID( xfer, &swInfo->m_id );
					*xfer == swInfo->m_timestamp;
					*xfer == swInfo->m_hiddenByScript;
					*xfer == swInfo->m_hiddenByScience;
					*xfer == swInfo->m_ready;
				}
			}
		}
		int noMorePlayers = -1;
		*xfer == noMorePlayers;
	}
	else
	{
		for( ;; )
		{
			int playerIndex;
			*xfer == playerIndex;
			if( playerIndex == -1 )
				break;
			else if( playerIndex < 0 || playerIndex >= MAX_PLAYER_COUNT )
				throw XferException( 0, 0 );

			AsciiString templateName;
			*xfer == templateName;
			const SpecialPowerTemplate *powerTemplate = TheSpecialPowerStore->findSpecialPowerTemplate( templateName );
			if( powerTemplate == 0 )
				throw XferException( 0, 0 );

			AsciiString powerName;
			ObjectID id;
			unsigned int timestamp;
			bool hiddenByScript, hiddenByScience, ready;
			*xfer == powerName;
			XferObjectID( xfer, &id );
			*xfer == timestamp;
			*xfer == hiddenByScript;
			*xfer == hiddenByScience;
			*xfer == ready;

			SuperweaponInfo *swInfo = findSWInfo( playerIndex, powerName, id, powerTemplate );
			if( swInfo == 0 )
			{
				const Player *player = ThePlayerList->getNthPlayer( playerIndex );
				swInfo = (SuperweaponInfo *)new Rva0029B816( id, timestamp, hiddenByScript, hiddenByScience, ready,
					m_superweaponNormalFont, m_superweaponNormalPointSize, m_superweaponNormalBold,
					player->getPlayerColor(), (int)powerTemplate );
				((SuperweaponList &)(*(SuperweaponSubscriptMap *)&m_superweapons[ playerIndex ])[ powerName ]).push_back( swInfo );
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
		if( xfer->IsStoring() && !xfer->IsCRC() )
		{
			int count = 0;
			for( int i = 0; i < TheGlobalData->m_maxLineBuildObjects; ++i )
			{
				if( m_placeIcon[ i ].drawable )
					++count;
			}
			*xfer == count;
			for( int j = 0; j < TheGlobalData->m_maxLineBuildObjects; ++j )
			{
				if( m_placeIcon[ j ].drawable )
				{
					int drawableID = m_placeIcon[ j ].drawable->getID();
					XferDrawableID( xfer, &drawableID );
				}
			}
		}
		else if( xfer->IsLoading() )
		{
			int count = 0;
			*xfer == count;
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
	else if( xfer->IsLoading() )
	{
		m_placeIconDrawableIDs.clear();
	}
}
