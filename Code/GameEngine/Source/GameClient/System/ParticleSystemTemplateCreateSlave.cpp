// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// ZH ParticleSys.cpp createSlaveSystem supplies the lookup/factory semantics.
// Target1F9CF3..1F9D98 instead returns a12-byte intrusive handle and creates
// only inside the initially-null cached-template branch. Retail export 1552 names it.
#include "ascii_string.h"
class ParticleSystemTemplate;
class ParticleSystem;
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID=0 };
#include "../../../Include/Common/RvaSmartPtr12.h"
class BfmeParticleSystemHandle {
public:
 BfmeParticleSystemHandle():ptr(0),prev(0),next(0){}
 BfmeParticleSystemHandle(const BfmeParticleSystemHandle &x) { ((RvaSmartPtr12*)this)->RvaSmartPtr12::RvaSmartPtr12(*(const RvaSmartPtr12*)&x); }
 BfmeParticleSystemHandle &operator=(const BfmeParticleSystemHandle &x) throw() { ((RvaSmartPtr12*)this)->operator=(*(const RvaSmartPtr12*)&x); return *this; }
 ~BfmeParticleSystemHandle() { if(ptr)((RvaSmartPtr12*)this)->rva0004CBC0(); }
 void *ptr; int prev,next;
};
// Retail export 1552 returns TrackingPtr<FXParticleSystem::ParticleSystem>, the same
// 12-byte handle the factory returns as BfmeParticleSystemHandle.
template <class T> class TrackingPtr {
public:
 TrackingPtr():ptr(0),prev(0),next(0){}
 TrackingPtr(const TrackingPtr &x) { ((RvaSmartPtr12*)this)->RvaSmartPtr12::RvaSmartPtr12(*(const RvaSmartPtr12*)&x); }
 TrackingPtr &operator=(const BfmeParticleSystemHandle &x) throw() { ((RvaSmartPtr12*)this)->operator=(*(const RvaSmartPtr12*)&x); return *this; }
 ~TrackingPtr() { if(ptr)((RvaSmartPtr12*)this)->rva0004CBC0(); }
 void *ptr; int prev,next;
};
#include "../../../Include/GameClient/ParticleSys.h"
extern ParticleSystemManager *TheParticleSystemManager;
namespace FXParticleSystem {
class ParticleSystem;
class ParticleSystemTemplate {
public:
 TrackingPtr<ParticleSystem> createSlaveSystem(bool createSlaves) const;
 unsigned char unknown00[0x68]; AsciiString m_slaveSystemName;
 unsigned char unknown6C[0xA0-0x6C]; mutable ::ParticleSystemTemplate *m_slaveTemplate;
};
TrackingPtr<ParticleSystem> ParticleSystemTemplate::createSlaveSystem(bool createSlaves)const {
 TrackingPtr<ParticleSystem> slave;
 if(m_slaveTemplate==0 && !m_slaveSystemName.isEmpty()) {
  m_slaveTemplate=TheParticleSystemManager->findTemplate(m_slaveSystemName);
  if(m_slaveTemplate)
   slave=TheParticleSystemManager->createParticleSystem(m_slaveTemplate,createSlaves);
 }
 return slave;
}
}
