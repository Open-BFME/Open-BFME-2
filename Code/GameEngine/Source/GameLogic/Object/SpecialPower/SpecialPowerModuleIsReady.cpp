// cl: /GX- /MD
// ?isReady@SpecialPowerModule@@UBE_NXZ @0x004934DE 128B: SpecialPowerModule::isReady virtual slot.
// Evidence: ZH isReady semantic lead; target adds blocked+28 and status70 check;
// MI receiver is SpecialPowerModuleInterface subobject at primary+10;
// layout agrees with rowed getPowerName 0x004934B8; callees rowed testStatus/getControllingPlayer/friend_getFinalOverride/getOrStart/TheGameLogic.
class Overridable { public: const Overridable *friend_getFinalOverride() const; char pad[0x10]; };
class SpecialPowerTemplate : public Overridable { public: unsigned unknown10; unsigned id; unsigned flags; char pad1C[4]; unsigned reloadTime; char pad24[0x59-0x24]; bool shared; };
class Rva002AC6B1PlayerTimers { public: unsigned getOrStart(const SpecialPowerTemplate *); void resetOrStart(const SpecialPowerTemplate *); };
class Rva002AA0B1FloatField { public: float get() const; };
class Player;
enum ObjectStatusTypes { Status70 = 70 };
class Object { public: bool testStatus(ObjectStatusTypes) const; Player *getControllingPlayer() const; bool rva0028C15E(int type, float *value, int a, int b); };
class GameLogic; extern GameLogic *TheGameLogic;
struct SpecialReadyFrameView { char pad[0x40]; unsigned frame; };
static unsigned frame() { return ((SpecialReadyFrameView *)TheGameLogic)->frame; }
class ModuleData { public: virtual ~ModuleData(); };
class SpecialPowerModuleData : public ModuleData { public: int unknown4; const SpecialPowerTemplate *power; };
class ObjectModule { protected: virtual ~ObjectModule(); const ModuleData *data; Object *object; };
class BehaviorModuleInterface { public: virtual void anchor(); };
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface { protected: virtual ~BehaviorModule(); };
class SpecialPowerModuleInterface {
public:
 virtual bool isModuleForPower(const SpecialPowerTemplate *) const = 0;
 virtual bool isReady() const = 0;
 virtual float getPercentReady() const = 0;
 virtual void slot3() = 0; virtual void slot4() = 0; virtual void slot5() = 0;
 virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const = 0;
 virtual void startPowerRecharge(float percent) = 0;
};
class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface {
public: virtual bool isReady() const; virtual void startPowerRecharge(float percent);
 int unknown14; unsigned available; int paused; unsigned pausedOnFrame; float pausedPercent; bool blocked;
};
bool SpecialPowerModule::isReady() const
{
 if (blocked)
  return false;
 const Object *obj = object;
 if (obj->testStatus(Status70))
  return false;
 const SpecialPowerModuleData *modData = (const SpecialPowerModuleData *)data;
 if (obj && modData) {
  Player *player = obj->getControllingPlayer();
  if (player) {
   const SpecialPowerTemplate *power = modData->power;
   if (((const SpecialPowerTemplate *)power->friend_getFinalOverride())->shared)
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
 const SpecialPowerModuleData *modData = (const SpecialPowerModuleData *)data;
 if (modData->power == 0)
  return;
 Object *obj = object;
 if (obj == 0)
  return;
 Player *player = obj->getControllingPlayer();
 if (player == 0)
  return;
 const SpecialPowerTemplate *power = modData->power;
 if (((const SpecialPowerTemplate *)power->friend_getFinalOverride())->shared)
 {
  ((Rva002AC6B1PlayerTimers *)player)->resetOrStart(power);
 }
 else
 {
  float modifier = 1.0f;
  obj->rva0028C15E(12, &modifier, 0, 1);
  float bonus = 1.0f;
  if (testBit(((const SpecialPowerTemplate *)modData->power->friend_getFinalOverride())->flags, 5))
   bonus = ((Rva002AA0B1FloatField *)player)->get() + 1.0f;
  unsigned frames = (unsigned)(((const SpecialPowerTemplate *)getSpecialPowerTemplate()->friend_getFinalOverride())->reloadTime * modifier * bonus);
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
