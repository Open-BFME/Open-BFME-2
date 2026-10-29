// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE /ICode/Libraries/Include/Lib
// ?onCollide@FireWeaponCollide@@UAEXPAVObject@@PBUCoord3D@@1@Z @0x004BB822 58B
// Evidence: ZH GeneralsMD FireWeaponCollide.cpp lines76..91 source primary guide. Native full58B RET12 slot0 atRVA85A024 (not CallHelp table which ends before85A010), class name getter4BB6FC plus ctor4BB79A proves FireWeaponCollide and MI interface+10. Local me before shouldFireWeapon preserves owner lifetime; existing loadAmmoNow2CE1AC/private fire wrapper2CE6C5 full rows. Original primary type and field offsets from native ctor.
#include "Coord3D.h"
class Object {public:char pad[0x74];int id;};
class Weapon {public:void loadAmmoNow(const Object*);bool rva002CE6C5(const Object*,int,const Object*,int*);};
#include "../../../../Include/Common/ObjectModule.h"
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
class CollideModuleInterface {public:virtual void onCollide(Object*,const Coord3D*,const Coord3D*)=0;};
class CollideModule:public BehaviorModule,public CollideModuleInterface{};
class FireWeaponCollide:public CollideModule {public:virtual void onCollide(Object*,const Coord3D*,const Coord3D*);virtual bool shouldFireWeapon();Weapon*m_collideWeapon;bool m_everFired;};
void FireWeaponCollide::onCollide(Object*other,const Coord3D*,const Coord3D*){
 if(!other)return;Object*me=getObject(); if(shouldFireWeapon()){m_collideWeapon->loadAmmoNow(me);m_collideWeapon->rva002CE6C5(me,other->id,other,0);}
}
