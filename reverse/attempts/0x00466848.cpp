// ?changeTeamOnAllConnectedCaves@CaveContain@@QAEXPAVTeam@@_N@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00466848 (148B) CaveContain::changeTeamOnAllConnectedCaves and
// 0x004668DC (155B) CaveContain::onRemoving.
// Bodies: Zero Hour's CaveContain.cpp as ported for BFME 1
// (reference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Contain/
// CaveContainChangeTeamOnAllConnectedCaves.cpp and CaveContainOnRemoving.cpp).
// The class view is the one of the matched recalcApparentControllingPlayer
// 0x00466977 (CaveContainRecalcApparentControllingPlayer.cpp), which calls
// changeTeamOnAllConnectedCaves directly. BFME 2 target evidence: cave index
// +0x104 and original team +0x108; the tunnel tracker's id list at +8;
// behavior modules Object+0x244 (interface at module+0x0C, getCaveInterface
// slot 0x40); Object team +0x304; Object::defect 0x00298C76 (placeholder pin);
// onRemoving entered through the ContainModuleInterface at +0x20, with
// clearDisabled(HELD), the 0x0028DCC4 world registration, setPosition at the
// cave, setDrawableHidden(false), doUnloadSound (primary slot 0x58),
// getContainCount(false) and the garrisoned condition bit (word bit 10 at
// Object+0x10C, notifier 0x0028AE6D) cleared on the removed object.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef Int Color;

enum TimeOfDay
{
	TIME_OF_DAY_NIGHT = 4
};

class Team;
class Player;
class Object;
struct Coord3D;
class CaveInterface;
enum DisabledType
{
	DISABLED_HELD = 3
};
class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[20];
};
class BehaviorModuleInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual CaveInterface *getCaveInterface();
};
class BehaviorModule
{
public:
	unsigned char m_pad00[0x0C];
	BehaviorModuleInterface m_interface;
};
class TunnelTracker
{
public:
	const _STL::list<int> *getContainerList() const { return &m_containerList; }
	unsigned char m_pad00[0x08];
	_STL::list<int> m_containerList;
};
class CaveSystem
{
public:
	TunnelTracker *getTunnelTrackerForCaveIndex( UnsignedInt index );
};
extern CaveSystem *TheCaveSystem;
class GameLogic
{
public:
	Object *findObjectByID( int id );
};
extern GameLogic *TheGameLogic;
class Drawable;
class Object;

struct BfmeContainedNode
{
	BfmeContainedNode *m_next;
	BfmeContainedNode *m_prev;
	Object *m_object;
};

struct BfmeContainedList
{
	BfmeContainedNode *m_head;
};

// BFME2 returns this two-word range through a hidden result pointer at
// ContainModuleInterface slot +0x118; the BFME1 donor returns a list pointer.
struct BfmeContainedRange
{
	BfmeContainedRange();
	void *m_unmodelled_00;
	BfmeContainedList *m_list;
};

class Player
{
public:
	Color getPlayerColor() const
	{
		return m_playerColor;
	}

	Color getPlayerNightColor() const
	{
		return m_playerNightColor;
	}

	Team *getDefaultTeam() const
	{
		return m_defaultTeam;
	}

private:
	unsigned char m_pad0[0x280];
	Color m_playerColor;
	Color m_playerNightColor;
	unsigned char m_pad1[0x2EC - 0x288];
	Team *m_defaultTeam;
};

class Thing
{
public:
	void setPosition( const Coord3D *pos );
};

class Object : public Thing
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	Drawable *getDrawable() const;
	Player *getControllingPlayer() const;
	Bool clearDisabled( DisabledType type );
	void rva0028DCC4();
	void rva00298C76( Team *team, UnsignedInt detectionTime );
	const Coord3D *getPosition() const { return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0x38); }
	BehaviorModule **getBehaviorModules() const { return *reinterpret_cast<BehaviorModule **const *>(reinterpret_cast<const char *>(this) + 0x244); }
	Rva0010CBits &getConditionBits() { return *reinterpret_cast<Rva0010CBits *>(reinterpret_cast<char *>(this) + 0x10C); }
	void rva0028AE6D();

	Team *getTeam() const
	{
		return *reinterpret_cast<Team *const *>(reinterpret_cast<const char *>(this) + 0x304);
	}
};

class Drawable
{
public:
	void setIndicatorColor(Color color);
	void setDrawableHidden(bool hidden);
};

class PlayerList
{
public:
	Player *getLocalPlayer() const
	{
		return m_localPlayer;
	}

private:
	unsigned char m_pad[0x10];
	Player *m_localPlayer;
};

extern PlayerList *ThePlayerList;

// EA's GlobalData (Common/GlobalData.h) is only forward declared here; retail
// reads its TimeOfDay at +0x218 through this pointer.  The local view below
// supplies that one field, and TheWritableGlobalData must be spelled
// GlobalData * (class, not struct) so the mangled name matches the one
// definition in GameEngine/Source/Common/GlobalData.cpp.
class GlobalData;

class CaveContainGlobalDataView
{
private:
	unsigned char m_pad[0x134];

public:
	TimeOfDay m_timeOfDay;
};

extern GlobalData *TheWritableGlobalData;

static inline CaveContainGlobalDataView *caveContainGlobalData()
{
	return reinterpret_cast<CaveContainGlobalDataView *>(TheWritableGlobalData);
}

// Retail CaveContain uses OpenContain's genuine multiple-inheritance layout.
// The primary module base contains the module-data and owning-Object pointers;
// the ContainModuleInterface base begins at complete-object +0x20.
class OpenContainPrimaryBase
{
public:
	virtual void primarySlot00() = 0;
	virtual void primarySlot01() = 0;
	virtual void primarySlot02() = 0;
	virtual void primarySlot03() = 0;
	virtual void primarySlot04() = 0;
	virtual void primarySlot05() = 0;
	virtual void primarySlot06() = 0;
	virtual void primarySlot07() = 0;
	virtual void primarySlot08() = 0;
	virtual void primarySlot09() = 0;
	virtual void primarySlot0A() = 0;
	virtual void primarySlot0B() = 0;
	virtual void primarySlot0C() = 0;
	virtual void primarySlot0D() = 0;
	virtual void primarySlot0E() = 0;
	virtual void primarySlot0F() = 0;
	virtual void primarySlot10() = 0;
	virtual void primarySlot11() = 0;
	virtual void primarySlot12() = 0;
	virtual void primarySlot13() = 0;
	virtual void primarySlot14() = 0;
	virtual void primarySlot15() = 0;
	virtual void doUnloadSound() = 0;

protected:
	Object *getObject() const
	{
		return m_object;
	}

private:
	UnsignedInt m_moduleData;
	Object *m_object;
};

class OpenContainBehaviorInterface
{
public:
	virtual void behaviorAnchor() = 0;
};

class OpenContainUpdateInterface
{
public:
	virtual void updateAnchor() = 0;

private:
	UnsignedInt m_nextCallFrameAndPhase;
	Int m_indexInLogic;
	UnsignedInt m_unreconstructed1C;
};

class ContainModuleInterface
{
public:
	virtual void pad00() = 0;
	virtual void pad04() = 0;
	virtual void pad08() = 0;
	virtual void pad0C() = 0;
	virtual void pad10() = 0;
	virtual void pad14() = 0;
	virtual void pad18() = 0;
	virtual void pad1C() = 0;
	virtual void pad20() = 0;
	virtual void pad24() = 0;
	virtual void pad28() = 0;
	virtual void pad2C() = 0;
	virtual void pad30() = 0;
	virtual void pad34() = 0;
	virtual void pad38() = 0;
	virtual void targetPad3C() = 0;
	virtual void targetPad40() = 0;
	virtual void targetPad44() = 0;
	virtual void targetPad48() = 0;
	virtual const Player *getApparentControllingPlayer(const Player *) const = 0;
	virtual void recalcApparentControllingPlayer() = 0;
	virtual void targetPad54() = 0;
	virtual void onContaining(Object *, Bool) = 0;
	virtual void onRemoving(Object *) = 0;
	virtual void pad50() = 0;
	virtual void pad54() = 0;
	virtual void pad58() = 0;
	virtual void pad5C() = 0;
	virtual void pad60() = 0;
	virtual void pad64() = 0;
	virtual void pad68() = 0;
	virtual void pad6C() = 0;
	virtual void pad70() = 0;
	virtual void pad74() = 0;
	virtual void pad78() = 0;
	virtual void pad7C() = 0;
	virtual void pad80() = 0;
	virtual void pad84() = 0;
	virtual void pad88() = 0;
	virtual void pad8C() = 0;
	virtual void pad90() = 0;
	virtual void pad94() = 0;
	virtual void pad98() = 0;
	virtual void pad9C() = 0;
	virtual void padA0() = 0;
	virtual void padA4() = 0;
	virtual void padA8() = 0;
	virtual void padAC() = 0;
	virtual void padB0() = 0;
	virtual void padB4() = 0;
	virtual void padB8() = 0;
	virtual void padBC() = 0;
	virtual void padC0() = 0;
	virtual void padC4() = 0;
	virtual void padC8() = 0;
	virtual void padCC() = 0;
	virtual void padD0() = 0;
	virtual void padD4() = 0;
	virtual void padD8() = 0;
	virtual void padDC() = 0;
	virtual void padE0() = 0;
	virtual void padE4() = 0;
	virtual void padE8() = 0;
	virtual void padEC() = 0;
	virtual void padF0() = 0;
	virtual void padF4() = 0;
	virtual void padF8() = 0;
	virtual void padFC() = 0;
	virtual void targetPad110() = 0;
	virtual UnsignedInt getContainCount(Bool countRiders) const = 0;
	virtual BfmeContainedRange getContainedItemsList() const = 0;
};

template <int Offset>
class OpenContainAuxiliaryInterface
{
public:
	virtual void auxiliaryAnchor() = 0;
};

class __declspec(novtable) OpenContain
	: public OpenContainPrimaryBase,
	  public OpenContainBehaviorInterface,
	  public OpenContainUpdateInterface,
	  public ContainModuleInterface,
	  public OpenContainAuxiliaryInterface<0x24>,
	  public OpenContainAuxiliaryInterface<0x28>,
	  public OpenContainAuxiliaryInterface<0x2C>,
	  public OpenContainAuxiliaryInterface<0x30>,
	  public OpenContainAuxiliaryInterface<0x34>
{
public:
	virtual void doUnloadSound();
	virtual void onRemoving(Object *obj);
	virtual UnsignedInt getContainCount(Bool countRiders) const;

protected:
	using OpenContainPrimaryBase::getObject;

private:
	unsigned char m_openContainData[0x9C];
};

typedef char OpenContainSizeMustBeD4[(sizeof(OpenContain) == 0xD4) ? 1 : -1];

class CaveInterface
{
public:
	virtual void tryToSetCaveIndex(Int newIndex) = 0;
	virtual void setOriginalTeam(Team *oldTeam) = 0;
};

class __declspec(novtable) CaveContain : public OpenContain, public CaveInterface
{
public:
	virtual void onRemoving(Object *obj);
	virtual UnsignedInt getContainCount(Bool countRiders) const;
	void changeTeamOnAllConnectedCaves(Team *newTeam, Bool setOriginalTeams);

private:
	unsigned char m_bfme2CaveFieldPrefix[0x28];
	Bool m_needToRunOnBuildComplete;
	unsigned char m_fieldAlignment[3];
	Int m_caveIndex;
	Team *m_originalTeam;
};

typedef char CaveContainSizeMustBe10C[(sizeof(CaveContain) == 0x10C) ? 1 : -1];

// ?recalcApparentControllingPlayer@CaveContain@@UAEXXZ
static CaveInterface *findCave( Object *obj )
{
	for( BehaviorModule **i = obj->getBehaviorModules(); *i; ++i )
	{
		CaveInterface *c = (*i)->m_interface.getCaveInterface();
		if( c != 0 )
			return c;
	}
	return 0;
}

void CaveContain::changeTeamOnAllConnectedCaves( Team *newTeam, Bool setOriginalTeams )
{
	TunnelTracker *myTracker = TheCaveSystem->getTunnelTrackerForCaveIndex( m_caveIndex );
	const _STL::list<int> *allCaves = myTracker->getContainerList();
	for( _STL::list<int>::const_iterator iter = allCaves->begin(); iter != allCaves->end(); iter++ )
	{
		// For each ID, look it up and change its team.  We all get captured together.
		Object *currentCave = TheGameLogic->findObjectByID( *iter );
		if( currentCave )
		{
			CaveInterface *caveModule = findCave( currentCave );
			if( caveModule == 0 )
				continue;
			caveModule->setOriginalTeam( !setOriginalTeams ? 0 : currentCave->getTeam() );

			currentCave->rva00298C76( newTeam, 0 );
		}
	}
}

void CaveContain::onRemoving( Object *obj )
{
	OpenContain::onRemoving( obj );

	// object is no longer held inside a garrisoned building
	obj->clearDisabled( DISABLED_HELD );

	/// place the object in the world at position of the container m_object
	obj->rva0028DCC4();
	obj->setPosition( getObject()->getPosition() );
	if( obj->getDrawable() )
		obj->getDrawable()->setDrawableHidden( false );

	doUnloadSound();

	if( getContainCount( false ) == 0 )
	{
		if( obj->getTeam() != 0 )
		{
			changeTeamOnAllConnectedCaves( m_originalTeam, false );
			m_originalTeam = 0;
		}

		// change the state back from garrisoned
		Rva0010CBits &bits = obj->getConditionBits();
		if( bits.test( 10 ) )
		{
			bits.clear( 10 );
			obj->rva0028AE6D();
		}
	}
}
