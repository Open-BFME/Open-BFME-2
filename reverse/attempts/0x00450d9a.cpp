// ?startPreparation@SpecialAbilityUpdate@@UAEXXZ
// partial score=0.97 date=2026-10-09
// cl: /O1 /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// SpecialAbilityUpdate.cpp: bodies retail links from this TU (tu_map approved),
// folded from three split units with these exact flags. The two
// address-named helper classes keep their names (their rows are mangled with
// them); Object and Overridable are shared views: object model-condition
// words at +0x10C and the status-base pointer at +0x04, final-override kind
// at +0x1C.

#include <list>
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

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
	OBJECT_STATUS_46 = 0x46
};
enum KindOfType
{
	KINDOF_INVALID = -1
};
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class Module;
class Drawable
{
public:
	void rva002723C0(int frames);		// rowed: the animation length in frames
};
class Thing
{
public:
	Drawable *getDrawable() const;
};
class Player
{
public:
	bool isLocalPlayer() const;
};
class Eva
{
public:
	void reportEvaEvent(int event, const Coord3D *position, int flag);
};
extern Eva *TheEva;
// The one-Drawable list the voice responses hand out; its destructor is the
// shared out-of-line pointer-list destructor 0x00239AF4.
class DrawableList : public _STL::list<Drawable *>
{
public:
	~DrawableList() throw();
};
class PickAndPlayInfo
{
public:
	PickAndPlayInfo();
	bool m_air;
	Drawable *m_drawTarget;
	void *m_weaponSlot;
	void *m_specialPowerTemplate; // +0x0C
	const void *m_10; // +0x10
	Coord3D m_position;
	unsigned int m_unmodelled_20;
};
class GameMessage
{
public:
	enum Type
	{
		MSG_BFME2_0x7DD = 0x7DD,
		MSG_BFME2_0x7DE = 0x7DE
	};
};
void pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);
// The rowed setter that stamps an audio event with its owning object.
class Rva002D9531
{
public:
	void rva002D9531(int objectID);
};
// The rowed two-bit mask builder (0x001E4912) behind the pack conditions.
class Rva001E4912
{
public:
	Rva001E4912 *rva001E4912(int a, unsigned int b, unsigned int c);
	unsigned int m_bits[19];
};
enum CommandSourceType
{
	CMD_FROM_AI = 2
};
class AICommandInterface
{
public:
	virtual void aiDoCommand(const void *parms);
	void aiIdle(CommandSourceType cmdSource);
	void rva0045003E(int value, CommandSourceType cmdSource);
};
// AIUpdateInterface: an update module whose AICommandInterface base is at +0x20.
class AIUpdateModuleView
{
public:
	virtual void v00();
	unsigned char m_pad04[0x20 - 4];
};
class AIUpdateInterface : public AIUpdateModuleView, public AICommandInterface
{
};
class Object;
class ContainModuleInterface
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual void s43();
	virtual void s44();
	virtual void s45();
	virtual void s46();
	virtual void s47();
	virtual void s48();
	virtual void s49();
	virtual void s50();
	virtual void s51();
	virtual void s52();
	virtual void s53();
	virtual void s54();
	virtual void s55();
	virtual void s56();
	virtual void s57();
	virtual void s58();
	virtual void useTarget(Object *target); // slot 59 (+0xEC)
};
class SpecialPowerModuleInterface
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void markSpecialPowerTriggered(const Coord3D *location); // slot 14 (+0x38)
};
// The rowed two-bit status mask (0x00391F4E) read as the status setter's mask.
class Rva00346BC0;
class Rva00391F4E
{
public:
	Rva00391F4E(int a, int b, int c);
	unsigned int m_bits[4];
};
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};
class Object : public Thing
{
	friend class SpecialAbilityUpdate;
public:
	Player *getControllingPlayer() const;
	bool isLocallyControlled() const;
	Relationship getRelationship(const Object *that) const;
	void rva0028CDEB(const Rva00346BC0 &mask, bool set);
	bool isKindOf(KindOfType kindOf) const;
	// rowed 0x0028CFB2: clears the first mask's conditions, sets the second's
	void rva0028CFB2(const int *clearMask, const int *setMask);
	// Zero Hour's inline Object::clearAndSetModelConditionState.
	void clearAndSetModelConditionState(ModelConditionFlagType clr, ModelConditionFlagType set);
	void setStatus(ObjectStatusTypes status, bool set);
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
	unsigned char m_pad008[0x38 - 8];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0x74 - 0x44];
	int m_id; // +0x74
	unsigned char m_pad078[0x10C - 0x78];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x250 - 0x158];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	unsigned char *m_ai; // +0x258 AIUpdateInterface (command interface at +0x20)
	AIUpdateInterface *getAI() const { return (AIUpdateInterface *)m_ai; }
	void *getTeam() const { return m_team; }
	unsigned char m_pad25C[0x304 - 0x25C];
	void *m_team; // +0x304
protected:
	Module *findModule(NameKeyType key) const;
};
class SpecialDisguiseUpdate
{
public:
	void rva004B05F5(bool disguise);
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
	unsigned char m_pad20[0x44 - 0x20];
	int m_evaEvent44; // +0x44
};
class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_pad[0x8];
	OpaqueRefElement4 m_packSound; // +0x08
	unsigned char m_pad0C[0x10 - 0x0C];
	OpaqueRefElement4 m_prepSoundLoop; // +0x10
	unsigned char m_pad14[0x18 - 0x14];
	ModelConditionFlagType m_18; // +0x18
	unsigned int m_1C; // +0x1C
	unsigned int m_20; // +0x20
	unsigned char m_pad24[0x38 - 0x24];
	Overridable *m_specialPowerTemplate; // +0x38
	unsigned char m_pad3C[0x54 - 0x3C];
	float m_packUnpackVariationFactor; // +0x54
	unsigned char m_pad58[0x6C - 0x58];
	int m_6C; // +0x6C ability condition selector (1..6)
	unsigned char m_pad70[0x74 - 0x70];
	unsigned int m_preparationFrames; // +0x74
	unsigned char m_pad78[0x84 - 0x78];
	unsigned int m_packTime; // +0x84
	unsigned int m_unpackTime; // +0x88
};
float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
typedef unsigned int AudioHandle;
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	unsigned char m_pad00[0x40];
	unsigned int m_frame; // +0x40
	unsigned int getFrame() const { return m_frame; }
};
class AudioManager
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
	virtual void vslot08(); virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12(); virtual void vslot13(); virtual void vslot14(); virtual void vslot15();
	virtual void vslot16(); virtual void vslot17(); virtual void vslot18(); virtual void vslot19();
	virtual void vslot20(); virtual void vslot21(); virtual void vslot22(); virtual void vslot23();
	virtual void vslot24(); virtual AudioHandle addAudioEvent(const BfmeAudioEventPrefix136 *event); virtual void vslot26();
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
__forceinline void Object::clearAndSetModelConditionState(ModelConditionFlagType clr, ModelConditionFlagType set)
{
	rva0028CFB2((const int *)&Rva0028F59A(0, clr), (const int *)&Rva0028F59A(0, set));
}
class SpecialAbilityUpdate : public BehaviorModule
{
public:
	void rva0044EE07();
	void rva0044EE80();
	void rva0044F72E();
	virtual void startPreparation();
	virtual void startPacking(bool success);
protected:
	Object *createSpecialObject();
	bool initLaser(Object *specialObject, Object *target);
public:
	virtual void startUnpacking();
protected:
	void endPreparation();
private:
	unsigned char m_pad0C[0x28 - 0x0C];
	unsigned int m_animFrames; // +0x28
	unsigned char m_pad2C[0x30 - 0x2C];
	int m_packingState; // +0x30
	AudioHandle m_prepSoundLoop; // +0x34
	AudioHandle m_packSoundHandle; // +0x38
	unsigned int m_prepFrames; // +0x3C
	ObjectID m_targetID; // +0x40
	unsigned char m_pad44[0x84 - 0x44];
	unsigned int m_84; // +0x84
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

// SpecialAbilityUpdate::startUnpacking, retail 0x004508B7 (562 bytes, vtable
// slot 22; WeaponFireSpecialAbilityUpdate overrides it under the same name).
// Zero Hour's startUnpacking reached through the matched BFME1 donor
// (SpecialAbilityUpdate_startUnpacking.cpp): unpack state 2, a randomised
// unpack time, conditions 94 -> 96, and a selector-chosen ability condition.
// BFME2 adds the module-data condition (+0x18) set now or timed from +0x20,
// a target-dependent condition for power type 0x28 and the disguise drop for
// power type 0x84.
void SpecialAbilityUpdate::startUnpacking()
{
	const SpecialAbilityUpdateModuleData *d = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	Object *self = m_object;
	m_packingState = 2;
	float variation = GetGameLogicRandomValueReal(1.0f - d->m_packUnpackVariationFactor,
		1.0f + d->m_packUnpackVariationFactor,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\SpecialAbilityUpdate.cpp",
		1370);
	m_animFrames = (unsigned int)(d->m_unpackTime * variation);
	self->rva0028CFB2((const int *)&Rva0028F59A(0, 0x5e), (const int *)&Rva0028F59A(0, 0x60));
	self->setStatus(OBJECT_STATUS_46, true);
	if (d->m_6C)
	{
		switch (d->m_6C)
		{
		case 1: self->setModelConditionState((ModelConditionFlagType)97); break;
		case 2: self->setModelConditionState((ModelConditionFlagType)98); break;
		case 3: self->setModelConditionState((ModelConditionFlagType)99); break;
		case 4: self->setModelConditionState((ModelConditionFlagType)585); break;
		case 5: self->setModelConditionState((ModelConditionFlagType)586); break;
		case 6: self->setModelConditionState((ModelConditionFlagType)587); break;
		}
	}
	if (d->m_18 != MODELCONDITION_INVALID)
	{
		if (d->m_20 == 0)
			rva0044EE80();
		else
			m_84 = d->m_20 + TheGameLogic->getFrame();
	}
	Object *target = TheGameLogic->findObjectByID(m_targetID);
	int type = d->m_specialPowerTemplate->friend_getFinalOverride()->m_val1C;
	if (type == 0x28)
	{
		if (target && (target->m_base4[0x118] & 0x10))
			self->setModelConditionState((ModelConditionFlagType)176);
	}
	else if (type == 0x84)
	{
		if (self->isKindOf((KindOfType)0x12c))
		{
			static NameKeyType key = TheNameKeyGenerator->nameToKey("SpecialDisguiseUpdate");
			SpecialDisguiseUpdate *disguise = (SpecialDisguiseUpdate *)self->findModule(key);
			if (disguise)
				disguise->rva004B05F5(false);
		}
	}
	Drawable *draw = self->getDrawable();
	if (draw)
		draw->rva002723C0(m_animFrames);
	unsigned char *ai = self->m_ai;
	if (ai)
		((AICommandInterface *)(ai + 0x20))->rva0045003E(0, CMD_FROM_AI);
}

// SpecialAbilityUpdate::startPacking, retail 0x00450635 (642 bytes; the
// WeaponFireSpecialAbilityUpdate slot override 0x004925DB forwards to it).
// Zero Hour's startPacking reached through the matched BFME1 donor
// (SpecialAbilityUpdate_startPacking.cpp): pack state 1, a randomised pack
// time, conditions 96/118 -> 94, the selector condition, the pack sound with
// the old loop handle dropped, the drawable animation time, an AI command
// unless the power type is 0x2A, and on success a one-Drawable voice
// response (0x7DD for power types 0x1A/0x1D, else 0x7DE) plus an Eva event
// for the local player.
void SpecialAbilityUpdate::startPacking(bool success)
{
	Object *self = m_object;
	Player *player = self->getControllingPlayer();
	const SpecialAbilityUpdateModuleData *d = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	m_packingState = 1;
	float variation = GetGameLogicRandomValueReal(1.0f - d->m_packUnpackVariationFactor,
		1.0f + d->m_packUnpackVariationFactor,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\SpecialAbilityUpdate.cpp",
		1281);
	m_animFrames = (unsigned int)(d->m_packTime * variation);
	Rva001E4912 clearMask;
	self->rva0028CFB2((const int *)clearMask.rva001E4912(0, 0x60, 0x76), (const int *)&Rva0028F59A(0, 0x5e));
	self->setStatus(OBJECT_STATUS_46, true);
	if (d->m_6C)
	{
		switch (d->m_6C)
		{
		case 1: self->setModelConditionState((ModelConditionFlagType)97); break;
		case 2: self->setModelConditionState((ModelConditionFlagType)98); break;
		case 3: self->setModelConditionState((ModelConditionFlagType)99); break;
		case 4: self->setModelConditionState((ModelConditionFlagType)585); break;
		case 5: self->setModelConditionState((ModelConditionFlagType)586); break;
		case 6: self->setModelConditionState((ModelConditionFlagType)587); break;
		}
	}
	BfmeAudioEventPrefix136 sound(d->m_packSound, 0);
	((Rva002D9531 *)&sound)->rva002D9531(self->m_id);
	TheAudio->addAudioEvent(&sound);
	TheAudio->removeAudioEvent(m_packSoundHandle);
	m_packSoundHandle = 1;
	Drawable *draw = self->getDrawable();
	if (draw)
		draw->rva002723C0(m_animFrames);
	if (d->m_specialPowerTemplate->friend_getFinalOverride()->m_val1C != 0x2a)
	{
		unsigned char *ai = self->m_ai;
		if (ai)
			((AICommandInterface *)(ai + 0x20))->rva0045003E(0, CMD_FROM_AI);
	}
	if (success)
	{
		DrawableList list;
		list.push_back(draw);
		PickAndPlayInfo info;
		info.m_10 = d->m_specialPowerTemplate;
		if (d->m_specialPowerTemplate->friend_getFinalOverride()->m_val1C == 0x1a
			|| d->m_specialPowerTemplate->friend_getFinalOverride()->m_val1C == 0x1d)
			pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_BFME2_0x7DD, &info);
		else
			pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_BFME2_0x7DE, &info);
		if (player && player->isLocalPlayer())
		{
			int evaEvent = d->m_specialPowerTemplate->friend_getFinalOverride()->m_evaEvent44;
			TheEva->reportEvaEvent(evaEvent, &self->m_position, 0);
		}
	}
}

// The rowed special-power-module lookup (0x0044E633), taking the update as
// this.
class Rva0044E633
{
public:
	void *rva0044E633();
};

// SpecialAbilityUpdate::startPreparation, retail 0x00450D9A (755 bytes,
// vtable slot 15; ArrowStormUpdate overrides it). Zero Hour's
// startPreparation reached through the matched BFME1 donor
// (SpecialAbilityUpdate_startPreparation.cpp): with preparation frames the
// container uses the target and conditions 96/118 -> 95 plus the selector
// condition; per power type the laser (0x15), the same-team guard and
// condition swap (0x1D) or the relationship guard, laser and swap (0x1A),
// each with an Eva event 0x10 for a locally controlled target; then the
// power module is marked, the AI idled, statuses 0x18/0x46 set and the
// preparation sound started.
void SpecialAbilityUpdate::startPreparation()
{
	const SpecialAbilityUpdateModuleData *d = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	Overridable *power = d->m_specialPowerTemplate;
	m_prepFrames = (unsigned int)((Rva0044F633 *)this)->rva0044F633();
	if (m_prepFrames)
	{
		Object *target = TheGameLogic->findObjectByID(m_targetID);
		ContainModuleInterface *contain = m_object->m_contain;
		if (contain && target)
			contain->useTarget(target);
		Object *self = m_object;
		Rva001E4912 clearMask;
		self->rva0028CFB2((const int *)clearMask.rva001E4912(0, 0x60, 0x76), (const int *)&Rva0028F59A(0, 0x5f));
		if (d->m_6C)
		{
			switch (d->m_6C)
			{
			case 1: self->setModelConditionState((ModelConditionFlagType)97); break;
			case 2: self->setModelConditionState((ModelConditionFlagType)98); break;
			case 3: self->setModelConditionState((ModelConditionFlagType)99); break;
			case 4: self->setModelConditionState((ModelConditionFlagType)585); break;
			case 5: self->setModelConditionState((ModelConditionFlagType)586); break;
			case 6: self->setModelConditionState((ModelConditionFlagType)587); break;
			}
		}
	}
	int type = power->friend_getFinalOverride()->m_val1C;
	if (type == 0x15)
	{
		Object *target = TheGameLogic->findObjectByID(m_targetID);
		if (target)
		{
			Object *special = createSpecialObject();
			if (special && !initLaser(special, target))
				return;
		}
	}
	else if (type == 0x1d)
	{
		Object *target = TheGameLogic->findObjectByID(m_targetID);
		if (target && target->m_team == m_object->m_team)
			return;
		m_object->clearAndSetModelConditionState((ModelConditionFlagType)0x60, (ModelConditionFlagType)0x76);
		Drawable *draw = m_object->getDrawable();
		if (draw)
			draw->rva002723C0(d->m_preparationFrames);
		if (target && target->isLocallyControlled())
			TheEva->reportEvaEvent(0x10, &target->m_position, 0);
	}
	else if (type == 0x1a)
	{
		Object *target = TheGameLogic->findObjectByID(m_targetID);
		if (target)
		{
			if (m_object->getRelationship(target) == ALLIES)
				return;
			Object *special = createSpecialObject();
			if (special)
			{
				if (!initLaser(special, target))
					return;
				m_object->clearAndSetModelConditionState((ModelConditionFlagType)0x60, (ModelConditionFlagType)0x29);
			}
			if (target->isLocallyControlled())
				TheEva->reportEvaEvent(0x10, &target->m_position, 0);
		}
	}
	SpecialPowerModuleInterface *module = (SpecialPowerModuleInterface *)((Rva0044E633 *)this)->rva0044E633();
	if (module)
		module->markSpecialPowerTriggered(0);
	if (m_object->getAI())
		m_object->getAI()->aiIdle(CMD_FROM_AI);
	Object *obj = m_object;
	obj->rva0028CDEB(*(const Rva00346BC0 *)&Rva00391F4E(0, 0x18, 0x46), true);
	BfmeAudioEventPrefix136 sound(d->m_prepSoundLoop, 0);
	((Rva002D9531 *)&sound)->rva002D9531(m_object->m_id);
	m_prepSoundLoop = TheAudio->addAudioEvent(&sound);
}
