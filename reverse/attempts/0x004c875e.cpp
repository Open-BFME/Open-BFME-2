// ?doSpecialPowerAtObject@RepairSpecialPower@@UAEXPAVObject@@I@Z
// partial score=0.95 date=2026-10-04
// cl: /O1 /MD /GX /arch:SSE
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
enum ObjectID
{
	INVALID_ID = 0
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};
class ThingTemplate
{
public:
	bool isKindOf108Bit7() const { return (m_kindOf[0] & 0x80) != 0; }
	bool isKindOf109Bit6() const { return (m_kindOf[1] & 0x40) != 0; }
private:
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf[4]; // +0x108
};
class Object;
class AICommandInterface
{
public:
	void rva0036F19B(Object *victim, CommandSourceType cmdSource);
};
class AIUpdateInterface
{
public:
	AICommandInterface *getCommandInterface() { return &m_commandInterface; }
private:
	unsigned char m_pad00[0x20];
	AICommandInterface m_commandInterface; // +0x20
};
class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() { return m_ai; }
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai; // +0x258
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

};
extern GameLogic *TheGameLogic;

class ModuleData;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};
class SpecialPowerModuleInterface
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s0A() = 0;
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options) = 0;
};
class SpecialPowerModule : public ModuleBase, public BehaviorModuleInterface,
	public SpecialPowerModuleInterface
{
};
class RepairSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);
};

void RepairSpecialPower::doSpecialPowerAtObject(Object *obj, unsigned int options)
{
	Object *self = m_object;
	if (self->getTemplate()->isKindOf109Bit6() && obj && obj->getTemplate()->isKindOf108Bit7())
	{
		AIUpdateInterface *ai = self->getAI();
		if (ai)
			ai->getCommandInterface()->rva0036F19B(TheGameLogic->findObjectByID(obj->getID()), CMD_FROM_PLAYER);
	}
}
