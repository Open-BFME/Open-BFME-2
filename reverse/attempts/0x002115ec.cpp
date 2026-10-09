// ?rva002115EC@Rva002115EC@@QAEXXZ
// partial score=0.97 date=2026-10-09
// cl: /O1 /Ob2 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?rva00211494@Rva00211494@@QAEXXZ, RVA 0x00211494, 113 bytes.
// Two back-to-back vectors of object pointers at +0x234/+0x240; each element
// virtual slot 3 (+0x0C) called in index order. Evidence: caller 0x002123BE
// calls this first with same this (its +0x218 hashtable pins WindowVideoManager).
struct Rva00211494_Item
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
};

struct Rva00211494
{
	unsigned char m_pad[0x234];
	Rva00211494_Item **m_vec1Begin; // +0x234
	Rva00211494_Item **m_vec1End; // +0x238
	void *m_vec1Cap; // +0x23C
	Rva00211494_Item **m_vec2Begin; // +0x240
	Rva00211494_Item **m_vec2End; // +0x244
	void *m_vec2Cap; // +0x248
	void rva00211494();
};

void Rva00211494::rva00211494()
{
	unsigned int i;
	for (i = 0; i < (unsigned int)(m_vec2End - m_vec2Begin); ++i)
		m_vec2Begin[i]->v3();
	for (i = 0; i < (unsigned int)(m_vec1End - m_vec1Begin); ++i)
		m_vec1Begin[i]->v3();
}

// Caller and terminal cleanup use one shared partial receiver view below.
// Native 002141D1..00214243, 114B, terminal jump to 002118C2.
// 16-byte vector at +2A8, existing null particle-system factory and two
// rowed particle calls establish the handle semantics. Receiver identity
// and record tails remain unknown; preserve the range-erase element view.
class ParticleSystem
{
public:
    void rva001F465E(void *);
    void destroy();
};
ParticleSystem *Make001FCBD7();
class Rva001F3852ByteOneSetter
{
public:
    void enable();
};
class BfmeParticleSystemPtr
{
public:
    operator ParticleSystem *() const { return target; }
    ParticleSystem *operator->() const
    {
        ParticleSystem *value = target;
        if (!value) value = Make001FCBD7();
        return value;
    }
private:
    ParticleSystem *volatile target;
};
struct Rva00213949Element
{
    BfmeParticleSystemPtr system;
    char unknown04[12];
};
namespace _STL
{
template<class T> class allocator {};
template<class T, class A=allocator<T> > class vector
{
public:
    unsigned int size() const { return last - first; }
    T *begin() { return first; }
    T *end() { return last; }
    T &operator[](unsigned int n) { return *(begin() + n); }
    T *erase(T *a, T *b);
    void clear() { erase(begin(), end()); }
private:
    T *first, *last, *limit;
};
}
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class RvaSmartPtr12;
class Rva003FC7FC { public: void rva003FC7FC(); void rva003FC7C7(const RvaSmartPtr12 &); };
class Rva002141D1
{
public:
    void rva002141D1();
    void rva002118C2();
private:
    char unknown00[0x234];
    Rva003FC7FC **first234, **last238, **limit23C;
    Rva003FC7FC **first240, **last244, **limit248;
    char unknown24C[0x2A8 - 0x24C];
    _STL::vector<Rva00213949Element> systems;
};
void Rva002141D1::rva002141D1()
{
    for (unsigned int i=0; i<systems.size(); ++i)
    {
        if (systems[i].system)
        {
            reinterpret_cast<Rva001F3852ByteOneSetter *>(systems[i].system.operator->())->enable();
            systems[i].system->destroy();
        }
    }
    systems.clear();
    rva002118C2();
}

// Native 002118C2..0021193B: this unit's rowed cleanup ends by calling
// this function on the same receiver. Compiler barriers preserve the native
// bound-load order, as in the matched Rva00211589 loop. Both ranges and the element
// clear target are independently visible in the complete native body.
void Rva002141D1::rva002118C2()
{
    unsigned int i;
    for (i=0; i<(unsigned int)(last238-first234); ++i) {
        _ReadWriteBarrier();
        Rva003FC7FC *item=first234[i];
        if (item) item->rva003FC7FC();
    }
    for (i=0; i<(unsigned int)(last244-first240); ++i) {
        _ReadWriteBarrier();
        Rva003FC7FC *item=first240[i];
        if (item) item->rva003FC7FC();
    }
}

// Native2115EC726B: instantiate missing particle handles for the two
// rowed item vectors240 and234 while singleton flag18 is set.
// Names remain address-derived; offset and call ABI claims are target facts.
#include "ascii_string.h"
struct Vec3 {
 Vec3(){}
 Vec3(const Vec3 &v){x=v.x;y=v.y;z=v.z;}
 float x,y,z;
};
class RvaSmartPtr12 { public:
 RvaSmartPtr12(const RvaSmartPtr12 &);
 void rva0004CBC0() throw();
};
class BfmeParticleSystemHandle {
public:
 ParticleSystem *system;void *previous,*next;
 BfmeParticleSystemHandle():system(0),previous(0),next(0){}
 BfmeParticleSystemHandle(const BfmeParticleSystemHandle &other) {
  ((RvaSmartPtr12 *)this)->RvaSmartPtr12::RvaSmartPtr12(*(const RvaSmartPtr12 *)&other);
 }
 ~BfmeParticleSystemHandle() throw() {if(system)((RvaSmartPtr12 *)this)->rva0004CBC0();}
 operator bool() const {return system!=0;}
 ParticleSystem *operator->() const {return system?system:Make001FCBD7();}
};
class Rva0021122A {
 char pad00[0x1c];BfmeParticleSystemHandle particle1C;
public: BfmeParticleSystemHandle rva0021122A() const;
};
BfmeParticleSystemHandle Rva0021122A::rva0021122A() const {return particle1C;}
class Rva003F936EHost {public:void rva003FB793(Vec3 *);};
struct Rva001F3899Arg {int x,y,z;};
class Rva001F3899Slot {public:void set(const Rva001F3899Arg &);};
class Rva001F465EView {public:void unused();};
// Existing ParticleSystem method takes the target dword unchanged; native
// stores1 at98, which is not enough evidence to call it a Boolean enable.
class ParticleEnableView {public:void rva001F465E(void *);};
class Rva003FC7FCView {public:void unused();};
class Rva003FD9FA {public:void rva003FD9FA(const RvaSmartPtr12 *,Vec3);};
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;
struct ParticleSetupEnabledView {char pad[0x18];bool enabled18; bool enabled()const{return enabled18;} };
class ParticleSystemTemplate;
namespace FXParticleSystem {class ParticleSystemTemplate;}
class ParticleSystemManager {public:
 ParticleSystemTemplate *findTemplate(const AsciiString &) const;
 BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *,bool);
};
extern ParticleSystemManager *TheParticleSystemManager;
class Rva002115EC {public:
 char pad00[0x130];AsciiString template130;Vec3 position134;
 char pad140[0x16c-0x140];AsciiString template16C;Vec3 position170;
 char pad17C[0x234-0x17c];
 Rva0021122A **begin234,**end238;void *cap23C;
 Rva0021122A **begin240,**end244;void *cap248;
 void rva002115EC();
};
void Rva002115EC::rva002115EC() {
 if(!((ParticleSetupEnabledView *)g_00DFEF18)->enabled())return;
 unsigned i;
 Vec3 position;
 for(i=0;i<(unsigned)(end244-begin240);++i) {
  _ReadWriteBarrier();
  if(!begin240[i]->rva0021122A()) {
   ParticleSystemTemplate *definition=TheParticleSystemManager->findTemplate(AsciiString(template130.str()));
   if(definition) {
    BfmeParticleSystemHandle handle=TheParticleSystemManager->createParticleSystem((const ParticleSystemTemplate *)definition,true);
    if(handle) {
     ((Rva003F936EHost *)begin240[i])->rva003FB793(&position);
     ((Rva001F3899Slot *)handle.operator->())->set(*(const Rva001F3899Arg *)&position);
     handle.operator->()->rva001F465E((void *)1);
     ((Rva001F3852ByteOneSetter *)handle.operator->())->enable();
     ((Rva003FD9FA *)begin240[i])->rva003FD9FA((const RvaSmartPtr12 *)&handle,position134);
    }
   }
  }
 }
 for(i=0;i<(unsigned)(end238-begin234);++i) {
  _ReadWriteBarrier();
  if(!begin234[i]->rva0021122A()) {
   ParticleSystemTemplate *definition=TheParticleSystemManager->findTemplate(AsciiString(template16C.str()));
   if(definition) {
    BfmeParticleSystemHandle handle=TheParticleSystemManager->createParticleSystem((const ParticleSystemTemplate *)definition,true);
    if(handle) {
     ((Rva003F936EHost *)begin234[i])->rva003FB793(&position);
     ((Rva001F3899Slot *)handle.operator->())->set(*(const Rva001F3899Arg *)&position);
     handle.operator->()->rva001F465E((void *)1);
     ((Rva001F3852ByteOneSetter *)handle.operator->())->enable();
     _ReadWriteBarrier();
     ((Rva003FC7FC *)begin234[i])->rva003FC7C7(*(const RvaSmartPtr12 *)&handle);
    }
   }
  }
 }
}
