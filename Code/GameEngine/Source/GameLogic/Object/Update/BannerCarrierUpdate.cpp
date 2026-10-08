// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// BFME1 BannerCarrierUpdate_update.cpp donor9cbfb551 supplies the update
// control-flow skeleton; native BFME2 constructor vtable C4F82C at owner10
// and WB BannerCarrierUpdate.cpp:477 corroborate identity independently.
// Native adds upgrade/status guards; Object fields and vslots are measured.
#include "ascii_string.h"
#include "../../../Common/GameLogicObjectLookupView.h"
typedef unsigned int UnsignedInt;
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1 };
enum KindOfType { KINDOF_DUMMY=0 };
enum ObjectStatusTypes { STATUS_DUMMY=0 };
class UpgradeTemplate;
class UpgradeCenter { public: const UpgradeTemplate *findUpgrade(const AsciiString &) const; };
extern UpgradeCenter *TheUpgradeCenter;
extern GameLogic *TheGameLogic;
class AIUpdateInterface { public: bool isMoving() const; char pad[0x3B1]; bool pending; };
class Gen_0028EF10 { public: bool rva004B0FA0(); };
template<int N> class BannerSlots : public BannerSlots<N-1> { public: virtual void gap(char (*)[N])=0; };
template<> class BannerSlots<0> {};
class BannerContainResult : public BannerSlots<36> { public: virtual bool testRefresh(int *,unsigned)=0; };
class BannerContain : public BannerSlots<31> { public: virtual BannerContainResult *getHorde()=0; };
class Object { public:
 bool isKindOf(KindOfType) const;
 bool testStatus(ObjectStatusTypes) const;
 bool rva00290D2B(const UpgradeTemplate *) const;
 Object *rva002931F5(bool);
 int rva0028AF76() const;
 char pad00[0x24C]; Gen_0028EF10 *m_stats; BannerContain *m_contain;
 char pad254[4]; AIUpdateInterface *m_ai;
 char pad25C[0x274-0x25C]; Object *m_containedBy;
};
struct BannerCarrierUpdateModuleData { char pad00[8]; unsigned delay,freeUnitTime; char pad10[0x28]; bool replenish; char pad39[7]; AsciiString upgrade; };
class BannerBase { public: virtual void slot0();
 void rva004973CF();
 bool rva00496BD2(Object *);
 const BannerCarrierUpdateModuleData *data; Object *object;
};
class BannerOther { public: virtual void slot0(); };
class UpdateModuleInterface { public: virtual UpdateSleepTime update()=0; };
class BannerCarrierUpdate : public BannerBase, public BannerOther, public UpdateModuleInterface {
public:
 virtual UpdateSleepTime update();
 void rva004973CF(); bool rva00496BD2(Object *);
};
UpdateSleepTime BannerCarrierUpdate::update() {
 const BannerCarrierUpdateModuleData *d=data;
 Object *obj=object;
 if(!obj) return (UpdateSleepTime)d->delay;
 if(!d->upgrade.isEmpty()) {
  const UpgradeTemplate *up=TheUpgradeCenter->findUpgrade(d->upgrade);
  if(!up || !obj->rva00290D2B(up)) return (UpdateSleepTime)d->delay;
 }
 if(obj->isKindOf((KindOfType)0x45) || obj->testStatus((ObjectStatusTypes)0x57)
  || obj->isKindOf((KindOfType)0x220) || obj->testStatus((ObjectStatusTypes)0x3E)) return (UpdateSleepTime)d->delay;
 AIUpdateInterface *ai=obj->m_ai;
 if(ai && (ai->isMoving() || ai->pending)) return (UpdateSleepTime)d->delay;
 Object *resolved=obj->rva002931F5(false);
 Gen_0028EF10 *stats=resolved?resolved->m_stats:obj->m_stats;
 if(stats && stats->rva004B0FA0()) return (UpdateSleepTime)d->delay;
 if(d->replenish) { rva004973CF(); return (UpdateSleepTime)d->delay; }
 if(obj->isKindOf((KindOfType)0x25) || obj->isKindOf((KindOfType)0x3D)) return (UpdateSleepTime)d->delay;
 if(obj->m_containedBy) {
  unsigned frame=TheGameLogic->getFrame();
  if((unsigned)obj->m_containedBy->rva0028AF76()>frame-d->freeUnitTime) return (UpdateSleepTime)d->delay;
 }
 {
  int out=0;
  if(obj->m_containedBy && obj->m_containedBy->rva002931F5(false)) {
   Object *contained=obj->m_containedBy->rva002931F5(false);
   if(contained->m_contain->getHorde()->testRefresh(&out,d->freeUnitTime)) return (UpdateSleepTime)d->delay;
  }
 }
 rva00496BD2(obj);
 return (UpdateSleepTime)d->delay;
}
