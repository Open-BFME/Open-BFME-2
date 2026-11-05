// cl: /MD
//
// ?xfer@AutoHealBehavior@@MAEXPAVXfer@@@Z, retail 0x00452401, 95 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0083FCDC (class of rowed AutoHealBehavior
// ctor 0x00452592). Version(1,2) via Xfer slot 0x28, then the UpdateModule
// base xfer (rowed 0x0044DF9F), the UpgradeMux base at +0x20 (rowed
// 0x004CE397), the uint at +0x2C via Xfer slot 0x78, the bool at +0x30 via
// Xfer slot 0x90, and the version-gated uint at +0x34 via Xfer slot 0x78.
// Retail diverges from the BFME1 donor, which xfers user/uint/bool. The
// class is AutoHealBehavior.cpp's view. Recipe is the
// FireWeaponWhenDamagedBehaviorXfer version-gated slot-3 pattern.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"

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

void AutoHealBehavior::xfer(Xfer *xfer)
{
    Xfer::Version version(1, 2);
    *xfer == version;
    UpdateModule::xfer(xfer);
    UpgradeMux::upgradeMuxXfer(xfer);
    *xfer == m_soonestHealFrame;
    *xfer == m_stopped;
    if (version.m_minimum >= 2) {
        *xfer == m_radiusParticleSystemID;
    }
}
