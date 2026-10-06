// cl: /DNDEBUG /MD
//
// ??0BodyModule@@QAE@PAVThing@@PBVModuleData@@@Z @0x004BD7FD 62B.
// Common base of InactiveBody ctor 0x4BD8BD and ActiveBody ctor 0x4BF6A1
// (both call here; both derive from BodyModule per ZH BodyModule.h).
// Retail calls BehaviorModule ctor 0x253330 then installs three vtables
// (+0/+0xC/+0x10) and the 1.0f damage scalar at +0x14, matching the ZH
// inline BodyModule : BehaviorModule, BodyModuleInterface with
// m_damageScalar(1.0f). 1.0f loads from the shared literal 0x7BB8D8.

class Thing;
class ModuleData;

class ObjectModule
{
public:
	virtual void objectAnchor();
	const ModuleData *m_moduleData;
	void *m_object;
};

class BehaviorIface
{
public:
	virtual void behaviorIfaceAnchor();
};

class BehaviorModule : public ObjectModule, public BehaviorIface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class BodyModuleInterface
{
public:
	virtual void bodyAnchor() = 0;
};

class BodyModule : public BehaviorModule, public BodyModuleInterface
{
public:
	BodyModule(Thing *thing, const ModuleData *moduleData);

private:
	float m_damageScalar;
};

BodyModule::BodyModule(Thing *thing, const ModuleData *moduleData)
	: BehaviorModule(thing, moduleData), m_damageScalar(1.0f)
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?behaviorIfaceAnchor@BehaviorIface@@UAEXXZ=?getDie@DieModule@@UAEPAVDieModuleInterface@@XZ")
#pragma comment(linker, "/alternatename:?objectAnchor@ObjectModule@@UAEXXZ=??_GRva004BD763@@UAEPAXI@Z")
