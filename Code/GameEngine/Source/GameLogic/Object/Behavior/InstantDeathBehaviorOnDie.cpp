// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /ICode/GameEngine/Source/Common
// Native0045CF9B..0045D137 RET4. WB1184540 names InstantDeathBehavior::onDie
// and retains this source path and random-selection lines135/145/155/169.
// BFME1 575ba2b04743f190f069805fbdc59936123c45da InstantDeathBehavior.cpp
// supplies the FX/OCL/weapon/death semantic guide; native adds sound selection.
// Native receiver is the DieModuleInterface at+10: primary data4/object8.
// Native four 12B pointer vectors start38/44/50/5C; source vector API names
// and complete ModuleData layout are not established by this prefix. Sound
// uses the owned four-byte ref copy and canonical136-byte owner-ID audio event.
// Count/selected-FX locals plus explicit position and sound-array locals retain
// native register allocation and the88-byte EH frame. No new callee pins.
#include "GameLogicObjectLookupView.h"
#include "Common/BfmeAudioEventPrefix136.h"
class DamageInfo;struct Coord3D;class WeaponTemplate;
class AIUpdateInterface { public:char pad[0x3BD];bool dead;void markAsDead();};
class Object{public:char pad[0x38];char position[12];char pad44[0x30];ObjectID id;char pad78[0x1e0];AIUpdateInterface*ai;};
class FXList{public:static void doFXObj(const FXList*,const Object*,const Object*);};
class ObjectCreationList {public:void create(void*,void*,void*);};
class WeaponStore {public:void createAndFireTempWeapon(const WeaponTemplate*,const Object*,const Coord3D*);};extern WeaponStore*TheWeaponStore;
extern GameLogic*TheGameLogic;
int GetGameLogicRandomValue(int,int,char*,int);
class Rva0036CA00Str {public:OpaqueRefCounted*item;__declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str&);~Rva0036CA00Str(){if(item)item->Release_Ref();}};
template<int N>class VSlots:public VSlots<N-1>{public:virtual void gap(char(*)[N])=0;};template<>class VSlots<0>{};
class AudioManager:public VSlots<25>{public:virtual unsigned addAudioEvent(const BfmeAudioEventPrefix136*)=0;};extern AudioManager*TheAudio;
template<class T>struct PtrVector{T*begin;T*end;T*storage;int size()const{return end-begin;}T&operator[](int i)const{return begin[i];}};
struct InstantDeathBehaviorModuleData{char pad[0x38];PtrVector<const FXList*>fx;PtrVector<ObjectCreationList*>ocls;PtrVector<const WeaponTemplate*>weapons;PtrVector<Rva0036CA00Str>sounds;};
class BehaviorModule{public:virtual~BehaviorModule();protected:const InstantDeathBehaviorModuleData*data;Object*object;int gap;};
class DieModuleInterface{public:virtual void onDie(const DamageInfo*)=0;};
class DieModule:public BehaviorModule,public DieModuleInterface{protected:bool isDieApplicable(const DamageInfo*)const;};
class InstantDeathBehavior:public DieModule{public:virtual void onDie(const DamageInfo*);};
void InstantDeathBehavior::onDie(const DamageInfo*d){
 if(!isDieApplicable(d))return;
 if(object->ai){if(object->ai->dead)return;object->ai->markAsDead();}
 const InstantDeathBehaviorModuleData*self=data;
 char*file="C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Behavior\\InstantDeathBehavior.cpp";
 int count=self->fx.size();if(count>0){int n=GetGameLogicRandomValue(0,count-1,file,135);const FXList*fx=self->fx[n];Object*obj=object;FXList::doFXObj(fx,obj,0);}
 count=self->ocls.size();if(count>0){int n=GetGameLogicRandomValue(0,count-1,file,145);ObjectCreationList*ocl=self->ocls[n];Object*obj=object;if(ocl)ocl->create(obj,0,0);}
 count=self->weapons.size();if(count>0){int n=GetGameLogicRandomValue(0,count-1,file,155);const WeaponTemplate*w=self->weapons[n];if(w){Object*obj=object;const Coord3D*pos=(const Coord3D*)obj->position;TheWeaponStore->createAndFireTempWeapon(w,obj,pos);}}
 count=self->sounds.size();if(count>0){int n=GetGameLogicRandomValue(0,count-1,file,169);const Rva0036CA00Str*ss=self->sounds.begin;Rva0036CA00Str sound(ss[n]);if(sound.item && TheAudio){BfmeAudioEventPrefix136 event(*(const OpaqueRefElement4*)&sound,object->id);TheAudio->addAudioEvent(&event);}}
 TheGameLogic->destroyObject(object);
}
