// cl: /MD /GX
//
// RepairSpecialPower::doSpecialPowerAtObject, retail 0x004C875E, 75 bytes:
// slot 11 of the class's +0x10 special-power interface vftable 0x00C5E640
// (the slot InvisibilitySpecialPower's rowed doSpecialPowerAtObject fills), so
// `this` is that subobject and the power's Object is at -0x08. Unlike the
// Zero Hour overrides it does not call the base first. When the power's
// Object has template kindOf byte +0x109 bit 0x40 set and the target has
// kindOf byte +0x108 bit 0x80, the Object's AI (+0x258) gets the matched
// AICommandInterface command 0x0036F19B (its interface at AI +0x20) on the
// target, re-looked-up by ID through TheGameLogic, from CMD_FROM_PLAYER.
// The options argument is unused.
#include "../../../Common/GameLogicObjectLookupView.h"
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};
#include "../../../../Include/Common/ThingTemplate.h"
class Object;
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	static __forceinline AIUpdateInterface *getAI(const Object *object) { return object->m_ai; }
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x74 - 0x08];
	// Read as a member: an inline getID() makes cl 7.1 load the ID into a
	// register before TheGameLogic, where retail pushes it from memory.
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai; // +0x258
};
extern GameLogic *TheGameLogic;

class Thing;
class ModuleData;
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/SpecialPowerModule.h"
class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	SpecialPowerModule(Thing *thing, const ModuleData *moduleData);
	virtual ~SpecialPowerModule();
};
class RepairSpecialPower : public SpecialPowerModule
{
public:
	RepairSpecialPower(Thing *thing, const ModuleData *moduleData);
protected:
	virtual ~RepairSpecialPower();
public:
	virtual NameKeyType getModuleNameKey() const;
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);
};

void RepairSpecialPower::doSpecialPowerAtObject(Object *obj, unsigned int options)
{
	Object *self = m_object;
	if (((self->getTemplate()->m_kindof[0] & (1U << 14)) != 0) && obj && ((obj->getTemplate()->m_kindof[0] & (1U << 7)) != 0))
	{
		AIUpdateInterface *ai = Object::getAI(self);
		if (ai)
			ai->rva0036F19B(TheGameLogic->findObjectByID(obj->m_id), CMD_FROM_PLAYER);
	}
}
