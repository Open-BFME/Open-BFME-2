// cl: /O1 /DNDEBUG /MD
//
// ?rva00488AC9@Rva00488AC9@@QAEXPAVObject@@W4CommandSourceType@@@Z @0x00488AC9 81B.
// Slot 20 on the member at +0x3E4 gates a repair check. Slot 12 runs
// when the target has no healing benefactor or it matches holder+0x74.

class Object;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum ObjectID
{
	OID_NONE = 0
};

class ActionManager
{
public:
	bool canRepairObject(const Object *a, const Object *b, CommandSourceType src);
};

extern ActionManager *TheActionManager;

class Object
{
public:
	ObjectID getSoleHealingBenefactor() const;
};

class Rva00488AC9Holder
{
public:
	char m_pad[0x74];
	ObjectID m_id;
};

class Rva00488AC9Slot
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10();
	virtual void s11();
	virtual void s12(int flag, Object *obj);
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual bool s20(Object *obj);
};

class Rva00488AC9
{
public:
	void rva00488AC9(Object *target, CommandSourceType src);

private:
	char m_pad[8];
	Rva00488AC9Holder *m_holder;
	char m_padC[0x3E4 - 0x0C];
	Rva00488AC9Slot m_slot;
};

void Rva00488AC9::rva00488AC9(Object *target, CommandSourceType src)
{
	Rva00488AC9Holder *holder = m_holder;
	Rva00488AC9Slot *slot = &m_slot;
	if (slot->s20(target) == 0)
		return;
	if (TheActionManager->canRepairObject((const Object *)holder, target, src) == 0)
		return;
	ObjectID id = target->getSoleHealingBenefactor();
	if (id == 0 || id == holder->m_id)
		slot->s12(1, target);
}
