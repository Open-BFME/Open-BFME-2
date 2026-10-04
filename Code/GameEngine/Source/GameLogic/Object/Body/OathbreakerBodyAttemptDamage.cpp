// cl: /O1 /DNDEBUG /MD
//
// OathbreakerBody::attemptDamage, retail 0x004C1F71 (90 bytes): slot 0 of the
// class's +0x10 body-module interface table 0x00C5C180, the slot ActiveBody,
// StructureBody, ImmortalBody and RespawnBody fill with 0x004BFE07 (pinned by
// address as ActiveBody::attemptDamage), so `this` is that subobject. Damage
// only lands when its source Object (input +0x08) still exists and has
// kindOf bit 0x113:0x04, judged instead on the source's producer (+0x78) when
// the source has kindOf bit 0x10B:0x02 (and dropped when that producer is
// gone).
enum ObjectID
{
	INVALID_ID = 0
};
class ThingTemplate
{
public:
	bool testKindOf10BBit1() const { return (m_kindOf[0x10B - 0x108] & 0x02) != 0; }
	bool testKindOf113Bit2() const { return (m_kindOf[0x113 - 0x108] & 0x04) != 0; }
private:
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x0C];	// +0x108
};
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
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
class DamageInfo
{
public:
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID;		// +0x08
};
class ModuleData;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};
class BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo) = 0;
};
class BodyModule : public ModuleBase, public BehaviorModuleInterface, public BodyModuleInterface
{
};
class ActiveBody : public BodyModule
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
};
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
	if (source->getTemplate()->testKindOf10BBit1())
	{
		Object *producer = logic->findObjectByID(source->getProducerID());
		if (producer == 0)
			return;
		if (!producer->getTemplate()->testKindOf113Bit2())
			return;
	}
	else if (!source->getTemplate()->testKindOf113Bit2())
		return;
	ActiveBody::attemptDamage(damageInfo);
}
