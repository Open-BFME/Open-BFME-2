// cl: /O1 /G7 /arch:SSE /MD /Ireference/shims/bfme2_ascii
// Native [000CB682,000CB826), 420B; RET0. Emitter creation for the
// W3DTruckDraw owner (BCC650 constructor381, updateBones3766, WB source
// W3DTruckDraw.cpp). Retain the established W3DTankTruckDraw callee spelling
// used by the matched tossEmitters191/enableEmitters165 family; this legacy binding is
// not independent evidence for the target's original class name.
// Semantic donor: GeneralsMD W3DTruckDraw.cpp createEmitters, at committed
// Open-BFME-1 revision575ba2b04. Retail provides module strings188/18C/190,
// drawable08/objectFC, 12B handles2EC/2F8/304 and all helper call targets.
// The smart-handle assignment44 is nonthrowing: its owned body only unlinks,
// copies and relinks intrusive nodes. The inline null test calls the existing
// owned55B handle cleanup. Early return on null in get() preserves native
// EBX=object then XOR EBX zero, and EDI->EAX fallback branches; assignment to
// a local fallback pointer instead grew the frame and commuted those roles.
#include "ascii_string.h"
class RvaSmartPtr12 { public: RvaSmartPtr12& operator=(const RvaSmartPtr12&) throw(); void rva0004CBC0() throw(); };
class Rva00270260 { public: bool rva00270260(); };
struct Rva001F3C43Arg;
struct DrawableTruckView { char pad[0xfc]; Rva001F3C43Arg *object; };
class Rva001F384AByteZeroSetter {
public:
    void disable();
};
class Rva001F3852ByteOneSetter {
public:
    void enable();
};
struct Rva001F3C43Arg {
    char m_pad[0x74];
    int m_value;
};
class Rva001F3C43Slot {
public:
    void set(const Rva001F3C43Arg *arg);
};
class ParticleSystem : public Rva001F3C43Slot {
public:
    void destroy(); void rva001F45F4(bool);
};
ParticleSystem *Make001FCBD7();
class BfmeParticleSystemHandle { public:
    __forceinline ~BfmeParticleSystemHandle() { if(m_system)((RvaSmartPtr12*)this)->rva0004CBC0(); }
    __forceinline BfmeParticleSystemHandle&operator=(const BfmeParticleSystemHandle&that){((RvaSmartPtr12*)this)->operator=(*(const RvaSmartPtr12*)&that);return *this;}
    ParticleSystem *volatile m_system;
    void *m_prev;
    void *m_next;
    ParticleSystem *get() const {
        ParticleSystem *p = m_system;
        if(!p)return Make001FCBD7();return p;
    }
};
class ParticleSystemTemplate;
class ParticleSystemManager { public: ParticleSystemTemplate *findTemplate(const AsciiString&)const; BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate*,bool); };
extern ParticleSystemManager*TheParticleSystemManager;
struct TruckDataEmitterView { char pad[0x188]; AsciiString dust,dirt,power; };
class W3DTankTruckDraw {
protected:
    void tossEmitters();
    void createEmitters();
    void enableEmitters(bool enable);
    char m_pad0[4];
    TruckDataEmitterView *data; DrawableTruckView*drawable;
    char rest[0x2e8-0xc];
    unsigned char m_effectsInitialized;
    char m_pad1[0x2ec - 0x2e9];
    BfmeParticleSystemHandle m_dust;
    BfmeParticleSystemHandle m_dirt;
    BfmeParticleSystemHandle m_power;
};
void W3DTankTruckDraw::createEmitters()
{
 if(((Rva00270260*)drawable)->rva00270260())return;
 if(data){
  const ParticleSystemTemplate *sysTemplate;
  if(!m_dust.m_system){
   sysTemplate=TheParticleSystemManager->findTemplate(data->dust);
   if(sysTemplate){
    m_dust=TheParticleSystemManager->createParticleSystem(sysTemplate,true);
    Rva001F3C43Arg *obj = drawable->object;
    m_dust.get()->set(obj);
    m_dust.get()->rva001F45F4(false);
   }
  }
  if(!m_dirt.m_system){
   sysTemplate=TheParticleSystemManager->findTemplate(data->dirt);
   if(sysTemplate){
    m_dirt=TheParticleSystemManager->createParticleSystem(sysTemplate,true);
    Rva001F3C43Arg *obj = drawable->object;
    m_dirt.get()->set(obj);
    m_dirt.get()->rva001F45F4(false);
   }
  }
  if(!m_power.m_system){
   sysTemplate=TheParticleSystemManager->findTemplate(data->power);
   if(sysTemplate){
    m_power=TheParticleSystemManager->createParticleSystem(sysTemplate,true);
    Rva001F3C43Arg *obj = drawable->object;
    m_power.get()->set(obj);
    m_power.get()->rva001F45F4(false);
   }
  }
 }
}
