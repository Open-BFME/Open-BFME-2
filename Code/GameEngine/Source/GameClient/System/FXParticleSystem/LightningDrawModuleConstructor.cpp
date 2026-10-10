// cl: /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ob2
// Primary clean donor: BFME1 LightningDrawModuleCtor005F4E90.cpp at 575ba2b04.
// Target 561C34..561D31 RET8 and named LightningDraw publisher/getInstance
// establish the constructor's family. Native calls ParticleModule55C86D and
// LightningInfo56142E; its two iterators independently prove 90 12-byte points
// at48 and480. Measured scalar/axis tail begins8B8 and ends8E0.
// The original array point typedef is unproven: the neutral point inherits
// canonical Coord3D storage. Its empty ctor is a whole3B relocation-free
// twin of the owned47A6A9 coordinate ctor; the alias adds no unique bytes.
// Actual C++ bases supply all three vtable stores and two EH cleanup states.
#include "Coord3D.h"
struct Rva00561C34Point:Coord3D { Rva00561C34Point(); };
class DefaultModuleHeadBase {public:virtual ~DefaultModuleHeadBase();private:unsigned int storage[4];};
namespace FXParticleSystem {class Rva003AA228Slice {public:virtual void unusedVirtual();};class Rva003AA228:public DefaultModuleHeadBase,public Rva003AA228Slice {public:Rva003AA228(void*,void*);};}
class ParticleModule005F2CA0:public FXParticleSystem::Rva003AA228 {public:ParticleModule005F2CA0(void*,void*);virtual void moduleSlot();virtual void slot2();virtual void slot3();};
struct Rva00561C34RandomVariable {unsigned distribution;float minimum,maximum;};
class RenderInfoClass;
namespace FXParticleSystem {
class LightningDrawModuleInfoBase {public:virtual ~LightningDrawModuleInfoBase();};
class LightningDrawModuleInfo:public LightningDrawModuleInfoBase {public:LightningDrawModuleInfo();virtual ~LightningDrawModuleInfo();virtual const char* GetSnapshotName();virtual void LoadPostProcess();virtual void DoXfer(class Xfer&);Rva00561C34RandomVariable a,b,c;float value;unsigned char flag;};
class ParticleSystem;template<class T>class TrackingPtr{};
class LightningDrawModuleTemplate {public:char pad[12];Rva00561C34RandomVariable a,b,c;float value;unsigned char flag;};
class LightningDrawModule:public ParticleModule005F2CA0,public LightningDrawModuleInfo {public:LightningDrawModule(TrackingPtr<ParticleSystem>&,const LightningDrawModuleTemplate*);virtual ~LightningDrawModule();virtual int doParticles(::RenderInfoClass&,void*,int*);private:Rva00561C34Point pointsA[3][30];Rva00561C34Point pointsB[3][30];int count;struct Vec{float x,y,z;void Set(float a,float b,float c){x=a;y=b;z=c;}} axisA,axisB,axisC;int tail;};
LightningDrawModule::LightningDrawModule(TrackingPtr<ParticleSystem>& system,const LightningDrawModuleTemplate* source):ParticleModule005F2CA0(&system,(void*)source),LightningDrawModuleInfo(){
 a=source->a;b=source->b;c=source->c;value=source->value;flag=source->flag;
 count=1;axisA.Set(1,0,0);axisB.Set(0,1,0);axisC.Set(0,1,0);tail=0;
}
}

Rva00561C34Point::Rva00561C34Point() {}
