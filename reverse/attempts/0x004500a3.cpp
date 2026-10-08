// ?initiateIntentToDoSpecialPower@SpecialAbilityUpdate@@UAEXPBVSpecialPowerTemplate@@PBVObject@@PBVCoord3D@@IPBVWaypoint@@@Z
// partial score=0.99 date=2026-10-08
// cl: /O1 /DNDEBUG /MD
// SpecialAbilityUpdate.cpp: bodies retail links from this TU (tu_map approved),
// folded from three split units with these exact flags. The two
// address-named helper classes keep their names (their rows are mangled with
// them); Object and Overridable are shared views: object model-condition
// words at +0x10C and the status-base pointer at +0x04, final-override kind
// at +0x1C.

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};
class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_IS_USING_ABILITY = 0x17
};
enum CommandSourceType
{
	CMD_FROM_AI = 2
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};
#define VSLOT(n) virtual void vslot##n();

class Player;
class Rva0036859FByteZeroSetter
{
public:
	void disable();
};
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
private:
	char m_pad[0x14];
};
// AI update interface view: AICommandInterface at +0x20, the temporary
// state machine at +0x34, the 0x3CA latch, and the three slots this TU calls.
class AIUpdateBase
{
public:
	char m_padAIBase[0x20 - 4];
	VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
	VSLOT(8) VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15)
	VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
	VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30) VSLOT(31)
	VSLOT(32) VSLOT(33) VSLOT(34) VSLOT(35) VSLOT(36) VSLOT(37) VSLOT(38) VSLOT(39)
	VSLOT(40) VSLOT(41) VSLOT(42) VSLOT(43) VSLOT(44) VSLOT(45) VSLOT(46) VSLOT(47)
	VSLOT(48) VSLOT(49) VSLOT(50) VSLOT(51) VSLOT(52) VSLOT(53) VSLOT(54) VSLOT(55)
	VSLOT(56) VSLOT(57) VSLOT(58) VSLOT(59) VSLOT(60) VSLOT(61) VSLOT(62) VSLOT(63)
	VSLOT(64) VSLOT(65) VSLOT(66) VSLOT(67) VSLOT(68) VSLOT(69) VSLOT(70) VSLOT(71)
	VSLOT(72) VSLOT(73) VSLOT(74) VSLOT(75) VSLOT(76) VSLOT(77) VSLOT(78) VSLOT(79)
	VSLOT(80) VSLOT(81) VSLOT(82) VSLOT(83) VSLOT(84) VSLOT(85) VSLOT(86) VSLOT(87)
	VSLOT(88) VSLOT(89) VSLOT(90)
	virtual bool slot091() const;
	VSLOT(92) VSLOT(93) VSLOT(94) VSLOT(95) VSLOT(96) VSLOT(97)
	virtual Rva0036859FByteZeroSetter *slot098() const;
	VSLOT(99) VSLOT(100) VSLOT(101) VSLOT(102) VSLOT(103)
	VSLOT(104) VSLOT(105) VSLOT(106) VSLOT(107) VSLOT(108) VSLOT(109) VSLOT(110) VSLOT(111)
	VSLOT(112) VSLOT(113) VSLOT(114) VSLOT(115) VSLOT(116) VSLOT(117) VSLOT(118) VSLOT(119)
	VSLOT(120) VSLOT(121) VSLOT(122) VSLOT(123) VSLOT(124) VSLOT(125) VSLOT(126) VSLOT(127)
	VSLOT(128) VSLOT(129) VSLOT(130) VSLOT(131) VSLOT(132) VSLOT(133) VSLOT(134) VSLOT(135)
	VSLOT(136) VSLOT(137) VSLOT(138) VSLOT(139) VSLOT(140) VSLOT(141) VSLOT(142)
	virtual int slot143() const;
};
class AIUpdateInterface : public AIUpdateBase, public AICommandInterface
{
public:
	void rva0026331C();
	void BeginTemporaryStateMachine();

	void *m_temporaryState; // +0x34
	char m_pad038[0x3CA - 0x38];
	bool m_3ca; // +0x3CA
};

class BehaviorModule;
class Object
{
public:
	void rva0028AE6D();
	void setSpecialModelConditionState(ModelConditionFlagType mc, unsigned int frames);
	void setStatus(ObjectStatusTypes status, bool set);
	Player *getControllingPlayer() const;
	ObjectID getID() const { return m_id; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	AIUpdateInterface *getAI() const { return m_ai; }
	__forceinline void setModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}

	unsigned char m_pad000[4];
	unsigned char *m_base4; // +0x04 status base (bytes +0x108/+0x114 read)
	unsigned char m_pad008[0x74 - 8];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x10C - 0x78];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x244 - 0x158];
	BehaviorModule **m_behaviors; // +0x244
	unsigned char m_pad248[0x258 - 0x248];
	AIUpdateInterface *m_ai; // +0x258
};
struct Rva004CE41ECondition
{
	ModelConditionFlagType m_type; // +0x00
	unsigned int m_frames; // +0x04
};
class SpecialPowerTemplate;
class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_pad[0x18];
	ModelConditionFlagType m_18; // +0x18
	unsigned int m_1C; // +0x1C
	unsigned char m_pad20[0x38 - 0x20];
	const SpecialPowerTemplate *m_specialPowerTemplate; // +0x38
	unsigned char m_pad3C[0x70 - 0x3C];
	int m_70; // +0x70
	unsigned char m_pad74[0x88 - 0x74];
	unsigned int m_unpackTime; // +0x88
	unsigned char m_pad8C[0xA8 - 0x8C];
	bool m_skipPackingWithNoTarget; // +0xA8
	unsigned char m_padA9[0xB7 - 0xA9];
	bool m_b7; // +0xB7
};
class ModuleData;
class Coord3D
{
public:
	float x, y, z;
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};
class Waypoint;
class CommandButton;
class SpecialPowerModuleInterface
{
public:
	VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
	VSLOT(8) VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13)
	virtual void slot014(bool b);
};
class SpecialPowerUpdateInterface
{
public:
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
		const Object *targetObj, const Coord3D *targetPos, unsigned int commandOptions, const Waypoint *way) = 0;
	virtual bool isSpecialAbility() const = 0;
	VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
	virtual bool isPowerCurrentlyInUse(const CommandButton *command) const = 0;
};
class ObjectModule
{
public:
	virtual ~ObjectModule();
	VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8)
	VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12)
	Object *getObject() const { return m_object; }
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
	VSLOT(8) VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15)
	VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
	VSLOT(24)
	virtual SpecialPowerUpdateInterface *getSpecialPowerUpdateInterface();
};
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};
class UpdateModuleInterface
{
public:
	VSLOT(0)
};
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
private:
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_updateState; // +0x1C
};
class Rva0044E9C7
{
public:
	Rva0044E9C7 *rva0044E9C7(int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g, unsigned int h, unsigned int i, unsigned int j, unsigned int k, unsigned int l, unsigned int m, unsigned int n, unsigned int o);
	unsigned int m_bits[19];
};
class Rva0028F59A
{
public:
	Rva0028F59A(int a, int bit);
	unsigned int m_bits[19];
};
class Rva001E42F2
{
public:
	void rva001E42F2(const int *mask);
};
struct Rva002A8AB1Record;
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;

class Rva0044E633
{
public:
	void *rva0044E633();
};
class SpecialAbilityUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	virtual void slot13(bool a, bool b);
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();

	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
		const Object *targetObj, const Coord3D *targetPos, unsigned int commandOptions, const Waypoint *way);
	void rva0044EE07();
	void rva0044EE80();
private:
	int m_24;
	unsigned int m_28;
	unsigned int m_2C;
	int m_packingState; // +0x30
	unsigned int m_34;
	unsigned int m_38;
	unsigned int m_3C;
	ObjectID m_targetID; // +0x40
	Coord3D m_targetPos; // +0x44
	Coord3D m_50;
	int m_5C;
	int m_60;
	void *m_64;
	unsigned int m_68;
	unsigned int m_commandOptions; // +0x6C
	float m_70;
	bool m_active; // +0x74
	unsigned int m_78;
	bool m_7C;
	bool m_noTargetCommand; // +0x7D
	bool m_7E;
	bool m_7F;
	bool m_80;
	bool m_81;
	bool m_82;
	bool m_83;
	int m_84; // +0x84
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	unsigned char m_pad00[0x1C];
	int m_val1C;
};

struct Rva0044EF2CHolder
{
	char m_pad[0x38];
	Overridable *m_over38;
};

class Rva0044EF2C
{
public:
	char m_pad0[4];
	Rva0044EF2CHolder *m_holder04;
	int rva0044EF2C();
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Rva0044F633Inner
{
public:
	char m_pad0[0x38];
	Overridable *m_override38;
	char m_pad1[0x74 - 0x38 - 4];
	void *m_fallback74;
};

class Rva0044F633
{
public:
	void *rva0044F633();

private:
	char m_pad0[4];
	Rva0044F633Inner *m_inner4;
	char m_pad1[0x40 - 8];
	ObjectID m_target40;
};

// Retail 0x004500A3 (555 bytes): SpecialAbilityUpdate::initiateIntentToDoSpecialPower,
// slot 0 of the SpecialPowerUpdateInterface vtable at +0x20 (0x008552A4,
// stored by base ctor 0x0044EF5E), so this arrives as the interface and
// fields read at -0x20. Zero Hour donor: template check, clear target and
// packing state, clear the ability model conditions (rowed 0x0044EE07), take
// the target object ID or position, idle the AI and decide unpacking, then
// stop the other active abilities and wake. BFME 2 deltas read from retail:
// void return, options/way stored at +0x6C/+0x5C, a module-data +0x70 count
// at +0x60, a no-target +0xB7 path that ends the ability through slots 17
// and 13 and the special power module (rowed 0x0044E633), the AI status 0x17
// plus temporary state machine handling (rowed callees), and the
// abilities-loop through BehaviorModuleInterface slot 25 and interface
// slots 1 and 6 (0x0044EECA isPowerCurrentlyInUse) for every other ability.
void SpecialAbilityUpdate::initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
	const Object *targetObj, const Coord3D *targetPos, unsigned int commandOptions, const Waypoint *way)
{
	const SpecialAbilityUpdateModuleData *data = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	if (data->m_specialPowerTemplate != specialPowerTemplate)
		return;

	m_targetID = INVALID_OBJECT_ID;
	m_targetPos.zero();
	m_5C = 0;
	m_24 = 0;
	m_2C = 0;
	m_3C = 0;
	m_28 = 0;
	m_packingState = 3;
	m_7E = false;
	m_7F = false;
	m_80 = false;
	m_82 = false;
	m_83 = false;
	m_commandOptions = commandOptions;
	m_60 = data->m_70;
	if (m_60 > 0)
		--m_60;

	rva0044EE07();
	bool forced = (m_commandOptions >> 29) & 1;

	if (targetObj)
	{
		m_targetID = targetObj->getID();
	}
	else if (targetPos)
	{
		m_targetPos = *targetPos;
		m_5C = (int)way;
	}
	else if (data->m_b7)
	{
		slot17();
		SpecialPowerModuleInterface *spm = (SpecialPowerModuleInterface *)((Rva0044E633 *)this)->rva0044E633();
		if (spm)
			spm->slot014(false);
		slot13(false, true);
		return;
	}

	Object *obj = getObject();
	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return;
	obj->setStatus(OBJECT_STATUS_IS_USING_ABILITY, true);
	if (ai->slot098())
		ai->slot098()->disable();
	ai->m_3ca = true;
	if (!((ai->slot143() == 2 || g_00DFEEF8->rva002A8AB1(obj->getControllingPlayer()))
		&& (ai->slot091() || forced)))
	{
		ai->rva0026331C();
		ai->aiIdle(CMD_FROM_AI);
	}
	if (ai->m_temporaryState == 0)
		ai->BeginTemporaryStateMachine();
	ai->aiIdle(CMD_FROM_AI);

	m_noTargetCommand = !targetObj && !targetPos;
	if (data->m_unpackTime == 0 || m_noTargetCommand && data->m_skipPackingWithNoTarget)
		m_packingState = 4;
	m_active = true;
	m_78 = 0;

	for (BehaviorModule **m = obj->getBehaviorModules(); *m; ++m)
	{
		SpecialPowerUpdateInterface *spu = (*m)->getSpecialPowerUpdateInterface();
		if (spu && spu->isSpecialAbility() && spu->isPowerCurrentlyInUse(0))
		{
			SpecialAbilityUpdate *other = static_cast<SpecialAbilityUpdate *>(spu);
			if (other != this)
				other->slot13(false, true);
		}
	}

	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}

// Retail 0x0044EE07 (121 bytes): SpecialAbilityUpdate::rva0044EE07, the
// partner of rva0044EE80 below (same module data +0x18/+0x1C pair). Clears the
// fourteen ability model conditions (0x60 0x5E 0x29 0x76 0x5F 0x84 0x61..0x63
// 0x249..0x24B 0x6E 0x6F) on the Object through the rowed mask clear 0x001E42F2
// with the rowed 0x0044E9C7 mask builder, then, for an untimed module-data
// condition, clears that one through the one-bit mask ctor 0x0028F59A and
// zeroes +0x84. Called by 0x004500A3 with the module as this.
void SpecialAbilityUpdate::rva0044EE07()
{
	{
		Rva0044E9C7 mask;
		((Rva001E42F2 *)getObject())->rva001E42F2((const int *)mask.rva0044E9C7(0,
			0x60, 0x5e, 0x29, 0x76, 0x5f, 0x84, 0x61, 0x62, 0x63,
			0x249, 0x24a, 0x24b, 0x6e, 0x6f));
	}
	const SpecialAbilityUpdateModuleData *data = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	if (data->m_18 != MODELCONDITION_INVALID && data->m_1C == 0)
	{
		((Rva001E42F2 *)getObject())->rva001E42F2((const int *)&Rva0028F59A(0, data->m_18));
		m_84 = 0;
	}
}

// Retail 0x0044EE80 (74 bytes): SpecialAbilityUpdate::rva0044EE80, a
// non-virtual helper called with the module as this by the SpecialAbilityUpdate
// slot-22 base 0x004508B7 and by 0x00451FA2 (SpecialAbilityUpdate block). Name
// by address. Sets the model condition named by the module data +0x18 on the
// Object (directly, notifier as a tail jump) or times it through the matched
// Object::setSpecialModelConditionState 0x0028AEB2 when the +0x1C frames are
// non-zero. Object condition words at +0x10C, masked-word accessors.
void SpecialAbilityUpdate::rva0044EE80()
{
	Object *object = m_object;
	const SpecialAbilityUpdateModuleData *data = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	ModelConditionFlagType mc = data->m_18;
	if (mc == MODELCONDITION_INVALID)
		return;
	if (data->m_1C == 0)
		object->setModelConditionState(mc);
	else
		object->setSpecialModelConditionState(mc, data->m_1C);
}

// ?rva0044EF2C@Rva0044EF2C@@QAEHXZ @0x0044EF2C 22B
// Null-checked final-override int forward. Retail is mov eax [ecx+4]
// mov ecx [eax+0x38] test ecx jne call rowed
// Overridable::friend_getFinalOverride at 0x00288609 then mov eax [eax+0x1C].
// Evidence: unlock lane; caller at 0x0028BDBA in 0x0028BD92 which cmps the
// result; unblocks 0x0028BD92; flags copied from prev TU
// ModuleDataBuildFieldParseChained.cpp. Owner unproven so the name stays
// address-derived.
int Rva0044EF2C::rva0044EF2C()
{
	Overridable *o = m_holder04->m_over38;
	if (o == 0)
		return 0;
	const Overridable *f = o->friend_getFinalOverride();
	return f->m_val1C;
}

// ?rva0044F633@Rva0044F633@@QAEPAXXZ, retail 0x0044F633, 70 bytes.
// Leaf __thiscall: reads this+4 (holder) and this+0x40 (ObjectID), resolves
// the object via TheGameLogic->findObjectByID (rowed 0x00049DC5), then checks
// the holder's Overridable final override (rowed friend_getFinalOverride
// 0x00288609) for kind 0x27 and the target's status bytes at +0x108/+0x114.
// Returns null when all checks pass, else holder+0x74. Evidence: packet
// disassembly, callee rows, TheGameLogic extern in use, SpecialAbilityUpdate
// m_40 ObjectID at +0x40 in neighbour SpecialAbilityUpdateXfer.cpp.
void *Rva0044F633::rva0044F633()
{
	Rva0044F633Inner *inner = m_inner4;
	Object *obj = TheGameLogic->findObjectByID(m_target40);
	const Overridable *ov = inner->m_override38->friend_getFinalOverride();
	if (ov->m_val1C == 0x27) {
		if (obj) {
			unsigned char *base = obj->m_base4;
			if ((base[0x108] & 0x40) == 0) {
				if ((base[0x114] & 8) == 0)
					return 0;
			}
		}
	}
	return inner->m_fallback74;
}
