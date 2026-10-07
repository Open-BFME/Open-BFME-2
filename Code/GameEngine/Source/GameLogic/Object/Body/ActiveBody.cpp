// cl: /O1 /EHsc /MD /arch:SSE
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

typedef float Real;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum BodyDamageType { BODY_PRISTINE, BODY_DAMAGED, BODY_REALLYDAMAGED, BODY_RUBBLE };

enum DamageType { DAMAGE_HEALING = 7 };
enum KindOfType { KINDOF_220 = 0x220 };
enum ObjectID { INVALID_ID = 0 };

class Object;
class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);	// 0x000B2235
};

class DamageInfoInput
{
public:
	UnsignedInt m_sourceID;			// +0x00
	unsigned char m_pad04[0x08];
	DamageType m_damageType;		// +0x0C
};

class DamageInfo
{
public:
	void *m_vptr;
	DamageInfoInput in;			// +0x04
	unsigned char m_pad14[0x70 - 0x14];
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
	virtual void doDamageFX(const DamageInfo *damageInfo);	// +0x48
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
	unsigned char m_pad34[0xC0 - 0x34];
	UnsignedInt m_lastHealingTimestamp;	// +0xC0
	unsigned char m_padC4[0xEC - 0xC4];
	ObjectID m_linkedObjectID;		// +0xEC
	unsigned char m_padF0[0xF8 - 0xF0];
	Armor m_curArmor;			// +0xF8
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
