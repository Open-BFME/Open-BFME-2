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
class DamageInfo;
class Thing;
class ModuleData;

#include "../object.h"

#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/BodyModule.h"

class BodyModule : public BehaviorModule, public BodyModuleInterface
{
public:
	BodyModule(Thing *thing, const ModuleData *moduleData);
	virtual ~BodyModule();
	// BehaviorModuleInterface slot 0 (retail VA 0x00C5AD78): BodyModule's override,
	// rowed at 0x002533D3 (BodyModuleCtor.cpp).
	virtual BodyModuleInterface *getBody();
private:
	float m_damageScalar;
};

class InactiveBody : public BodyModule
{
public:
	InactiveBody(Thing *thing, const ModuleData *moduleData);
	virtual void attemptDamage(DamageInfo *damageInfo);
private:
	bool m_dieCalled;
public:
	// retail slot 4: the rowed ?getModuleNameKey@InactiveBody@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
public:
	// retail vftable slot: the rowed override
	virtual void attemptHealing(DamageInfo *);
};

InactiveBody::InactiveBody(Thing *thing, const ModuleData *moduleData)
	: BodyModule(thing, moduleData), m_dieCalled(false)
{
	getObject()->setEffectivelyDead(true);
}
