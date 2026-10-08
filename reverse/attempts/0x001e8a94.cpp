// ?parseLocomotorTemplateDefinition@LocomotorStore@@SAXPAVINI@@@Z
// partial score=0.98 date=2026-10-08
// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
#include "ascii_string.h"
#include <map>
#include <vector>
struct FieldParse;
class INI { public: const char *getNextToken(const char *); void initFromINI(void *,const FieldParse *); char prefix[8]; int type; };
class INIException { public: INIException(int,const char*,...); INIException(const INIException &); ~INIException(); char *message; int code; };
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Overridable { public: Overridable *friend_getFinalOverride(); };
class Rva001E3955 { public: Rva001E3955() throw(); char storage[0x154]; };
class Rva001E520C { public: Rva001E3955 *rva001E520C(Rva001E3955 *); };
class Rva001E6731 { public: unsigned rva001E71FA(const int &); };
class LocomotorTemplate { public: void validate(); };
struct LocomotorParserView { void *vtable; Overridable *next; bool overrideFlag; char pad9[3]; int retired; AsciiString name; __forceinline void setName(const AsciiString &value) { name.set(value); } };
class LocomotorStore {
public:
 LocomotorTemplate *findLocomotorTemplate(int);
 static void parseLocomotorTemplateDefinition(INI *);
 char pad[0xC]; _STL::map<int,int> templates; _STL::vector<Rva001E3955 *> retired;
};
extern LocomotorStore *TheLocomotorStore;
extern "C" bool g_Va00DFDC61;
extern const FieldParse g_00BDE2F8;
void LocomotorStore::parseLocomotorTemplateDefinition(INI *ini) {
 if(!TheLocomotorStore) throw INIException(3,"TheLocomotorStore==NULL");
 const char *token=ini->getNextToken(0);
 Rva001E3955 *loco;
 {
 int key=TheNameKeyGenerator->nameToKey(token);
 LocomotorStore *store=TheLocomotorStore;
 Rva001E3955 *original=(Rva001E3955 *)store->findLocomotorTemplate(key);
 loco=original;
 if(loco) {
  if(ini->type==2) {
   LocomotorParserView *v=(LocomotorParserView *)loco;
   Rva001E3955 *final=v->next ? (Rva001E3955 *)v->next->friend_getFinalOverride() : loco;
   loco=((Rva001E520C *)store)->rva001E520C(final);
  } else if(ini->type==5) {
   ((LocomotorParserView *)loco)->retired=1;
   Rva001E6731 *map=(Rva001E6731 *)&TheLocomotorStore->templates;
   map->rva001E71FA(key);
   TheLocomotorStore->retired.push_back(original);
   if(((LocomotorParserView *)loco)->overrideFlag) g_Va00DFDC61=true;
   loco=new Rva001E3955;
   ((LocomotorParserView *)loco)->retired=0;
   TheLocomotorStore->templates[key]=(int)loco;
  } else return;
 } else {
  loco=new Rva001E3955;
  if(ini->type==2) ((LocomotorParserView *)loco)->overrideFlag=true;
  TheLocomotorStore->templates[key]=(int)loco;
 }
 }
 if(loco) {
  { AsciiString name(token); AsciiString *dest=&((LocomotorParserView *)loco)->name; dest->set(name); }
  ini->initFromINI(loco,&g_00BDE2F8);
  ((LocomotorTemplate *)loco)->validate();
 }
}


