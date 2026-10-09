// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native587479..587490: RET4 deleting helper, bit0 invokes standard operator delete2FD60; returns original receiver.
// BF1 AI unit sweep found an identical compiler helper; its TurretAIData name is not a target fact.
void __cdecl operator delete(void*);
class Rva00587479 {public:void *rva00587479(unsigned flags);};
void *Rva00587479::rva00587479(unsigned flags){if(flags&1)operator delete(this);return this;}
