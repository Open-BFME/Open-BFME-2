// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x00458997, 241B: BridgeTowerBehavior::onHealing, entered through
// the DamageModuleInterface subobject at BridgeTowerBehavior+0x18 (the
// tower interface is this-0x08 and the object this-0x10).
// Body: Zero Hour's onHealing (GeneralsMD GameEngine/Source/GameLogic/Object/
// Behavior/BridgeTowerBehavior.cpp); the BFME 1 port
// (reference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Behavior/
// BridgeTowerBehaviorOnHealing.cpp) supplies the same shape. BFME 2 target
// evidence: body module at Object+0x254 (getMaxHealth slot 0x18), behavior
// module array at Object+0x244 with the BehaviorModuleInterface at module
// +0x0C (getBridgeBehaviorInterface slot 0x30), DamageInfo amount +0x20 and
// source id +0x08, the source kind-of bits tested together at the template's
// +0x10A word (mask 0x140: ZH KINDOF_BRIDGE and KINDOF_BRIDGE_TOWER), and
// out-of-line Object::attemptHealing 0x0028FE55.

typedef float Real;

#include "../../../Common/GameLogicObjectLookupView.h"

class DamageInfo
{
public:
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID;
	unsigned char m_pad0C[0x20 - 0x0C];
	Real m_amount;
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
	void attemptHealing(Real amount, const Object *source);
	BodyModuleInterface *getBodyModule() const { return m_body; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x244 - 0x08];
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
void BridgeTowerBehavior::onHealing( DamageInfo *damageInfo )
{
	BridgeTowerBehaviorInterface *towerInterface =
		(BridgeTowerBehaviorInterface *)((unsigned char *)this - 0x08);

	// get the bridge object
	Object *bridge = TheGameLogic->findObjectByID( towerInterface->getBridgeID() );
	if( bridge == 0 )
		return;

	// get the percentage of healing applied to us
	BodyModuleInterface *body = getObject()->getBodyModule();
	Real healingPercentage = damageInfo->m_amount / body->getMaxHealth();

	// find the bridge behavior interface on the bridge
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
		// do not heal again when the healing came from the bridge or another tower
		Object *source = TheGameLogic->findObjectByID( damageInfo->m_sourceID );
		if( source == 0 || (source->m_template->m_kindOf10A & 0x140) == 0 )
		{

			// heal the other towers
			for( int i = 0; i < 4; ++i )
			{
				Object *tower = TheGameLogic->findObjectByID( bridgeInterface->getTowerID( i ) );
				if( tower && tower != getObject() )
				{
					BodyModuleInterface *towerBody = tower->getBodyModule();
					tower->attemptHealing( healingPercentage * towerBody->getMaxHealth(), getObject() );
				}
			}

			// heal the bridge
			BodyModuleInterface *bridgeBody = bridge->getBodyModule();
			bridge->attemptHealing( healingPercentage * bridgeBody->getMaxHealth(), getObject() );

		}

	}

}  // end onHealing
