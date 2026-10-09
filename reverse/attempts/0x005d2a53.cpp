// ?rva005D2A53@Rva005D25F2@@QAEXXZ
// partial score=0.9652579852579852 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
struct TargetRef00217D4C {virtual void*destroy(unsigned);virtual void slot1();int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct TreeHintRef00217D4C {TargetRef00217D4C*m_ptr;TreeHintRef00217D4C(const TreeHintRef00217D4C&);TreeHintRef00217D4C&operator=(const TreeHintRef00217D4C&);~TreeHintRef00217D4C(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}};
class Rva005C39C4 {public:TreeHintRef00217D4C rva005C39C4(int);};
class Rva002BED91 {public:void clear();TargetRef00217D4C*ptr;};
class Rva005C3F02 {public:void rva005C3E81();};
struct CommandSlot {int button;Rva005C3F02*submenu;void*flash;Rva002BED91 queued;TreeHintRef00217D4C active;unsigned startTime,timeout;};
class BfmeAptWindowManager;extern BfmeAptWindowManager*g_bfmeAptWindowManager;
int __cdecl Rva00525338Fire(void*,void*,const char*,const char*,int*,void*);
class Rva005D25F2 {public:void rva005D2A53();private:char unknown[4];void*level;AsciiString name;char unknownC[16];CommandSlot slots[6];};
void Rva005D25F2::rva005D2A53(){ Rva005D25F2* volatile self=this;
 for(int i=0;i<6;++i){
  CommandSlot*s=(CommandSlot*)((char*)self+(i+1)*28);
  if(s->button){
   if(s->queued.ptr){s->active=((Rva005C39C4*)s->queued.ptr)->rva005C39C4(s->button);s->queued.clear();}
   if(s->active.m_ptr)s->active.m_ptr->slot1();
  }
  if(s->submenu)s->submenu->rva005C3E81();
  if(s->timeout&&timeGetTime()-s->startTime>=s->timeout){Rva005D25F2*owner=self;Rva00525338Fire(g_bfmeAptWindowManager,owner->level,owner->name.str(),"SetFlashEffectState",&i,(void*)"_hide");s->timeout=0;}
 }
}
