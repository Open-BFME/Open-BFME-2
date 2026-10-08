// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x00458841, 342B: BridgeTowerBehavior::onDamage, entered through
// the DamageModuleInterface subobject at BridgeTowerBehavior+0x18 (the
// tower interface is this-0x08 and the object this-0x10).
// Body: Zero Hour's onDamage (GeneralsMD GameEngine/Source/GameLogic/Object/
// Behavior/BridgeTowerBehavior.cpp), the damage twin of the matched
// onHealing 0x00458997 with the same BFME 2 layout (body Object+0x254,
// behavior array Object+0x244, DamageInfo amount +0x20 / source +0x08,
// source kind-of word mask 0x140). Each propagated DamageInfo (0x7C bytes)
// is built by the out-of-line constructor 0x00263895 and carries our id,
// the damage type (+0x10) and death type (+0x1C) into Object::attemptDamage
// 0x0029848E.

typedef float Real;

#include "../../../Common/GameLogicObjectLookupView.h"

class DamageInfo
{
public:
	DamageInfo();
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID;
	unsigned char m_pad0C[0x10 - 0x0C];
	int m_damageType;
	unsigned char m_pad14[0x1C - 0x14];
	int m_deathType;
	Real m_amount;
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

class BridgeBehaviorInterface
{
public:
	virtual void setTower(int towerType, Object *tower);
	virtual ObjectID getTowerID(int towerType);
};

class BehaviorModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual BridgeBehaviorInterface *getBridgeBehaviorInterface();
};

class BehaviorModule
{
public:
	unsigned char m_pad00[0x0C];
	BehaviorModuleInterface m_interface;
};

class ThingTemplate
{
public:
	unsigned char m_pad00[0x10A];
	unsigned short m_kindOf10A;
};

class Object
{
public:
	void attemptDamage(DamageInfo *damageInfo);
	ObjectID getID() const { return m_id; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id;
	unsigned char m_pad78[0x244 - 0x78];
	BehaviorModule **m_behaviors;
	unsigned char m_pad248[0x254 - 0x248];
	BodyModuleInterface *m_body;
};

extern GameLogic *TheGameLogic;

class BridgeTowerBehaviorInterface
{
public:
	virtual void setBridge(Object *bridge);
	virtual ObjectID getBridgeID();
	virtual void setTowerType(int type);
};

class BridgeTowerBehavior
{
public:
	virtual void onDamage(DamageInfo *damageInfo);
	virtual void onHealing(DamageInfo *damageInfo);

	Object *getObject() const
	{
		return *(Object *const *)((const unsigned char *)this - 0x10);
	}
};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void BridgeTowerBehavior::onDamage( DamageInfo *damageInfo )
{
	BridgeTowerBehaviorInterface *towerInterface =
		(BridgeTowerBehaviorInterface *)((unsigned char *)this - 0x08);

	Object *bridge = TheGameLogic->findObjectByID( towerInterface->getBridgeID() );

	// sanity
	if( bridge == 0 )
		return;

	//
	// get our body info so we now how much damage percent is being done to us ... we need this
	// so that we can propagate the same damage percentage amont the towers and the bridge
	//
	BodyModuleInterface *body = getObject()->getBodyModule();
	Real damagePercentage = damageInfo->m_amount / body->getMaxHealth();

	// get the bridge behavior module for our bridge
	BehaviorModule **bmi;
	BridgeBehaviorInterface *bridgeInterface = 0;
	for( bmi = bridge->getBehaviorModules(); *bmi; ++bmi )
	{

		bridgeInterface = (*bmi)->m_interface.getBridgeBehaviorInterface();
		if( bridgeInterface )
			break;

	}  // end for bmi

	if( bridgeInterface )
	{

		//
		// damage each of the other towers if the source of this damage isn't from the bridge
		// or other towers
		//
		Object *source = TheGameLogic->findObjectByID( damageInfo->m_sourceID );
		if( source == 0 || (source->m_template->m_kindOf10A & 0x140) == 0 )
		{

			for( int i = 0; i < 4; ++i )
			{
				Object *tower;

				tower = TheGameLogic->findObjectByID( bridgeInterface->getTowerID( i ) );
				if( tower && tower != getObject() )
				{
					BodyModuleInterface *towerBody = tower->getBodyModule();
					DamageInfo towerDamage;

					towerDamage.m_amount = damagePercentage * towerBody->getMaxHealth();
					towerDamage.m_sourceID = getObject()->getID();  // we're now the source
					towerDamage.m_damageType = damageInfo->m_damageType;
					towerDamage.m_deathType = damageInfo->m_deathType;
					tower->attemptDamage( &towerDamage );

				}  // end if

			}  // end for i

			//
			// damage bridge object, but make sure it's done through the bridge interface
			// so that it doesn't automatically propagate that damage to the towers
			//
			BodyModuleInterface *bridgeBody = bridge->getBodyModule();
			DamageInfo bridgeDamage;

			bridgeDamage.m_amount = damagePercentage * bridgeBody->getMaxHealth();
			bridgeDamage.m_sourceID = getObject()->getID();  // we're now the source
			bridgeDamage.m_damageType = damageInfo->m_damageType;
			bridgeDamage.m_deathType = damageInfo->m_deathType;
			bridge->attemptDamage( &bridgeDamage );

		}  // end if

	}  // end if

}  // end onDamage
