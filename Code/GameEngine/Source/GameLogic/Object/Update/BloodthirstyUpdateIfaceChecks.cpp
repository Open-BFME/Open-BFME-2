// cl: /O1 /DNDEBUG /MD
//
// BloodthirstyUpdate +0x20 interface override (vtable 0x00C3EFC4, installed
// by the matched ctor 0x0044E0AA and dtor 0x0044DFE0). Overrides of a
// non-primary base take the +0x20 subobject this: the module data (+0x04) is
// [this-0x1C], the Object (+0x08) [this-0x18], m_bestTargetID (+0x24, the
// member name the matched ctor carries from the BFME 1 donor) [this+4].
// Names by address; the slot names are not established.
//
// It resolves the candidate through the rowed Object::rva002931F5(false),
// fetches its rowed 0x0028C1A9 interface (slots 6 and 7 read a state and an
// owner ID), and runs the module data's +0x08 filter (rowed
// Rva2225E0Filter::accepts 0x00362437) against our controlling player.
// Retail 0x0044E12F (138 bytes), slot 2: also requires the candidate's AI
// (+0x258) slot-110 predicate when it has an AI; true when the interface's
// owner ID is zero or ours and its state is zero. The BFME 1 analog
// (0x00287130, banked there at 0.78 as Gen_00287130::bfmeAccept) has the same
// flow.
// Slot 3 (0x0044E1B9) is banked in reverse/attempts/.
// Retail 0x0044E222 (138 bytes), slot 8: for a victim whose resolved
// Object passes slot 3, count it (+0x2C); the first one sets model
// condition 0x40 on it; then the Object our own resolves to scores it
// through 0x00294C1A (experience-tracker gated, Object +0x264) with the
// module data's +0x0C value, and when the victim's +0x250 module answers 1
// to its slot 69 query, slot 1 runs.
// Retail 0x0044E4A9 (138 bytes), slot 1: releases the best target (+0x24)
// when it still exists, has the 0x0028C1A9 interface and passes slot 3:
// interface slot 5 with 0, best target and kill count cleared, status 0x41
// cleared on our Object through 0x00346C53, and on the target: model
// condition 0x40 cleared (rowed 0x00293955), status 0x4A cleared through both
// setStatus and 0x00346C53, and its AI idled from CMD_FROM_AI.
// Retail 0x0044E533 (119 bytes), update: slot 0 of the +0x10
// UpdateModuleInterface table 0x00C3EFEC. While the ID at +0x28 is set and
// that Object is gone, flagged (+0x438 bit 0) or lacks status 0x41, interface
// slot 5 runs with 0 and our own Object gets the same release as the target
// above; sleeps 2 * g_009BA4E4 + 1 (the logic frame rate) either way.
//
// 0x00346C53 (pinned by address): the setStatus twin (same mask build via
// 0x0023DA79) that hands the mask to 0x00293D3B instead of 0x0028CDEB.
class Player;
enum ObjectID
{
	INVALID_ID = 0
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_41 = 0x41,
	OBJECT_STATUS_4A = 0x4a
};
enum CommandSourceType
{
	CMD_FROM_AI = 2
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};
extern const int g_009BA4E4;
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
};

#define VSLOTS10(P) \
	virtual void P##0(); virtual void P##1(); virtual void P##2(); \
	virtual void P##3(); virtual void P##4(); virtual void P##5(); \
	virtual void P##6(); virtual void P##7(); virtual void P##8(); \
	virtual void P##9()

class AIUpdateInterface
{
public:
	VSLOTS10(a0); VSLOTS10(a1); VSLOTS10(a2); VSLOTS10(a3); VSLOTS10(a4);
	VSLOTS10(a5); VSLOTS10(a6); VSLOTS10(a7); VSLOTS10(a8); VSLOTS10(a9);
	VSLOTS10(aA);
	virtual bool rvaSlot110();
	AICommandInterface *getCommandInterface() { return &m_commandInterface; }
private:
	unsigned char m_pad04[0x20 - 0x04];
	AICommandInterface m_commandInterface; // +0x20
};

class Rva0028C1A9Interface
{
public:
	virtual void i0();
	virtual void i1();
	virtual void i2();
	virtual void i3();
	virtual void i4();
	virtual void release(int arg);
	virtual int getState();
	virtual ObjectID getOwnerID();
};

enum ModelConditionFlagType
{
	MODELCONDITION_40 = 0x40
};
class Rva250Module
{
public:
	VSLOTS10(m0); VSLOTS10(m1); VSLOTS10(m2); VSLOTS10(m3); VSLOTS10(m4);
	VSLOTS10(m5);
	virtual void m60(); virtual void m61(); virtual void m62();
	virtual void m63(); virtual void m64(); virtual void m65();
	virtual void m66(); virtual void m67(); virtual void m68();
	virtual int rvaSlot69(int arg);
};
class Object
{
public:
	void rva00293A05(ModelConditionFlagType flag);
	void rva00293955(ModelConditionFlagType flag);
	void setStatus(ObjectStatusTypes status, bool set);
	void rva00346C53(ObjectStatusTypes status, bool set);
	bool testStatus(ObjectStatusTypes status) const;
	bool testBfme438Bit0() const { return (m_438 & 1) != 0; }
	void rva00294C1A(Object *victim, bool flag, float amount);
	Rva250Module *getRva250() { return m_250; }
	Object *rva002931F5(bool checkProducer);
	void *rva0028C1A9() const;
	Player *getControllingPlayer() const;
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() { return m_ai; }
private:
	unsigned char m_pad00[0x74];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x250 - 0x78];
	Rva250Module *m_250; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned char m_438; // +0x438
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

struct Rva2225E0Filter
{
	bool accepts(Object *value, Player *player);
};

struct BloodthirstyUpdateModuleData
{
	unsigned char m_pad00[0x08];
	Rva2225E0Filter m_filter; // +0x08
	unsigned char m_pad09[0x0C - 0x09];
	float m_0C; // +0x0C
};

struct B00 { virtual void f00(); BloodthirstyUpdateModuleData *m_moduleData; Object *m_object; };
struct B0C { virtual void f0C(); };
struct B10 { virtual UpdateSleepTime update() = 0; unsigned char m_pad[12]; };
class Iface20
{
public:
	virtual void s00();
	virtual void rva0044E4A9() = 0;
	virtual bool rva0044E12F(Object *obj) = 0;
	virtual bool rva0044E1B9(Object *obj);
	virtual void s04();
	virtual void s05(int arg);
	virtual void s06();
	virtual void s07();
	virtual void rva0044E222(Object *victim) = 0;
};
class BloodthirstyUpdate : public B00, public B0C, public B10, public Iface20
{
public:
	virtual bool rva0044E12F(Object *obj);
	virtual void rva0044E222(Object *victim);
	virtual void rva0044E4A9();
	virtual UpdateSleepTime update();
private:
	ObjectID m_bestTargetID; // +0x24
	ObjectID m_28; // +0x28
	int m_kills; // +0x2C
};

bool BloodthirstyUpdate::rva0044E12F(Object *obj)
{
	Object *candidate = obj->rva002931F5(false);
	BloodthirstyUpdateModuleData *data = m_moduleData;
	if (candidate == 0)
		return false;
	else
	{
		AIUpdateInterface *ai = candidate->getAI();
		if (ai != 0)
		{
			if (!ai->rvaSlot110())
				return false;
		}
		Rva0028C1A9Interface *iface = (Rva0028C1A9Interface *)candidate->rva0028C1A9();
		if (iface == 0)
			return false;
		Object *self = m_object;
		if (!data->m_filter.accepts(candidate, self->getControllingPlayer()))
			return false;
		if (iface->getOwnerID() == 0 || iface->getOwnerID() == self->getID())
		{
			bool idle = (iface->getState() == 0);
			return idle;
		}
		return false;
	}
}

void BloodthirstyUpdate::rva0044E222(Object *victim)
{
	Object *self = m_object;
	if (victim == 0)
		return;
	Object *resolved = victim->rva002931F5(false);
	if (resolved == 0)
		return;
	if (!rva0044E1B9(victim))
		return;
	++m_kills;
	if (m_kills == 1)
		resolved->rva00293A05(MODELCONDITION_40);
	self->rva002931F5(false)->rva00294C1A(victim, true, m_moduleData->m_0C);
	Rva250Module *module = resolved->getRva250();
	if (module && module->rvaSlot69(0) == 1)
		rva0044E4A9();
}

void BloodthirstyUpdate::rva0044E4A9()
{
	Object *self = m_object;
	Object *target = TheGameLogic->findObjectByID(m_bestTargetID);
	if (target == 0)
		return;
	Rva0028C1A9Interface *iface = (Rva0028C1A9Interface *)target->rva0028C1A9();
	if (iface == 0)
		return;
	if (!rva0044E1B9(target))
		return;
	iface->release(0);
	m_bestTargetID = INVALID_ID;
	m_kills = 0;
	self->rva00346C53(OBJECT_STATUS_41, false);
	target->rva00293955(MODELCONDITION_40);
	target->setStatus(OBJECT_STATUS_4A, false);
	target->rva00346C53(OBJECT_STATUS_4A, false);
	target->getAI()->getCommandInterface()->aiIdle(CMD_FROM_AI);
}

UpdateSleepTime BloodthirstyUpdate::update()
{
	if (m_28 != 0)
	{
		Object *other = TheGameLogic->findObjectByID(m_28);
		if (other == 0 || other->testBfme438Bit0() || !other->testStatus(OBJECT_STATUS_41))
		{
			s05(0);
			Object *self = m_object;
			self->rva00293955(MODELCONDITION_40);
			self->setStatus(OBJECT_STATUS_4A, false);
			self->rva00346C53(OBJECT_STATUS_4A, false);
			self->getAI()->getCommandInterface()->aiIdle(CMD_FROM_AI);
		}
	}
	return (UpdateSleepTime)(g_009BA4E4 * 2 + 1);
}
