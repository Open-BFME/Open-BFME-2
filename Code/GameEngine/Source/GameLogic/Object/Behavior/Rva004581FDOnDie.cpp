// cl: /DNDEBUG /MD /O1
// Target evidence: 0x004581FD is a 79-byte function with a four-iteration
// tower-ID lookup through the interface at this-8, kills each found object
// with (8, 0), calls 0x00457577 on this-0x28, then copies GameLogic+0x40 to
// this+0xDC. The BridgeBehavior constructor installs its bridge and die
// interface vtables at object+0x20 and object+0x28. The matching ZH
// BridgeBehavior::onDie source is semantic donor evidence; the target owner
// remains address-derived. The helper is BridgeBehavior::handleObjectsOnBridgeOnDie
// (BridgeBehaviorHandleObjectsOnBridgeOnDie.cpp).

enum ObjectID
{
	Rva004581FDInvalidObjectID = 0
};

enum BridgeTowerType
{
	Rva004581FDBridgeTower0 = 0
};

enum DamageType
{
	Rva004581FDDamageType0 = 0
};

enum DeathType
{
	Rva004581FDDeathType0 = 0
};

class Object
{
public:
	void kill(DamageType damageType, DeathType deathType);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class BridgeBehaviorInterfaceView
{
public:
	virtual ~BridgeBehaviorInterfaceView();
	virtual ObjectID getTowerID(BridgeTowerType towerType) = 0;
};

class BridgeBehavior
{
	friend class Rva004581FD;
protected:
	void handleObjectsOnBridgeOnDie();
};

class DamageInfo;

class Rva004581FD
{
public:
	virtual void onDie(const DamageInfo *damageInfo);
};

void Rva004581FD::onDie(const DamageInfo *)
{
	int towerType = 0;
	BridgeBehaviorInterfaceView *bridge =
		(BridgeBehaviorInterfaceView *)((char *)this - 8);
	while (towerType < 4)
	{
		ObjectID id = bridge->getTowerID((BridgeTowerType)towerType);
		Object *tower = TheGameLogic->findObjectByID(id);
		if (tower)
			tower->kill((DamageType)8, (DeathType)0);
		++towerType;
	}
	((BridgeBehavior *)((char *)this - 0x28))->handleObjectsOnBridgeOnDie();
	*(unsigned int *)((char *)this + 0xDC) =
		*(unsigned int *)((char *)TheGameLogic + 0x40);
}
