// cl: /O1 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
//
// ?ProcessScriptedEvent@LuaScriptEngine@@QAEXPAVXmlNameSlotList@@@Z, retail 0x00336be4, 121 bytes. Banked partial (score 0.9338842975) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
// BFME1 9cbfb551 LuaScriptEngineParseScriptedEvent.cpp; native WB BFFE20.
#include <vector>
#include <string.h>
#pragma function(strcmp)
class XmlNameSlotList
{
public:
	int count();
	int finish();
	const char *tagAt(int);
	const char *nameAt(int);
};
struct Rva00336BE4Key {
 unsigned key;
 __declspec(noinline) Rva00336BE4Key();	// Rva00336BE4KeyCtor.cpp (0x00326BE6)
};

struct EventFlagEntry {void setKeyFromName(const char *);};
// The 4-byte key vector's push_back is the shared body at 0x002E01C6, rowed
// as vector<NameKeyType>::push_back (the key is set from a name); declared
// only, so this unit emits no copy.
enum NameKeyType { NAMEKEY_INVALID = 0 };
namespace _STL { template <> void vector<NameKeyType>::push_back(const NameKeyType &); }
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
    ((_STL::vector<NameKeyType> *)&scriptedEvents)->push_back((const NameKeyType &)record);
   }
   ++i;
  }while(i<xml->count());
 }
 xml->finish();
}
