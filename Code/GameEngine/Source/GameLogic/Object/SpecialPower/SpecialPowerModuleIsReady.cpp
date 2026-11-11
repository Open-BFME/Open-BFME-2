// cl: /GX- /MD
// ?isReady@SpecialPowerModule@@UBE_NXZ @0x004934DE 128B: SpecialPowerModule::isReady virtual slot.
// Evidence: ZH isReady semantic lead; target adds blocked+28 and status70 check;
// MI receiver is SpecialPowerModuleInterface subobject at primary+10;
// layout agrees with rowed getPowerName 0x004934B8; callees rowed testStatus/getControllingPlayer/friend_getFinalOverride/getOrStart/TheGameLogic.
#include "../../../../Include/Common/Overridable.h"
#include "../../../../Include/Common/SpecialPower.h"
#include "../../../../Include/GameLogic/Module/Rva002AC6B1PlayerTimers.h"
class Rva002AA0B1FloatField { public: float get() const; };
class Player;
enum ObjectStatusTypes { Status70 = 70 };
class Object { public: bool testStatus(ObjectStatusTypes) const; Player *getControllingPlayer() const; bool rva0028C15E(int type, float *value, int a, int b); };
class GameLogic; extern GameLogic *TheGameLogic;
struct SpecialReadyFrameView { char pad[0x40]; unsigned frame; };
static unsigned frame() { return ((SpecialReadyFrameView *)TheGameLogic)->frame; }
#include "../../../../Include/GameLogic/Module/SpecialPowerModuleData.h"
#include "../../../../Include/Common/ObjectModule.h"
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/SpecialPowerModule.h"
class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface {
public: virtual bool isReady() const; virtual void startPowerRecharge(float percent);
 int unknown14; unsigned available; int paused; unsigned pausedOnFrame; float pausedPercent; bool blocked;
};
bool SpecialPowerModule::isReady() const
{
 if (blocked)
  return false;
 const Object *obj = getObject();
 if (obj->testStatus(Status70))
  return false;
 const SpecialPowerModuleData *modData = static_cast<const SpecialPowerModuleData *>(getModuleData());
 if (obj && modData) {
  Player *player = obj->getControllingPlayer();
  if (player) {
   const SpecialPowerTemplate *power = modData->m_specialPowerTemplate;
   if (((const SpecialPowerTemplate *)power->friend_getFinalOverride())->m_sharedSyncedTimer)
    return frame() >= ((Rva002AC6B1PlayerTimers *)player)->getOrStart(power);
  }
 }
 return paused == 0 && frame() >= available;
}

// ?startPowerRecharge@SpecialPowerModule@@UAEXM@Z @0x0049369D 360B (WorldBuilder
// SpecialPowerModule::startPowerRecharge, SpecialPowerModule.cpp:627). ZH's
// shared-sync reset or reload rearm; BFME 2 scales the reload by the object's
// modifier query (type 12) and, for templates with flag bit 5, by one plus the
// player's float at 0x002AA0B1, keeps at least one frame, and a percent below
// one restarts the countdown from the current percent ready.
static inline bool testBit(unsigned flags, int bit) { return (flags & (1 << bit)) != 0; }
void SpecialPowerModule::startPowerRecharge(float percent)
{
 const SpecialPowerModuleData *modData = static_cast<const SpecialPowerModuleData *>(getModuleData());
 if (modData->m_specialPowerTemplate == 0)
  return;
 Object *obj = getObject();
 if (obj == 0)
  return;
 Player *player = obj->getControllingPlayer();
 if (player == 0)
  return;
 const SpecialPowerTemplate *power = modData->m_specialPowerTemplate;
 if (((const SpecialPowerTemplate *)power->friend_getFinalOverride())->m_sharedSyncedTimer)
 {
  ((Rva002AC6B1PlayerTimers *)player)->resetOrStart(power);
 }
 else
 {
  float modifier = 1.0f;
  obj->rva0028C15E(12, &modifier, 0, 1);
  float bonus = 1.0f;
  if (testBit(((const SpecialPowerTemplate *)modData->m_specialPowerTemplate->friend_getFinalOverride())->m_flags, 5))
   bonus = ((Rva002AA0B1FloatField *)player)->get() + 1.0f;
  unsigned frames = (unsigned)(((const SpecialPowerTemplate *)getSpecialPowerTemplate()->friend_getFinalOverride())->m_reloadTime * modifier * bonus);
  if (frames == 0)
   frames = 1;
  if (percent < 1.0f)
  {
   float ready = getPercentReady();
   if (ready == 0.0f)
    return;
   ready -= percent;
   if (ready < 0.0f)
    ready = 0.0f;
   available = frame() + (unsigned)(frames * (1.0f - ready));
  }
  else
  {
   available = frame() + frames;
   unknown14 = available - frame();
  }
 }
 blocked = false;
}
