// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// INI reload slots of the Locomotor store (vftable 0x00BDE970, class
// Rva001E72B4):
//
//   slot 4, 0x001E51AC  clear the "needs restart" byte; when the shared
//                       slot 2 (0x001B5384) reports a reload, put "RIF:
//                       Locomotor reloaded" on screen through TheInGameUI
//                       (slot 16, cdecl; skipped without TheInGameUI) and
//                       latch the "reloaded" byte; pass a pending restart out
//                       through the argument, clearing it; answer the latch.
//   slot 5, 0x001E3934  once after a reload latched its byte: run
//                       0x002CF1C9 on TheThingFactory, clear the latch and
//                       answer true.
//
// Both bytes (VA 0x00DFDC60 "reloaded", 0x00DFDC61 "needs restart") are
// file-static: slot 4 loads the vptr before it stores the restart byte,
// which MSVC 7.1 schedules that way only for a static it can prove `this`
// does not alias. Their only other user (around 0x001E8B6A) sits in the same
// address range. Names are address-derived; the byte meanings are inferred
// from their uses.

#include "unicode_string.h"

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void message(UnicodeString format, ...);
};
extern InGameUI *TheInGameUI;	// VA 0x00DFEDF0

class Rva002CF1C9
{
public:
	void rva002CF1C9();
};

// View: only the 0x002CF1C9 member is called here.
class ThingFactory : public Rva002CF1C9
{
};
extern ThingFactory *TheThingFactory;	// VA 0x00DFF000

// g_Va00DFDC60: VA 0x00DFDC60 (.bss); retail initial byte 00.
static bool g_Va00DFDC60;
// g_Va00DFDC61: VA 0x00DFDC61 (.bss); retail initial byte 00.
static bool g_Va00DFDC61;

static __forceinline void clearLocomotorRestart()
{
	g_Va00DFDC61 = false;
}

class Rva001E72B4Base
{
public:
	virtual void v00();
	virtual void v01();
	virtual bool rva001B5384Slot2();
};

class Rva001E72B4 : public Rva001E72B4Base
{
public:
	bool rva001E51AC(bool *needsRestart);
	bool rva001E3934();
};

bool Rva001E72B4::rva001E51AC(bool *needsRestart)
{
	clearLocomotorRestart();
	if (rva001B5384Slot2())
	{
		if (TheInGameUI)
			TheInGameUI->message(UnicodeString(L"RIF: Locomotor reloaded"));
		g_Va00DFDC60 = true;
	}
	if (g_Va00DFDC61)
	{
		*needsRestart = true;
		clearLocomotorRestart();
	}
	return g_Va00DFDC60;
}

bool Rva001E72B4::rva001E3934()
{
	if (g_Va00DFDC60)
	{
		TheThingFactory->rva002CF1C9();
		g_Va00DFDC60 = false;
		return true;
	}
	return false;
}

// Native1E8A94..1E8C1B; WB ADD4F0 names LocomotorStore parser.
// BFME1/ZH supplies parser semantics; target adds INI type5 retirement.
// Native template154 map+C vector+18 and restart byte are target facts.
// The vector adapter reuses the verified49B pointer-word ABI at4DFCB0;
// it preserves LocomotorTemplate pointer bits, without asserting ModuleData identity.
// The field-table label describes its measured parser role; data contents unclaimed.
#include "ascii_string.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <map>
#include <vector>
class ModuleData;
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

extern const FieldParse LocomotorTemplateFields;
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
   reinterpret_cast<_STL::vector<const ModuleData*> *>(&TheLocomotorStore->retired)->push_back(reinterpret_cast<const ModuleData* const&>(original));
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
 // Diagnostic lifetime inferred from native EH; original local spelling unknown.
 if(0){AsciiString diagnostic;}
  ini->initFromINI(loco,&LocomotorTemplateFields);
  ((LocomotorTemplate *)loco)->validate();
 }
}


