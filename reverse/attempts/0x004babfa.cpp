// ?onDamage@ReflectDamage@@UAEXPAVDamageInfo@@@Z
// partial score=0.97 date=2026-10-04
// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ReflectDamage::onDamage, retail 0x004BABFA, 137 bytes: slot 0 of the
// class's +0x10 damage-module interface vftable 0x00C59CB0, so `this` is that
// subobject (module data at -0x0C, Object at -0x08).
// Donor: BFME 1 ReflectDamage_onDamage.cpp (reference/open-bfme-1) gives the
// flow and the module data fields; BFME2 differs in the DamageInfo (0x7C
// bytes, out-of-line ctor 0x00263895, see ObjectKill.cpp) and in calling the
// non-virtual Object::attemptDamage 0x0029848E.
// Target: damage of type 13 is never reflected (it is what reflection
// deals); otherwise when the type's bit (type - 1) is in the module data mask
// (+0x08) and the source Object (input +0x08, looked up through TheGameLogic)
// still exists, it takes percentage (+0x0C) times the amount (+0x20), at least
// the minimum (+0x10), as type 13 with +0x14 and death type (+0x1C) both 2,
// from our Object's ID.
enum DamageType
{
	DAMAGE_REFLECTED = 13
};
enum DeathType
{
	DEATH_02 = 2
};
enum ObjectID
{
	INVALID_ID = 0
};

// The DamageInfo: input fields as the target body and Object::kill read and
// write them; constructed by the pinned 0x00263895.
class Rva00263895Member
{
public:
	Rva00263895Member() throw();
	int m_00;
	int m_04;
	ObjectID m_sourceID;		// +0x08
	int m_0C;
	DamageType m_damageType;	// +0x10
	int m_14;			// +0x14
	int m_18;
	DeathType m_deathType;		// +0x1C
	float m_amount;			// +0x20
	unsigned char m_pad24[0x7C - 0x24];
};
class DamageInfo : public Rva00263895Member
{
public:
	DamageInfo() throw() {}
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	void attemptDamage(DamageInfo *damageInfo);
private:
	unsigned char m_pad00[0x74];
	ObjectID m_id; // +0x74
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

struct ReflectDamageModuleData
{
	unsigned char m_pad00[0x08];
	unsigned int m_damageTypes;		// +0x08
	float m_reflectDamagePercentage;	// +0x0C
	float m_reflectDamageMinimum;		// +0x10
};

class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};
class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo) = 0;
};
class DamageModule : public BehaviorModule, public BehaviorModuleInterface,
	public DamageModuleInterface
{
};
class ReflectDamage : public DamageModule
{
public:
	virtual void onDamage(DamageInfo *damageInfo);
	const ReflectDamageModuleData *getReflectDamageModuleData() const
	{
		return (const ReflectDamageModuleData *)m_moduleData;
	}
};

void ReflectDamage::onDamage(DamageInfo *damageInfo)
{
	const ReflectDamageModuleData *data = getReflectDamageModuleData();
	if (damageInfo->m_damageType == DAMAGE_REFLECTED)
		return;
	if ((data->m_damageTypes & (1 << (damageInfo->m_damageType - 1))) == 0)
		return;
	Object *source = TheGameLogic->findObjectByID(damageInfo->m_sourceID);
	if (source == 0)
		return;
	DamageInfo reflected;
	float amount = damageInfo->m_amount * data->m_reflectDamagePercentage;
	reflected.m_14 = 2;
	reflected.m_deathType = DEATH_02;
	reflected.m_damageType = DAMAGE_REFLECTED;
	reflected.m_sourceID = m_object->getID();
	if (!(amount > data->m_reflectDamageMinimum))
		amount = data->m_reflectDamageMinimum;
	reflected.m_amount = amount;
	source->attemptDamage(&reflected);
}
