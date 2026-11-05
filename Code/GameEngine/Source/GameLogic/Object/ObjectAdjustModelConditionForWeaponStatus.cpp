// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva0028DB3C@Object@@QAEXXZ
// Object weapon-status model conditions, full392B target28DB3C..28DCC4.
// The existing address-derived Object pin is retained; no new identity alias.
// Calls from AI privateIdle independently support the source purpose; native
// status queries22/25/13, six-slot WeaponSet330, Drawable84, last conditions384
// agree with existing Object layouts. Native WeaponTemplate78/80/E4/169 and
// Weapon frame1C/24/2C are target facts; the name of template80 remains unknown.
// Native lookup at7FBE98 is exactly the compiler table {0,0,2,3,4,1}; source
// data and all callbacks reproduce retail without an address-named global.
// Clean ZH Object::adjustModelConditionForWeaponStatus and BF1 cee35b7d8
// ObjectAdjustModelConditionThunk.cpp guide status-purpose and branch structure.
// Retail 28DB3C..28DCC4; all offsets below read independently from its instructions.
enum ObjectStatusTypes { AIM=22,FIRE=25,ATTACK=13 };
enum WeaponSlotType { PRIMARY_WEAPON=0 };
enum WeaponStatus { READY_TO_FIRE=0,OUT_OF_AMMO,BETWEEN_FIRING_SHOTS,RELOADING_CLIP,PRE_ATTACK,UNUSED };
enum WeaponSetConditionType { WSF_INVALID=-1,WSF_NONE=0,WSF_FIRING,WSF_BETWEEN,WSF_RELOADING,WSF_UNUSED,WSF_PREATTACK };
#include "../../../Include/GameLogic/WeaponTemplate.h"
#include "../../../Include/GameLogic/Weapon.h"
#include "../../../Include/GameLogic/WeaponSetClass.h"
class GameLogic;extern GameLogic*TheGameLogic;
struct ClockView {char p0[0x40];unsigned frame;};
class Rva002716Holder
{
public:
	void Rva0027164EBroadcast(int a, int b);
	void Rva00271619Broadcast(int,int,int);
};
class WeaponTemplateSetHead {char data[0x4c];};
WeaponTemplateSetHead* __cdecl Rva002C76B2Build(WeaponTemplateSetHead*,int,int);
WeaponTemplateSetHead* __cdecl rva002C777E(WeaponTemplateSetHead*,int);
class Object {public:
 char p0[0x84];void*draw;char p88[0x384-0x88];signed char lastCondition[6];
 bool testStatus(ObjectStatusTypes)const;void rva0028CFB2(const int*,const int*);void rva0028DB3C();
};
void Object::rva0028DB3C(){
 unsigned now=((ClockView*)TheGameLogic)->frame;
 const bool aiming=testStatus(AIM),firing=testStatus(FIRE),attacking=testStatus(ATTACK);
 for(int i=0;i<6;++i){
  Weapon*weapon=((const WeaponSet*)((const char*)this+0x330))->getWeaponInWeaponSlot((WeaponSlotType)i);
  bool special=weapon && weapon->m_template->m_field80;
  WeaponSetConditionType condition=WSF_INVALID;
  if(!weapon)condition=WSF_NONE;
  else {
   unsigned shot=weapon->m_unknown2C;
   if(shot>0){int delay=weapon->m_template->m_idleAfterFiringDelay;if(delay>=0 && shot+delay>now)condition=WSF_FIRING;}
   if(condition==WSF_INVALID && shot==now)condition=WSF_FIRING;
   if(condition==WSF_INVALID && weapon->m_template->m_field169 && now<weapon->m_lastFireFrame && now>weapon->m_whenPreAttackFinished)condition=WSF_PREATTACK;
   if(condition==WSF_INVALID && !testStatus(AIM)){
    if(!weapon->rva002C9586() && (!special || weapon->getStatus()!=RELOADING_CLIP))condition=WSF_NONE;
   }
   if(condition==WSF_INVALID){
    static const WeaponSetConditionType lookup[6]={WSF_NONE,WSF_NONE,WSF_BETWEEN,WSF_RELOADING,WSF_UNUSED,WSF_FIRING};
    WeaponStatus status=weapon->getStatus();condition=lookup[status];
    if(status==READY_TO_FIRE && condition==WSF_NONE && aiming && (attacking||firing))condition=WSF_BETWEEN;
   }
  }
  if(draw){
   if(weapon && weapon->m_template->m_clipSize>0)((Rva002716Holder*)draw)->Rva00271619Broadcast(weapon->getRemainingAmmo(true),weapon->m_template->m_clipSize,(int)weapon->m_wslot);
   if(condition!=WSF_INVALID && condition!=lastCondition[i]){
    lastCondition[i]=(signed char)condition;
    WeaponTemplateSetHead tmp1;Rva002C76B2Build(&tmp1,i,condition);
    WeaponTemplateSetHead tmp2;rva0028CFB2((const int*)rva002C777E(&tmp2,i),(const int*)&tmp1);
   }
  }
 }
}
