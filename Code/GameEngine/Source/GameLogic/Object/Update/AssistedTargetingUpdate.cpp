// cl: /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/update_modules_bfme2 /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
#define BFME_SNAPSHOT_NAME_SLOT
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };
enum SleepyUpdatePhase { PHASE_NORMAL = 2 };
enum WeaponStatus { READY_TO_FIRE = 0 };
enum WeaponSlotType { PRIMARY_WEAPON = 0, SECONDARY_WEAPON = 1, TERTIARY_WEAPON = 2 };
enum WeaponLockType { LOCKED_TEMPORARILY = 1 };
enum CommandSourceType { CMD_FROM_AI = 2 };
#include "../../../../Include/Common/NameKeyGenerator.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Weapon.h"
#include "../object.h"
class UnicodeString; class PooledString; class Coord3DBase;
struct ICoord3D; struct Region3D; struct IRegion3D;
class Coord2D; struct ICoord2D; struct Region2D; struct IRegion2D;
class RealRange; struct RGBColor; class RGBAColorReal; class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"
class AICommandInterface {
public:
    void rva0026C2D9(Object *victim, int shots, CommandSourceType source);
};
struct BfmeAssistedLaserTemplates {
    char prefix[8];
    int m_clipSize;
    WeaponSlotType m_weaponSlot;
    const ThingTemplate *fromAssisted;
    const ThingTemplate *toTarget;
};
class AssistedTargetingUpdate : public UpdateModule {
public:
    AssistedTargetingUpdate(Thing *thing, const ModuleData *data);
    virtual ~AssistedTargetingUpdate();
    virtual NameKeyType getModuleNameKey() const;
    virtual UpdateSleepTime update();
    bool isFreeToAssist() const;
    void assistAttack(const Object *requestingObject, Object *victimObject);
protected:
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *xfer);
private:
    void makeFeedbackLaser(const ThingTemplate *laserTemplate, const Object *from, const Object *to);
};
typedef char AssistedExtent[sizeof(AssistedTargetingUpdate) == 0x20 ? 1 : -1];


bool AssistedTargetingUpdate::isFreeToAssist() const
{
    const Object *me = getObject();
    if (!me->isAbleToAttack())
        return false;
    bool ready = me->getCurrentWeapon(0) && me->getCurrentWeapon(0)->getStatus() == READY_TO_FIRE;
    return ready;
}
void AssistedTargetingUpdate::assistAttack(const Object *requestingObject, Object *victimObject)
{
    const BfmeAssistedLaserTemplates *md = reinterpret_cast<const BfmeAssistedLaserTemplates *>(getModuleData());
    Object *me = getObject();
    if (*reinterpret_cast<void **>(reinterpret_cast<char *>(me) + 0x258) == 0)
        return;
    me->setWeaponLock(md->m_weaponSlot, LOCKED_TEMPORARILY);
    reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(*reinterpret_cast<void **>(reinterpret_cast<char *>(me) + 0x258)) + 0x20)->
        rva0026C2D9(victimObject, md->m_clipSize, CMD_FROM_AI);
    const BfmeAssistedLaserTemplates *lasers = md;
    if (lasers->fromAssisted)
        makeFeedbackLaser(lasers->fromAssisted, requestingObject, me);
    if (lasers->toTarget)
        makeFeedbackLaser(lasers->toTarget, me, victimObject);
}
UpdateSleepTime AssistedTargetingUpdate::update() { return UPDATE_SLEEP_FOREVER; }
void AssistedTargetingUpdate::loadPostProcess() { UpdateModule::loadPostProcess(); }


NameKeyType AssistedTargetingUpdate::getModuleNameKey() const
{
    static NameKeyType nk = TheNameKeyGenerator->nameToKey("AssistedTargetingUpdate");
    return nk;
}
