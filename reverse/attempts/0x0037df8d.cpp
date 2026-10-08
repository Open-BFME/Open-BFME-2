// ?rva0037DF8D@Rva0037DCA5@@QAEHPAVRva002206F9Sink@@@Z
// partial score=0.98 date=2026-10-08
// stlport
// cl: /O1 /MD /EHsc /G7 /arch:SSE /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
#include "ascii_string.h"
#include <list>
#include <utility>
class Rva002206F9Sink { public: virtual int add(void *value); };
__declspec(noinline) static int IterateTemplates(Rva002206F9Sink *sink,void *type,int count) {
 while(count>0) { if(!sink->add(type))return 0;--count; }
 return 1;
}
class Rva002D06CA {public:void *rva002D06CA(const AsciiString *);};
class ThingFactory;
extern ThingFactory *TheThingFactory;
typedef _STL::pair<AsciiString,int> HordeMember;
typedef _STL::list<HordeMember> HordeMembers;
class HordeModuleData {public:char pad[0xA4];HordeMembers members;};
class ModuleData {public:
#define SLOT(N) virtual void slot##N();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7)
 SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
 SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20)
#undef SLOT
 virtual const HordeModuleData *getHordeModuleData()const;
};
class ModuleInfo {public:char *begin,*end,*storage;const ModuleData *getNthData(int)const;};
struct CarryoverTemplate {char pad[0x115];unsigned char flag;char pad116[0x2E4-0x116];ModuleInfo modules;};
class Rva0037DCA5 {public:
 void *rva0037DC52();int rva0037DF8D(Rva002206F9Sink *sink);
 char pad[0x90];int count;
};
int Rva0037DCA5::rva0037DF8D(Rva002206F9Sink *sink) {
 if(!TheThingFactory)return 1;
 CarryoverTemplate *type=(CarryoverTemplate *)rva0037DC52();
 if(!type)return 1;
 if(!(type->flag&0x20))return IterateTemplates(sink,type,count);
 ModuleInfo &mods=type->modules;
 int n=(mods.end-mods.begin)/20;
 for(int i=0;i<n;++i) {
  if(mods.getNthData(i)) {
   const HordeModuleData *horde=mods.getNthData(i)->getHordeModuleData();
   if(horde) {
    const HordeMembers &members=horde->members;
    for(HordeMembers::const_iterator j=members.begin();j!=members.end();++j) {
     void *found=((Rva002D06CA *)TheThingFactory)->rva002D06CA(&j->first);
     if(found && !IterateTemplates(sink,found,j->second*count))return 0;
    }
   }
  }
 }
 return 1;
}
