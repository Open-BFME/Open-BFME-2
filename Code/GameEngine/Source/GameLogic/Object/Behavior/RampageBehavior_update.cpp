// ?update@RampageBehavior@@UAE?AW4UpdateSleepTime@@XZ
// ?update@RampageBehavior@@UAE?AW4UpdateSleepTime@@XZ
// ?update@RampageBehavior@@UAE?AW4UpdateSleepTime@@XZ
// Native full689B 458CCB..458F7C, secondary update callback at +10.
// New native corrections to the old bank: AI commands are embedded at
// AIUpdate+20; decrement expiry always clears weapon8/possibly idles;
// saved state compares/stores absolute health; max reference retains NaN
// selection (one > max ? one : max). No global float alias is introduced.
// cl: /I. /I. /O1 /DNDEBUG /MD /arch:SSE /G7
//
// ?update@RampageBehavior@@UAE?AW4UpdateSleepTime@@XZ
// Target identity: slot 0 of RampageBehavior's UpdateModuleInterface table
// (secondary vtable at 0x00C40DA8); the callback's this pointer is the
// interface subobject at complete-object +0x10. The target reads module data
// from this-0x0C and Object from this-0x08. The vtable owner and module-data
// layout are independently established by the rowed constructor and data
// constructor.
//
// Reference evidence: GeneralsMD AIRampageStateUpdate/OnEnter establish the
// rampage state purpose and frame-timer behavior. This BFME2 method is not a
// donor-body match: its upgrade gate, health ratio, weapon commands, condition
// bits and timer fields are reconstructed from this body's calls and offsets.
// Names for the two BodyModuleInterface float slots and Object condition bits
// remain address-derived; the target calls below use only rowed helpers.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
enum UpdateSleepTime

{
 UPDATE_SLEEP_NONE = 1,
 UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
 
}
;
enum WeaponSetType

{
 WEAPONSET_7 = 7,
 WEAPONSET_8 = 8
 
}
;
enum CommandSourceType

{
 CMD_FROM_AI = 2
 
}
;
class Thing;
class ModuleData;
class Object;
class UpgradeTemplate;
class AsciiString;
#include "../../../../Include/GameClient/Drawable.h"
#include "../../../Common/Thing/thing.h"
class RampageBehaviorModuleDataView

{
 public:
 unsigned char m_pad00[8];
 const unsigned char *m_requiredUpgradeStart;
 const unsigned char *m_requiredUpgradeFinish;
 const unsigned char *m_requiredUpgradeEnd;
 float m_healthThreshold;
 Int m_lifeTimer;
 Int m_angryLifeTimer;
 Int m_resetTimer;
 float m_enemyCheckRange;
 Int m_enemyThreshold;
 
}
;
class BodyModuleFloatInterface

{
 public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual float rva0048F64EGetA();
 virtual void slot14();
 virtual float rva0048F64EGetB();
 
}
;
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
class AIUpdateInterfaceView

{
 public:
 unsigned char m_pad00[0x20];
 __forceinline AICommandInterface *commands() 
 {
  return (AICommandInterface *)((char *)this + 0x20);
  
 }
 
}
;
class Rva0028B7AELeaGetter

{
 public:
 void *get() const;
 
}
;
class Rva0028BD3AInterface

{
 public:
 virtual void slot00();
 virtual void slot04();
 virtual void set(Bool enabled);
 
}
;
class Object : public Thing

{
 public:
 Int rva0028B7C8() const;
 void rva0028AE6D();
 Bool hasUpgrade(const UpgradeTemplate *upgrade) const;
 void clearWeaponSetFlag(WeaponSetType type);
 void setWeaponSetFlag(WeaponSetType type);
 void *rva0028BD3A() const;
 const UnsignedInt *getWeaponSetFlags() const
 
 {
  return (const UnsignedInt *)((const Rva0028B7AELeaGetter *)this)->get();
  
 }
 const Coord3D *getPosition() const 
 {
  return &m_cachedPos;
  
 }
 __forceinline void clearConditionWord5Bit2()
 
 {
  if (*((volatile unsigned char *)this+0x120) & 4) 
  {
   UnsignedInt *words = m_conditionWords;
   words[5] &= ~4U;
   rva0028AE6D();
   
  }
  
 }
 __forceinline void setConditionWord5Bit2()
 
 {
  if (!(m_conditionWords[5] & 4)) 
  {
   UnsignedInt *words = m_conditionWords;
   words[5] |= 4U;
   rva0028AE6D();
   
  }
  
 }
 __forceinline void clearConditionWord5Bit0()
 
 {
  if (((const unsigned char *)&m_conditionWords[5])[0] & 1) 
  {
   m_conditionWords[5] &= ~1U;
   rva0028AE6D();
   
  }
  
 }
 __forceinline void clearConditionWord5Byte1Bits()
 
 {
  const volatile unsigned char *testBytes = (const volatile unsigned char *)&m_conditionWords[5];
  unsigned char *bytes = (unsigned char *)&m_conditionWords[5];
  if (testBytes[1] & 0x10) 
  {
   bytes[1] &= (unsigned char)0xEF;
   rva0028AE6D();
   
  }
  if (testBytes[1] & 0x20) 
  {
   bytes[1] &= (unsigned char)0xDF;
   rva0028AE6D();
   
  }
  if (testBytes[1] & 0x40) 
  {
   bytes[1] &= (unsigned char)0xBF;
   rva0028AE6D();
   
  }
  if (testBytes[1] & 0x80) 
  {
   bytes[1] &= (unsigned char)0x7F;
   rva0028AE6D();
   
  }
  
 }
 __forceinline Bool hasStatusBit1() const 
 {
  return (m_status438 & 1) != 0;
  
 }
 __forceinline Bool hasWeaponSet(WeaponSetType type) const
 
 {
  unsigned char flags = (unsigned char)(*getWeaponSetFlags() >> type);
  return (flags & 1) != 0;
  
 }
 private:
 unsigned char m_pad60[0x10C - 0x60];
 UnsignedInt m_conditionWords[19];
 unsigned char m_pad158[0x254 - 0x158];
 public:
 BodyModuleFloatInterface *m_body;
 AIUpdateInterfaceView *m_ai;
 private:
 unsigned char m_pad25C[0x438 - 0x25C];
 unsigned char m_status438;
 
}
;
#include "../../../../Include/Common/Upgrade.h"
extern UpgradeCenter *TheUpgradeCenter;
__forceinline const float &rampageMax(const float &a, const float &b) 
{
 return a > b ? a : b;
 
}
struct Rva00458BE1Sub;
class Rva00458BE1
{
public:
	unsigned char rva00458BE1();
	char m_pad00[0x4];
private:
	Rva00458BE1Sub *m_sub; // +0x04
	Object *m_obj; // +0x08
};
class RampageBehavior

{
 public:
 virtual UpdateSleepTime update();
 private:
 unsigned char m_pad04[0x10 - 4];
 float m_10;
 Int m_14;
 Int m_18;
 
}
;
UpdateSleepTime RampageBehavior::update()

{
 Object *owner = *(Object **)((char *)this - 8);
 AIUpdateInterfaceView *ai = owner->m_ai;
 BodyModuleFloatInterface *body = owner->m_body;
 Drawable *drawable = owner->getDrawable();
 if (!body || !ai || !drawable)
 return UPDATE_SLEEP_FOREVER;
 const RampageBehaviorModuleDataView *data =
 (const RampageBehaviorModuleDataView *)*(const ModuleData **)((char *)this - 0xC);
 for (const unsigned char *upgrade = data->m_requiredUpgradeStart;
 upgrade != data->m_requiredUpgradeFinish; upgrade += 4) 
 {
  const UpgradeTemplate *required = TheUpgradeCenter->findUpgrade(
  *(const AsciiString *)upgrade);
  if (!owner->hasUpgrade(required))
  return UPDATE_SLEEP_NONE;
  
 }
 float health = body->rva0048F64EGetA();
 float maxHealth = body->rva0048F64EGetB();
 const float denominator = rampageMax(1.0f, maxHealth);
 float healthRatio = health / denominator;
 if (m_14 > 0) 
 {
  --m_14;
  if (m_14 > 0 && !owner->hasStatusBit1() && !(unsigned char)owner->rva0028B7C8())
  goto updateResetTimer;
  if (owner->hasWeaponSet(WEAPONSET_8))
  owner->clearWeaponSetFlag(WEAPONSET_8);
  if (!owner->hasStatusBit1() && !(unsigned char)owner->rva0028B7C8())
  ai->commands()->aiIdle(CMD_FROM_AI);
  Int resetTime = data->m_resetTimer;
  m_18 = resetTime;
  m_14 = 0;
  _ReadWriteBarrier();
  owner->clearConditionWord5Bit2();
  drawable->rva00274176(false);
  goto updateResetTimer;
  
 }
 if (!(data->m_healthThreshold > healthRatio)
 || owner->hasStatusBit1()
 || owner->hasWeaponSet(WEAPONSET_8)
 || !(m_10 > health)
 || m_18 != 0)
 goto updateResetTimer;
 if (((Rva00458BE1 *)((char *)this - 0x10))->rva00458BE1()) 
 {
  owner->clearWeaponSetFlag(WEAPONSET_7);
  owner->setWeaponSetFlag(WEAPONSET_8);
  ai->commands()->aiAttackPosition(owner->getPosition(), 0x0FFFFFFE,
  CMD_FROM_AI);
  m_14 = data->m_lifeTimer;
  
 }
 else 
 {
  owner->setConditionWord5Bit2();
  ai->commands()->rva0045003E(0, CMD_FROM_AI);
  m_14 = data->m_angryLifeTimer;
  
 }
 owner->clearConditionWord5Bit0();
 owner->clearConditionWord5Byte1Bits();
 Rva0028BD3AInterface *iface = (Rva0028BD3AInterface *)owner->rva0028BD3A();
 if (iface)
 iface->set(false);
 drawable->rva00274176(false);
 updateResetTimer:
 if (m_18 > 0) 
 {
  --m_18;
  if (m_18 <= 0)
  m_10 = health;
  
 }
 return UPDATE_SLEEP_NONE;
 
}
