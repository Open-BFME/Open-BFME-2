// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// WB b16130 names FXParticleSystem::ParticleSystemManager::GetShaderSetup;
// retail boundary 1F47F8..1F4882 (138B) preserves its lazy creation and holder return.
// Target accesses prove m_particleShader at +80 and referent count at +4.
// RefCountPtr copy/release follow the existing shader factory's holder semantics;
// WB documents IsBound and the exact shader/technique literals. BFME1's clean
// particle sources do not contain this GPU shader getter, so this body is
// reconstructed from WB control flow and independently byte-verified retail.
// The legacy Rva00072A94 assignment provider is a four-byte reference holder:
// factory callers and its own bytes prove the same Add_Ref/Release_Ref contract.
#include <vector>
struct Rva0007BB16Record;
class RefCountClass {public:virtual void Delete_This();void Add_Ref(){++NumRefs;}void Release_Ref(){--NumRefs;if(!NumRefs)Delete_This();}private:int NumRefs;};
class FXShaderSetup:public RefCountClass {};
template<class T> class RefCountPtr {public:RefCountPtr():m_ptr(0){}explicit RefCountPtr(T*p):m_ptr(p){}RefCountPtr(const RefCountPtr&o):m_ptr(o.m_ptr){if(m_ptr)m_ptr->Add_Ref();}~RefCountPtr(){if(m_ptr)m_ptr->Release_Ref();}T*m_ptr;};
class Rva00072A94 {public:Rva00072A94 &operator=(const Rva00072A94&);};
RefCountPtr<FXShaderSetup> Rva00152C47_CreateFXShaderSetup(const char*,const char*,const _STL::vector<Rva0007BB16Record>*,int);
void BFME_DX8_Thread_Lock();bool BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock {public:BFMEDX8DeviceLock(){BFME_DX8_Thread_Lock();}~BFMEDX8DeviceLock(){BFME_DX8_Thread_Assert();}};
namespace FXParticleSystem {
class ParticleSystemManager {public:RefCountPtr<FXShaderSetup> GetShaderSetup();private:char opaque00[0x80];RefCountPtr<FXShaderSetup> m_particleShader;};
RefCountPtr<FXShaderSetup> ParticleSystemManager::GetShaderSetup(){
 if(!m_particleShader.m_ptr){
  BFMEDX8DeviceLock lock;
  *reinterpret_cast<Rva00072A94*>(&m_particleShader)=reinterpret_cast<const Rva00072A94&>(Rva00152C47_CreateFXShaderSetup("gpuparticle.fx","Default",0,4));
 }
 return m_particleShader;
}
}
