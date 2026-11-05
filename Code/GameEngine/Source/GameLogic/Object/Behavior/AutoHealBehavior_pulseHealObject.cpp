// cl: /MD /DNDEBUG
// ?pulseHealObject@AutoHealBehavior@@QAEXPAVObject@@_N@Z @0x004526C6 207B: Zero Hour's
// pulseHealObject with BFME 2's FX flag. The nonStackable gate reads the body's
// last healing timestamp (BodyModuleInterface slot 17), the heal amount takes the
// attribute bonus 0x13, and the radius selects sole-benefactor healing.
// Evidence: onDamage 0x0045266B reads the same +0x04/+0x08/+0x2C/+0x30 layout;
// callees rowed rva0028C149, attemptHealing, attemptHealingFromSoleBenefactor and
// doFXObj; TheGameLogic frame +0x40; module data 0x11C/0x120/0x128/0x150/0x154
// from the AutoHealBehaviorModuleData ctor. The class is AutoHealBehavior.cpp's view.
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

enum NameKeyType
{
	NK_UNKNOWN = 0
};

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };

class DamageInfo;
class Xfer;
class Object;
class AutoHealBehaviorModuleData;

enum BodyDamageType;

class DamageModuleInterface
{
public:
    virtual void onDamage(DamageInfo *) = 0;
    virtual void onHealing(DamageInfo *) = 0;
    virtual void onBodyDamageStateChange(const DamageInfo *, BodyDamageType, BodyDamageType) = 0;
};

class AutoHealBehavior : public UpdateModule, public UpgradeMux, public DamageModuleInterface
{
public:
    AutoHealBehavior(Thing *, const ModuleData *);
    virtual ~AutoHealBehavior();
    void stopHealing();
    void rva004523CC();
    void pulseHealObject(Object *obj, bool playFX);
    static NameKeyType rva00045235E();
    virtual void onDamage(DamageInfo *);
protected:
    virtual void xfer(Xfer *xfer);
    virtual void upgradeImplementation();
    virtual void performUpgradeFX();
    bool isUpgradeActive() const { return isAlreadyUpgraded(); }
    const AutoHealBehaviorModuleData *getAutoHealBehaviorModuleData() const
    {
        return (const AutoHealBehaviorModuleData *)m_moduleData;
    }
private:
    unsigned int m_soonestHealFrame;
    bool m_stopped;
    unsigned int m_radiusParticleSystemID;
};

#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

#include "../../../../Include/GameLogic/Module/BodyModule.h"

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary = 0);
};

// The Object accessors pulseHealObject reaches; +0x254 is the body module.
class Object
{
public:
	bool rva0028C149(int attribute, float *value, int arg);
	void attemptHealing(float amount, const Object *source);
	bool attemptHealingFromSoleBenefactor(float amount, const Object *source, unsigned int extra);
	BodyModuleInterface *getBodyModule() const { return m_body; }
private:
	unsigned char m_pad00[0x254];
	BodyModuleInterface *m_body; // +0x254
};

// Offsets from the rowed AutoHealBehaviorModuleData ctor and field parse table.
class AutoHealBehaviorModuleData
{
public:
	char m_pad00[0x11C];
	int m_healingAmount; // +0x11C
	unsigned int m_healingDelay; // +0x120
	unsigned int m_startHealingDelay; // +0x124
	int m_radius; // +0x128
	char m_pad12C[0x150 - 0x12C];
	const FXList *m_unitHealPulseFX; // +0x150
	bool m_nonStackable; // +0x154
};

void AutoHealBehavior::pulseHealObject(Object *obj, bool playFX)
{
	if (m_stopped)
		return;
	const AutoHealBehaviorModuleData *data = getAutoHealBehaviorModuleData();
	if (data->m_nonStackable)
	{
		BodyModuleInterface *body = obj->getBodyModule();
		if (body)
		{
			unsigned int frame = TheGameLogic->getFrame();
			if (body->getLastHealingTimestamp() + data->m_healingDelay > frame)
				return;
		}
	}
	float bonus;
	int zero = 0;
	getObject()->rva0028C149(0x13, &bonus, zero);
	int amount = (int)((float)data->m_healingAmount + bonus);
	if (data->m_radius == zero)
		obj->attemptHealing((float)amount, getObject());
	else
		obj->attemptHealingFromSoleBenefactor((float)amount, getObject(), data->m_healingDelay);
	if (playFX)
		FXList::doFXObj(data->m_unitHealPulseFX, obj, (const Object *)zero);
	m_soonestHealFrame = TheGameLogic->getFrame() + data->m_healingDelay;
}
