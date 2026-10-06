// cl: /Oa /GX- /MD
// ?isReady@SpecialPowerModule@@UBE_NXZ @0x004934DE 128B: SpecialPowerModule::isReady virtual slot.
// Evidence: ZH isReady semantic lead; target adds blocked+28 and status70 check;
// MI receiver is SpecialPowerModuleInterface subobject at primary+10;
// layout agrees with rowed getPowerName 0x004934B8; callees rowed testStatus/getControllingPlayer/friend_getFinalOverride/getOrStart/TheGameLogic.
class Overridable { public: const Overridable *friend_getFinalOverride() const; char pad[0x10]; };
class SpecialPowerTemplate : public Overridable { public: unsigned unknown10; unsigned id; char pad18[0x59-0x18]; bool shared; };
class Rva002AC6B1PlayerTimers { public: unsigned getOrStart(const SpecialPowerTemplate *); };
class Player;
enum ObjectStatusTypes { Status70 = 70 };
class Object { public: bool testStatus(ObjectStatusTypes) const; Player *getControllingPlayer() const; };
class GameLogic; extern GameLogic *TheGameLogic;
struct SpecialReadyFrameView { char pad[0x40]; unsigned frame; };
static unsigned frame() { return ((SpecialReadyFrameView *)TheGameLogic)->frame; }
class ModuleData { public: virtual ~ModuleData(); };
class SpecialPowerModuleData : public ModuleData { public: int unknown4; const SpecialPowerTemplate *power; };
class ObjectModule { protected: virtual ~ObjectModule(); const ModuleData *data; Object *object; };
class BehaviorModuleInterface { public: virtual void anchor(); };
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface { protected: virtual ~BehaviorModule(); };
class SpecialPowerModuleInterface { public: virtual bool isReady() const = 0; };
class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface {
public: virtual bool isReady() const;
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
  if (player && ((const SpecialPowerTemplate *)modData->power->friend_getFinalOverride())->shared)
   return frame() >= ((Rva002AC6B1PlayerTimers *)player)->getOrStart(modData->power);
 }
 return paused == 0 && frame() >= available;
}
