// ?roam@AIRoamingDefenseTactic@@QAEXPAVObject@@@Z
// partial score=0.9401215346010823 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /I. /ICode/Libraries/Include /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include <stdlib.h>
namespace _STL {void __cdecl free(void *); }
#define free _STL::free
#include <vector>
#undef free

#include <functional>
#include "Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
namespace _STL {
 template<class T>struct hash;
 template<class K,class V,class H,class E,class A>class hash_map {public:unsigned int bucket_count()const;};
}
typedef _STL::hash_map<int,int,_STL::hash<int>,_STL::equal_to<int>,_STL::allocator<_STL::pair<const int,int> > > IntMap;
class Rva005C4AD1LeaField{public:void *get()const;};
struct RoamOwnerStats{char pad[8];Rva005C4AD1LeaField *all;IntMap *targets;};
struct Rva002A8AB1Record;
class Player;
class Rva002A8F24 {public:void *rva002A8F24(Player *);Rva002A8AB1Record *rva002A8AB1(void *);};
extern Rva002A8F24 *g_00DFEEF8;
class Rva004EBF4B{public:Coord3D rva004EBF4B();};
class Rva00295A0FCommands{public:void Rva00295A0FCommand(void*,int,int);};
struct RoamAI {char pad[0x20];Rva00295A0FCommands commands;};
struct RoamObjectTemplate{char pad[0x120];unsigned int bits;};
class Object{public:char pad0[4];RoamObjectTemplate *objectTemplate;char pad8[0x38-8];Coord3D position;char pad44[0x258-0x44];RoamAI *ai;};
int GetGameLogicRandomValue(int,int,char *,int);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
// Arithmetic follows Zero Hour WWMath vector3.h; WB independently names
// Vector3 Distance2/Length2/Rotate_Z in the target caller.
struct RoamVector3 {
 float X,Y,Z;
 __forceinline RoamVector3(float x,float y,float z):X(x),Y(y),Z(z){}
 __forceinline float length2()const{return X*X+Y*Y+Z*Z;}
 __forceinline void rotate(float angle){float sn=(float)sin(angle),cs=(float)cos(angle);float x=X,y=Y;X=cs*x-sn*y;Y=sn*x+cs*y;}
 __forceinline void scale(float f){X*=f;Y*=f;Z*=f;}
};
static __forceinline float RoamDistance2(const RoamVector3 &a,const RoamVector3 &b){RoamVector3 diff(0,0,0);diff.Z=a.Z-b.Z;diff.Y=a.Y-b.Y;diff.X=a.X-b.X;return diff.length2();}
class AIRoamingDefenseTactic {public:void roam(Object *);char pad[0x24];Player *owner;};
void AIRoamingDefenseTactic::roam(Object *obj)
{
 RoamOwnerStats *stats=(RoamOwnerStats *)g_00DFEEF8->rva002A8F24(owner);
 IntMap *targets=stats->targets;
 if(targets->bucket_count()>0){
  Rva002A8AB1Record *record=g_00DFEEF8->rva002A8AB1(owner);
  Coord3D center=((Rva004EBF4B *)record)->rva004EBF4B();
  _STL::vector<ObjectID> *ids=(_STL::vector<ObjectID> *)((Rva005C4AD1LeaField *)targets)->get();
  _STL::vector<Object *> nearby;
  _STL::vector<ObjectID>::iterator end=ids->end();
  for(_STL::vector<ObjectID>::iterator it=ids->begin();it!=end;++it){
   Object *target=TheGameLogic->findObjectByID(*it);
   if(target){
    if(RoamDistance2(RoamVector3(center.x,center.y,center.z),RoamVector3(target->position.x,target->position.y,target->position.z))<810000.0f)nearby.push_back(target);
   }
  }
  if(!nearby.empty()){
   Object *target=nearby[GetGameLogicRandomValue(0,nearby.size()-1,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\TargetlessTactics\\AIRoamingDefenseTactic.cpp",164)];
   RoamAI *ai=obj->ai;ai->commands.Rva00295A0FCommand(&target->position,0x7FFFFFFF,0);
  }
 }else{
  Object *building=0;
  _STL::vector<ObjectID> *ids=(_STL::vector<ObjectID> *)stats->all->get();
  _STL::vector<ObjectID>::iterator end=ids->end();
  for(_STL::vector<ObjectID>::iterator it=ids->begin();it!=end;++it){
   if(!building){
    Object *target=TheGameLogic->findObjectByID(*it);
    if(target && (target->objectTemplate->bits &4))building=target;
   }else break;
  }
  if(building){
   float angle=(float)GetGameLogicRandomValue(0,6,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\TargetlessTactics\\AIRoamingDefenseTactic.cpp",186);
   RoamVector3 relative(1.0f,0.0f,0.0f);
   relative.rotate(angle);
   relative.scale(400.0f);
   Coord3D point;
   point.x=building->position.x+relative.X;
   point.y=building->position.y+relative.Y;
   point.z=building->position.z+relative.Z;
   obj->ai->commands.Rva00295A0FCommand(&point,0x7FFFFFFF,0);
  }
 }
}
