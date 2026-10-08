// ??0Rva005770F2@@QAE@PAVImpl@PlanRetreatsPhaseBehavior@StrategicInGameUI@@PBVModuleData@@@Z
// partial score=0.95 date=2026-10-08
// cl: /O1 /DNDEBUG /MD /EHsc
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
class SecondBase005D2111 {
public:
 virtual void observerSlot0(int);
 virtual void observerSlot1(void *,unsigned);
 virtual void observerSlot2(void *);
 virtual void observerSlot3(void *);
 virtual void observerSlot4(void *);
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
Rva005770F2::Rva005770F2(StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl *p,const ModuleData *a)
: Rva005D2111(*(void **)((char *)p+0x10),(void *)a),owner(p) {}
