// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native20453C full111: receiver ID4 / destroy-on-reset flag8; native204032 allocates12
// and installs vtable7E39F4. Reset destroys the flagged particle if present,
// then zerosID. Original receiver/method names unresolved. Semantic source
// lead: ZH ScriptEngine particle editor cleanup; target callback layout and
// Existing neutral HolderBase name is adopted from its owned11B destructor
// and71B caller so those consumers resolve this provider directly.
// by-value12B handle are BF2 facts, independently established by owned
// ParticleSystemManager find111 and ParticleSystemHandle destructor55.
class ParticleSystem {public:void destroy();};
ParticleSystem *Make001FCBD7();
class Rva001F3852ByteOneSetter {public:void enable();};
class RvaSmartPtr12 {public:void rva0004CBC0() throw();};
class BfmeParticleSystemHandle {
public:
 __forceinline ~BfmeParticleSystemHandle(){if(system)((RvaSmartPtr12 *)this)->rva0004CBC0();}
 operator bool() const{return system!=0;}
 ParticleSystem *operator->() const{return system?system:Make001FCBD7();}
 ParticleSystem *system;
 BfmeParticleSystemHandle *previous,*next;
};
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID=0 };
class Rva0020453CHolderBase;
class ParticleSystemManager {
 friend class Rva0020453CHolderBase;
 BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID);
};
extern ParticleSystemManager *TheParticleSystemManager;
class Rva0020453CHolderBase {
public:void release();
private:unsigned int unknown00;ParticleSystemID id;bool destroyOnReset;
};
void Rva0020453CHolderBase::release(){
 if(id!=INVALID_PARTICLE_SYSTEM_ID && destroyOnReset){
  BfmeParticleSystemHandle handle=TheParticleSystemManager->findParticleSystemByID(id);
  if(handle){
   reinterpret_cast<Rva001F3852ByteOneSetter *>(handle.system)->enable();
   handle->destroy();
  }
 }
 id=INVALID_PARTICLE_SYSTEM_ID;
}
