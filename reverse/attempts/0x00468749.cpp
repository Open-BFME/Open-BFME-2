// ?update@TransportContain@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.995 date=2026-10-09
// ?update@TransportContain@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.995 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?update@TransportContain@@UAE?AW4UpdateSleepTime@@XZ, retail 0x00468749,
// 392 bytes: the update slot of TransportContain's +0x10 UpdateModuleInterface
// (this-0x10 is the module; WB 0x0115B1B0, BitFlags<591> test inlined). The
// Zero Hour body (TransportContain.cpp update) with BFME2 deltas:
//  - the payload is created when module data byte +0x150 is set and the logic
//    frame (TheGameLogic +0x40) has reached the frame at module +0x108, through
//    primary vtable slot 29 (createPayload, 0x004670D6);
//  - the health-regeneration heal of every contained object whose body is hurt
//    (contained list via the Object's contain module at +0x250, its slot 70;
//    body at +0x254, slots 4/6 health/max) goes through the rowed
//    Object::attemptHealing 0x0028FE55 with max * regen * seconds-per-frame *
//    0.01 (0x00DBA4F8 times the 0.01f literal);
//  - UpdateUpgradeCreationTriggers (0x00468045) runs;
//  - when the model-condition bit 61 (Object flags +0x110 bit 29) differs from
//    the byte at module +0x10C, the byte follows it and bit 89 (+0x114 bit 25)
//    of every contained object is set or cleared with the rowed model-condition
//    notifier 0x0028AE6D;
//  - OpenContain::update (0x004640BE) provides the result, followed by primary
//    vtable slot 30.
// Names: update and createPayload come from Zero Hour / the sibling 0x004670D6;
// the remaining labels are by address.
#define V(n) virtual void slot##n();

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class Object;

class BodyModuleInterface
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual float getHealth();
	virtual void s05();
	virtual float getMaxHealth();
};

struct TransportContainListNode
{
	TransportContainListNode *m_next;
	TransportContainListNode *m_prev;
	Object *m_data;
};

struct TransportContainList
{
	TransportContainListNode *m_head;
};

struct TransportContainItems
{
	void *m_lock;
	const TransportContainList *m_list;
};

class ContainModuleInterface
{
public:
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V10(1) V10(2) V10(3) V10(4) V10(5)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	virtual TransportContainItems getContainedItems();
#undef V10
};

struct TransportContainModelFlags
{
	unsigned m_bits[19];
	__forceinline unsigned test(unsigned i) const { return m_bits[i >> 5] & (1u << (i & 31)); }
	__forceinline void set(unsigned i) { m_bits[i >> 5] |= 1u << (i & 31); }
	__forceinline void reset(unsigned i) { m_bits[i >> 5] &= ~(1u << (i & 31)); }
};

class Object
{
public:
	void attemptHealing(float amount, const Object *source);
	void rva0028AE6D();
	unsigned char m_pad00[0x10C];
	TransportContainModelFlags m_modelFlags;
	unsigned char m_pad158[0x250 - 0x158];
	ContainModuleInterface *m_contain;
	BodyModuleInterface *m_body;
};

class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;
extern float g_secondsPerLogicFrame;

struct TransportContainModuleDataView
{
	unsigned char m_pad00[0xA8];
	float m_healthRegen;
	unsigned char m_padAC[0x150 - 0xAC];
	bool m_createsPayload;
};


class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const void *m_moduleData;			// +0x04
	Object *m_object;					// +0x08
};

struct BehaviorModuleInterface { virtual void f0C(); };

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class Rva004640BE : public UpdateModuleInterface
{
public:
	int rva004640BE();
};

class TransportContain : public BehaviorModule, public BehaviorModuleInterface, public Rva004640BE
{
public:
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V10(1) V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28)
#undef V10
	virtual void createPayload();		// slot 29 (0x004670D6)
	virtual void slot30();
	virtual UpdateSleepTime update();
	void UpdateUpgradeCreationTriggers();	// 0x00468045
private:
	unsigned char m_pad14[0x108 - 0x14];
	unsigned int m_payloadFrame;		// +0x108
	bool m_hiddenState;					// +0x10C
};

UpdateSleepTime TransportContain::update()
{
	const TransportContainModuleDataView *md = (const TransportContainModuleDataView *)m_moduleData;
	if (md->m_createsPayload && TheGameLogic->m_frame >= m_payloadFrame)
		createPayload();

	if (md->m_healthRegen != 0.0f)
	{
		ContainModuleInterface *contain = m_object->m_contain;
		if (contain)
		{
			TransportContainItems items = contain->getContainedItems();
			TransportContainListNode *head = items.m_list->m_head;
			for (TransportContainListNode *node = head->m_next; node != items.m_list->m_head;)
			{
				Object *object = node->m_data;
				node = node->m_next;
				BodyModuleInterface *body = object->m_body;
				if (body->getHealth() < body->getMaxHealth())
				{
					float regen = body->getMaxHealth();
					regen *= md->m_healthRegen;
					regen *= g_secondsPerLogicFrame;
					regen *= 0.01f;
					object->attemptHealing(regen, m_object);
				}
			}
		}
	}

	UpdateUpgradeCreationTriggers();

	bool changed = false;
	bool hidden = (m_object->m_modelFlags.test(61) != 0);
	if (m_hiddenState && !hidden)
	{
		m_hiddenState = false;
		changed = true;
	}
	else if (!m_hiddenState && hidden)
	{
		m_hiddenState = true;
		changed = true;
	}
	if (changed)
	{
		ContainModuleInterface *contain = m_object->m_contain;
		if (contain)
		{
			TransportContainItems items = contain->getContainedItems();
			TransportContainListNode *head = items.m_list->m_head;
			for (TransportContainListNode *node = head->m_next; node != items.m_list->m_head; node = node->m_next)
			{
				Object *object = node->m_data;
				if (!object)
					continue;
				if (m_hiddenState)
				{
					if (object->m_modelFlags.test(89))
						continue;
					object->m_modelFlags.set(89);
				}
				else
				{
					if (!object->m_modelFlags.test(89))
						continue;
					object->m_modelFlags.reset(89);
				}
				object->rva0028AE6D();
			}
		}
	}
	UpdateSleepTime result = (UpdateSleepTime)Rva004640BE::rva004640BE();
	slot30();
	return result;
}
