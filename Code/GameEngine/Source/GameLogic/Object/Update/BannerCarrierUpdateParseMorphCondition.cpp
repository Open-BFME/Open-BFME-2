// cl: /O1 /G7 /MD /EHsc /Oi- /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BannerCarrierUpdate module-data MorphCondition parser (retail 0x0049714F, 345 B; table
// C4FA2C points here, ExpLevelDraw 0x004972A9 beside it): "UnitType" then an optional
// "Locomotor" and "ModelState", building a record through the rowed 0x00496ADE
// constructor and appending it to the module-data vector. BFME1 BannerCarrierParseExpLevelDraw
// supplies the skeleton; its donor field names are not transferred to BFME2. The throws sit
// inline: with goto labels the two exception temporaries swap stack slots.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include "ascii_string.h"
#include "Common/INIException.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <string.h>
class INI { public:
 const char *getNextToken(const char *);const char *getNextTokenOrNull(const char *);int scanInt(const char *);
 char pad00[0x420];const char *colon,*quote;
};
class ModuleData;
class Rva000B664E { public: void rva0033394D(AsciiString);unsigned words[19]; };
class Rva0042526Member
{
public:
	Rva0042526Member();
private:
	unsigned char m_pad[0x4C];
};

class Rva00496ADE
{
public:
	Rva00496ADE();
	AsciiString unitType; // +0x00
	int m_04;
	Rva0042526Member modelState; // +0x08
	AsciiString locomotor; // +0x54
};

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
 reinterpret_cast<Rva000B664E *>(&entry->modelState)->rva0033394D(AsciiString(ini->getNextToken(ini->quote)));
 reinterpret_cast<_STL::vector<const ModuleData *> *>(store)->push_back(slot);
 return;
}

// ExpLevelDraw (retail 0x004972A9, 293 B; table C4FA3C): "Level" integer, then
// repeated "SubObject" show-flag/name pairs appended to the entry's own
// pointer vector. A native redundant re-read of the parser's token pointer
// survives after the sub-object test; the self-compare of ini->colon in that
// branch condition reproduces it (tautology carrier, zero bytes).
class Rva004BA1B2 { public: Rva004BA1B2() throw();int level;unsigned vec[3]; };
struct BannerExpDraw { AsciiString subObject;bool show; };
bool rva004969E7(const char *);
static __forceinline bool isSubToken(const char *token) { return token && strcmp(token,"SubObject")==0; }
void parseBannerCarrierExpLevelDraw(INI *ini,void *instance,void *store,const void *userData) {
 Rva004BA1B2 *entry=new Rva004BA1B2;
 const ModuleData *slot=reinterpret_cast<const ModuleData *>(entry);
 const char *token=ini->getNextTokenOrNull(ini->colon);
 if(!token || strcmp(token,"Level")!=0) goto badLevel;
 entry->level=ini->scanInt(ini->getNextToken(ini->colon));
 token=ini->getNextTokenOrNull(ini->colon);
 while(token) {
  if((!isSubToken(token)) && (ini->colon != 0 || ini->colon == 0)) goto badSub;
  BannerExpDraw *sub=new BannerExpDraw;
  const ModuleData *subslot=reinterpret_cast<const ModuleData *>(sub);
  sub->show=rva004969E7(ini->getNextToken(ini->colon));
  sub->subObject.set(ini->getNextToken(ini->colon));
  reinterpret_cast<_STL::vector<const ModuleData *> *>(&entry->vec)->push_back(subslot);
  token=ini->getNextTokenOrNull(ini->colon);
 }
 reinterpret_cast<_STL::vector<const ModuleData *> *>(store)->push_back(slot);
 return;
 badSub: throw INIException(3,"'ModelState' expected");
 badLevel: throw INIException(3,"UnitType expected");
}
