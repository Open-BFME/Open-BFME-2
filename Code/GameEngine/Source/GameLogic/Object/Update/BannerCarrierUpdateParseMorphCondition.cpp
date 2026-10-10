// cl: /O1 /G7 /MD /EHsc /Oi- /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception
// stlport
//
// BannerCarrierUpdate module-data MorphCondition parser (retail 0x0049714F, 345 B; table
// C4FA2C points here, ExpLevelDraw 0x004972A9 beside it): "UnitType" then an optional
// "Locomotor" and "ModelState", building a record through the rowed 0x00496ADE
// constructor and appending it to the module-data vector. BFME1 BannerCarrierParseExpLevelDraw
// supplies the skeleton; its donor field names are not transferred to BFME2. The throws sit
// inline: with goto labels the two exception temporaries swap stack slots.
#include "ascii_string.h"
#include "Common/INIException.h"
#include <vector>
extern "C" int __cdecl strcmp(const char *,const char *);
class INI { public:
 const char *getNextToken(const char *);const char *getNextTokenOrNull(const char *);int scanInt(const char *);
 char pad00[0x420];const char *colon,*quote;
};
class ModuleData;
class Rva000B664E { public: void rva0033394D(AsciiString);unsigned words[19]; };
class Rva00496ADE { public:Rva00496ADE();AsciiString unitType;int unknown04;Rva000B664E modelState;AsciiString locomotor; };
void parseBannerCarrierMorphCondition(INI *ini,void *instance,void *store,const void *userData) {
 Rva00496ADE *entry=new Rva00496ADE;
 const ModuleData *slot=reinterpret_cast<const ModuleData *>(entry);
 const char *token=ini->getNextTokenOrNull(ini->colon);
 if(!token || strcmp(token,"UnitType")!=0) throw INIException(3,"UnitType expected");
 entry->unitType.set(ini->getNextToken(ini->colon));
 token=ini->getNextTokenOrNull(ini->colon);
 if(token && strcmp(token,"Locomotor")==0) {
  const char *name=ini->getNextToken(ini->colon);
  if(name) entry->locomotor.set(name);
  token=ini->getNextTokenOrNull(ini->colon);
 }
 if(!token || strcmp(token,"ModelState")!=0) throw INIException(3,"'ModelState' expected");
 entry->modelState.rva0033394D(AsciiString(ini->getNextToken(ini->quote)));
 reinterpret_cast<_STL::vector<const ModuleData *> *>(store)->push_back(slot);
 return;
}
