// cl: /MD
//
// ?rva004523CC@AutoHealBehavior@@QAEXXZ, retail 0x004523CC, 29 bytes.
// Gap between 0x004523B6 (stopHealing) and 0x004523F5 (Rva ctor).
// Clears m_stopped at +0x30, gives the UpgradeMux base at +0x20 its self
// upgrade (rowed giveSelfUpgrade 0x45230C), then wakes the module now
// through rowed setWakeFrame 0x44DF71. Caller at 0x451A2D finds
// AutoHealBehavior by its cached pool key and calls this when non-null.
// The class is AutoHealBehavior.cpp's view (rowed ctor 0x452592 layout).
// Honest address name: method purpose unproven beyond activation, the
// opposite of stopHealing.
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

void AutoHealBehavior::rva004523CC()
{
    m_stopped = false;
    giveSelfUpgrade();
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
