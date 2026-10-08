// ?onExit@SpecialAbilityUpdate@@MAEX_N0@Z
// partial score=0.98 date=2026-10-08
// cl: /O1 /DNDEBUG /MD
// SpecialAbilityUpdate.cpp: bodies retail links from this TU (tu_map approved),
// folded from three split units with these exact flags. The two
// address-named helper classes keep their names (their rows are mangled with
// them); Object and Overridable are shared views: object model-condition
// words at +0x10C and the status-base pointer at +0x04, final-override kind
// at +0x1C.

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
	OBJECT_STATUS_18 = 0x18,
	OBJECT_STATUS_3F = 0x3F
};
enum KindOfType
{
	KINDOF_6E = 0x6E
};
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
enum CommandSourceType
{
	CMD_FROM_AI = 2
};
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
	void rva0045003E(int a, CommandSourceType cmdSource);
};
// AI update interface view: AICommandInterface at +0x20.
class AIUpdateBase
{
public:
	virtual ~AIUpdateBase();
	char m_padAIBase[0x20 - 4];
};
class AIUpdateInterface : public AIUpdateBase, public AICommandInterface
{
public:
	void rva0026331C();
	char m_pad20[0x3CA - 0x20];
	bool m_3ca; // +0x3CA
};
class Module;
class AsciiString
{
public:
	bool isEmpty() const;
private:
	void *m_data;
};
class SpecialPowerTemplate;
class SpecialPowerModuleInterface
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
	virtual void vslot08(); virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12(); virtual void vslot13(); virtual void vslot14(); virtual void vslot15();
	virtual void vslot16(); virtual void vslot17(); virtual void vslot18();
	virtual void vslot19(); // +0x4C
};
class Rva00346BC0;
class Object;
// Object +0x250 view: slot 43 (+0xAC) takes (target, module data +0x2C, owner).
class Rva00450500
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
	virtual void vslot08(); virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12(); virtual void vslot13(); virtual void vslot14(); virtual void vslot15();
	virtual void vslot16(); virtual void vslot17(); virtual void vslot18(); virtual void vslot19();
	virtual void vslot20(); virtual void vslot21(); virtual void vslot22(); virtual void vslot23();
	virtual void vslot24(); virtual void vslot25(); virtual void vslot26(); virtual void vslot27();
	virtual void vslot28(); virtual void vslot29(); virtual void vslot30(); virtual void vslot31();
	virtual void vslot32(); virtual void vslot33(); virtual void vslot34(); virtual void vslot35();
	virtual void vslot36(); virtual void vslot37(); virtual void vslot38(); virtual void vslot39();
	virtual void vslot40(); virtual void vslot41(); virtual void vslot42();
	virtual void vslot43(Object *target, int value, Object *owner);
};
// Object +0x254 view: slot 5 (+0x14) reads a fraction, slot 21 (+0x54) stores it.
class Rva0045050A
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04();
	virtual float vslot05() const;
	virtual void vslot06(); virtual void vslot07();
	virtual void vslot08(); virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12(); virtual void vslot13(); virtual void vslot14(); virtual void vslot15();
	virtual void vslot16(); virtual void vslot17(); virtual void vslot18(); virtual void vslot19();
	virtual void vslot20();
	virtual void vslot21(float value, int flag);
};
class Object
{
	friend class SpecialAbilityUpdate;
public:
	void setStatus(ObjectStatusTypes status, bool set);
	void rva0028CDEB(const Rva00346BC0 &mask, bool set);
	void clearStatus(const Rva00346BC0 &mask) { rva0028CDEB(mask, false); }
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *t) const;
	bool isKindOf(KindOfType t) const;
	void removeAttributeModifierFromPool(const AsciiString &name);
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() const { return m_ai; }
protected:
	Module *findModule(NameKeyType key) const;
public:
	void rva0028AE6D();
	void setSpecialModelConditionState(ModelConditionFlagType mc, unsigned int frames);
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
	unsigned char m_pad078[0x80 - 0x78];
	ObjectID m_80; // +0x80
	unsigned char m_pad084[0x10C - 0x84];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x250 - 0x158];
	Rva00450500 *m_250; // +0x250
	Rva0045050A *m_254; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x484 - 0x25C];
	int m_484; // +0x484
};
struct Rva004CE41ECondition
{
	ModelConditionFlagType m_type; // +0x00
	unsigned int m_frames; // +0x04
};
class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	unsigned char m_pad00[0x1C];
	int m_val1C;
};
class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_pad[0x18];
	ModelConditionFlagType m_18; // +0x18
	unsigned int m_1C; // +0x1C
	unsigned char m_pad20[0x24 - 0x20];
	ModelConditionFlagType m_24; // +0x24
	unsigned int m_28; // +0x28
	int m_2C; // +0x2C
	float m_30; // +0x30
	unsigned char m_pad34[0x38 - 0x34];
	Overridable *m_specialPowerTemplate; // +0x38
	unsigned char m_pad3C[0x48 - 0x3C];
	AsciiString m_48; // +0x48
	unsigned char m_pad4C[0x90 - 0x4C];
	int m_90; // +0x90
	int m_94; // +0x94
	unsigned char m_pad98[0xA9 - 0x98];
	bool m_specialObjectsPersistent; // +0xA9
	bool m_aa;
	bool m_specialObjectsPersistWhenOwnerDies; // +0xAB
	unsigned char m_padAC[0xB3 - 0xAC];
	bool m_b3; // +0xB3
};
typedef unsigned int AudioHandle;
class AudioManager
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
	virtual void vslot08(); virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12(); virtual void vslot13(); virtual void vslot14(); virtual void vslot15();
	virtual void vslot16(); virtual void vslot17(); virtual void vslot18(); virtual void vslot19();
	virtual void vslot20(); virtual void vslot21(); virtual void vslot22(); virtual void vslot23();
	virtual void vslot24(); virtual void vslot25(); virtual void vslot26();
	virtual void removeAudioEvent(AudioHandle handle); // slot 27 (+0x6C)
};
extern AudioManager *TheAudio;
class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	Object *getObject() const { return m_object; }
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
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
class SpecialAbilityUpdate : public BehaviorModule
{
public:
	void rva0044EE07();
	void rva0044EE80();
	void rva0044F72E();
protected:
	virtual void onExit(bool cleanup, bool b);
	void endPreparation();
private:
	unsigned char m_pad0C[0x24 - 0x0C];
	int m_24; // +0x24
	unsigned char m_pad28[0x30 - 0x28];
	int m_packingState; // +0x30
	AudioHandle m_prepSoundLoop; // +0x34
	AudioHandle m_38; // +0x38
	unsigned char m_pad3C[0x40 - 0x3C];
	ObjectID m_targetID; // +0x40
	unsigned char m_pad44[0x6C - 0x44];
	unsigned int m_commandOptions; // +0x6C
	unsigned char m_pad70[0x74 - 0x70];
	bool m_active; // +0x74
	unsigned char m_pad75[0x7C - 0x75];
	bool m_7c; // +0x7C
	unsigned char m_pad7D[0x80 - 0x7D];
	bool m_80; // +0x80
	bool m_81;
	bool m_82; // +0x82
	bool m_83; // +0x83
	int m_84; // +0x84
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

// Retail 0x0044F81E (99 bytes): ZH SpecialAbilityUpdate::endPreparation. Clears
// object status 0x18 via the rowed Object::setStatus, drops the prep sound loop
// handle at +0x34 through TheAudio slot 0x6C and clears model condition 0x5F
// through the rowed mask helpers 0x0028F59A / 0x001E42F2 (BFME2 additions);
// then switches on the special power type and for types 0x15 0x1A 0x1D runs
// the rowed 0x0044F72E (ZH killSpecialObjects position in the switch).
void SpecialAbilityUpdate::endPreparation()
{
	getObject()->setStatus(OBJECT_STATUS_18, false);
	TheAudio->removeAudioEvent(m_prepSoundLoop);
	((Rva001E42F2 *)getObject())->rva001E42F2((const int *)&Rva0028F59A(0, 0x5f));
	const SpecialAbilityUpdateModuleData *data = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	switch (data->m_specialPowerTemplate->friend_getFinalOverride()->m_val1C)
	{
	case 0x15:
	case 0x1a:
	case 0x1d:
		rva0044F72E();
		break;
	}
}

class AutoHealBehavior
{
public:
	void stopHealing();
};
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class Rva0044EAF3
{
public:
	Rva0044EAF3 *rva0044EAF3(int a, unsigned int b, unsigned int c, unsigned int d);
	unsigned int m_bits[4];
};
extern unsigned int g_00E033D0;

void SpecialAbilityUpdate::onExit(bool cleanup, bool b)
{
	Object *obj = getObject();
	const SpecialAbilityUpdateModuleData *data = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	rva0044EE07();
	{
		Rva0044EAF3 mask;
		obj->clearStatus(*(const Rva00346BC0 *)mask.rva0044EAF3(0, 0x18, 0x46, 0x17));
	}
	AIUpdateInterface *ai = getObject()->getAI();
	if (ai)
	{
		ai->m_3ca = false;
		ai->rva0026331C();
	}
	TheAudio->removeAudioEvent(m_prepSoundLoop);
	m_prepSoundLoop = 1;
	TheAudio->removeAudioEvent(m_38);
	m_38 = 1;
	endPreparation();
	SpecialPowerModuleInterface *spm = obj->getSpecialPowerModule((const SpecialPowerTemplate *)data->m_specialPowerTemplate);
	if (spm)
		spm->vslot19();
	int type = data->m_specialPowerTemplate->friend_getFinalOverride()->m_val1C;
	if (type == 0x28 || type == 0x27)
	{
		Object *target = TheGameLogic->findObjectByID(m_targetID);
		obj->m_484 = 0;
		if (target)
		{
		target->setStatus(OBJECT_STATUS_3F, false);
		if (m_24 == 1)
		{
		if (target->m_base4[0x108] & 0x40)
			target->setModelConditionState((ModelConditionFlagType)0x5b);
		else if (target->m_base4[0x118] & 0x10)
			obj->clearModelConditionState((ModelConditionFlagType)0xb0);
		if (m_commandOptions & 0x4000)
		{
			Rva00450500 *a = obj->m_250;
			Rva0045050A *c = obj->m_254;
			if (a)
			{
				a->vslot43(target, data->m_2C, obj);
				float value = c->vslot05() * 100.0f + data->m_30;
				if (value > 100.0f)
					value = 100.0f;
				c->vslot21(value, 0);
				obj->setSpecialModelConditionState(data->m_24, data->m_28);
				target->setSpecialModelConditionState(data->m_24, data->m_28);
				if (obj->getAI())
					obj->getAI()->rva0045003E(data->m_28, CMD_FROM_AI);
			}
		}
		}
		}
	}
	else if (type == 0x80 || type == 0x8f)
	{
		static const NameKeyType key = TheNameKeyGenerator->nameToKey("AutoHealBehavior");
		AutoHealBehavior *heal = (AutoHealBehavior *)obj->findModule(key);
		if (heal)
			heal->stopHealing();
	}
	else if (type == 0x1d || type == 0x1a)
	{
		Object *target = TheGameLogic->findObjectByID(m_targetID);
		if (target && target->isKindOf(KINDOF_6E) && target->m_80 == getObject()->getID())
		{
			target->m_80 = INVALID_OBJECT_ID;
			target->clearModelConditionState((ModelConditionFlagType)0x6e);
			target->setSpecialModelConditionState((ModelConditionFlagType)0x6f, g_00E033D0);
		}
	}
	int exitCommand = b ? data->m_94 : data->m_90;
	if (exitCommand && ai)
		ai->rva0045003E(exitCommand, CMD_FROM_AI);
	if (!data->m_specialObjectsPersistent || cleanup && !data->m_specialObjectsPersistWhenOwnerDies)
		rva0044F72E();
	if (m_82)
	{
		if (obj->getAI())
			obj->getAI()->aiIdle(CMD_FROM_AI);
		m_82 = false;
	}
	if (!m_7c)
		m_active = false;
	m_packingState = 0;
	m_80 = false;
	m_83 = false;
	if (data->m_b3)
	{
		const AsciiString &name = data->m_48;
		if (!name.isEmpty())
			obj->removeAttributeModifierFromPool(name);
	}
}
