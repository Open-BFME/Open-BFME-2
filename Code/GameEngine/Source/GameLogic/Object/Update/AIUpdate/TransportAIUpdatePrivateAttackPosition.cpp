// cl: /O1 /DNDEBUG /MD /EHsc
// ?privateAttackPosition@TransportAIUpdate@@MAEXPBUCoord3D@@HW4CommandSourceType@@@Z @0x004A9279 153B: TransportAIUpdate slot 40 override fanning attack-position to passengers then base.
// ?privateAttackObject@TransportAIUpdate@@MAEXPAVObject@@HW4CommandSourceType@@@Z @0x004A9147 153B and
// ?privateForceAttackObject@TransportAIUpdate@@MAEXPAVObject@@HW4CommandSourceType@@@Z @0x004A91E0 153B: the same
// passenger fan-out for slots 34 and 38 (vtable VA 0x00C53B30/0x00C53B40). Slot 38's passenger call is the rowed
// aiForceAttackObject 0x0036F05A; the base calls 0x0026BCD2/0x0026BEE6 are slots 34/38 of every non-overriding
// AIUpdateInterface vtable (aiDoCommand commands 0x0B/0x0C per re_attempts); names from the ZH TransportAIUpdate donor.
// Evidence: vtable 0x00853AA8 slot 40 off 0xA0; ret 0xc three args; contain +0x250 isPassengerAllowedToFire +0xb4 CMD 0 or 1 getContainedItemsList +0x118 Bfme ring; kindof byte +0x10f bit1 disabled mask +0x1c8 0x14 ai +0x258 +0x20 aiAttackPosition 0x29599A base privateAttackPosition 0x26DB1A; ZH TransportAIUpdate::privateAttackPosition donor.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum KindOfType
{
	KINDOF_39 = 0x39
};

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_kindof[t >> 5] & (1U << (t & 31)); }

	unsigned char m_unmodelled_08[0x108 - 8];
	UnsignedInt m_kindof[4];
};

class Thing
{
public:
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_template->isKindOf(t); }

	virtual void slot00();
	ThingTemplate *m_template;
};

class Object;
class AIUpdateInterface;

struct BfmeContainedNode
{
	BfmeContainedNode *m_next;
	BfmeContainedNode *m_prev;
	Object *m_object;
};

struct BfmeContainedList
{
	BfmeContainedNode *m_head;
};

struct BfmeContainedRange
{
	BfmeContainedRange();

	void *m_unmodelled_00;
	BfmeContainedList *m_list;
};

class ContainModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44();
	virtual Bool isPassengerAllowedToFire();
	virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
	virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57();
	virtual void slot58(); virtual void slot59(); virtual void slot60(); virtual void slot61();
	virtual void slot62(); virtual void slot63(); virtual void slot64(); virtual void slot65();
	virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69();
	virtual BfmeContainedRange getContainedItemsList();
};

class AICommandInterface
{
public:
	// 0x0026C2D9 keeps its address name in the ledger; Zero Hour calls aiAttackObject here.
	void rva0026C2D9(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource);
	void aiForceAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource);
	void aiAttackPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33();
protected:
	virtual void privateAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource);
public:
	virtual void slot35(); virtual void slot36(); virtual void slot37();
protected:
	virtual void privateForceAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource);
public:
	virtual void slot39();
protected:
	virtual void privateAttackPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType commandSource);
public:

	Object *getObject() const { return m_object; }

	unsigned char m_unmodelled_04[4];
	Object *m_object;
};

class Object : public Thing
{
public:
	UnsignedInt isDisabledByType(Int type) const { return m_disabledMask & (1U << type); }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() const { return m_ai; }

	unsigned char m_unmodelled_08[0x1C8 - 8];
	UnsignedInt m_disabledMask;
	unsigned char m_unmodelled_1CC[0x250 - 0x1CC];
	ContainModuleInterface *m_contain;
	unsigned char m_unmodelled_254[0x258 - 0x254];
	AIUpdateInterface *m_ai;
};

class TransportAIUpdate : public AIUpdateInterface
{
protected:
	virtual void privateAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource);
	virtual void privateForceAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource);
	virtual void privateAttackPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType commandSource);
};

void TransportAIUpdate::privateAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource)
{
	ContainModuleInterface *contain = getObject()->getContain();
	if (contain != 0 && contain->isPassengerAllowedToFire())
	{
		if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_SCRIPT)
		{
			BfmeContainedRange items = contain->getContainedItemsList();
			for (BfmeContainedNode *node = items.m_list->m_head->m_next; node != items.m_list->m_head;)
			{
				Object *passenger = node->m_object;
				node = node->m_next;
				if (passenger->isKindOf(KINDOF_39))
				{
					if (passenger->isDisabledByType(2) || passenger->isDisabledByType(4))
						continue;
				}
				AIUpdateInterface *passengerAI = passenger->getAI();
				if (passengerAI)
					((AICommandInterface *)((char *)passengerAI + 0x20))->rva0026C2D9(victim, maxShotsToFire, cmdSource);
			}
		}
	}
	AIUpdateInterface::privateAttackObject(victim, maxShotsToFire, cmdSource);
}

void TransportAIUpdate::privateForceAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource)
{
	ContainModuleInterface *contain = getObject()->getContain();
	if (contain != 0 && contain->isPassengerAllowedToFire())
	{
		if (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_SCRIPT)
		{
			BfmeContainedRange items = contain->getContainedItemsList();
			for (BfmeContainedNode *node = items.m_list->m_head->m_next; node != items.m_list->m_head;)
			{
				Object *passenger = node->m_object;
				node = node->m_next;
				if (passenger->isKindOf(KINDOF_39))
				{
					if (passenger->isDisabledByType(2) || passenger->isDisabledByType(4))
						continue;
				}
				AIUpdateInterface *passengerAI = passenger->getAI();
				if (passengerAI)
					((AICommandInterface *)((char *)passengerAI + 0x20))->aiForceAttackObject(victim, maxShotsToFire, cmdSource);
			}
		}
	}
	AIUpdateInterface::privateForceAttackObject(victim, maxShotsToFire, cmdSource);
}

void TransportAIUpdate::privateAttackPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType commandSource)
{
	ContainModuleInterface *contain = getObject()->getContain();
	if (contain != 0 && contain->isPassengerAllowedToFire())
	{
		if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		{
			BfmeContainedRange items = contain->getContainedItemsList();
			for (BfmeContainedNode *node = items.m_list->m_head->m_next; node != items.m_list->m_head;)
			{
				Object *passenger = node->m_object;
				node = node->m_next;
				if (passenger->isKindOf(KINDOF_39))
				{
					if (passenger->isDisabledByType(2) || passenger->isDisabledByType(4))
						continue;
				}
				AIUpdateInterface *passengerAI = passenger->getAI();
				if (passengerAI)
					((AICommandInterface *)((char *)passengerAI + 0x20))->aiAttackPosition(pos, maxShotsToFire, commandSource);
			}
		}
	}
	AIUpdateInterface::privateAttackPosition(pos, maxShotsToFire, commandSource);
}
