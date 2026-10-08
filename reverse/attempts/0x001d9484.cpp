// ?parseArmorDefinition@ArmorStore@@SAXPAVINI@@@Z
// partial score=0.88688 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC
// stlport
// WB ABCAB0 names ArmorStore::parseArmorDefinition; native1D9484..1D9611
// supplies override/new/template layout and the exact four-entry field table.
// ZH and BFME1 ba7ddda7 Armor.cpp support INI/Armor identity; BF1 donor place0.
// Best source still differs: key -20 vs retail -10, conversion bitmap -14
// vs -18, allocator homes swapped, and one cmp-load form differs by two bytes.
// Real pointer containers emit operator[]63B and push_back49B; their scratch
// call bindings improved score to .89369 but were NOT independent helper proof
// or landed pins. Normal symbol-map score is recorded below.
#include <hash_map>
#include <vector>
#include "ascii_string.h"
enum NameKeyType { NAMEKEY_INVALID=0,NAMEKEY_MAX=1<<23,FORCE_NAMEKEYTYPE_LONG=0x7fffffff };
namespace rts {template<class T>struct hash{size_t operator()(const T&)const;};}
class INI;struct FieldParse{const char*name;void(*parse)(INI*,void*,void*,const void*);const void*data;int offset;};
class INI {public:const char*getNextToken(const char*);void initFromINI(void*,const FieldParse*);static void parsePercentToReal(INI*,void*,void*,const void*);char opaque00[8];int loadType;};
class NameKeyGenerator{public:NameKeyType nameToKey(const char*);};extern NameKeyGenerator*TheNameKeyGenerator;
class ArmorTemplate {public:ArmorTemplate(const AsciiString&);~ArmorTemplate(){ }static void parseDamageScalar(INI*,void*,void*,const void*);static void parseArmorCoefficients(INI*,void*,void*,const void*);float head;float coefficients[27];float scalar;int flag;AsciiString name;};
class ModuleData;
namespace _STL {template<>void vector<const ModuleData*>::push_back(const ModuleData*const&);}
class Object;class ObjectLookupMap{public:Object**findSlot(int*);};
typedef _STL::hash_map<NameKeyType,ArmorTemplate*,rts::hash<NameKeyType>,_STL::equal_to<NameKeyType> > ArmorMap;
class ArmorStore{public:static void parseArmorDefinition(INI*);char opaque00[0xc];ArmorMap templates;char opaque20[0xc];_STL::vector<ArmorTemplate*> overrides;};extern ArmorStore*TheArmorStore;
void ArmorStore::parseArmorDefinition(INI*ini){
 static const FieldParse myFieldParse[]={ {"DamageScalar",ArmorTemplate::parseDamageScalar,0,0},{"FlankedPenalty",INI::parsePercentToReal,0,0},{"Armor",ArmorTemplate::parseArmorCoefficients,0,0},{0,0,0,0} };
 const char*c=ini->getNextToken(0);
 NameKeyType key=TheNameKeyGenerator->nameToKey(c);
 ArmorTemplate*armorTmpl;
 ArmorMap::const_iterator it=TheArmorStore->templates.find(key);
 if(it!=TheArmorStore->templates.end()){
  armorTmpl=it->second;
  if(ini->loadType==5){
   armorTmpl->flag=1;
   armorTmpl=new ArmorTemplate(c);
   armorTmpl->flag=0;
   TheArmorStore->overrides.push_back(armorTmpl);
  }else{
   ArmorTemplate temp(c);ini->initFromINI(&temp,myFieldParse);return;
  }
 }else{
  armorTmpl=new ArmorTemplate(c);
  TheArmorStore->templates[key]=armorTmpl;
 }
 ini->initFromINI(armorTmpl,myFieldParse);
}
