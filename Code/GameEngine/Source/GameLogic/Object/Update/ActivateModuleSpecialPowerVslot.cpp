// Native004CDDBA..004CDEED RET4 and WB1278F70 identify the implementation
// as ActivateModuleSpecialPower::SetWakeState. Retain the established
// address-derived call view, shared with the already-matched slot wrappers.
// Module data4/owner8, target44, entriesC8 of eight bytes and module interface
// at0C are independent native reads. The class/role is established by the
// existing ActivateModule constructor, wrapper and WB assertion.
// ZH has no ActivateModule counterpart and BFME1 donor575 has no clean body;
// WB supplies the subsystem guide. Slots9/8 return interface pointers and
// their accessed slots take the verified one-word delay / coord-word pair;
// descriptive interface names are structural roles, not recovered ABI names.
// The self-activation error and debug calls remain as they are in retail.
// cl: /I. /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Debug {public:
 class Format{public:Format(const char*,...);private:char text[512];};
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual Debug&operator<<(const char*);virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual bool CrashDone(int);virtual void s20();virtual void s21();virtual void s22();virtual void s23();virtual void SkipNext();virtual void s25();virtual void s26();virtual Debug&CrashBegin(const char*,int,int);
 Debug&operator<<(const Format&f){return*this<<(const char*)&f;}
};extern Debug*theDebug;void _bfme_debugRecordCallsite(int);
class UpdateModuleInterface{public:virtual void s0();virtual void s1();virtual void setSleepTime(unsigned);};
class SpecialPowerModuleInterface{public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void atLocation(const Coord3D*,int);};
class BehaviorModuleInterface{public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual SpecialPowerModuleInterface*getSpecialPower();virtual UpdateModuleInterface*getUpdate();};
class BehaviorModule{public:char pad[12];BehaviorModuleInterface iface;};
struct ThingTemplate{char pad[0x64];AsciiString name;};
class Object{public:BehaviorModule*rva0028F2C4(int)const;char p0[4];const ThingTemplate*tmpl;char p8[0x38-8];Coord3D position;};
struct WakeEntry{int key,mode;};struct WakeVector{WakeEntry*begin,*end,*capacity;};struct WakeData{char p[0xc8];WakeVector entries;};
class SpecialAbilityUpdate{public:virtual void triggerAbilityEffect();};
class Rva004CDF00:public SpecialAbilityUpdate{public:void rva004CDDBA(int);const WakeData*data;Object*object;char pc[0x44-12];Coord3D target;};
void Rva004CDF00::rva004CDDBA(int state)
{
 Object*obj=object;
 const WakeVector&v=data->entries;
 for(WakeEntry*it=v.begin;it!=v.end;++it){
  BehaviorModule*module=obj->rva0028F2C4(it->key);
  if(!module)continue;
  if((void*)this==(void*)module){
   const char*name=obj->tmpl->name.str();
   _bfme_debugRecordCallsite(1);theDebug->SkipNext();
   Debug&report=theDebug->CrashBegin(0,0,0);
   report<<Debug::Format("ERROR: ActivateModuleSpecialPower can not be used on it self! Check the INI for Object %s",name);report.CrashDone(1);
  }else{
   UpdateModuleInterface*update=module->iface.getUpdate();
   if(update){
    unsigned sleep=0x3fffffff;switch(state){case 0:sleep=1;break;case 1:sleep=update?0x3fffffff:0x3fffffff;break;default:break;}update->setSleepTime(sleep);
   }else if(state==0){
    SpecialPowerModuleInterface*power=module->iface.getSpecialPower();
    if(power){Coord3D position;if(it->mode==1)position=obj->position;else position=target;power->atLocation(&position,0);}
   }
  }
 }
}

class ActivateModuleSpecialPower:public Rva004CDF00
{public:virtual void rva004CDEED();};

// Existing19B slot17 still calls the base and then this helper with state0.
void ActivateModuleSpecialPower::rva004CDEED()
{
 SpecialAbilityUpdate::triggerAbilityEffect();
 Rva004CDF00::rva004CDDBA(0);
}
