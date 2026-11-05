// cl: /FIzh_ascii.h /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/update_modules_bfme2 /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_autoheal /Ireference/shims/dockupdate /Ireference/shims/ocls /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfmefrustum
// stlport

// Native AutoHealBehavior bodies. The constructor establishes UpdateModule
// at +0, UpgradeMux at +0x20, damage interface at +0x28 and state at +0x2C.
// The remaining methods retain their existing owners until tu_skeleton merges
// their verified donors. No donor-only lifetime or postload bodies are emitted.
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/UpgradeMux.h"
#include "../../../../Include/Common/BfmeAccessorMacros.h"

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };
class DamageInfo;
enum BodyDamageType;
enum NameKeyType;
class GameLogic;
extern GameLogic *TheGameLogic;

class DamageModuleInterface
{
public:
    virtual void onDamage(DamageInfo *) = 0;
    virtual void onHealing(DamageInfo *) = 0;
    virtual void onBodyDamageStateChange(const DamageInfo *, BodyDamageType, BodyDamageType) = 0;
};

class UpgradeMuxData
{
public:
    void performUpgradeFX(Object *) const;
};

class AutoHealBehavior : public UpdateModule, public UpgradeMux, public DamageModuleInterface
{
public:
    AutoHealBehavior(Thing *, const ModuleData *);
    virtual ~AutoHealBehavior();
    void stopHealing();
    static NameKeyType rva00045235E();
    virtual void onDamage(DamageInfo *);
protected:
    virtual void upgradeImplementation();
    virtual void performUpgradeFX();
    bool isUpgradeActive() const { return isAlreadyUpgraded(); }
private:
    unsigned int m_soonestHealFrame;
    bool m_stopped;
    unsigned int m_radiusParticleSystemID;
};

struct BfmeAutoHealDamageData
{
    unsigned char m_padding[0x124];
    unsigned int m_startHealingDelay;
    unsigned int m_radius;
};

BFME_DISP8_LEA_NEG_SBB_GETTER(Rva004523A9LeaNegSbbField, 12, 0x1C)

class Rva0024C7B3Member
{
public:
    Rva0024C7B3Member();
private:
    char m_bytes[0x1C];
};
class Rva004523F5
{
public:
    Rva004523F5();
private:
    Rva0024C7B3Member m_00;
};

void AutoHealBehavior::stopHealing()
{
	m_stopped = true;
	m_soonestHealFrame = 0x3FFFFFFF;
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
/** Damage has been dealt, this is an opportunity to reach to that damage */
//-------------------------------------------------------------------------------------------------
void AutoHealBehavior::onDamage( DamageInfo *damageInfo )
{
	// BFME's AutoHealBehavior base layout differs from the vendored Zero Hour
	// declaration in this interface-adjusted method.  Use the retail offsets
	// explicitly so the generated body keeps the original field accesses.
	if (*(const bool *)((const char *)this + 0x30))
		return;

	const BfmeAutoHealDamageData *d =
		*(const BfmeAutoHealDamageData *const *)((const char *)this + 0x04);
	if (isUpgradeActive() && d->m_radius == 0)
	{
		// if this is nonzero, getting damaged resets our healing process. so go to
		// sleep for this long.
		if (*(const int *)((const char *)damageInfo + 0x18) != 2 && d->m_startHealingDelay > 0)
		{
			setWakeFrame(*(Object *const *)((const char *)this + 0x08), (UpdateSleepTime)d->m_startHealingDelay);
		}
		else if( *(const unsigned int *)((const char *)TheGameLogic + 0x40) > *(const unsigned int *)((const char *)this + 0x2c) ) // BFME2 GameLogic frame at +0x40
		{
			// We can only force an immediate wake if we are ready to heal.  Otherwise we will
			// heal on a timer AND at every damage input.
			setWakeFrame(*(Object *const *)((const char *)this + 0x08), UPDATE_SLEEP_NONE);
		}
	}
}

void AutoHealBehavior::upgradeImplementation()
{
    setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}

void AutoHealBehavior::performUpgradeFX()
{
    ((const UpgradeMuxData *)((const char *)m_moduleData + 0x08))->performUpgradeFX(getObject());
}

Rva004523F5::Rva004523F5()
{
}
