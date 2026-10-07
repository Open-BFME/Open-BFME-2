// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /ICode/Libraries/Include /Ireference/shims/bfme2_ascii
//
// ProductionUpdate queue members (BFME 2), from the Generals Zero Hour
// ProductionUpdate.cpp and ProductionUpdate.h.
//
// Target facts. The ProductionUpdateInterface vftable 0x00C51478 sits at
// +0x20 (after UpdateModule), so these members get `this` at +0x20: the
// object is at [this-0x18] and the module data at [this-0x1C]. Slots 0-22
// are rowed here, except:
// - slot 8 (queueCreateUnit), slot 16 and slot 17 (getProductionCount);
// - slot 10 cancelUnitCreate (0x0049DC50) and slot 12 (0x0049CCF0);
// - slot 15 cancelAndRefundAllProduction (ProductionUpdate.cpp);
// - slot 21 firstProduction, folded into a shared getter.
// Slots without a ZH counterpart keep placeholder names.
// The queue head and tail are at +0x28/+0x2C, the unique id at +0x30 and the
// entry count at +0x34. +0x130 holds a vector of type names (slot 13) and
// +0x13C a flag that disables unit queueing (slot 0).
// addToProductionQueue and removeFromProductionQueue are the rowed 0x0049D526
// and 0x0049D57F, spelled through their Rva view here. The module data keeps
// MaxQueueEntries at +0x28.
// Each entry is a 0x54-byte Rva0049D1B1 (rowed ctor 0x0049D162) with:
// - type +4, object template +8, upgrade +0xC, production id +0x10;
// - percent complete +0x14, cost +0x28, a door/slot index +0x30 (-1 for
//   none), the upgrade's +0x70 copy at +0x38 and +0x3C (set by slot 14);
// - next/prev links at +0x48/+0x4C.
// The unit test (type 1 or 3) is the rowed out-of-line copy 0x00327C1B.
// BFME 2 differences from ZH:
// - queueUpgrade has no canProduceUpgrade check.
// - canAffordUpgrade and calcCostToBuild also take the object.
// - the withdrawal and refund are recorded against the player's +0x3BC
//   tracker, and the refund is the cost stored on the entry.
// - when the object's castle-member module (0x00395708) has its data flag
//   +0x18 set, the cost is also stored as a float at object +0x324.
// - addUpgrade and removeUpgrade take a trailing 0.
// - unit matches go through ThingTemplate::isEquivalentTo.

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define TRUE 1
#define FALSE 0
#define NULL 0

class Thing;
class ModuleData;
class Object;
class Player;
class Upgrade;


namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A = allocator<T> > class vector
{
public:
	void push_back(const T &x);

private:
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

enum CanMakeType
{
	CANMAKE_OK = 0,
	CANMAKE_NO_PREREQ,
	CANMAKE_NO_MONEY,
	CANMAKE_FACTORY_IS_DISABLED,
	CANMAKE_QUEUE_FULL
};

enum ProductionID
{
	PRODUCTIONID_INVALID = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_3E = 0x3E
};

struct Rva0049D0DEMask
{
	UnsignedInt m_bits[1];
};

class ThingTemplate
{
public:
	Bool isEquivalentTo(const ThingTemplate *tt) const;
	const AsciiString &getName() const { return m_name; }

private:
	char m_unknown00[0x64];
	AsciiString m_name; // +0x64
};

enum UpgradeType
{
	UPGRADE_TYPE_PLAYER = 0,
	UPGRADE_TYPE_OBJECT = 1
};

enum UpgradeStatusType
{
	UPGRADE_STATUS_INVALID = 0,
	UPGRADE_STATUS_IN_PRODUCTION = 1
};

enum ProductionType
{
	PRODUCTION_INVALID = 0,
	PRODUCTION_UNIT,
	PRODUCTION_UPGRADE,
	PRODUCTION_HORDE_UNIT
};

class UpgradeTemplate
{
public:
	UpgradeType getUpgradeType() const { return m_type; }
	UnsignedInt rva0026EF50(Player *player, Object *obj) const; // calcCostToBuild

	char m_unknown00[4];
	UpgradeType m_type; // +4
	char m_unknown08[0x70 - 8];
	Int m_bfme70; // +0x70
};

class UpgradeCenter
{
public:
	Bool rva0026F11A(Player *player, const UpgradeTemplate *upgrade, Object *obj, Bool displayReason); // canAffordUpgrade
};

extern UpgradeCenter *TheUpgradeCenter;

class Rva0039B795
{
	char m_unknown00[4];
};

class Rva0039B7AD;

// Money.
class Rva003B0D7C
{
public:
	UnsignedInt rva003B0CB3(UnsignedInt amount, Rva0039B795 *tracker, bool flag); // withdraw
	void rva003B0D7C(Int amount, Rva0039B7AD *tracker, bool flag); // deposit

private:
	char m_unknown00[0xC];
};

class Player
{
public:
	Rva003B0D7C *getMoney() { return &m_money; }
	Bool rva002AB87D(const UpgradeTemplate *upgrade) const; // hasUpgradeComplete
	Bool rva002AA8EF(const UpgradeTemplate *upgrade) const; // hasUpgradeInProduction
	Upgrade *rva002AE329(const UpgradeTemplate *upgrade, UpgradeStatusType status, Int flag); // addUpgrade
	void rva002ADAC3(const UpgradeTemplate *upgrade, Int flag); // removeUpgrade

	char m_unknown00[0x90];
	Rva003B0D7C m_money; // +0x90
	char m_unknown9C[0x3BC - 0x9C];
	Rva0039B795 m_tracker; // +0x3BC
};

enum ObjectID
{
	INVALID_ID = 0
};

enum ExitDoorType
{
	DOOR_1 = 0
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class Module;

// ZH ExitInterface slots 0..10 (BFME 1 UpdateModule.h); BFME 2 adds slot 11.
class ExitInterface
{
public:
	virtual Bool isExitBusy() const = 0;
	virtual ExitDoorType reserveDoorForExit(const ThingTemplate *objType, Object *specificObject) = 0;
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor) = 0;
	virtual void exitObjectByBudding(Object *newObj, Object *budHost) = 0;
	virtual void unreserveDoorForExit(ExitDoorType exitDoor) = 0;
	virtual void exitObjectInAHurry(Object *newObj) = 0;
	virtual void setRallyPoint(const void *pos) = 0;
	virtual const void *getRallyPoint() const = 0;
	virtual Bool useSpawnRallyPoint() const = 0;
	virtual Bool getNaturalRallyPoint(void *rallyPoint, Bool offset) const = 0;
	virtual Bool getExitPosition(void *exitPosition) const = 0;
	virtual void exitSlot11() = 0;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	ExitInterface *getObjectExitInterface() const;
	Module *findUpdateModule(NameKeyType key) const { return findModule(key); }
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool rva00290D2B(const UpgradeTemplate *upgrade) const; // hasUpgrade
	Bool rva002940B9(const UpgradeTemplate *upgrade); // affectedByUpgrade

	char m_unknown00[0x324];
	Real m_bfme324; // +0x324

protected:
	Module *findModule(NameKeyType key) const;
};

struct Rva00395708Data
{
	char m_unknown00[0x18];
	Bool m_flag; // +0x18
};

class Module
{
public:
	char m_unknown00[4];
	const Rva00395708Data *m_moduleData; // +4
};

class CastleBehavior
{
public:
	static Module *rva000395708(Object *obj);
};

class Rva00327C1B
{
public:
	Bool rva00327C1B() const;
};

// ProductionEntry.
class Rva0049D1B1
{
public:
	Rva0049D1B1() throw();
	virtual ~Rva0049D1B1();

	// type 1 or 3, the rowed out-of-line copy 0x00327C1B
	Bool isUnit() const { return ((const Rva00327C1B *)this)->rva00327C1B(); }
	ProductionType getProductionType() const { return m_type; }
	const ThingTemplate *getProductionObject() const { return m_objectToProduce; }
	const UpgradeTemplate *getProductionUpgrade() const { return m_upgradeToResearch; }

	ProductionType m_type; // +4
	const ThingTemplate *m_objectToProduce; // +8
	const UpgradeTemplate *m_upgradeToResearch; // +0xC
	Int m_productionID; // +0x10
	Real m_percentComplete; // +0x14
	char m_unknown18[0x28 - 0x18];
	Int m_cost; // +0x28
	char m_unknown2C[0x30 - 0x2C];
	Int m_bfme30; // +0x30
	char m_unknown34[0x38 - 0x34];
	Int m_bfme38; // +0x38
	Int m_bfme3C; // +0x3C
	char m_unknown40[0x48 - 0x40];
	Rva0049D1B1 *m_next; // +0x48
	Rva0049D1B1 *m_prev; // +0x4C
	char m_unknown50[0x54 - 0x50];
};

class ProductionUpdateModuleData
{
public:
	char m_unknown00[0x28];
	UnsignedInt m_maxQueueEntries; // +0x28
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class ProductionUpdateInterface
{
public:
	virtual CanMakeType rva0049CFCD() const;
	virtual CanMakeType canQueueUpgrade(const UpgradeTemplate *upgrade) const;
	virtual ProductionID requestUniqueUnitID();
	virtual Bool queueUpgrade(const UpgradeTemplate *upgrade);
	virtual void cancelUpgrade(const UpgradeTemplate *upgrade);
	virtual void rva0049CC9D(const ThingTemplate *unitType, Bool five);
	virtual Bool isUpgradeInQueue(const UpgradeTemplate *upgrade) const;
	virtual UnsignedInt countUnitTypeInQueue(const ThingTemplate *unitType) const;
	virtual void i08();
	virtual Bool rva0049CC36(ProductionID productionID) const;
	virtual void cancelUnitCreate(ProductionID productionID);
	virtual void rva0049CC61(const ThingTemplate *unitType);
	virtual void i12();
	virtual void rva0049F8A9(const ThingTemplate *unitType, Bool cancel);
	virtual void rva0049CC15(ProductionID productionID, Int value);
	virtual void cancelAndRefundAllProduction();
	virtual void rva0049DEC8();
	virtual void i17();
	virtual UnsignedInt rva0049CEAE(const ThingTemplate *unitType) const;
	virtual UnsignedInt rva0049CEE1(Int value) const;
	virtual UnsignedInt rva0049D0DE(const Rva0049D0DEMask *mask) const;
	virtual const Rva0049D1B1 *firstProduction() const;
	virtual const Rva0049D1B1 *nextProduction(const Rva0049D1B1 *p) const;
};

class DieModuleInterface
{
public:
	virtual void onDie();
};

class Rva0049D526
{
public:
	void rva0049D526(void *entry); // addToProductionQueue
	void rva0049D57F(void *entry); // removeFromProductionQueue
};

class ProductionUpdate : public UpdateModule, public ProductionUpdateInterface, public DieModuleInterface
{
public:
	virtual CanMakeType rva0049CFCD() const;
	virtual CanMakeType canQueueUpgrade(const UpgradeTemplate *upgrade) const;
	virtual ProductionID requestUniqueUnitID();
	virtual Bool queueUpgrade(const UpgradeTemplate *upgrade);
	virtual void cancelUpgrade(const UpgradeTemplate *upgrade);
	virtual void rva0049CC9D(const ThingTemplate *unitType, Bool five);
	virtual Bool isUpgradeInQueue(const UpgradeTemplate *upgrade) const;
	virtual UnsignedInt countUnitTypeInQueue(const ThingTemplate *unitType) const;
	virtual Bool rva0049CC36(ProductionID productionID) const;
	virtual void rva0049CC61(const ThingTemplate *unitType);
	virtual void rva0049F8A9(const ThingTemplate *unitType, Bool cancel);
	virtual void rva0049CC15(ProductionID productionID, Int value);
	virtual void cancelAndRefundAllProduction();
	virtual void rva0049DEC8();
	virtual UnsignedInt rva0049CEAE(const ThingTemplate *unitType) const;
	virtual UnsignedInt rva0049CEE1(Int value) const;
	virtual UnsignedInt rva0049D0DE(const Rva0049D0DEMask *mask) const;
	virtual const Rva0049D1B1 *nextProduction(const Rva0049D1B1 *p) const;

protected:
	const ProductionUpdateModuleData *getProductionUpdateModuleData() const
	{
		return (const ProductionUpdateModuleData *)m_moduleData;
	}
	void addToProductionQueue(Rva0049D1B1 *production)
	{
		((Rva0049D526 *)this)->rva0049D526(production);
	}
	void removeFromProductionQueue(Rva0049D1B1 *production)
	{
		((Rva0049D526 *)this)->rva0049D57F(production);
	}

	Rva0049D1B1 *m_productionQueue; // +0x28
	Rva0049D1B1 *m_productionQueueTail; // +0x2C
	ProductionID m_uniqueID; // +0x30
	UnsignedInt m_productionCount; // +0x34
	char m_unknown38[0x120 - 0x38];
	ObjectID m_bfme120; // +0x120
	char m_unknown124[0x130 - 0x124];
	_STL::vector<AsciiString> m_bfme130; // +0x130
	Bool m_bfme13C; // +0x13C
};

// ?queueUpgrade@ProductionUpdate@@UAE_NPBVUpgradeTemplate@@@Z @0x0049D867 315B
Bool ProductionUpdate::queueUpgrade( const UpgradeTemplate *upgrade )
{

	// sanity
	if( upgrade == NULL )
		return FALSE;

	// get the player
	Player *player = getObject()->getControllingPlayer();

	// sanity check to make sure we can build this upgrade
	if( upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER &&
			TheUpgradeCenter->rva0026F11A( player, upgrade, getObject(), FALSE ) == FALSE )
		return FALSE;
	else if( upgrade->getUpgradeType() == UPGRADE_TYPE_OBJECT &&
					 (getObject()->rva00290D2B( upgrade ) == TRUE ||
					  getObject()->rva002940B9( upgrade ) == FALSE) )
		return FALSE;

	// you cannot queue the production of an upgrade twice in this queue
	if( isUpgradeInQueue( upgrade ) == TRUE )
		return FALSE;

	//
	// you cannot queue a player upgrade production if you are producing one already somewhere else
	// (or that somewhere else could even possibly be here)
	//
	if( upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER &&
      (player->rva002AB87D( upgrade ) || player->rva002AA8EF( upgrade )) )
		return FALSE;

	if (m_productionCount >= getProductionUpdateModuleData()->m_maxQueueEntries)
		return FALSE;

	// allocate a new production entry
	Rva0049D1B1 *production = new Rva0049D1B1;

	// assing production entry data
	production->m_productionID = 0;
	production->m_type = PRODUCTION_UPGRADE;
	production->m_upgradeToResearch = upgrade;
	production->m_bfme38 = upgrade->m_bfme70;

	// take the cost for the build away from the player
	production->m_cost = upgrade->rva0026EF50( player, getObject() );
	player->getMoney()->rva003B0CB3( production->m_cost, &player->m_tracker, true );

	Object *obj = getObject();
	Module *castle = CastleBehavior::rva000395708( obj );
	if( castle && castle->m_moduleData->m_flag )
		obj->m_bfme324 = (Real)production->m_cost;

	// tie to the end of the production queue
	addToProductionQueue( production );

	// add this upgrade as in progress in the player
	player->rva002AE329( upgrade, UPGRADE_STATUS_IN_PRODUCTION, 0 );

	return TRUE;  // queued

}  // end queueUpgrade

// ?cancelUpgrade@ProductionUpdate@@UAEXPBVUpgradeTemplate@@@Z @0x0049D9A2 146B
void ProductionUpdate::cancelUpgrade( const UpgradeTemplate *upgrade )
{

	// sanity
	if( upgrade == NULL )
		return;

	// get the player
	Player *player = getObject()->getControllingPlayer();

	// sanity, you can't cancel it if the player isn't actually building one
	if( upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER && player->rva002AA8EF( upgrade ) == FALSE )
		return;

	//
	// find the production entry for this upgrade in the queue here, there can only be one
	// of this type in the queue
	//
	Rva0049D1B1 *production;
	for( production = m_productionQueue; production; production = production->m_next )
	{

		if( production->m_type == PRODUCTION_UPGRADE &&
				production->m_upgradeToResearch == upgrade )
			break;

	}  // end for

	// sanity, entry not found
	if( production == NULL )
		return;

	// refund the cost paid back to the player
	player->getMoney()->rva003B0D7C( production->m_cost, (Rva0039B7AD *)&player->m_tracker, true );

	// remove this production from the queue
	removeFromProductionQueue( production );

	// delete production instance
	::delete production;

	//
	// remove the IN_PRODUCTION status of this upgrade from the player, object upgrades don't
	// have any other IN_PRODUCTION status other than their existence in the build queue
	//
	if( upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER )
		player->rva002ADAC3( upgrade, 0 );

}  // end cancelUpgrade

// ?rva0049CFCD@ProductionUpdate@@UBE?AW4CanMakeType@@XZ @0x0049CFCD 30B
// Slot 0, where ZH has canQueueCreateUnit; BFME 2's takes no argument and
// refuses while the +0x13C flag is set.
CanMakeType ProductionUpdate::rva0049CFCD() const
{
	if( m_bfme13C )
		return CANMAKE_FACTORY_IS_DISABLED;

	if (m_productionCount >= getProductionUpdateModuleData()->m_maxQueueEntries)
		return CANMAKE_QUEUE_FULL;

	return CANMAKE_OK;
}

// ?canQueueUpgrade@ProductionUpdate@@UBE?AW4CanMakeType@@PBVUpgradeTemplate@@@Z @0x0049CFA9 36B
CanMakeType ProductionUpdate::canQueueUpgrade( const UpgradeTemplate *upgrade ) const
{
	if (m_productionCount >= getProductionUpdateModuleData()->m_maxQueueEntries)
		return CANMAKE_QUEUE_FULL;

	return getObject()->testStatus( OBJECT_STATUS_BFME_3E ) ? CANMAKE_FACTORY_IS_DISABLED : CANMAKE_OK;
}

// ?requestUniqueUnitID@ProductionUpdate@@UAE?AW4ProductionID@@XZ @0x0049E142 10B
ProductionID ProductionUpdate::requestUniqueUnitID( void )
{
	ProductionID tmp = m_uniqueID;
	m_uniqueID = (ProductionID)(m_uniqueID+1);
	return tmp;
}

// ?rva0049CC9D@ProductionUpdate@@UAEXPBVThingTemplate@@_N@Z @0x0049CC9D 83B
// Cancels the last one (or five) queued units of the type, newest first.
void ProductionUpdate::rva0049CC9D( const ThingTemplate *unitType, Bool five )
{
	Int count = five ? 5 : 1;
	Rva0049D1B1 *production = m_productionQueueTail;
	while( count )
	{
		if( production == NULL )
			break;
		if( production->isUnit() && unitType->isEquivalentTo( production->m_objectToProduce ) )
		{
			cancelUnitCreate( (ProductionID)production->m_productionID );
			--count;
			production = m_productionQueueTail;
		}
		else
			production = production->m_prev;
	}
}

// ?isUpgradeInQueue@ProductionUpdate@@UBE_NPBVUpgradeTemplate@@@Z @0x0049CDF9 47B
Bool ProductionUpdate::isUpgradeInQueue( const UpgradeTemplate *upgrade ) const
{
	const Rva0049D1B1 *production;

	for( production = firstProduction(); production; production = nextProduction( production ) )
		if( production->getProductionType() == PRODUCTION_UPGRADE &&
				production->getProductionUpgrade() == upgrade )
			return TRUE;

	return FALSE;  // not in queue

}  // end isUpgradeInQueue

// ?countUnitTypeInQueue@ProductionUpdate@@UBEIPBVThingTemplate@@@Z @0x0049CE28 59B
UnsignedInt ProductionUpdate::countUnitTypeInQueue( const ThingTemplate *unitType ) const
{
	UnsignedInt count = 0;
	const Rva0049D1B1 *production;

	for( production = firstProduction(); production; production = nextProduction( production ) )
		if( production->getProductionType() == PRODUCTION_UNIT &&
				unitType->isEquivalentTo( production->getProductionObject() ) )
			count++;

	return count;

}  // end countUnitTypeInQueue

// ?rva0049CC36@ProductionUpdate@@UBE_NW4ProductionID@@@Z @0x0049CC36 43B
// Is a unit with this production id in the queue.
Bool ProductionUpdate::rva0049CC36( ProductionID productionID ) const
{
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
		if( production->isUnit() && production->m_productionID == productionID )
			return TRUE;

	return FALSE;
}

// ?rva0049CC61@ProductionUpdate@@UAEXPBVThingTemplate@@@Z @0x0049CC61 60B
// Cancels the oldest queued unit of the type.
void ProductionUpdate::rva0049CC61( const ThingTemplate *unitType )
{
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
	{
		if( production->isUnit() && unitType->isEquivalentTo( production->m_objectToProduce ) )
		{
			cancelUnitCreate( (ProductionID)production->m_productionID );
			return;
		}
	}
}

// ?rva0049F8A9@ProductionUpdate@@UAEXPBVThingTemplate@@_N@Z @0x0049F8A9 113B
// Without the flag, records the type's name in the +0x130 list; with it,
// cancels every unfinished queued unit of the type.
void ProductionUpdate::rva0049F8A9( const ThingTemplate *unitType, Bool cancel )
{
	if( !cancel )
	{
		m_bfme130.push_back( unitType->getName() );
		return;
	}

	Rva0049D1B1 *production = m_productionQueue;
	while( production )
	{
		ProductionType type = production->m_type;
		if( production->m_percentComplete < 100.0f &&
				(type == PRODUCTION_UNIT || type == PRODUCTION_HORDE_UNIT) &&
				unitType->isEquivalentTo( production->m_objectToProduce ) )
		{
			Rva0049D1B1 *next = production->m_next;
			cancelUnitCreate( (ProductionID)production->m_productionID );
			production = next;
		}
		else
			production = production->m_next;
	}
}

// ?rva0049CC15@ProductionUpdate@@UAEXW4ProductionID@@H@Z @0x0049CC15 33B
// Sets the +0x3C field of the entry with this production id.
void ProductionUpdate::rva0049CC15( ProductionID productionID, Int value )
{
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
	{
		if( production->m_productionID == productionID )
		{
			production->m_bfme3C = value;
			return;
		}
	}
}

// ?rva0049CEAE@ProductionUpdate@@UBEIPBVThingTemplate@@@Z @0x0049CEAE 51B
// Counts the queued units (and hordes) of the type.
UnsignedInt ProductionUpdate::rva0049CEAE( const ThingTemplate *unitType ) const
{
	UnsignedInt count = 0;
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
		if( production->isUnit() && unitType->isEquivalentTo( production->m_objectToProduce ) )
			count++;
	return count;
}

// ?rva0049CEE1@ProductionUpdate@@UBEIH@Z @0x0049CEE1 27B
// Counts the entries whose +0x30 field equals the value.
UnsignedInt ProductionUpdate::rva0049CEE1( Int value ) const
{
	UnsignedInt count = 0;
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
		if( value == production->m_bfme30 )
			count++;
	return count;
}

// ?rva0049D0DE@ProductionUpdate@@UBEIPBURva0049D0DEMask@@@Z @0x0049D0DE 54B
// Counts the entries whose +0x30 index (-1 for none) is set in the mask.
UnsignedInt ProductionUpdate::rva0049D0DE( const Rva0049D0DEMask *mask ) const
{
	UnsignedInt count = 0;
	for( Rva0049D1B1 *production = m_productionQueue; production; production = production->m_next )
	{
		UnsignedInt index = production->m_bfme30;
		if( index != (UnsignedInt)-1 && (mask->m_bits[index >> 5] & (1 << (index & 31))) )
			count++;
	}
	return count;
}

// ?nextProduction@ProductionUpdate@@UBEPBVRva0049D1B1@@PBV2@@Z @0x0049E14C 18B
const Rva0049D1B1 *ProductionUpdate::nextProduction( const Rva0049D1B1 *p ) const
{
	return p ? p->m_next : NULL;
}

// ?rva0049DEC8@ProductionUpdate@@UAEXXZ @0x0049DEC8 154B
// Slot 16: cancels and refunds the queue, then sends the object held at
// +0x120 out through door 1 unless it has a RespawnUpdate, and finally
// calls the exit interface's slot 11.
void ProductionUpdate::rva0049DEC8()
{
	cancelAndRefundAllProduction();
	ExitInterface *exitInterface = getObject()->getObjectExitInterface();
	ObjectID id = m_bfme120;
	if( id != INVALID_ID )
	{
		Object *obj = TheGameLogic->findObjectByID( id );
		if( obj )
		{
			static NameKeyType key_RespawnUpdate = NAMEKEY( "RespawnUpdate" );
			if( obj->findUpdateModule( key_RespawnUpdate ) == NULL )
				exitInterface->exitObjectViaDoor( obj, DOOR_1 );
		}
	}
	if( exitInterface )
		exitInterface->exitSlot11();
}
