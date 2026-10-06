// cl: /O1 /DNDEBUG /MD
//
// ?getBridgeBehaviorInterfaceFromObject@BridgeBehavior@@SAPAVBridgeBehaviorInterface@@PAVObject@@@Z,
// retail 0x00456556, 41 bytes. Dedicated TU.
// Sits between Bridge::setTowerObjectID (0x00456547) and BridgeBehavior::setTower
// (0x0045657F) in the BridgeBehavior.cpp code range; called by the Dozer/Worker
// scaffolding and repair paths. Like Object::getSpawnBehaviorInterface (0x0028BCD4)
// BFME2 scans the BehaviorModule array at +0x244 (not the ZH +0x18C behaviors
// array) and asks each module's +0x0C interface sub-object for the bridge
// interface at slot 12 (+0x30).

class BridgeBehaviorInterface;

class BehaviorModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual BridgeBehaviorInterface *getBridgeBehaviorInterface() = 0;
};

class BfmeObjectModule
{
public:
	virtual void slot0() = 0;

private:
	unsigned int m_data[2];
};

class BehaviorModule : public BfmeObjectModule, public BehaviorModuleInterface
{
};

class Object
{
public:
	BehaviorModule **getBehaviorModules() const { return m_modules244; }

private:
	char m_pad[0x244];
	BehaviorModule **m_modules244;
};

class BridgeBehavior
{
public:
	static BridgeBehaviorInterface *getBridgeBehaviorInterfaceFromObject(Object *obj);
};

// ?getBridgeBehaviorInterfaceFromObject@BridgeBehavior@@SAPAVBridgeBehaviorInterface@@PAVObject@@@Z
BridgeBehaviorInterface *BridgeBehavior::getBridgeBehaviorInterfaceFromObject(Object *obj)
{
	// sanity
	if (obj == 0)
		return 0;

	// get the bridge behavior module
	BehaviorModule **bmi;
	BridgeBehaviorInterface *bbi;
	for (bmi = obj->getBehaviorModules(); *bmi; ++bmi)
	{
		bbi = (*bmi)->getBridgeBehaviorInterface();
		if (bbi)
			return bbi;
	}

	// interface not found
	return 0;
}
