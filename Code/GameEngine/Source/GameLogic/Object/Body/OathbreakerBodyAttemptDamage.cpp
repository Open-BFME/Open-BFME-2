// cl: /DNDEBUG /MD
//
// OathbreakerBody::attemptDamage, retail 0x004C1F71 (90 bytes): slot 0 of the
// class's +0x10 body-module interface table 0x00C5C180, the slot ActiveBody,
// StructureBody, ImmortalBody and RespawnBody fill with 0x004BFE07 (pinned by
// address as ActiveBody::attemptDamage), so `this` is that subobject. Damage
// only lands when its source Object (input +0x08) still exists and has
// kindOf bit 0x113:0x04, judged instead on the source's producer (+0x78) when
// the source has kindOf bit 0x10B:0x02 (and dropped when that producer is
// gone).
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../Include/Common/ThingTemplate.h"
class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getProducerID() const { return m_producerID; }
private:
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad008[0x78 - 0x08];
	ObjectID m_producerID;		// +0x78
};
extern GameLogic *TheGameLogic;
#include "../../../../Include/GameLogic/Damage.h"
class ModuleData;
#include "../../../../Include/GameLogic/Module/ModuleBase.h"
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/BodyModule.h"
#include "../../../../Include/GameLogic/Module/ActiveBody.h"
class OathbreakerBody : public ActiveBody
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
};
void OathbreakerBody::attemptDamage(DamageInfo *damageInfo)
{
	GameLogic *logic = TheGameLogic;
	Object *source = logic->findObjectByID(damageInfo->m_sourceID);
	if (source == 0)
		return;
	if (((source->getTemplate()->m_kindof[0] & (1U << 25)) != 0))
	{
		Object *producer = logic->findObjectByID(source->getProducerID());
		if (producer == 0)
			return;
		if (!((producer->getTemplate()->m_kindof[2] & (1U << 26)) != 0))
			return;
	}
	else if (!((source->getTemplate()->m_kindof[2] & (1U << 26)) != 0))
		return;
	ActiveBody::attemptDamage(damageInfo);
}
