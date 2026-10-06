// cl: /DNDEBUG /MD
//
// ?getBridgeScaffoldBehaviorInterfaceFromObject@BridgeScaffoldBehavior@@SAPAVBridgeScaffoldBehaviorInterface@@PAVObject@@@Z,
// retail 0x004582F3, 41 bytes. Dedicated TU.
// In the BridgeScaffoldBehavior.cpp code range, immediately after
// reverseMotion (0x004582CB + 40) and before the BridgeScaffoldBehavior ctor
// (0x0045831C). Same ZH shape as getBridgeBehaviorInterfaceFromObject
// (0x00456556, slot 12) and getBridgeTowerBehaviorInterfaceFromObject
// (0x0045880B, slot 13), with no template test: reject a null object, then scan
// the BehaviorModule array at +0x244 and ask each module's +0x0C interface
// sub-object for the scaffold interface at slot 14 (+0x38). Called from the
// Dozer/Worker scaffolding paths.

class BridgeScaffoldBehaviorInterface;

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
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual BridgeScaffoldBehaviorInterface *getBridgeScaffoldBehaviorInterface() = 0;
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

	char m_pad[0x244];
	BehaviorModule **m_modules244;
};

class BridgeScaffoldBehavior
{
public:
	static BridgeScaffoldBehaviorInterface *getBridgeScaffoldBehaviorInterfaceFromObject(Object *obj);
};

// ?getBridgeScaffoldBehaviorInterfaceFromObject@BridgeScaffoldBehavior@@SAPAVBridgeScaffoldBehaviorInterface@@PAVObject@@@Z
BridgeScaffoldBehaviorInterface *BridgeScaffoldBehavior::getBridgeScaffoldBehaviorInterfaceFromObject(Object *obj)
{
	// sanity
	if (obj == 0)
		return 0;

	// get the bridge scaffold behavior module
	BehaviorModule **bmi;
	BridgeScaffoldBehaviorInterface *bbi;
	for (bmi = obj->getBehaviorModules(); *bmi; ++bmi)
	{
		bbi = (*bmi)->getBridgeScaffoldBehaviorInterface();
		if (bbi)
			return bbi;
	}

	// interface not found
	return 0;
}
