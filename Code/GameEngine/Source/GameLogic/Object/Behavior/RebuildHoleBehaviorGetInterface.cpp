// cl: /DNDEBUG /MD /EHsc
// ?getRebuildHoleBehaviorInterfaceFromObject@RebuildHoleBehavior@@SAPAVRebuildHoleBehaviorInterface@@PAVObject@@@Z @0x004831CB 115B. Static RebuildHoleBehavior
// NameKey plus behavior-module scan at +0x244 via slot 0x10 tag compare, returns module+0x24.
// Evidence: "RebuildHoleBehavior" literal with TheNameKeyGenerator row 0x00148E1A; callers
// 0x0031C0EE 0x00486908 0x00507017; ZH donor RebuildHoleBehavior.cpp getRebuildHoleBehaviorInterfaceFromObject
// loops getBehaviorModules; BFME2 uses NameKey tag at slot 0x10 per retail.
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

class RebuildHoleBehaviorInterface
{
public:
	virtual void dummy() = 0;
};

class BehaviorModule
{
public:
	virtual void s00() = 0;
	virtual void s04() = 0;
	virtual void s08() = 0;
	virtual void s0C() = 0;
	virtual NameKeyType getModuleTag() = 0;
};

class Object
{
public:
	BehaviorModule **getBehaviorModules() { return m_behaviorModules; }

private:
	char m_pad[0x244];
	BehaviorModule **m_behaviorModules;
};

class RebuildHoleBehavior
{
public:
	static RebuildHoleBehaviorInterface *getRebuildHoleBehaviorInterfaceFromObject(Object *obj);
};

RebuildHoleBehaviorInterface *RebuildHoleBehavior::getRebuildHoleBehaviorInterfaceFromObject(Object *obj)
{
	static NameKeyType key = TheNameKeyGenerator->nameToKey("RebuildHoleBehavior");
	for (BehaviorModule **i = obj->getBehaviorModules(); *i; ++i)
	{
		if ((*i)->getModuleTag() == key)
		{
			BehaviorModule *m = *i;
			if (m)
				return (RebuildHoleBehaviorInterface *)((char *)m + 0x24);
			return 0;
		}
	}
	return 0;
}
