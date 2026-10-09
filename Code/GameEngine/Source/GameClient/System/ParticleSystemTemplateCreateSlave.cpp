// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// ZH ParticleSys.cpp createSlaveSystem supplies the lookup/factory semantics.
// Target1F9CF3..1F9D98 instead returns a12-byte intrusive handle and creates
// only inside the initially-null cached-template branch. Name remains neutral.
#include "ascii_string.h"
class ParticleSystemTemplate;
class ParticleSystem;
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID=0 };
class RvaSmartPtr12 {
public:
 RvaSmartPtr12(const RvaSmartPtr12&);
 RvaSmartPtr12 &operator=(const RvaSmartPtr12&) throw();
 void rva0004CBC0() throw();
 void *ptr; int prev,next;
};
class BfmeParticleSystemHandle {
public:
 BfmeParticleSystemHandle():ptr(0),prev(0),next(0){}
 BfmeParticleSystemHandle(const BfmeParticleSystemHandle &x) { ((RvaSmartPtr12*)this)->RvaSmartPtr12::RvaSmartPtr12(*(const RvaSmartPtr12*)&x); }
 BfmeParticleSystemHandle &operator=(const BfmeParticleSystemHandle &x) throw() { ((RvaSmartPtr12*)this)->operator=(*(const RvaSmartPtr12*)&x); return *this; }
 ~BfmeParticleSystemHandle() { if(ptr)((RvaSmartPtr12*)this)->rva0004CBC0(); }
 void *ptr; int prev,next;
};
class ParticleSystemManager {
public:
 ParticleSystemTemplate *findTemplate(const AsciiString&)const;
 BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate*,bool);
};
extern ParticleSystemManager *TheParticleSystemManager;
namespace FXParticleSystem {
class ParticleSystemTemplate {
public:
 BfmeParticleSystemHandle rva001F9CF3(bool createSlaves) const;
 unsigned char unknown00[0x68]; AsciiString m_slaveSystemName;
 unsigned char unknown6C[0xA0-0x6C]; mutable ::ParticleSystemTemplate *m_slaveTemplate;
};
BfmeParticleSystemHandle ParticleSystemTemplate::rva001F9CF3(bool createSlaves)const {
 BfmeParticleSystemHandle slave;
 if(m_slaveTemplate==0 && !m_slaveSystemName.isEmpty()) {
  m_slaveTemplate=TheParticleSystemManager->findTemplate(m_slaveSystemName);
  if(m_slaveTemplate)
   slave=TheParticleSystemManager->createParticleSystem(m_slaveTemplate,createSlaves);
 }
 return slave;
}
}
