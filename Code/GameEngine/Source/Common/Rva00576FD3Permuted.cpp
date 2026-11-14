// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva005770F2@@QAE@PAVImpl@PlanRetreatsPhaseBehavior@StrategicInGameUI@@PBVModuleData@@@Z, retail 0x00576fd3, 43 bytes. Banked partial (score 0.95) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Native576FD3 full43B RET8; primary table86E884 matches Rva005770F2's
// rowed scalar destructor5770D6. WB14CE990 proves
// the base call and the captured Impl at18; full base425B was read too.
// This remains BANKED: native secondary table86E870 is five observer
// callbacks (5D1D8F,50B238,47A69C,47A69C,47A69C), not a destructor.
// Slot identities/types are pending reconciliation with the existing owners;
// a byte match that copies DIR32 bindings does not prove those declarations.
class ModuleData;
namespace StrategicInGameUI { class PlanRetreatsPhaseBehavior {public:class Impl;}; }
class Rva005CCDDD {
public:virtual ~Rva005CCDDD();
protected:int unknown4,unknown8;
};
#include "../../Include/Common/LivingWorldBattleListener.h"

class SecondBase005D2111 : public LivingWorldBattleListener {
public:
};
class Rva005D2111:public Rva005CCDDD,public SecondBase005D2111 {
public:Rva005D2111(void *,void *);virtual ~Rva005D2111();
private:void *planner;void *army;
};
class Rva005770F2:public Rva005D2111 {
public:
 Rva005770F2(StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl *,const ModuleData *);
 virtual ~Rva005770F2();
private:StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl *owner;
};
Rva005770F2::Rva005770F2(StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl *p,const ModuleData *moduleData)
: Rva005D2111(*(void **)((char *)p+0x10),(void *)moduleData),owner(p) {}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?observerSlot0@SecondBase005D2111@@UAEXH@Z=?rva005D1D8F@Rva005D1D8F@@QAEXH@Z")
#pragma comment(linker, "/alternatename:?observerSlot1@SecondBase005D2111@@UAEXPAXI@Z=?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z")
#pragma comment(linker, "/alternatename:?observerSlot2@SecondBase005D2111@@UAEXPAX@Z=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:?observerSlot3@SecondBase005D2111@@UAEXPAX@Z=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:?observerSlot4@SecondBase005D2111@@UAEXPAX@Z=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
