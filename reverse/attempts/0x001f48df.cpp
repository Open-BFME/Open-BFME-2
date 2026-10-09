// ?rva001F48DF@Rva001F48DF@@QAEHIH@Z
// partial score=0.9363 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc
class ParticleSystem;
ParticleSystem *Make001FCBD7();
class Rva0004CABDSevenEight {public:int get()const;};
struct OldestHandle191 {ParticleSystem *system;void*prev,*next;ParticleSystem *operator->()const{return system?system:Make001FCBD7();}};
struct OldestParticle191 {virtual void *destroy(unsigned flags);char pad[0x38];OldestHandle191 system;};
class Rva001F48DF {
public:int rva001F48DF(unsigned count,int priorityCap);
 char pad[0x10];OldestParticle191 *heads[16];unsigned particleCount;
};
int Rva001F48DF::rva001F48DF(unsigned count,int priorityCap) {
 int original=count;
 while(count-- && particleCount) {
  for(int i=1;i<priorityCap;++i) {
   if(heads[i]) {
    if((unsigned char)((Rva0004CABDSevenEight*)heads[i]->system.operator->())->get())continue;
    OldestParticle191 *particle=heads[i];
    void *allocation=0;
    if(particle)allocation=particle->destroy(0);
    ::operator delete(allocation);
    break;
   }
  }
 }
 return original-count;
}
