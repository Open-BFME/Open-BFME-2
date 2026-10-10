// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x004572B1, 141B: BridgeBehavior::onHealing, entered through the
// DamageModuleInterface subobject at BridgeBehavior+0x24 (object this-0x1C,
// BridgeBehaviorInterface this-0x04 whose slot 1 is getTowerID).
// Body: Zero Hour's onHealing (GeneralsMD GameEngine/Source/GameLogic/Object/
// Behavior/BridgeBehavior.cpp) with the BFME 2 layout shared by the matched
// BridgeTowerBehavior::onHealing 0x00458997: body module Object+0x254
// (getMaxHealth slot 0x18), DamageInfo amount +0x20 / source +0x08, the
// tower kind-of bit at template+0x10B bit 0 (ZH KINDOF_BRIDGE_TOWER) and
// out-of-line Object::attemptHealing 0x0028FE55.

typedef float Real;
typedef int Int;

#include "../../../Common/GameLogicObjectLookupView.h"

class DamageInfo
{
public:
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID;			// +0x08
	unsigned char m_pad0C[0x10 - 0x0C];
	Int m_damageType;			// +0x10
	unsigned char m_pad14[0x1C - 0x14];
	Int m_deathType;			// +0x1C
	Real m_amount;				// +0x20
};

// BFME 2's 0x7C-byte DamageInfo as a local: its default constructor is the
// rowed 0x00263895, address-named Rva00263895Member; trivially destroyed.
class Rva00263895Member
{
public:
	Rva00263895Member();
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID;			// +0x08
	unsigned char m_pad0C[0x10 - 0x0C];
	Int m_damageType;			// +0x10
	unsigned char m_pad14[0x1C - 0x14];
	Int m_deathType;			// +0x1C
	Real m_amount;				// +0x20
	unsigned char m_pad24[0x7C - 0x24];
};

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getMaxHealth() const;
};

class ThingTemplate
{
public:
	unsigned char m_pad00[0x10B];
	unsigned char m_kindOf10B;
};

class Object
{
public:
	void attemptHealing(Real amount, const Object *source);
	void attemptDamage(DamageInfo *info);
	BodyModuleInterface *getBodyModule() const { return m_body; }
	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id;				// +0x74
	unsigned char m_pad78[0x254 - 0x78];
	BodyModuleInterface *m_body;
	ObjectID getID() const { return m_id; }
};

extern GameLogic *TheGameLogic;

enum BridgeTowerType
{
	BRIDGE_MAX_TOWERS = 4
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
protected:
	Object *getObject() const { return m_object; }
private:
	const void *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x20 - 0x0C];
};

class BridgeBehaviorInterface
{
public:
	virtual void setTower(BridgeTowerType towerType, Object *tower) = 0;
	virtual ObjectID getTowerID(BridgeTowerType towerType) = 0;
};

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo) = 0;
	virtual void onHealing(DamageInfo *damageInfo) = 0;
};

class BridgeBehavior : public UpdateModule, public BridgeBehaviorInterface,
	public DamageModuleInterface
{
public:
	virtual void setTower(BridgeTowerType towerType, Object *tower);
	virtual ObjectID getTowerID(BridgeTowerType towerType);
	virtual void onDamage(DamageInfo *damageInfo);
	virtual void onHealing(DamageInfo *damageInfo);
};

// ------------------------------------------------------------------------------------------------
// Retail 0x004571FB, 182B: BridgeBehavior::onDamage, the damage-interface slot
// before onHealing. Zero Hour's body in the same BFME 2 layout; the tower
// damage record is the 0x7C-byte local built by 0x00263895 and handed to the
// out-of-line Object::attemptDamage 0x0029848E.
// ------------------------------------------------------------------------------------------------
void BridgeBehavior::onDamage( DamageInfo *damageInfo )
{

	// get the bridge object
	Object *bridge = getObject();

	// get bridge body module
	BodyModuleInterface *body = bridge->getBodyModule();

	// what is our percentage of the damage done to the bridge
	Real damagePercentage = damageInfo->m_amount / body->getMaxHealth();

	// if our source is a tower, don't do anything
	Object *source = TheGameLogic->findObjectByID( damageInfo->m_sourceID );
	if( source && (source->m_template->m_kindOf10B & 1) )
		return;

	// apply damage to all towers
	for( Int i = 0; i < BRIDGE_MAX_TOWERS; ++i )
	{
		Object *tower = TheGameLogic->findObjectByID( getTowerID( (BridgeTowerType)i ) );
		if( tower )
		{
			BodyModuleInterface *towerBody = tower->getBodyModule();
			Rva00263895Member towerDamage;
			towerDamage.m_amount = towerBody->getMaxHealth() * damagePercentage;
			towerDamage.m_sourceID = getObject()->getID();
			towerDamage.m_damageType = damageInfo->m_damageType;
			towerDamage.m_deathType = damageInfo->m_deathType;
			tower->attemptDamage( (DamageInfo *)&towerDamage );
		}
	}

}  // end onDamage

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void BridgeBehavior::onHealing( DamageInfo *damageInfo )
{

	//
	// get our body info so we now how much healing percent is being done to us ... we need this
	// so that we can propagate the same healing percentage amont the towers and the bridge
	//
	BodyModuleInterface *body = getObject()->getBodyModule();
	Real healingPercentage = damageInfo->m_amount / body->getMaxHealth();

	//
	// if the healing didn't come from a bridge tower, then we must propagate this healing
	// to all our towers
	//
	Object *source = TheGameLogic->findObjectByID( damageInfo->m_sourceID );
	if( source == 0 || (source->m_template->m_kindOf10B & 1) == 0 )
	{
		Object *tower;

		for( Int i = 0; i < BRIDGE_MAX_TOWERS; i++ )
		{

			tower = TheGameLogic->findObjectByID( getTowerID( (BridgeTowerType)i ) );
			if( tower )
			{
				BodyModuleInterface *towerBody = tower->getBodyModule();
				tower->attemptHealing( healingPercentage * towerBody->getMaxHealth(), getObject() );
			}  // end if

		}  // end for i

	}  // end if

}  // end onHealing
