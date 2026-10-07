// cl: /O1 /EHsc /MD /arch:SSE /Ireference/shims/bfme2_ascii
// ActiveBody.cpp -- ActiveBody members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function (vtable
// pairing); retail supplies the bytes. Zero Hour's setDamageState
// (GameLogic/Object/Body/ActiveBody.cpp) as a switch over the state with the
// thresholds held in the body itself.
//
// Layout (target evidence, matching Body/ActiveBodyDamageState.cpp): the body
// module interface is the second base at +0x10, so this body runs with ecx at
// +0x10; health +0x18, max health +0x20, damaged and really-damaged ratios
// +0x24/+0x28. The health change is interface slot 32 (+0x80); the final
// call is slot 21 (+0x54) of the primary vtable with a zero argument.

#include "ascii_string.h"

typedef float Real;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum BodyDamageType { BODY_PRISTINE, BODY_DAMAGED, BODY_REALLYDAMAGED, BODY_RUBBLE };

enum DamageType { DAMAGE_HEALING = 7 };
enum KindOfType { KINDOF_220 = 0x220 };
enum ObjectID { INVALID_ID = 0 };

// class-gate: allow Coord3D the bone-position array is built and torn down through BFME 2's out-of-line empty Coord3D constructor and destructor (the eh vector iterators push 0x0047A6A9 and 0x000B3FD0); the canonical data-only header cannot declare them; same three floats
struct Coord3D
{
	float x, y, z;
	Coord3D();
	~Coord3D();
};

class Matrix3D;
class ParticleSystemTemplate;

enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID = 0 };

// The particle system's setters, rowed under placeholder names: position copy
// 0x001F3899 and attached object 0x001F3C43.
struct Rva001F3899Arg
{
	int m_00;
	int m_04;
	int m_08;
};
class Rva001F3899Slot
{
public:
	void set(const Rva001F3899Arg &arg);
};
struct Rva001F3C43Arg;
class Rva001F3C43Slot
{
public:
	void set(const Rva001F3C43Arg *arg);
};

class Object;
class ParticleSystem
{
public:
	ParticleSystemID getSystemID() const { return m_systemID; }
	void setPosition(const Coord3D *pos)
	{
		((Rva001F3899Slot *)this)->set(*(const Rva001F3899Arg *)pos);
	}
	void attachToObject(const Object *obj)
	{
		((Rva001F3C43Slot *)this)->set((const Rva001F3C43Arg *)obj);
	}

private:
	char m_pad00[0xA8];
	ParticleSystemID m_systemID;	// +0xA8
};
ParticleSystem *Make001FCBD7();

// The 12-byte handle: the out-of-line unlink is 0x0004CBC0, which the handle's
// destructor calls only for a live system.
class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw();
};
class BfmeParticleSystemHandleBase
{
public:
	~BfmeParticleSystemHandleBase()
	{
		if (m_system)
			((RvaSmartPtr12 *)this)->rva0004CBC0();
	}
	ParticleSystem *m_system;
	BfmeParticleSystemHandleBase *m_previous;
	BfmeParticleSystemHandleBase *m_next;
};
class BfmeParticleSystemHandle : public BfmeParticleSystemHandleBase
{
public:
	operator bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		return m_system ? m_system : Make001FCBD7();
	}
};

class ParticleSystemManager
{
public:
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *sysTemplate, bool createSlaves);
};
extern ParticleSystemManager *TheParticleSystemManager;

extern Int GetGameClientRandomValue(Int lo, Int hi, char *file, Int line);
#define GameClientRandomValue(lo, hi) \
	GetGameClientRandomValue((lo), (hi), __FILE__, __LINE__)

// BodyParticleSystem: BFME 2 drops Zero Hour's memory pool, so the 12-byte
// entry is a plain new with a vptr (vtable VA 0x00C5AEB0, whose only slot is
// the rowed scalar deleting destructor 0x004BDA0C named after its address).
class Rva004BDA0C
{
public:
	virtual ~Rva004BDA0C();

	ParticleSystemID m_particleSystemID;	// +0x04
	Rva004BDA0C *m_next;			// +0x08
};
typedef Rva004BDA0C BodyParticleSystem;

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);	// 0x000B2235
};

class DamageInfoInput
{
public:
	UnsignedInt m_field00;			// +0x00
	ObjectID m_sourceID;			// +0x04
	UnsignedInt m_field08;			// +0x08
	DamageType m_damageType;		// +0x0C
	Int m_damageFXType;			// +0x10
	unsigned char m_pad14[0x28 - 0x14];
	Int m_creationType;			// +0x28
};

class DamageInfo
{
public:
	void *m_vptr;
	DamageInfoInput in;			// +0x04
	unsigned char m_pad30[0x70 - 0x30];
	Real m_actualDamageDealt;		// +0x70
	Real m_actualDamageClipped;		// +0x74
};

class DamageModuleInterface
{
public:
	virtual void d00();
	virtual void onHealing(DamageInfo *damageInfo);					// +0x04
	virtual void onBodyDamageStateChange(DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState);	// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
	virtual DamageModuleInterface *getDamage();	// +0x10
};

class BehaviorModule
{
public:
	unsigned char m_pad00[0x0C];
	BehaviorModuleInterface m_iface;	// +0x0C
};

class ThingTemplate
{
public:
	UnsignedInt testKindOf(Int k) const { return m_kindOf[k >> 5] & (1U << (k & 31)); }

	unsigned char m_pad000[0x108];
	UnsignedInt m_kindOf[0x10];		// +0x108
	unsigned char m_pad148[0x632 - 0x148];
	Bool m_byte632;				// +0x632
};

class BodyModuleInterface;

class Object
{
public:
	Bool isKindOf(KindOfType kindOf) const;	// 0x0006F039
	Int getMultiLogicalBonePosition(const char *boneNamePrefix, Int maxBones, Coord3D *positions,
		Matrix3D *transforms, Bool convertToWorld, Int extra) const;	// 0x0028BF81
	const ThingTemplate *getTemplate() const { return m_template; }
	Int getID() const { return m_id; }
	Bool testStatusBit6() const { return (m_status >> 6) & 1; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	BodyModuleInterface *getBodyModule() const { return m_body; }

	void *m_vptr;
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad08[0x74 - 0x08];
	Int m_id;			// +0x74
	unsigned char m_pad78[0x94 - 0x78];
	UnsignedInt m_status;			// +0x94
	unsigned char m_pad98[0x244 - 0x98];
	BehaviorModule **m_behaviors;		// +0x244
	unsigned char m_pad248[0x254 - 0x248];
	BodyModuleInterface *m_body;		// +0x254
	unsigned char m_pad258[0x438 - 0x258];
	UnsignedInt m_flags438;			// +0x438
};

class DOTManager
{
public:
	UnsignedInt rva0043B72D(Int id);	// 0x0043B72D
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	Object *findObjectByID(ObjectID id);	// 0x00049DC5

	unsigned char m_pad00[0x40];
	UnsignedInt m_frame;			// +0x40
	unsigned char m_pad44[0x174 - 0x44];
	DOTManager *m_dotManager;		// +0x174
};
extern GameLogic *TheGameLogic;

class DamageFX
{
public:
	Bool rva003608DF(Int damageType, Real amount, const Object *source, const Object *victim);	// 0x003608DF
};

class Rva003605D5	// DamageFX throttle-time lookup (Zero Hour getDamageFXThrottleTime)
{
public:
	Int rva003605D5(Int damageType, Int source);	// 0x003605D5
};

class ObjectCreationList
{
public:
	void create(void *primary, void *secondary, void *lifetime);	// 0x001F08D3
};

struct DamageCreation
{
	ObjectCreationList *m_ocl;		// +0x00
	Int m_type;				// +0x04
	Int m_field08;				// +0x08
};

class Armor
{
public:
	Real adjustDamage(const DamageInfoInput *input, const Object *obj, Bool flag) const;	// 0x001D90A1

private:
	void *m_name;
};

class ActiveBodyModuleData
{
public:
	unsigned char m_pad00[0x48];
	const FXList *m_healingFX;		// +0x48
	unsigned char m_pad4C[0x51 - 0x4C];
	Bool m_byte51;				// +0x51
};

class ActiveBodyModuleBase
{
public:
	virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
	virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
	virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
	virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
	virtual void m16();
	virtual void validateArmorAndDamageFX();		// +0x44
	virtual void doDamageFX(const DamageInfo *damageInfo) = 0;	// +0x48
	virtual void m19(); virtual void m20();
	virtual void rvaSlot21(Int arg);			// +0x54

protected:
	const ActiveBodyModuleData *m_moduleData;	// +0x04
	Object *m_object;				// +0x08
	void *m_vptr0C;
};

class BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);	// +0x00
	virtual void attemptHealing(DamageInfo *damageInfo);	// +0x04
	virtual void i02(); virtual void i03();
	virtual void i04(); virtual void i05(); virtual void i06(); virtual void i07();
	virtual void i08();
	virtual void setDamageState(BodyDamageType newState);	// +0x24
	virtual void i10(); virtual void i11();
	virtual void i12(); virtual void i13(); virtual void i14(); virtual void i15();
	virtual void i16(); virtual void i17(); virtual void i18(); virtual void i19();
	virtual void i20(); virtual void i21(); virtual void i22(); virtual void i23();
	virtual void i24(); virtual void i25(); virtual void i26(); virtual void i27();
	virtual void i28(); virtual void i29(); virtual void i30(); virtual void i31();
	virtual void internalChangeHealth(Real delta, DamageInfo *damageInfo);	// +0x80
	virtual void i33(); virtual void i34(); virtual void i35(); virtual void i36();
	virtual void i37(); virtual void i38();
	virtual void rvaSlot39(BodyDamageType state);		// +0x9C
};

class ActiveBody : public ActiveBodyModuleBase, public BodyModuleInterface
{
public:
	virtual void attemptHealing(DamageInfo *damageInfo);
	virtual void setDamageState(BodyDamageType newState);

protected:
	virtual void doDamageFX(const DamageInfo *damageInfo);
	virtual void createParticleSystems(const AsciiString &boneBaseName,
		const ParticleSystemTemplate *systemTemplate, Int maxSystems);

private:
	const ActiveBodyModuleData *getActiveBodyModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

	unsigned char m_pad14[4];
	Real m_currentHealth;			// +0x18
	Real m_prevHealth;			// +0x1C
	Real m_maxHealth;			// +0x20
	Real m_damagedRatio;			// +0x24
	Real m_reallyDamagedRatio;		// +0x28
	unsigned char m_pad2C[4];
	BodyDamageType m_curDamageState;	// +0x30
	unsigned char m_pad34[4];
	UnsignedInt m_nextDamageFXTime;		// +0x38
	Int m_lastDamageFXDone;			// +0x3C
	unsigned char m_pad40[0xC0 - 0x40];
	UnsignedInt m_lastHealingTimestamp;	// +0xC0
	unsigned char m_padC4[4];
	BodyParticleSystem *m_particleSystems;	// +0xC8
	unsigned char m_padCC[0xE0 - 0xCC];
	DamageCreation *m_damageCreationBegin;	// +0xE0
	DamageCreation *m_damageCreationEnd;	// +0xE4
	unsigned char m_padE8[4];
	ObjectID m_linkedObjectID;		// +0xEC
	unsigned char m_padF0[0xF8 - 0xF0];
	Armor m_curArmor;			// +0xF8
	DamageFX *m_curDamageFX;		// +0xFC
};

// ActiveBody::setDamageState, retail 0x004BDAA9.
void ActiveBody::setDamageState(BodyDamageType newState)
{
	switch (newState)
	{
	case BODY_PRISTINE:
		internalChangeHealth(m_maxHealth - m_currentHealth, 0);
		break;
	case BODY_DAMAGED:
		internalChangeHealth(m_damagedRatio * m_maxHealth - m_currentHealth, 0);
		break;
	case BODY_REALLYDAMAGED:
		internalChangeHealth(m_reallyDamagedRatio * m_maxHealth - m_currentHealth, 0);
		break;
	case BODY_RUBBLE:
		internalChangeHealth(0.0f - m_currentHealth, 0);
		break;
	}
	rvaSlot21(0);
}

// ActiveBody::attemptHealing, retail 0x004BEE21 (484B): BodyModuleInterface
// slot 1. Zero Hour shape (validate armor, hand non-healing damage to
// attemptDamage, armor-adjust the amount, change health, record the healing
// frame, tell the damage modules about the heal and any damage-state change,
// then the damage FX) with the BFME 2 additions the bytes show: an early out
// when module data +0x51 is set and the Object has kind 0x220; the "can it
// be healed" test on template byte +0x632, template kinds 150/22/24 and
// Object +0x438 bit 0; the healing FX of module data +0x48 (skipped for
// template kind 7 and status bit 6); the DOT manager notification; and the
// damage state handed on to the body of the linked object at +0xEC.
void ActiveBody::attemptHealing(DamageInfo *damageInfo)
{
	validateArmorAndDamageFX();

	const ActiveBodyModuleData *md = getActiveBodyModuleData();
	Object *obj = getObject();
	if (md->m_byte51 && obj->isKindOf(KINDOF_220))
		return;

	if (damageInfo == 0)
		return;

	if (damageInfo->in.m_damageType != DAMAGE_HEALING)
	{
		attemptDamage(damageInfo);
		return;
	}

	const ThingTemplate *tmpl = obj->getTemplate();
	if (!tmpl->m_byte632 && !tmpl->testKindOf(150) && !tmpl->testKindOf(22) && !tmpl->testKindOf(24)
		&& (obj->m_flags438 & 1))
		return;

	damageInfo->m_actualDamageDealt = 0.0f;
	damageInfo->m_actualDamageClipped = 0.0f;

	Real amount = m_curArmor.adjustDamage(&damageInfo->in, getObject(), false);
	if (amount > 0.0f)
	{
		BodyDamageType oldState = m_curDamageState;
		internalChangeHealth(amount, damageInfo);

		damageInfo->m_actualDamageDealt = amount;
		damageInfo->m_actualDamageClipped = m_prevHealth - m_currentHealth;
		m_lastHealingTimestamp = TheGameLogic->getFrame();

		if (m_currentHealth > m_prevHealth)
		{
			for (BehaviorModule **m = obj->getBehaviorModules(); *m; ++m)
			{
				DamageModuleInterface *d = (*m)->m_iface.getDamage();
				if (d)
					d->onHealing(damageInfo);
			}

			if (!obj->getTemplate()->testKindOf(7) && md->m_healingFX && !obj->testStatusBit6())
				FXList::doFXObj(md->m_healingFX, obj, 0);

			TheGameLogic->m_dotManager->rva0043B72D(obj->getID());
		}

		if (m_curDamageState != oldState)
		{
			for (BehaviorModule **m = obj->getBehaviorModules(); *m; ++m)
			{
				DamageModuleInterface *d = (*m)->m_iface.getDamage();
				if (d)
					d->onBodyDamageStateChange(damageInfo, oldState, m_curDamageState);
			}

			if (m_linkedObjectID)
			{
				Object *linked = TheGameLogic->findObjectByID(m_linkedObjectID);
				if (linked && linked->getBodyModule())
					linked->getBodyModule()->rvaSlot39(m_curDamageState);
			}
		}
	}

	doDamageFX(damageInfo);
}

// ActiveBody::doDamageFX, retail 0x004BED62 (191B): primary vtable slot 18.
// Zero Hour's throttled damage FX, except that BFME 2 takes the FX damage
// type straight from DamageInfoInput +0x10, records the throttle only when
// DamageFX 0x003608DF reports it played something, and then runs the
// damage-creation list (+0xE0, 12-byte entries): each entry whose type
// matches DamageInfoInput +0x28 and whose third word is clear creates its
// ObjectCreationList on this Object.
void ActiveBody::doDamageFX(const DamageInfo *damageInfo)
{
	DamageFX *fx = m_curDamageFX;
	Int type = damageInfo->in.m_damageFXType;
	if (fx)
	{
		UnsignedInt now = TheGameLogic->getFrame();
		if (type == m_lastDamageFXDone && m_nextDamageFXTime > now)
			return;
		Object *source = TheGameLogic->findObjectByID(damageInfo->in.m_sourceID);
		if (fx->rva003608DF(type, damageInfo->m_actualDamageDealt, source, getObject()))
		{
			m_lastDamageFXDone = type;
			m_nextDamageFXTime = ((Rva003605D5 *)m_curDamageFX)->rva003605D5(type, (Int)source) + now;
		}
	}

	for (DamageCreation *it = m_damageCreationBegin; it != m_damageCreationEnd; ++it)
	{
		DamageCreation c = *it;
		if (c.m_type == damageInfo->in.m_creationType && c.m_field08 == 0 && c.m_ocl)
			c.m_ocl->create(getObject(), 0, 0);
	}
}

// ActiveBody::createParticleSystems, retail 0x004BE24A (421B): primary vtable
// slot 19. The BFME 1 donor shape: up to maxSystems systems, each on a random
// bone not used yet (a used-bone array instead of Zero Hour's shrinking
// range), each recorded on the body's particle-system list at +0xC8.
void ActiveBody::createParticleSystems(const AsciiString &boneBaseName,
	const ParticleSystemTemplate *systemTemplate, Int maxSystems)
{
	Object *us = getObject();
	if (systemTemplate == 0)
		return;

	enum { MAX_BONES = 16 };
	Coord3D bonePositions[MAX_BONES];
	Int numBones = us->getMultiLogicalBonePosition(boneBaseName.str(), MAX_BONES, bonePositions, 0, false, 0);
	if (numBones == 0)
		return;
	if (numBones < maxSystems)
		maxSystems = numBones;

	Bool usedBoneIndices[MAX_BONES] = {};
	for (Int i = 0; i < maxSystems; ++i)
	{
#line 1514 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Body\\ActiveBody.cpp"
		Int boneIndex = GameClientRandomValue(0, numBones - 1);
		for (Int j = 0; j < numBones; ++j)
		{
			if (usedBoneIndices[boneIndex] != true)
			{
				const Coord3D *pos = &bonePositions[boneIndex];
				usedBoneIndices[boneIndex] = true;
				if (pos)
				{
					BfmeParticleSystemHandle particleSystem =
						TheParticleSystemManager->createParticleSystem(systemTemplate, true);
					if (particleSystem)
					{
						particleSystem->setPosition(pos);
						particleSystem->attachToObject(us);

						BodyParticleSystem *newEntry = new BodyParticleSystem;
						newEntry->m_particleSystemID = particleSystem->getSystemID();
						newEntry->m_next = m_particleSystems;
						m_particleSystems = newEntry;
					}
				}
				break;
			}
			boneIndex = (boneIndex + 1) % numBones;
		}
	}
}
