// ?parseBannerCarrierMorphCondition@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /MD /EHsc /Oi- /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception
// stlport
// Retail BannerCarrier table C4FA2C MorphCondition points to49714F and
// C4FA3C ExpLevelDraw to4972A9; both have standard INI four-argument ABI.
// BFME1 BannerCarrierParseExpLevelDraw.cpp supplies the MorphCondition
// parser skeleton, but its donor field name is not transferred to BFME2.
#include "ascii_string.h"
// Existing data-ledger ThrowInfo CFE2FC owns the real INIException cleanup
// and copy constructor. Transfer the two-field payload to that chain using
// the existing formatter ABI; no new metadata anchor or exception identity.
struct BannerINIExceptionPayload { char *message;int code; };
extern "C" void rva002f681_fill(void *,int,const char *,...);
extern const int g_00CFE2FC;
extern "C" void __stdcall _CxxThrowException(void *,const _s__ThrowInfo *);
#include <vector>
extern "C" int __cdecl strcmp(const char *,const char *);
class INI { public:
 const char *getNextToken(const char *);const char *getNextTokenOrNull(const char *);int scanInt(const char *);
 char pad00[0x420];const char *colon,*quote;
};
class Rva004BA1B2 { public: Rva004BA1B2() throw();int level;unsigned vec[3]; };
struct BannerExpDraw { AsciiString subObject;bool show; };
bool rva004969E7(const char *);
class ModuleData;
struct BannerModelINIExceptionPayload { char *message;int code; };
class Rva000B664E { public: void rva0033394D(AsciiString);unsigned words[19]; };
class Rva00496ADE { public:Rva00496ADE();AsciiString unitType;int unknown04;Rva000B664E modelState;AsciiString locomotor; };
void parseBannerCarrierMorphCondition(INI *ini,void *instance,void *store,const void *userData) {
 Rva00496ADE *entry=new Rva00496ADE;
 const ModuleData *slot=reinterpret_cast<const ModuleData *>(entry);
 const char *token=ini->getNextTokenOrNull(ini->colon);
 if(!token || strcmp(token,"UnitType")!=0) goto badUnit;
 entry->unitType.set(ini->getNextToken(ini->colon));
 token=ini->getNextTokenOrNull(ini->colon);
 if(token && strcmp(token,"Locomotor")==0) {
  const char *name=ini->getNextToken(ini->colon);
  if(name) entry->locomotor.set(name);
  token=ini->getNextTokenOrNull(ini->colon);
 }
 if(!token || strcmp(token,"ModelState")!=0) goto badModel;
 entry->modelState.rva0033394D(AsciiString(ini->getNextToken(ini->quote)));
 reinterpret_cast<_STL::vector<const ModuleData *> *>(store)->push_back(slot);
 return;
 badModel: {
  BannerModelINIExceptionPayload e;
  rva002f681_fill(&e,3,"'ModelState' expected");
  _CxxThrowException(&e,reinterpret_cast<const _s__ThrowInfo *>(&g_00CFE2FC)); __assume(0);
 }
 badUnit: {
  BannerINIExceptionPayload e;
  rva002f681_fill(&e,3,"UnitType expected");
  _CxxThrowException(&e,reinterpret_cast<const _s__ThrowInfo *>(&g_00CFE2FC)); __assume(0);
 }
}
