// ?update@AIHarvestWorkSiteState@@UAE?AW4StateReturnType@@XZ
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /ICode/GameEngine/Source/Common
// Ported from Open-BFME-1 revision a7c38d3b2597121f178ab5190b3062478823257d,
// game/GameEngine/Source/GameLogic/AI/AIHarvestWorkSiteState_update.cpp.
// Native 0x005450D3..0x005451F3 and WB 0x0134B7A0 supply the BFME2
// offsets and flag 257. The terrain query takes four arguments; its two
// constant arguments are pushed before the virtual radius getter.
// The one-argument bool terrain check was repaired at its owning definition.
// Native vtable VA 0x00C69CF8 slot 6 is this update; slot 2, 0x00544C4B,
// returns the literal "AIHarvestWorkSiteState". The accessed state prefix
// is machine +0x18 / frame +0x20; no construction of private views occurs.
#include "GameLogicObjectLookupView.h"
#include "../../../Include/Common/StateMachine.h"
class Rva0027D3CB { public: bool rva0027D3CB(int); };
class Rva0027D378 { public: int rva0027D378(void *,int); };
#include "../../../Include/GameLogic/Module/BfmeThingCME.h"
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
extern GameLogic *TheGameLogic;
class Thing;
#include "../../../Include/GameLogic/Module/Rva001E702E.h"
class HarvestTarget {
public:
 virtual int slot00(); virtual int slot01(); virtual void slot02(); virtual void slot03(int);
 virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual float getValue();
 virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11(int);
 virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
 virtual void slot16(); virtual void slot17(); virtual int getOwner();
};
#define V(n) virtual void slot##n();
class HarvestAI {
public:
 V(0)
 V(1)
 V(2)
 V(3)
 V(4)
 V(5)
 V(6)
 V(7)
 V(8)
 V(9)
 V(10)
 V(11)
 V(12)
 V(13)
 V(14)
 V(15)
 V(16)
 V(17)
 V(18)
 V(19)
 V(20)
 V(21)
 V(22)
 V(23)
 V(24)
 V(25)
 V(26)
 V(27)
 V(28)
 V(29)
 V(30)
 V(31)
 V(32)
 V(33)
 V(34)
 V(35)
 V(36)
 V(37)
 V(38)
 V(39)
 V(40)
 V(41)
 V(42)
 V(43)
 V(44)
 V(45)
 V(46)
 V(47)
 V(48)
 V(49)
 V(50)
 V(51)
 V(52)
 V(53)
 V(54)
 V(55)
 V(56)
 V(57)
 V(58)
 V(59)
 V(60)
 V(61)
 V(62)
 V(63)
 V(64)
 V(65)
 V(66)
 V(67)
 V(68)
 V(69)
 V(70)
 V(71)
 V(72)
 V(73)
 V(74)
 V(75)
 V(76)
 V(77)
 V(78)
 V(79)
 V(80)
 V(81)
 V(82)
 V(83)
 V(84)
 V(85)
 V(86)
 V(87)
 V(88)
 V(89)
 V(90)
 V(91)
 V(92)
 V(93)
 V(94)
 virtual HarvestTarget *getHarvestTarget();
 char pad[0x1f0-4]; Rva001E702E *locomotor;
};
#undef V
struct HarvestFlags {unsigned bits[19];  unsigned test(unsigned i) const {return bits[i>>5] & (1u<<(i&31));}  void set(unsigned i) {bits[i>>5]|=1u<<(i&31);} };
class Object {
public:
 void rva0028AE6D();
 char pad[0x38]; float position[3]; char pad44[0x10c-0x44]; HarvestFlags flags;
 char pad158[0x258-0x158]; HarvestAI *ai;
};
struct HarvestMachine { char pad[0x14]; Object *owner; };
struct HarvestRecord { char pad[0xc]; int id; int owner; char pad14[0x28-0x14]; int amount; };
class AIHarvestWorkSiteState {
public:
 virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
 virtual void slot04(); virtual void slot05(); virtual StateReturnType update();
 char pad[0x18-4]; HarvestMachine *machine; char pad1c[4]; unsigned frame;
};
StateReturnType AIHarvestWorkSiteState::update() {
 HarvestTarget *target=machine->owner->ai->getHarvestTarget();
 if(target) {
  Object *owner=machine->owner;
  HarvestRecord *record=(HarvestRecord*)((BfmeThingCME*)TheTerrainLogic)->rva0027F108(owner->position,target->getValue(),0,2);
  int recordOwner=0;
  if(record) recordOwner=record->owner;
  if(record && recordOwner==target->getOwner() && ((Rva0027D3CB*)TheTerrainLogic)->rva0027D3CB(record->id)) {
   if(TheGameLogic->getFrame() >= frame) {
    int first=target->slot01();
    int second=target->slot00();
    int previousAmount=record->amount;
    int amount=first-second;
    int remaining=((Rva0027D378*)TheTerrainLogic)->rva0027D378(record,amount);
    for(int count=0;count<remaining;++count) target->slot03(previousAmount-remaining);
    return STATE_SUCCESS;
   }
   if(machine->owner->ai->locomotor) machine->owner->ai->locomotor->rva001E702E((Thing*)machine->owner,(int)record,0);
  } else {
   target->slot11(1);
   return STATE_FAILURE;
  }
 }
 Object *owner=machine->owner;
 if(!owner->flags.test(257)) {owner->flags.set(257);owner->rva0028AE6D();}
 return STATE_CONTINUE;
}
