// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// ParticleSystem destructor native 001FBD17..001FBEB1 (410B).
// Existing opaque Rva001FBD17 owns the retail BE1A10 scalar-delete slot;
// constructor001FC701 independently proves ParticleSystem identity/1DC extent.
// BF1 f98983a7d ParticleSystemDestructor.cpp and ZH ParticleSys.cpp guide
// detach slave/master/control-particle and manager removal semantics. Target
// replaces ZH's particle-delete loop with drawer scalar destruction and free.
// Constructor stores, native destructor offsets and ten-state unwind map
// establish each live member: stringB8, smart handles15C/16C and tail1AC.
// Native setters1F5467/1F5496 and assignment4CC3D only read the empty source
// handle. Restoring its known-zero pointer explicitly makes that invariant
// visible to MSVC, removing redundant inline cleanup while retaining retail's
// EH cleanup for each scoped temporary. No emitted restoration store remains.
// The last-handle loop clears a handle pointer only inside its nonnull branch.
// Snapshot surface and all accessed field widths agree with the exact ctor.
#include "ascii_string.h"
class ParticleSystemTemplate;
class ParticleSystem;
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID=0 };
class Rva001F5467;
class Rva001F5496;
ParticleSystem *Make001FCBD7();
class RvaSmartPtr12 {
public:
 RvaSmartPtr12():ptr(0),prev(0),next(0){}
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
 void release(){if(ptr){((RvaSmartPtr12*)this)->rva0004CBC0();ptr=0;}}
 ~BfmeParticleSystemHandle() { if(ptr)((RvaSmartPtr12*)this)->rva0004CBC0(); }
 Rva001F5467 *operator->()const {return (Rva001F5467*)(ptr?ptr:Make001FCBD7());}
 Rva001F5496 *getMaster()const {return (Rva001F5496*)(ptr?ptr:Make001FCBD7());}
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
class Rva001F4A22 {public:void rva001F4A22();};
class Rva001F8109 {public:void rva001F8109(const RvaSmartPtr12&);};
class FxDrawer {public:virtual void *destroyDelete(unsigned);};
class Rva001FBD17 : public FXParticleSystem::ParticleSystemInfo {
public:

 virtual ~Rva001FBD17();virtual bool update(int);
 BfmeParticleSystemHandle *head,*tail;FxDrawer *drawer;ParticleSystemID id;float accumulated;unsigned attachedDrawable,attachedObject;
 AsciiString unknownB8;ParticleMatrix localTransform,transform;
 unsigned burstLeft,delayLeft,startTime,lifetimeLeft,count;
 ParticleVec velocityCoefficient;float countCoefficient,delayCoefficient;ParticleVec position,lastPosition;
 BfmeParticleSystemHandle slave;unsigned slaveId;BfmeParticleSystemHandle master;unsigned masterId;
 float sizeCoefficient,unknown180,unknown184;ParticleVec unknown188;unsigned char unknown194;
 const FXParticleSystem::ParticleSystemTemplate *sysTemplate;Rva001F4A22 *controlParticle;
 bool localIdentity,identity,forever,stopped,destroyed,firstPos,saveable,skip;
 unsigned char unknown1A8;FXParticleSystem::ParticleSystemTemplateTail chain;
};
typedef char ParticleExtent[sizeof(Rva001FBD17)==0x1DC?1:-1];

Rva001FBD17::~Rva001FBD17() {
 if(slave.ptr) {
  { RvaSmartPtr12 empty;slave->rva001F5467(empty);empty.ptr=0; }
  { RvaSmartPtr12 empty;((Rva001F5496*)this)->rva001F5496(empty);empty.ptr=0; }
 }
 if(master.ptr) {
  { RvaSmartPtr12 empty;master.getMaster()->rva001F5496(empty);empty.ptr=0; }
  { RvaSmartPtr12 empty;((Rva001F5467*)this)->rva001F5467(empty);empty.ptr=0; }
 }
 attachedDrawable=0;attachedObject=0;unknownB8.clear();
 if(controlParticle)controlParticle->rva001F4A22();controlParticle=0;
 ::operator delete(drawer?drawer->destroyDelete(0):0);drawer=0;
 ((Rva001F8109*)TheParticleSystemManager)->rva001F8109(RvaSmartPtr12(this));
 while(head) head->release();
}
