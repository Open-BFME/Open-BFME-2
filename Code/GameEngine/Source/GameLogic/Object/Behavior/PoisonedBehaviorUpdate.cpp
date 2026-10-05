// cl: /O1 /MD /arch:SSE
//
// ?update@PoisonedBehavior@@UAE?AW4UpdateSleepTime@@XZ, retail 0x00483133,
// 152 bytes: Zero Hour's PoisonedBehavior::update (Behavior/
// PoisonedBehavior.cpp). Slot 16 of the UpdateModuleInterface vtable
// 0x008497B4 at PoisonedBehavior+0x10, so MSVC compiles the override with
// `this` at that subobject. Formerly rowed as the address-named
// ?rva00483133@Rva00482E96 view, which hand-adjusted by -0x10.
// Target evidence: poison stop frame +0x28, damage frame +0x24, amount
// +0x2C, death type +0x30 (PoisonedBehaviorCtor.cpp layout); the
// DamageInfo built through the rowed ctor 0x00263895 with source 0,
// damage type 8 (unresistable), FX override 0x1B (poison); interval at
// module data +0x08; stopPoisonedEffects is the rowed 0x00483083 and
// isEffectivelyDead the owner's bit 0 at +0x438.
//
// onDamage (0x004830FB, 22B) and onHealing (0x00483111, 34B) are slots 0
// and 1 of the DamageModuleInterface vtable 0x008497E8 at +0x20 (compiled
// with `this` at that subobject); startPoisonedEffects (0x00483011, 114B) is
// onDamage's callee. Target evidence: BFME 2's DAMAGE_POISON is 0x1A (damage
// type +0x10); out.m_actualDamageDealt at +0x70 and the death type at +0x1C;
// duration at module data +0x0C; getDrawable is the pinned out-of-line
// getter 0x005508E2 and TINT_STATUS_POISONED sets bit 2 of the drawable's
// +0x118; ZH's min on the damage frame keeps the current frame when lower.
class Thing;
class ModuleData;
class Object;
class DamageInfo;
class Drawable;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Rva00263895Member
{
public:
	Rva00263895Member();
	unsigned m_a;
	unsigned m_b;
};

class DamageInfo
{
public:
	Rva00263895Member m_head;
	unsigned m_08;
	unsigned m_0C;
	unsigned m_10;
	unsigned m_14;
	unsigned m_18;
	unsigned m_1C;
	float m_20;
	unsigned char m_pad[0x70 - 0x24];
	float m_70; // out.m_actualDamageDealt
	unsigned char m_pad74[0x7c - 0x74];
};

class Object
{
public:
	Drawable *getDrawable() const;
	void attemptDamage(DamageInfo *damageInfo);
	unsigned char m_pad[0x438];
	unsigned char m_flag;
};

class GameLogic
{
public:
	unsigned getFrame() { return m_frame; }
private:
	unsigned char m_pad[0x40];
	unsigned m_frame;
};

extern GameLogic *TheGameLogic;

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class DamageModuleInterface
{
public:
	DamageModuleInterface() {}
	virtual void onDamage(DamageInfo *damageInfo) = 0;
	virtual void onHealing(DamageInfo *damageInfo) = 0;
};

class Drawable
{
public:
	void setTintStatus(int statusBits) { m_tintStatus |= statusBits; }
private:
	unsigned char m_pad[0x118];
	unsigned m_tintStatus; // +0x118
};

template <typename T> inline const T &pbMin(const T &a, const T &b) { return (a < b) ? a : b; }

class PoisonedBehaviorModuleData
{
public:
	unsigned char m_pad[8];
	unsigned m_poisonDamageIntervalData;
	unsigned m_poisonDurationData;
};

class PoisonedBehavior : public UpdateModule, public DamageModuleInterface
{
public:
	virtual UpdateSleepTime update();
	virtual void onDamage(DamageInfo *damageInfo);
	virtual void onHealing(DamageInfo *damageInfo);
	void rva00483083(); // stopPoisonedEffects
protected:
	void startPoisonedEffects(const DamageInfo *damageInfo);
	UpdateSleepTime calcSleepTime();
	const PoisonedBehaviorModuleData *getPoisonedBehaviorModuleData() const { return (const PoisonedBehaviorModuleData *)m_moduleData; }
	Object *getObject() const { return m_object; }
private:
	unsigned int m_poisonDamageFrame;
	unsigned int m_poisonOverallStopFrame;
	float m_poisonDamageAmount;
	int m_deathType;
};

UpdateSleepTime PoisonedBehavior::update()
{
	const PoisonedBehaviorModuleData* d = getPoisonedBehaviorModuleData();
	unsigned now = TheGameLogic->getFrame();

	if( m_poisonOverallStopFrame == 0 )
	{
		return UPDATE_SLEEP_FOREVER;
		//we aren't poisoned, so nevermind
	}

	if (m_poisonDamageFrame != 0 && now >= m_poisonDamageFrame)
	{
		// If it is time to do damage, then do it and reset the damage timer
		DamageInfo damage;
		damage.m_08 = 0;		// in.m_sourceID = INVALID_ID
		damage.m_1C = (unsigned)m_deathType;	// in.m_deathType
		damage.m_20 = m_poisonDamageAmount;	// in.m_amount
		damage.m_10 = 8;		// in.m_damageType = DAMAGE_UNRESISTABLE
		damage.m_14 = 0x1b;		// in.m_damageFXOverride = DAMAGE_POISON
		getObject()->attemptDamage( &damage );

		m_poisonDamageFrame = now + d->m_poisonDamageIntervalData;
	}

	// If we are now at zero we need to turn off our special effects...
	// unless the poison killed us, then we continue to be a pulsating toxic pus ball
	if( m_poisonOverallStopFrame != 0 &&
			now >= m_poisonOverallStopFrame &&
			!(getObject()->m_flag & 1))
	{
		rva00483083();
	}

	return calcSleepTime();
}

void PoisonedBehavior::onDamage( DamageInfo *damageInfo )
{
	if( damageInfo->m_10 == 0x1a )	// in.m_damageType == DAMAGE_POISON
		startPoisonedEffects( damageInfo );
}

void PoisonedBehavior::onHealing( DamageInfo *damageInfo )
{
	rva00483083();
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

void PoisonedBehavior::startPoisonedEffects( const DamageInfo *damageInfo )
{
	const PoisonedBehaviorModuleData* d = getPoisonedBehaviorModuleData();
	unsigned now = TheGameLogic->getFrame();

	// We are going to take the damage dealt by the original poisoner every so often for a while.
	m_poisonDamageAmount = damageInfo->m_70;

	m_poisonOverallStopFrame = now + d->m_poisonDurationData;

	// If we are getting re-poisoned, don't reset the damage counter if running, but do set it if unset
	if( m_poisonDamageFrame != 0 )
		m_poisonDamageFrame = pbMin( m_poisonDamageFrame, now + d->m_poisonDamageIntervalData );
	else
		m_poisonDamageFrame = now + d->m_poisonDamageIntervalData;

	m_deathType = damageInfo->m_1C;

	Drawable *myDrawable = getObject()->getDrawable();
	if( myDrawable )
		myDrawable->setTintStatus( 1 << 2 );	// TINT_STATUS_POISONED

	setWakeFrame(getObject(), calcSleepTime());
}
