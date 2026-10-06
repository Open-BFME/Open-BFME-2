// cl: /DNDEBUG /MD /EHsc
//
// ??0InactiveBody@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004BD8BD, 83
// bytes (pinned; instance factory 0x00251375). Zero Hour InactiveBody.cpp
// body: BodyModule(thing, moduleData) (rowed 0x004BD7FD), m_dieCalled(false)
// at +0x18, then getObject()->setEffectivelyDead(true). The callee
// 0x0028D2FB is pinned as Object::setEffectivelyDead from this call: it
// sets or clears the private-status bit at Object+0x438 by its Bool (13
// callers). Retail's unwind map destroys the BodyModule base (0x004BD763)
// in state 0. Base layout as in BodyModuleCtor.cpp.
class Thing;
class ModuleData;

class Object
{
public:
	void setEffectivelyDead(bool dead);
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
	Object *getObject() const { return m_object; }
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
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
	virtual ~BodyModule();
private:
	float m_damageScalar;
};

class InactiveBody : public BodyModule
{
public:
	InactiveBody(Thing *thing, const ModuleData *moduleData);
	virtual void bodyAnchor();
private:
	bool m_dieCalled;
};

InactiveBody::InactiveBody(Thing *thing, const ModuleData *moduleData)
	: BodyModule(thing, moduleData), m_dieCalled(false)
{
	getObject()->setEffectivelyDead(true);
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?behaviorIfaceAnchor@BehaviorIface@@UAEXXZ=?getDie@DieModule@@UAEPAVDieModuleInterface@@XZ")
