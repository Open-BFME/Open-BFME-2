// ?adjustTargetPositionOnVictim@WeaponTemplate@@QAE?AUTargetCoord@@PAVObject@@0_N@Z
// partial score=0.9533102109003333 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// Complete native 002CAB3A..002CAC6E, RET16, 308B. WB BB2780 names
// adjustTargetPositionOnVictim; hidden return pointer is established by
// direct callers and independent result-copy paths, not the earlier bank name.
// Target receiver/object offsets and flag bits come from native accesses.
// GetGameLogicRandomValue range 0..12345678 is immediate data, not a pointer.
// Canonical Coord3D supplies the 12B fields. TargetCoord is a return ABI view:
// explicit copy shape is an inference; original returned type is not proven.
// Float cap +11C4 is observed; neutral name preserves its semantic uncertainty.
// Emitted 303B vs native308: remaining compiler merge of separate capped and
// ordinary height additions. All calls resolved; this is evidence, not progress.
#include "../../Code/Libraries/Include/Lib/Coord3D.h"
#include "ascii_string.h"
enum ObjectStatusTypes { TARGET_CONTACT_STATUS_55=0x55 };
class ThingTemplate {public:char unknown00[0x108];unsigned char flag108,flag109;};
class Rva0073A1C0FloatField {public:float get()const;};
class Object {
public:
 bool testStatus(ObjectStatusTypes)const;
 bool getWorldspaceBestContactPoint(Coord3D*,const Coord3D*,const char*,int,int,bool)const;
 char unknown00[4];ThingTemplate *m_template;
 char unknown08[0x38-8];Coord3D m_position;
 char unknown44[0xa8-0x44];unsigned char geometry[0x14];
};
class GlobalData;extern GlobalData *TheWritableGlobalData;
struct TargetHeightCapView {char unknown00[0x11c4];float heightCap;};
int GetGameLogicRandomValue(int,int,char*,int);
class Rva002CAAFA {public:bool rva002CAAFA(Object*,Coord3D*);};
struct TargetCoord:Coord3D{__forceinline TargetCoord(){}__forceinline TargetCoord(const TargetCoord&p){x=p.x;y=p.y;z=p.z;}};
class WeaponTemplate {public:TargetCoord adjustTargetPositionOnVictim(Object *source,Object *victim,bool randomContact);};
TargetCoord WeaponTemplate::adjustTargetPositionOnVictim(Object *source,Object *victim,bool randomContact)
{
 TargetCoord pos;
 pos.x=0.0f;pos.y=0.0f;pos.z=0.0f;
 if(!victim)return pos;
 if(reinterpret_cast<Rva002CAAFA*>(this)->rva002CAAFA(victim,&pos))return pos;
 if(randomContact){
  victim->getWorldspaceBestContactPoint(&pos,&source->m_position,0,3,
   GetGameLogicRandomValue(0,12345678,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Weapon.cpp",1749),false);
 }else{
  static_cast<Coord3D&>(pos)=victim->m_position;
  float height=reinterpret_cast<const Rva0073A1C0FloatField*>(victim->geometry)->get();
  if((victim->m_template->flag108&0x80)&&!(source->m_template->flag109&8)&&!source->testStatus(TARGET_CONTACT_STATUS_55)&&victim->testStatus(TARGET_CONTACT_STATUS_55)){
   const float &cap=reinterpret_cast<const TargetHeightCapView*>(TheWritableGlobalData)->heightCap;
   height=height>cap?cap:height;
  }
  pos.z+=height;
 }
 return pos;
}
