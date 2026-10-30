// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /DNDEBUG /MD /EHsc
// stlport
// Native004DFB7E..004DFBED RET4; WB0129B1A0 callgraph twin; same name-vector
// search as AIStructureCreepTactic::isOffensiveBuilding but with a null-record
// guard. Target receiver owner28; lookup002A8AB1 returns record160 pointer;
// names98 is a three-word vector of four-byte strings; argument's template4
// supplies name64. Original receiver and method spellings remain unproved.
#include <vector>
#include <hash_map>
#include "ascii_string.h"
struct BuilderNames004DFB7E {unsigned char prefix[0x98];_STL::vector<AsciiString> names;};
struct Rva002A8AB1Record {unsigned char prefix[0x160];BuilderNames004DFB7E *data;};
class Rva002A8F24 {public:Rva002A8AB1Record *rva002A8AB1(void*);};
// Data-ledger owner of the registry pointer at VA 0x00DFEEF8.
extern Rva002A8F24 *TheSkirmishAIManager;
struct BuilderTemplate004DFB7E {unsigned char prefix[0x64];AsciiString name;};
class Object {public:unsigned char prefix[4];BuilderTemplate004DFB7E *thingTemplate;};
class Player;
class ModuleData;
class Rva005961D6;
class Rva00596069;
class Rva005965A5;
class AIEconomyStats;
class Rva00283081;
class AIStatCollector {
public: AIStatCollector(Player *);
 void Register(Object *,int);
 void addInfoReceiver(const ModuleData *);
 bool rva004DFB7E(Object *);
private:
 Rva005961D6 *units;
 Rva00596069 *otherUnits;
 Rva005965A5 *structures;
 AIEconomyStats *resources;
 Rva00283081 *positions;
 _STL::hash_map<int,int> counts;
 Player *player;
 _STL::vector<const ModuleData *> listeners;
};
bool AIStatCollector::rva004DFB7E(Object *object)
{
 Rva002A8AB1Record *record=TheSkirmishAIManager->rva002A8AB1(player);
 if(record) {
  for(unsigned int i=0;i<record->data->names.size();++i) {
   const AsciiString &name=object->thingTemplate->name;
   if(((const StringBase<char>&)record->data->names[i]).compare((const StringBase<char>&)name)==0)return true;
  }
 }
 return false;
}
