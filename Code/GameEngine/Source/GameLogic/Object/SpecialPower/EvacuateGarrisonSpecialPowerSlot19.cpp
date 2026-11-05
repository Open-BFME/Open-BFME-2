// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// EvacuateGarrisonSpecialPower::finishAbility, primary slot 19 (vtable
// 0x00C5FC28), retail 0x004CDCB4 (78 bytes): the base
// SpecialAbilityUpdate::finishAbility 0x00451B92 (the slot-19 entry of 26
// special-ability vtables, SpecialAbilityUpdate's own 0x00C3FBA8 among them;
// 23 sibling tables name slot 19 finishAbility), then, when the Object has an AI
// and the Object recorded at +0x40 still exists, status 0x5D is set on our
// Object and the AI gets the rowed AICommandInterface command 0x0036EBB8 on
// that Object, from the command source its slot 143 reports.
#include "../../../Common/GameLogicObjectLookupView.h"
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_5D = 0x5d
};
class Object;
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
#define VSLOTS10(P) \
	virtual void P##0(); virtual void P##1(); virtual void P##2(); \
	virtual void P##3(); virtual void P##4(); virtual void P##5(); \
	virtual void P##6(); virtual void P##7(); virtual void P##8(); \
	virtual void P##9()
#include "../object.h"
extern GameLogic *TheGameLogic;
class ModuleData;
#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"
class EvacuateGarrisonSpecialPower : public SpecialAbilityUpdate
{
public:
	virtual void finishAbility();
};
void EvacuateGarrisonSpecialPower::finishAbility()
{
	SpecialAbilityUpdate::finishAbility();
	Object *self = m_object;
	AIUpdateInterface *ai = self->getAI();
	if (ai == 0)
		return;
	Object *target = TheGameLogic->findObjectByID(m_targetID);
	if (target == 0)
		return;
	self->setStatus(OBJECT_STATUS_5D, true);
	ai->rva0036EBB8(target, ai->vslot143());
}
