// cl: /Ireference/shims/bfme2_ascii /O1 /G6 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// Complete native343B entry parser at RVA004CB572; EH metadata also EXACT.
// Target FieldParse C5F1F0 and UpgradeSoundSelector consumer stride384 establish
// the owner family; the entry and parse method keep address-derived names.
// Native two128B mask temporaries plus MultiIniFieldParse132B prove frame188.
// Vector clear wrapper preserves native cached receiver/EDI and zero/EBX.
// All five table tokens, offsets, userdata and procedure VAs read from retail.
// The first procedure is the independently matched33DC9C28B dispatcher,
// whose nested C10C2C table uses the matched183B33DBE5 sound-map callback.
// The complete table is separately byte, relocation and extent verified.
// BF1 semantic lead874e38488c7dcf8cf3343452e8e5371bb3a0e64c:
// UpgradeSoundSelectorClientBehaviorParseSoundUpgrade.cpp (528B donor record).
// The target records are900B, supplied by independently matched ctor/copy/dtor.
// stlport
#include <vector>
#include <string.h>
#include "ascii_string.h"
class INI;
typedef void (*INIFieldParseProc)(INI*,void*,void*,const void*);
#include "../../Include/Common/INI/FieldParse.h"
#include "../../Include/Common/INI/INI.h"
#include "../../Include/GameClient/ModelConditionFlags.h"
class Rva001EAE6FHelper { char bytes[128];public:Rva001EAE6FHelper(){clear80();}Rva001EAE6FHelper*clear80(); };
struct UpgradeMaskType: Rva001EAE6FHelper {};
class Object;
class UpgradeMuxData
{
public:
	bool rva004CB333(Object *obj);
	void getUpgradeActivationMasks(UpgradeMaskType&,UpgradeMaskType&)const;
};
class UpgradeCenter;extern UpgradeCenter*TheUpgradeCenter;
int Rva0033A495Get();
void Rva0033DC9CParse(INI*,void*,void*,const void*);
void Rva000B9468Parse(INI*,void*,void*,const void*);
struct BfmeE16;
class UpgradeSoundSelectorClientBehaviorModuleData
{
public:
	UpgradeSoundSelectorClientBehaviorModuleData();
	static void parseVoicePriority(INI*,void*,void*,const void*);
	static void parseSoundUpgrade(INI *, void *, void *, const void *);
	virtual ~UpgradeSoundSelectorClientBehaviorModuleData();
	char m_pad04[0x4];
	_STL::vector<BfmeE16> m_vec08; // +0x08
};
extern const FieldParse BfmeSoundUpgradeEntryFields[]={
 {"UnitSpecificSounds",Rva0033DC9CParse,0,0x370},
 {"ExcludedUpgrades",INI::parseAsciiStringVectorAppend,0,0x10C},
 {"VoicePriority",UpgradeSoundSelectorClientBehaviorModuleData::parseVoicePriority,0,0x37C},
 {"RequiredModelConditions",Rva000B9468Parse,0,0x118},
 {"ExcludedModelConditions",Rva000B9468Parse,0,0x164},
 {0,0,0,0}
};
namespace _STL {
template<> AsciiString* vector<AsciiString,allocator<AsciiString> >::erase(AsciiString*,AsciiString*);
template<> void vector<AsciiString,allocator<AsciiString> >::push_back(const AsciiString&);
}
class Rva004CB572 {
 char fixed0[128],fixed80[128];
 _STL::vector<AsciiString> names,excluded;
 ModelConditionFlags required,excludedConditions;
 char rest1B0[0x381-0x1B0];bool hasRequired,hasExcluded;
 public:void parse(INI*);
};
void Rva004CB572::parse(INI*ini){
 names.clear();memset(fixed0,0,sizeof(fixed0));
 excluded.clear();memset(fixed80,0,sizeof(fixed80));
 memset(&required,0,sizeof(required));memset(&excludedConditions,0,sizeof(excludedConditions));
 const char*token;
 while((token=ini->getNextTokenOrNull(0))!=0){AsciiString value(token);names.push_back(value);}
 MultiIniFieldParse parse;
 parse.add(BfmeSoundUpgradeEntryFields,0);
 parse.add((const FieldParse*)Rva0033A495Get(),0x1B0);
 ini->initFromINIMulti(this,parse);
 if(TheUpgradeCenter){UpgradeMaskType activation,conflicting;((UpgradeMuxData*)this)->getUpgradeActivationMasks(activation,conflicting);}
 hasRequired=required.rva000B3EB3();hasExcluded=excludedConditions.rva000B3EB3();
}
