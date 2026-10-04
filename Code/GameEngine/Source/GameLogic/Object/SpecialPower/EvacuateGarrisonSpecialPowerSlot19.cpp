// cl: /O1 /DNDEBUG /MD
//
// EvacuateGarrisonSpecialPower primary slot 19 (vtable 0x00C5FC28), retail
// 0x004CDCB4 (78 bytes): the SpecialAbilityUpdate slot-19 base 0x00451B92
// (the slot-19 entry of 26 special-ability vtables, SpecialAbilityUpdate's own
// 0x00C3FBA8 among them; pinned by address), then, when the Object has an AI
// and the Object recorded at +0x40 still exists, status 0x5D is set on our
// Object and the AI gets the rowed AICommandInterface command 0x0036EBB8 on
// that Object, from the command source its slot 143 reports. Named by the
// base's address.
enum ObjectID
{
	INVALID_ID = 0
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_5D = 0x5d
};
class Object;
class AICommandInterface
{
public:
	void rva0036EBB8(Object *target, CommandSourceType cmdSource);
};
#define VSLOTS10(P) \
	virtual void P##0(); virtual void P##1(); virtual void P##2(); \
	virtual void P##3(); virtual void P##4(); virtual void P##5(); \
	virtual void P##6(); virtual void P##7(); virtual void P##8(); \
	virtual void P##9()
class AIUpdateInterface
{
public:
	VSLOTS10(a00); VSLOTS10(a01); VSLOTS10(a02); VSLOTS10(a03); VSLOTS10(a04);
	VSLOTS10(a05); VSLOTS10(a06); VSLOTS10(a07); VSLOTS10(a08); VSLOTS10(a09);
	VSLOTS10(a10); VSLOTS10(a11); VSLOTS10(a12); VSLOTS10(a13);
	virtual void a140(); virtual void a141(); virtual void a142();
	virtual CommandSourceType rvaSlot143();
	AICommandInterface *getCommandInterface() { return &m_commandInterface; }
private:
	unsigned char m_pad04[0x20 - 0x04];
	AICommandInterface m_commandInterface;	// +0x20
};
class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
	AIUpdateInterface *getAI() { return m_ai; }
private:
	unsigned char m_pad000[0x258];
	AIUpdateInterface *m_ai;	// +0x258
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
class ModuleData;
class SpecialAbilityUpdate
{
public:
	virtual ~SpecialAbilityUpdate();
	VSLOTS10(s0);
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
	virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
	virtual void rva00451B92();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	unsigned char m_pad0C[0x40 - 0x0C];
	ObjectID m_40;			// +0x40
};
class EvacuateGarrisonSpecialPower : public SpecialAbilityUpdate
{
public:
	virtual void rva00451B92();
};
void EvacuateGarrisonSpecialPower::rva00451B92()
{
	SpecialAbilityUpdate::rva00451B92();
	Object *self = m_object;
	AIUpdateInterface *ai = self->getAI();
	if (ai == 0)
		return;
	Object *target = TheGameLogic->findObjectByID(m_40);
	if (target == 0)
		return;
	self->setStatus(OBJECT_STATUS_5D, true);
	ai->getCommandInterface()->rva0036EBB8(target, ai->rvaSlot143());
}
