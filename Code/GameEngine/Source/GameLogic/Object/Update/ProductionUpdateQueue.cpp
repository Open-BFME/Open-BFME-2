// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /ICode/Libraries/Include
//
// ProductionUpdate queue members (BFME 2), from the Generals Zero Hour
// ProductionUpdate.cpp.
//
// Target facts. The ProductionUpdateInterface vftable 0x00C51478 sits at
// +0x20 (after UpdateModule), so these members get `this` at +0x20: the
// object is at [this-0x18] and the module data at [this-0x1C]. Slot 3 is
// queueUpgrade and slot 6 isUpgradeInQueue (the rowed 0x0049CDF9). The queue
// head and tail are at +0x28/+0x2C, the unique id at +0x30 and the entry
// count at +0x34; addToProductionQueue is the rowed 0x0049D526 (spelled
// through its Rva view here). The module data keeps MaxQueueEntries at +0x28.
// Each entry is a 0x54-byte Rva0049D1B1 (rowed ctor 0x0049D162): type +4,
// upgrade +0xC, production id +0x10, cost +0x28 and the upgrade's +0x70
// copied to +0x38.
// BFME 2 differences from ZH: no canProduceUpgrade check; canAffordUpgrade
// and calcCostToBuild also take the object; the withdrawal is recorded
// against the player's +0x3BC tracker; when the object's castle-member
// module (0x00395708) has its data flag +0x18 set, the cost is also stored
// as a float at object +0x324; addUpgrade takes a trailing 0.

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
	PRODUCTION_UPGRADE
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

class Object
{
public:
	Player *getControllingPlayer() const;
	Bool rva00290D2B(const UpgradeTemplate *upgrade) const; // hasUpgrade
	Bool rva002940B9(const UpgradeTemplate *upgrade); // affectedByUpgrade

	char m_unknown00[0x324];
	Real m_bfme324; // +0x324
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

// ProductionEntry.
class Rva0049D1B1
{
public:
	Rva0049D1B1() throw();
	virtual ~Rva0049D1B1();

	ProductionType m_type; // +4
	char m_unknown08[4];
	const UpgradeTemplate *m_upgradeToResearch; // +0xC
	Int m_productionID; // +0x10
	char m_unknown14[0x28 - 0x14];
	Int m_cost; // +0x28
	char m_unknown2C[0x38 - 0x2C];
	Int m_bfme38; // +0x38
	char m_unknown3C[0x48 - 0x3C];
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
	virtual void i00(); virtual void i01(); virtual void i02();
	virtual Bool queueUpgrade(const UpgradeTemplate *upgrade);
	virtual void cancelUpgrade(const UpgradeTemplate *upgrade);
	virtual void i05();
	virtual Bool isUpgradeInQueue(const UpgradeTemplate *upgrade) const;
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
	virtual Bool queueUpgrade(const UpgradeTemplate *upgrade);
	virtual void cancelUpgrade(const UpgradeTemplate *upgrade);

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
	Int m_uniqueID; // +0x30
	UnsignedInt m_productionCount; // +0x34
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
