// cl: /O1 /arch:SSE /DNDEBUG /MD /GX
//
// ?attemptDamage@DetachableRiderBody@@UAEXPAVDamageInfo@@@Z, retail
// 0x004C1D49, 322 bytes: slot 0 of DetachableRiderBody's +0x10 body-module
// interface table 0x00C5BF48 (the matched ctor 0x004C1C82 installs it; its
// other slots are ActiveBody's, slot 1 the rowed attemptHealing 0x004BEE21),
// the slot ActiveBody fills with 0x004BFE07 (pinned as
// ActiveBody::attemptDamage), so `this` is that subobject and the +0x100
// UpgradeMux is reached at +0xF0.
//
// While the mux's slot 0 reports the upgrade active, a game-logic random
// roll in [0,1) (DetachableRiderBody.cpp line 94 by the retail path string)
// at or above the module data's +0x17C chance, with the owner's +0x114 bit 8
// clear, status 0x27 clear and +0x1C8 bit 4 clear, turns a killing hit (the
// DamageInfo +0x24 flag, or an amount at +0x20 that would take getHealth to
// zero) into one that leaves getMaxHealth() * data +0x174 health, and kills
// the rider through the owner's DetachableRiderUpdate (rowed killRider
// 0x004AE988, found by the function-local name key). The damage then goes to
// ActiveBody::attemptDamage. getHealth/getMaxHealth are interface slots 4 and
// 6, whose bodies read ActiveBody +0x18 and +0x20. Field names past those are
// positional: their identities are not established.

class Object;
class ModuleData;

typedef float Real;

enum ObjectStatusTypes
{
	OBJECT_STATUS_27 = 0x27
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, int line);

class DamageInfo
{
public:
	unsigned char m_pad00[0x20];
	Real m_amount;			// +0x20
	bool m_kill;			// +0x24
};

struct DetachableRiderBodyModuleData
{
	unsigned char m_pad000[0x174];
	Real m_174;			// +0x174
	unsigned char m_pad178[0x17C - 0x178];
	Real m_17C;			// +0x17C
};

class Module
{
};

class DetachableRiderUpdate
{
public:
	void killRider();
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	bool test114Bit8() const { return ((m_114 >> 8) & 1) != 0; }
	bool test1C8Bit4() const { return (m_1C8 & 0x10) != 0; }
protected:
	Module *findModule(NameKeyType key) const;
	friend class DetachableRiderBody;
private:
	unsigned char m_pad000[0x114];
	unsigned int m_114;		// +0x114
	unsigned char m_pad118[0x1C8 - 0x118];
	unsigned char m_1C8;		// +0x1C8
};

class UpgradeMux
{
public:
	virtual bool isUpgradeActive() const = 0;
};

class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};

class BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo) = 0;
	virtual void i01() = 0;
	virtual void i02() = 0;
	virtual void i03() = 0;
	virtual Real getHealth() const = 0;
	virtual void i05() = 0;
	virtual Real getMaxHealth() const = 0;
};

class BodyModule : public ModuleBase, public BehaviorModuleInterface, public BodyModuleInterface
{
};

class ActiveBody : public BodyModule
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
protected:
	unsigned char m_pad014[0x100 - 0x14];
};

class DetachableRiderBody : public ActiveBody, public UpgradeMux
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
private:
	const DetachableRiderBodyModuleData *data() const { return (const DetachableRiderBodyModuleData *)m_moduleData; }
};

// ?attemptDamage@DetachableRiderBody@@UAEXPAVDamageInfo@@@Z @0x004C1D49
void DetachableRiderBody::attemptDamage(DamageInfo *damageInfo)
{
	Object *obj = m_object;
	const DetachableRiderBodyModuleData *d = data();
	bool active = isUpgradeActive();
	bool keepRider = GetGameLogicRandomValueReal(0.0f, 1.0f, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Body\\DetachableRiderBody.cpp", 94) < d->m_17C;
	if (obj->test114Bit8())
		keepRider = true;

	if (active && !keepRider && !obj->testStatus(OBJECT_STATUS_27) && !obj->test1C8Bit4())
	{
		Real health = getHealth();
		Real floor = getMaxHealth() * data()->m_174;
		Real amount = damageInfo->m_amount;
		if (damageInfo->m_kill || health - amount <= 0.0f)
		{
			damageInfo->m_amount = health - floor;
			damageInfo->m_kill = false;
			static NameKeyType key = TheNameKeyGenerator->nameToKey("DetachableRiderUpdate");
			DetachableRiderUpdate *update = (DetachableRiderUpdate *)obj->findModule(key);
			if (update)
				update->killRider();
		}
	}

	ActiveBody::attemptDamage(damageInfo);
}
