// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// ParticleSystem constructor, native001FC701..001FCBD7 RET0C, 1238B.
// Identity: existing named constructor pin and factory1F50BC new(1DC),
// ParticleSystemInfo base1F4E82, target BE1A10 vtable and manager insertion.
// ZH GeneralsMD ParticleSys.cpp and matrix3d.h at BF1f98983a7d guide the
// initialization/identity-matrix/slave-link semantics. BFME2 adds the drawer
// constructors,12-byte intrusive handles and48-byte module-forwarding tail.
// Target stores and EH cleanup offsets establish all accessed field widths;
// unknown fields retain neutral names. The tail default-constructor chain
// 1FBF37 ->1FBA45 ->1FA5A5 ->1F9060 ->ObjectCreationList/vector base only
// initializes fields and null pointers, justifying its no-throw declaration.
// Inline row Set operations preserve native EH state4 after first matrix row.
// Row16 ctor is a3-byte twin of retail's empty constructor47A6A9: the
// native array-iterator arguments independently prove16-byte rows/count3.
#include "ascii_string.h"
class ParticleSystemTemplate;
class ParticleSystem;
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID=0 };
class Rva001F5467;
ParticleSystem *Make001FCBD7();
class RvaSmartPtr12 {
public:
 RvaSmartPtr12(void *) throw();
 RvaSmartPtr12(const RvaSmartPtr12&);
 RvaSmartPtr12 &operator=(const RvaSmartPtr12&) throw();
 ~RvaSmartPtr12() { if(ptr)rva0004CBC0(); }
 void rva0004CBC0() throw();
 void *ptr; int prev,next;
};
class BfmeParticleSystemHandle {
public:
 BfmeParticleSystemHandle():ptr(0),prev(0),next(0){}
 BfmeParticleSystemHandle(ParticleSystem *p) { ((RvaSmartPtr12*)this)->RvaSmartPtr12::RvaSmartPtr12(p); }
 BfmeParticleSystemHandle(const BfmeParticleSystemHandle &x) { ((RvaSmartPtr12*)this)->RvaSmartPtr12::RvaSmartPtr12(*(const RvaSmartPtr12*)&x); }
 BfmeParticleSystemHandle &operator=(const BfmeParticleSystemHandle &x) throw() { ((RvaSmartPtr12*)this)->operator=(*(const RvaSmartPtr12*)&x); return *this; }
 ~BfmeParticleSystemHandle() { if(ptr)((RvaSmartPtr12*)this)->rva0004CBC0(); }
 Rva001F5467 *operator->()const {return (Rva001F5467*)(ptr?ptr:Make001FCBD7());}
 void *ptr; int prev,next;
};
class ParticleSystemManager {
public:
 ParticleSystemTemplate *findTemplate(const AsciiString&)const;
 BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate*,bool);
};
extern ParticleSystemManager *TheParticleSystemManager;

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "Common/Snapshot.h"
struct ParticleVec {float x,y,z;void zero(){z=y=x=0.0f;}};
class GameClientRandomVariable {public: float getValue()const;int type;float low,high;};
struct ParticleRegion {float x1,y1,x2,y2;};
struct Rva0047A6A9Row16 {__declspec(noinline) Rva0047A6A9Row16();float x,y,z,w;void Set(float a,float b,float c,float d){x=a;y=b;z=c;w=d;}};
Rva0047A6A9Row16::Rva0047A6A9Row16() {}
struct ParticleMatrix {__forceinline ParticleMatrix() {} Rva0047A6A9Row16 r[3];void Make_Identity(){
 r[0].Set(1.0f,0.0f,0.0f,0.0f);
 r[1].Set(0.0f,1.0f,0.0f,0.0f);
 r[2].Set(0.0f,0.0f,1.0f,0.0f);
}};
class Rva001FBCDC {public:~Rva001FBCDC();};
namespace FXParticleSystem {
class ParticleSystemInfo :public Snapshot {
public:
 ParticleSystemInfo();virtual ~ParticleSystemInfo();virtual const char *GetSnapshotName();virtual void LoadPostProcess();virtual void DoXfer(Xfer&);
 unsigned char oneShot;unsigned shader,particleType;AsciiString typeName;
 GameClientRandomVariable angle;unsigned lifetime,depth;GameClientRandomVariable angularRate,angularDamping;
 unsigned windMotion;GameClientRandomVariable velocityDamping,life,startSize;
 AsciiString slaveName;ParticleVec slaveOffset;AsciiString attachedName;unsigned emissionVelocity;
 unsigned char hollow,ground,above,up,windMoving;ParticleRegion uv;unsigned unknown98;
};
class ParticleSystemTemplateTail {public:ParticleSystemTemplateTail() throw();~ParticleSystemTemplateTail(){((Rva001FBCDC*)this)->Rva001FBCDC::~Rva001FBCDC();} unsigned data[12];};
class ParticleSystemTemplate : public ParticleSystemInfo {
public:
 BfmeParticleSystemHandle rva001F9CF3(bool)const;
 char unknown9C[4];::ParticleSystemTemplate *cached;
};
}
class ParticleSystem *Make001FCBD7();
class Rva001F5496 {public:void rva001F5496(const RvaSmartPtr12&);};
class Rva001F5467 {public:void rva001F5467(const RvaSmartPtr12&);};
class Rva001FC451 {public:void rva001FC451(void*,void*);};
class Rva001F88B4 {public:void rva001F88B4(const RvaSmartPtr12&);};
class ClientFrameSubsystem {
public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual void s19();
 virtual void s20();
 virtual void s21();
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void s26();
 virtual void s27();
 virtual void s28();
 virtual void s29();
 virtual void s30();
 virtual unsigned getFrame();};
class GameClient;
extern GameClient *TheGameClient;
class Rva003B00D6 {public:virtual ~Rva003B00D6();char data[0x18];};
class Rva003B0152:public Rva003B00D6 {public:Rva003B0152(const RvaSmartPtr12&);};
class Rva003B0344 {public:Rva003B0344(const RvaSmartPtr12&);virtual ~Rva003B0344();char data[0x40];};
class Rva003B0401:public Rva003B0344 {public:Rva003B0401(const RvaSmartPtr12&);};
class ParticleSystem : public FXParticleSystem::ParticleSystemInfo {
public:
 ParticleSystem(const FXParticleSystem::ParticleSystemTemplate*,ParticleSystemID,bool);
 virtual ~ParticleSystem();virtual bool update(int);
 void *head,*tail,*drawer;ParticleSystemID id;float accumulated;unsigned attachedDrawable,attachedObject;
 AsciiString unknownB8;ParticleMatrix localTransform,transform;
 unsigned burstLeft,delayLeft,startTime,lifetimeLeft,count;
 ParticleVec velocityCoefficient;float countCoefficient,delayCoefficient;ParticleVec position,lastPosition;
 BfmeParticleSystemHandle slave;unsigned slaveId;BfmeParticleSystemHandle master;unsigned masterId;
 float sizeCoefficient,unknown180,unknown184;ParticleVec unknown188;unsigned char unknown194;
 const FXParticleSystem::ParticleSystemTemplate *sysTemplate;unsigned personality;
 bool localIdentity,identity,forever,stopped,destroyed,firstPos,saveable,skip;
 unsigned char unknown1A8;FXParticleSystem::ParticleSystemTemplateTail chain;
};
typedef char ParticleExtent[sizeof(ParticleSystem)==0x1DC?1:-1];
ParticleSystem::ParticleSystem(const FXParticleSystem::ParticleSystemTemplate *t,ParticleSystemID value,bool createSlaves):head(0),tail(0)
{
 firstPos=true;sysTemplate=t;id=value;
 lastPosition.zero();position.zero();velocityCoefficient.zero();
 attachedDrawable=0;attachedObject=0;
 localIdentity=true;localTransform.Make_Identity();identity=true;transform.Make_Identity();
 stopped=false;destroyed=false;saveable=true;skip=false;
 slaveOffset=t->slaveOffset;windMotion=0;
 velocityCoefficient.x=1.0f;velocityCoefficient.y=1.0f;velocityCoefficient.z=1.0f;
 countCoefficient=1.0f;delayCoefficient=1.0f;sizeCoefficient=1.0f;unknown184=1.0f;
 unknown188.zero();unknown194=0;
 angle=t->angle;angularRate=t->angularRate;angularDamping=t->angularDamping;velocityDamping=t->velocityDamping;
 burstLeft=0;life=t->life;oneShot=t->oneShot;
 delayLeft=(unsigned)t->startSize.getValue();startTime=((ClientFrameSubsystem*)TheGameClient)->getFrame();lifetimeLeft=t->lifetime;
 forever=t->lifetime==0;depth=t->depth;unknown180=0.0f;emissionVelocity=t->emissionVelocity;
 hollow=t->hollow;ground=t->ground;above=t->above;up=t->up;windMoving=t->windMoving;
 shader=t->shader;particleType=t->particleType;typeName=t->typeName;stopped=false;
 if(t->particleType==7)drawer=new Rva003B0344(*(const RvaSmartPtr12*)&RvaSmartPtr12(this));
 else if(t->particleType==8)drawer=new Rva003B0401(*(const RvaSmartPtr12*)&RvaSmartPtr12(this));
 else drawer=new Rva003B0152(*(const RvaSmartPtr12*)&RvaSmartPtr12(this));
 masterId=0;slaveId=0;
 if(createSlaves) {
  BfmeParticleSystemHandle child=t->rva001F9CF3(true);
  if(child.ptr) {
   ((Rva001F5496*)this)->rva001F5496(*(const RvaSmartPtr12*)&child);
   slave->rva001F5467(RvaSmartPtr12(this));
  }
 }
 attachedName=t->attachedName;count=0;personality=0;accumulated=0.0f;unknown1A8=0;uv=t->uv;
 ((Rva001FC451*)&chain)->rva001FC451(&RvaSmartPtr12(this),(void*)t);
 ((Rva001F88B4*)TheParticleSystemManager)->rva001F88B4(*(const RvaSmartPtr12*)&RvaSmartPtr12(this));
}
