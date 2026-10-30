// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// CaveContain::recalcApparentControllingPlayer, target 0x00466977, 217 bytes.
// Target identity: CaveContainCtor.cpp installs the secondary table at
// 0x00843A70; slot +0x50 points to this body, and onContaining at 0x004664BB
// dispatches the same slot on that interface. The body reads the original
// team at secondary +0xE8, the owner Object at secondary -0x18, Object team at
// +0x304, count/list slots +0x114/+0x118, and day/night colors at Player
// +0x280/+0x284. It calls the direct Object::getDrawable target at 0x005508E2
// and Drawable::setIndicatorColor at 0x006741DE. The local CaveContain layout
// follows the target constructor and these accesses.
// Donor provenance: Open-BFME-1 revision 6583b3c1ff21db4a561285717028fdafc780b7db,
// CaveContainRecalcApparentControllingPlayer.cpp. It supports the routine's
// behavior; BFME2 vtable, offsets, list ABI, globals, and calls are established
// from target evidence. The target callee at 0x00466848 is still address-named
// because its donor-supported semantic name has not been independently proven.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "../../../../Include/GameLogic/ContainmentListView.h"

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
class Drawable;
enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2
};
enum DisabledType
{
	DISABLED_HELD = 3
};
class Object;
class DamageInfo;
class BfmeTab1026;
class BodyModuleInterfaceView;
class BehaviorModule;
class Rva0010CBits;
class Drawable;
struct Coord3D;
enum NameKeyType;

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
	// LINK: same-body helpers under TU-unique names (identical inlined
	// bytes). This TU's copies lose (first-copy); both calls below inline
	// them but still emit loser COMDATs. Rebinding there emits only unique
	// (trivially kept) copies. No flags touched, no layout claim.
	Color bfme_player_color() const
	{
		return m_playerColor;
	}
	Color bfme_player_night_color() const
	{
		return m_playerNightColor;
	}
	char m_pad00[0x280];
private:
	Color m_playerColor; // +0x280
	Color m_playerNightColor; // +0x284
	char m_pad288[0x64];
	Team *m_defaultTeam; // +0x2EC
};

#include "../../../Common/Thing/thing.h"
class Object : public Thing
{
public:
	void setDisabled(DisabledType type);
	void rva0028FB6F(void *owner);
	Bool testStatus(ObjectStatusTypes status) const;
	BodyModuleInterfaceView *bodyModule() const
	{
		return *reinterpret_cast<BodyModuleInterfaceView *const *>(
			reinterpret_cast<const char *>(this) + 0x250);
	}
	Drawable *getDrawable() const;
	Player *getControllingPlayer() const;
	Bool clearDisabled( DisabledType type );
	void rva0028DCC4();
	void defect( Team *team, UnsignedInt detectionTime );
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
#include "../../../../Include/Common/ObjectModule.h"

class OpenContainPrimaryBase : public ObjectModule
{
public:
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
	virtual int getContainMax() const = 0;
	virtual void pad64() = 0;
	virtual void pad68() = 0;
	virtual void pad6C() = 0;
	virtual void pad70() = 0;
	virtual void pad74() = 0;
	virtual void pad78() = 0;
	virtual void pad7C() = 0;
	virtual void pad80() = 0;
	virtual void pad84() = 0;
	virtual Bool isValidContainerFor(Object *, Bool, Bool) = 0;
	virtual void pad8C() = 0;
	virtual void addToContainList(Object *) = 0;
	virtual void removeFromContain(Object *, Bool) = 0;
	virtual void removeAllContained(Bool) = 0;
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
	virtual void iterateContained(void (*)(Object *, void *), void *, unsigned int) = 0;
	virtual int rva00466504(BfmeTab1026 *) = 0;
	virtual Rva0036AE51ListView rva00466534() = 0;
};

template <int Offset>
class OpenContainAuxiliaryInterface
{
public:
	virtual void auxiliaryAnchor() = 0;
};

template <>
class OpenContainAuxiliaryInterface<0x28>
{
public:
	virtual void onDie(const DamageInfo *) = 0;
};

template <>
class OpenContainAuxiliaryInterface<0x34>
{
public:
	virtual void onCreate() = 0;
	virtual void onBuildComplete() = 0;
	virtual void rva004B3FD0() = 0;
	virtual Bool shouldDoOnBuildComplete() = 0;
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
	OpenContain(Thing *thing, const ModuleData *moduleData);
	virtual ~OpenContain();
	virtual const Player *getApparentControllingPlayer(const Player *) const;
	virtual void onRemoving(Object *obj);
	virtual void onContaining(Object *, Bool);

protected:
	virtual void doUnloadSound();
	virtual void xfer(Xfer *xfer);
	using OpenContainPrimaryBase::getObject;

private:
	unsigned char m_openContainData[0xC4];
};

typedef char OpenContainSizeMustBeFC[(sizeof(OpenContain) == 0xFC) ? 1 : -1];

class CaveInterface
{
public:
	virtual void tryToSetCaveIndex(Int newIndex) = 0;
	virtual void setOriginalTeam(Team *oldTeam) = 0;
};

class CaveContain : public OpenContain, public CaveInterface
{
public:
	CaveContain(Thing *thing, const ModuleData *moduleData);
	virtual void onRemoving(Object *obj);
	virtual void recalcApparentControllingPlayer();
	void rva00466848(Team *, Bool);
	virtual void onContaining(Object *, Bool);
	virtual void removeFromContain(Object *obj, Bool exposeStealthUnits);
	virtual void removeAllContained(Bool exposeStealthUnits);
	virtual void iterateContained(void (*callback)(Object*,void*), void *data, unsigned int flags);
	// Implemented for the CaveInterface subobject at complete-object +0xFC.
	virtual void tryToSetCaveIndex(int newIndex);
	// Implemented for the one-entry die interface at complete-object +0x28.
	virtual void onDie(const DamageInfo *damageInfo);
	virtual void addToContainList(Object *obj);
	virtual Bool isValidContainerFor(Object *obj, Bool checkCapacity, Bool testPath);
	virtual int rva00466504(BfmeTab1026 *tab);
	virtual int getContainMax() const;
	virtual Rva0036AE51ListView rva00466534();
	// Lifecycle interface at complete-object +0x34.
	virtual void onCreate();
	virtual void onBuildComplete();

protected:
	virtual ~CaveContain();
	virtual void xfer(Xfer *xfer);

private:
	Bool m_needToRunOnBuildComplete; // +0x100
	unsigned char m_fieldAlignment[3];
	Int m_caveIndex; // +0x104
	Team *m_originalTeam; // +0x108
public:
	virtual NameKeyType getModuleNameKey() const;
};

typedef char CaveContainSizeMustBe10C[(sizeof(CaveContain) == 0x10C) ? 1 : -1];

// ?recalcApparentControllingPlayer@CaveContain@@UAEXXZ
void CaveContain::recalcApparentControllingPlayer()
{
	if (m_originalTeam == 0)
		m_originalTeam = getObject()->getTeam();

	if (getObject()->getTeam() == 0)
		m_originalTeam = 0;

	if (rva00466504(0) == 1)
	{
		Object *rider = reinterpret_cast<Object *>(containmentFirstWord(*rva00466534().b->begin()));
		if (rider->getControllingPlayer() != 0)
			rva00466848(
				rider->getControllingPlayer()->getDefaultTeam(), true);
	}
	else if (rva00466504(0) == 0)
	{
		rva00466848(m_originalTeam, false);
	}

	const Player *controller =
		getApparentControllingPlayer(ThePlayerList->getLocalPlayer());
	if (controller != 0)
	{
		if (caveContainGlobalData()->m_timeOfDay == TIME_OF_DAY_NIGHT)
		{
			Color indicatorColor = controller->bfme_player_night_color();
			getObject()->getDrawable()->setIndicatorColor(indicatorColor);
		}
		else
		{
			Color indicatorColor = controller->bfme_player_color();
			getObject()->getDrawable()->setIndicatorColor(indicatorColor);
		}
	}
}
