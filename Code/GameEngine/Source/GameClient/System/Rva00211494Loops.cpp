// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
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

#include "ascii_string.h"

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

// Native21122A27B: copy the item smart handle at1C and return it by value.
// Native2115EC caller owns and conditionally destroys the returned12B object.
// Names remain address-derived; offset and call ABI claims are target facts.
// The rowed 0x0004CC19 copy only stores pointers and calls the attach at
// 0x0004CB9A, which cannot throw either; declaring that keeps the 2115EC
// handle copies out of an unwind state and its frame at 0x30.
#include "../../../Include/Common/RvaSmartPtr12.h"
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
 char pad00[0x1c];BfmeParticleSystemHandle m_particleSystem;
public: BfmeParticleSystemHandle rva0021122A() const;
};
BfmeParticleSystemHandle Rva0021122A::rva0021122A() const {return m_particleSystem;}

// Native 002115EC..002118C2 (726 bytes, RET 0): while the singleton flag at
// +0x18 is set, give every item of the pointer vectors at +0x240 and +0x234
// that has no particle handle yet a new particle system from the templates
// named at +0x130 and +0x16C: position it at the item, enable it and hand the
// handle back (with the +0x134 position for the +0x240 items). WorldBuilder
// 0xB63F70 carries the same two setup loops. Names remain address-derived;
// offsets and call ABI are target facts. Retail loads each vector's begin
// pointer before the call arguments and the element after them, which is
// what the inline vector operator[] reference gives.
struct Vec3 {
 Vec3(){}
 Vec3(const Vec3 &vec3){x=vec3.x;y=vec3.y;z=vec3.z;}
 float x,y,z;
};
class Rva003F936EHost {public:void rva003FB793(Vec3 *);};
struct Rva001F3899Arg {int x,y,z;};
#include "../../../Include/GameLogic/Module/Rva001F3899Slot.h"
class Rva003FD9FA {public:void rva003FD9FA(const RvaSmartPtr12 *,Vec3);};
class Rva002D3627Host;
class LivingWorld; extern LivingWorld *TheLivingWorld;
struct ParticleSetupEnabledView {char pad[0x18];bool enabled18; bool enabled()const{return enabled18;} };
class ParticleSystemTemplate;
#include "../../../Include/GameClient/ParticleSys.h"
extern ParticleSystemManager *TheParticleSystemManager;
class Rva002115EC {public:
 char pad00[0x130];AsciiString template130;Vec3 position134;
 char pad140[0x16c-0x140];AsciiString template16C;Vec3 position170;
 char pad17C[0x234-0x17c];
 _STL::vector<Rva0021122A *> items234;
 _STL::vector<Rva0021122A *> items240;
 void rva002115EC();
};
void Rva002115EC::rva002115EC() {
 if(!((ParticleSetupEnabledView *)((Rva002D3627Host *)TheLivingWorld))->enabled())return;
 unsigned i;
 Vec3 position;
 for(i=0;i<items240.size();++i) {
  if(!items240[i]->rva0021122A()) {
   ParticleSystemTemplate *definition=TheParticleSystemManager->findTemplate(AsciiString(template130.str()));
   if(definition) {
    BfmeParticleSystemHandle handle=TheParticleSystemManager->createParticleSystem((const ParticleSystemTemplate *)definition,true);
    if(handle) {
     ((Rva003F936EHost *)items240[i])->rva003FB793(&position);
     ((Rva001F3899Slot *)handle.operator->())->set(*(const Rva001F3899Arg *)&position);
     handle.operator->()->rva001F465E((void *)1);
     ((Rva001F3852ByteOneSetter *)handle.operator->())->enable();
     ((Rva003FD9FA *)items240[i])->rva003FD9FA((const RvaSmartPtr12 *)&handle,position134);
    }
   }
  }
 }
 for(i=0;i<items234.size();++i) {
  if(!items234[i]->rva0021122A()) {
   ParticleSystemTemplate *definition=TheParticleSystemManager->findTemplate(AsciiString(template16C.str()));
   if(definition) {
    BfmeParticleSystemHandle handle=TheParticleSystemManager->createParticleSystem((const ParticleSystemTemplate *)definition,true);
    if(handle) {
     ((Rva003F936EHost *)items234[i])->rva003FB793(&position);
     ((Rva001F3899Slot *)handle.operator->())->set(*(const Rva001F3899Arg *)&position);
     handle.operator->()->rva001F465E((void *)1);
     ((Rva001F3852ByteOneSetter *)handle.operator->())->enable();
     ((Rva003FC7FC *)items234[i])->rva003FC7C7(*(const RvaSmartPtr12 *)&handle);
    }
   }
  }
 }
}
