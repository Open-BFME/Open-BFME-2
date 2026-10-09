// ?ProcessScriptedEvent@LuaScriptEngine@@QAEXPAVXmlNameSlotList@@@Z
// partial score=0.9338842975 date=2026-10-09
// stlport
// cl: /O1 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// BFME1 9cbfb551 LuaScriptEngineParseScriptedEvent.cpp; native WB BFFE20.
#include <vector>
#include <string.h>
#pragma function(strcmp)
class XmlNameSlotList {public:int count();int finish();const char *tagAt(int);const char *nameAt(int);};
struct Rva00336BE4Key {
 unsigned key;
 __declspec(noinline) Rva00336BE4Key();
};

struct EventFlagEntry {void setKeyFromName(const char *);};
extern template void _STL::vector<Rva00336BE4Key>::push_back(const Rva00336BE4Key &);
class LuaScriptEngine {public:
 void ProcessScriptedEvent(XmlNameSlotList *);
 char pad[0xA0];_STL::vector<Rva00336BE4Key> scriptedEvents;
};
void LuaScriptEngine::ProcessScriptedEvent(XmlNameSlotList *xml) {
 int i=0;
 if(xml->count()>0) {
  do {
   int diff=strcmp(xml->tagAt(i),"Name");
   if(diff==0) {
    const char *value=xml->nameAt(i);
    Rva00336BE4Key record;
    ((EventFlagEntry *)&record)->setKeyFromName(value);
    scriptedEvents.push_back(record);
   }
   ++i;
  }while(i<xml->count());
 }
 xml->finish();
}
