// ?rva0049C93F@Rva0049C93F@@QAEHXZ
// partial score=0.9 date=2026-10-07
// ?rva0049C93F@Rva0049C93F@@QAEHXZ @0x0049C93F 240B.
// Slot 0 of the vtable stored at GiveUpgradeUpdate+0x10 (VA 0x00C51214).
// ecx arrives already adjusted. Parent fields sit at negative offsets.
// State 2 keeps the delivery; any other state clears +0x89 and forwards
// slot 0x34. The +0x88 countdown subtracts the +0x04 object's +0xDC.

enum ObjectID
{
	INVALID_OBJECTID = 0
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class Drawable
{
public:
	char m_pad00[0xb0];
	int m_bitsB0;
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
};

template <int N>
class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <>
class VSlots<0>
{
};

class AIUpdate : public VSlots<143>
{
public:
	virtual int state143() = 0;

	char m_pad04[0x20 - 4];
	AICommandInterface m_commands;
};

class Object : public Thing
{
public:
	char m_pad00[0x258];
	AIUpdate *m_ai;
	char m_pad25C[0x438 - 0x25c];
	unsigned char m_b438;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void destroyObject(Object *object);
};

extern GameLogic *TheGameLogic;

class Rva0049C93FClock
{
public:
	char m_pad00[0xdc];
	float m_delta;
};

class GiveUpgradeUpdate
{
public:
	void GetDeliveryTarget();
};

class Rva0044E6AE
{
public:
	void rva0044E6AE();
};

class Rva0049C6E1
{
public:
	bool rva0049C6E1(Object *object);
};

class Rva0049C93F
{
public:
	int rva0049C93F();
	int rva00451FA2();

private:
	char m_pad00[0x30];
	ObjectID m_id;
	char m_pad34[0x78 - 0x34];
	bool m_flag88;
	bool m_flag89;
	float m_value;
};

static GiveUpgradeUpdate *parentOf(Rva0049C93F *self)
{
	return (GiveUpgradeUpdate *)((char *)self - 0x10);
}

int Rva0049C93F::rva0049C93F()
{
	Object *owner = *(Object **)((char *)this - 8);
	AIUpdate *ai = owner->m_ai;
	int state = ai->state143();
	int code = rva00451FA2();
	if (state != 2)
	{
		m_flag89 = false;
		((Rva0044E6AE *)parentOf(this))->rva0044E6AE();
		return code;
	}

	if (m_flag89)
		parentOf(this)->GetDeliveryTarget();

	if (m_flag88)
		goto timer;

	if (Object *found = TheGameLogic->findObjectByID(m_id))
	{
		if ((found->m_b438 & 1) == 0 &&
			((Rva0049C6E1 *)parentOf(this))->rva0049C6E1(found))
			goto recheck;
	}

	m_flag89 = false;
	((Rva0044E6AE *)parentOf(this))->rva0044E6AE();
	ai->m_commands.aiIdle(CMD_FROM_AI);
	return code;

recheck:
	if (!m_flag88)
		goto done;
timer:
	m_value -= (*(Rva0049C93FClock **)((char *)this - 0xc))->m_delta;
	owner = *(Object **)((char *)this - 8);
	if (m_value < 0.0f)
	{
		TheGameLogic->destroyObject(owner);
		m_flag88 = false;
		m_value = 0.0f;
	}
	else if (Drawable *drawable = owner->getDrawable())
		drawable->m_bitsB0 = *(int *)&m_value;
done:
	if (!m_flag89)
		return code;
	return 1;
}
