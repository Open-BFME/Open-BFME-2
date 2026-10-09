// ?createParticle@ParticleSystem@FXParticleSystem@@QAE_NPBVRva001F376E@@HPBVParticleSystemTemplate@@_N@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /MD /EHsc /arch:SSE /G7 /ICode/Libraries/Include
#include <new>
#include "Lib/Coord3D.h"
class GlobalData;extern GlobalData *TheWritableGlobalData;
class GameLODManager;extern GameLODManager *TheGameLODManager;
class PlayerList;extern PlayerList*ThePlayerList;
class PartitionManager;extern PartitionManager*TheShroudManager;
class Rva007397E0 {public:int rva007397E0(int,const Coord3D*)const;};
struct FactoryGlobals731 {char unknown[0x9AF];bool useFX;char unknown9B0[0xAC8-0x9B0];int maximum;int getMaximum()const{return maximum;}};
struct FactoryLOD731 {char unknown[0x178C];int generations,mask;char unknown1794[12];int minimum,skipMinimum;int minimumPriority()const{return minimum;}bool skipped(){int bitmask=mask;return (++generations&bitmask)!=bitmask;}};
struct FactoryPlayer731 {char unknown[0x54];int id;int getID()const{return id;}};
struct FactoryPlayerList731 {char unknown[0x10];FactoryPlayer731*local;};
class Rva001F48DF {public:int rva001F48DF(unsigned,int);};
class ParticleSystemManager;extern ParticleSystemManager*TheParticleSystemManager;
struct FactoryManager731 {char unknown[0x50];unsigned count;unsigned getCount()const{return count;}};
class ParticleSystem;ParticleSystem*Make001FCBD7();
class BfmeParticleSystemHandle {public:BfmeParticleSystemHandle();BfmeParticleSystemHandle(const BfmeParticleSystemHandle&)throw();~BfmeParticleSystemHandle()throw();ParticleSystem*system;void*prev,*next;ParticleSystem*operator->()const{return system?system:Make001FCBD7();}};
class RvaSmartPtr12 {public:RvaSmartPtr12(void*)throw();RvaSmartPtr12&operator=(const RvaSmartPtr12&);~RvaSmartPtr12()throw(){if(system)((BfmeParticleSystemHandle*)this)->BfmeParticleSystemHandle::~BfmeParticleSystemHandle();}void*system;void*prev,*next;};
class ParticleSystemTemplate;
class ParticleSystemManager {public:BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate*,bool);};
class Rva001F376E {public:char unknown[0x1C];Coord3D position;};
class Rva001F4D06 {public:Rva001F4D06(void*,void*);char unknown[0x88];};
class Rva001FC0F1 {public:Rva001FC0F1(const RvaSmartPtr12&,const Rva001F376E&);char unknown[0xC0];};
struct FactoryParticle731 {char unknown[0x78];RvaSmartPtr12 slave;unsigned unknown84,id;};
class ParticleSystem {public:char unknown[0x19C];FactoryParticle731*slaveParticle;};
__forceinline void*temporary731(const RvaSmartPtr12&h){return(void*)&h;}
namespace FXParticleSystem {
class ParticleSystem {public:bool createParticle(const Rva001F376E*,int,const ParticleSystemTemplate*,bool);char unknown00[0xC];int kind;char unknown10[0x74];bool groundAligned;char unknown85[0xA7];unsigned nextID;};
// Native1FCC73..1FCE6B/WBB10E40; BF1 createParticle2f243e26d guide.
// BF2 adds local-player shroud gate, kinds7/8 and slaved-system handle setup.
bool ParticleSystem::createParticle(const Rva001F376E*info,int priority,const ParticleSystemTemplate*slaveTemplate,bool force){
 if(!force){
  if(!((FactoryGlobals731*)TheWritableGlobalData)->useFX)return false;
  if(groundAligned&&((Rva007397E0*)TheShroudManager)->rva007397E0(((FactoryPlayerList731*)ThePlayerList)->local->getID(),&info->position)>1)return false;
  FactoryLOD731*lod=(FactoryLOD731*)TheGameLODManager;
  if(priority<lod->minimumPriority() ||(priority<lod->skipMinimum&&lod->skipped()))return false;
  if(priority!=6){
   int excess=((FactoryManager731*)TheParticleSystemManager)->getCount()-((FactoryGlobals731*)TheWritableGlobalData)->getMaximum();
   if(excess>0&&((Rva001F48DF*)TheParticleSystemManager)->rva001F48DF(excess,priority)!=excess)return false;
   if(((FactoryGlobals731*)TheWritableGlobalData)->getMaximum()==0)return false;
  }
 }
 FactoryParticle731*particle=0;
 if(kind==7)particle=(FactoryParticle731*)new Rva001F4D06(temporary731(RvaSmartPtr12(this)),(void*)info);
 else if(kind!=8){particle=(FactoryParticle731*)new Rva001FC0F1(RvaSmartPtr12(this),*info);particle->id=nextID++;}
 if(slaveTemplate){BfmeParticleSystemHandle slave=TheParticleSystemManager->createParticleSystem(slaveTemplate,true);slave->slaveParticle=particle;particle->slave=*(RvaSmartPtr12*)&slave;}
 return true;
}
}
