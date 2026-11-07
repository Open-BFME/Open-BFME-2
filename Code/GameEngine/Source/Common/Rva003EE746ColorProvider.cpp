// Living-world region effects observer and colour-provider lifetimes.
// Target 3EEAFB constructor164: 88B observer with map+8 and RGB groups+20/+2C/+38.
// WB1036DE0 and named SyncRegion establish the existing manager identity.
// BFDF68 observer slots RET12/12/8/8; C363C8 overrides only slot0.
// C363B8 provider has scalar destructor and pure colour; C363C0 implements colour.
// Provider scalar destructor C66C calls the folded 7C51E derived destructor.
// RegionObject FieldParse+1C and destructor3EF14A independently prove the second string.
// cl: /O1 /MD /EHsc /arch:SSE /Ireference/shims/bfme2_ascii
struct Rva003EE746Color {Rva003EE746Color(float r,float g,float b):red(r),green(g),blue(b){} float red,green,blue;};
struct Rva003EE746Region {char pad[0x13c];int id0,id1;};
struct Rva003EEAFBColourView {char pad[0x20];Rva003EE746Color color;};
class Rva00DFE1C8Host {public:char pad[0x268];Rva003EEAFBColourView*effects;};
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;
class Rva002E2903Player {public:char pad[0x184];Rva003EE746Color color;};
#include "../../Include/GameLogic/Rva002BA8F1Logic.h"
struct Rva0059E647World;
class LivingWorldLogic; extern LivingWorldLogic*TheLivingWorldLogic;
class Rva003EE711 {public:__declspec(dllimport) __forceinline Rva003EE711(){} virtual ~Rva003EE711(){};virtual Rva003EE746Color color(const Rva003EE746Region*)=0;};
class Rva003EE746ColorProvider:public Rva003EE711 {public:Rva003EE746ColorProvider(int*s):selector(s){} virtual Rva003EE746Color color(const Rva003EE746Region*);int*selector;};
// ?color@Rva003EE746ColorProvider@@UAE?AURva003EE746Color@@PBURva003EE746Region@@@Z
Rva003EE746Color Rva003EE746ColorProvider::color(const Rva003EE746Region*region) {
 int id;
 switch(*selector){case 0:id=region->id0;break;case 1:id=region->id1;break;default:id=-1;break;}
 if(id==-1){Rva003EEAFBColourView*regionEffectsManager=((Rva00DFE1C8Host*)TheLivingWorldManager)->effects;return *(const Rva003EE746Color*)((char*)regionEffectsManager+0x20);}
 Rva002E2903Player*player=((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(id,0);
 if(player)return player->color;
 return Rva003EE746Color(1.0f,1.0f,1.0f);
}

#include "ascii_string.h"
class Rva004E35A3 {public:Rva004E35A3();char bytes[12];};
class Rva004E2E58 {public:__forceinline Rva004E2E58(){((Rva004E35A3*)this)->Rva004E35A3::Rva004E35A3();}~Rva004E2E58();char bytes[12];};
class S3RegionObserverBase {public:
 virtual void rva003EF13E(int,int,int){}virtual void event1(int,int,int){}virtual void event2(int,int){}virtual void event3(int,int){}
 __declspec(noinline) ~S3RegionObserverBase(){}
};
struct S3ColorGroup {S3ColorGroup(float a,float b,float c):x(a),y(b),z(c){}float x,y,z;};
class INI; struct FieldParse;
class LivingWorldRegionEffectsManager:public S3RegionObserverBase {public:
 LivingWorldRegionEffectsManager(const AsciiString&); static FieldParse s_parseTable[];
 virtual void rva003EF13E(int,int,int); void SyncRegion(int);
 int u4;Rva004E2E58 map8;int u14;AsciiString name18;AsciiString regionObject1c;
 S3ColorGroup group20,group2c,group38;
 int selector44;Rva003EE711*active48;Rva003EE746ColorProvider provider4c;bool flag54;
};
// ??0LivingWorldRegionEffectsManager@@QAE@ABVAsciiString@@@Z
LivingWorldRegionEffectsManager::LivingWorldRegionEffectsManager(const AsciiString&asciiString)
 :u4(0),u14(0),name18(asciiString),regionObject1c(),group20(1,1,1),group2c(1,1,1),group38(0.95f,0.95f,0.95f),selector44(0),provider4c(&selector44),flag54(true){active48=&provider4c;}
typedef char S3RegionRecordSize[sizeof(LivingWorldRegionEffectsManager)==88?1:-1];

// ?rva003EF13E@LivingWorldRegionEffectsManager@@UAEXHHH@Z
void LivingWorldRegionEffectsManager::rva003EF13E(int regionId,int,int){SyncRegion(regionId);}

#include "../../Include/Common/INI/FieldParse.h"
#include "../../Include/Common/INI/INI.h"
// Retail startup body7AF9D6 fills nine dynamic effect-key entries after the
// five constant entries. Each uses the same AsciiString for token/user data.
extern AsciiString g_Va00E02E70,g_Va00E02E74;
extern AsciiString g_Rva00E02E68,g_Rva00E02E6C,g_Rva00E02E64,g_Rva00E02E78,g_Rva00E02E7C,g_Rva00E02E80,g_Rva00E02E84;
void SplineEffectParseINIBlock(INI*,void*,void*,const char*);
typedef void (__cdecl *S3FieldParser)(INI*,void*,void*,const void*);
FieldParse LivingWorldRegionEffectsManager::s_parseTable[15] = {
 {"RegionObject",INI::Rva003EEABF_ParseAsciiString,0,0x1c},
 {"NeutralRegionColor",INI::parseRGBColor,0,0x20},
 {"RegionBorderColor",INI::parseRGBColor,0,0x2c},
 {"ShellStartPositionColor",INI::parseRGBColor,0,0x38},
 {"ShouldShowRegionBorders",INI::parseBool,0,0x54},
 {0,0,0,0}
};

// ?initializeRegionEffectField absent-from-retail
static __forceinline void initializeRegionEffectField(FieldParse &entry,const AsciiString &key) {
 const char *buffer=*reinterpret_cast<char *const *>(&key);
 if(buffer) entry.token=buffer+8; else entry.token="";
 entry.parse=(S3FieldParser)SplineEffectParseINIBlock;
 if(buffer) entry.userData=buffer+8; else entry.userData="";
 entry.offset=0;
}
// CRT initializer pointer at native9A4E24 independently names7AF9D6.
// Its stores fill the nine runtime entries and the final terminator; retain
// the existing five constant entries and the same240-byte table storage.
void initializeRegionEffectFields() {
 initializeRegionEffectField(LivingWorldRegionEffectsManager::s_parseTable[5],g_Va00E02E70);
 initializeRegionEffectField(LivingWorldRegionEffectsManager::s_parseTable[6],g_Va00E02E74);
 initializeRegionEffectField(LivingWorldRegionEffectsManager::s_parseTable[7],g_Rva00E02E68);
 initializeRegionEffectField(LivingWorldRegionEffectsManager::s_parseTable[8],g_Rva00E02E6C);
 initializeRegionEffectField(LivingWorldRegionEffectsManager::s_parseTable[9],g_Rva00E02E64);
 initializeRegionEffectField(LivingWorldRegionEffectsManager::s_parseTable[10],g_Rva00E02E78);
 initializeRegionEffectField(LivingWorldRegionEffectsManager::s_parseTable[11],g_Rva00E02E7C);
 initializeRegionEffectField(LivingWorldRegionEffectsManager::s_parseTable[12],g_Rva00E02E80);
 initializeRegionEffectField(LivingWorldRegionEffectsManager::s_parseTable[13],g_Rva00E02E84);
 LivingWorldRegionEffectsManager::s_parseTable[14].token=0;
 LivingWorldRegionEffectsManager::s_parseTable[14].parse=0;
 LivingWorldRegionEffectsManager::s_parseTable[14].userData=0;
 LivingWorldRegionEffectsManager::s_parseTable[14].offset=0;
}
class Rva003EF34AOwner {public:int fwd(int result,int value);};
struct S3RegionEntry;struct S3RegionInsertResult;
class Rva003EF328 {public:void insert(S3RegionInsertResult &,const S3RegionEntry &);char pad[12];Rva003EF34AOwner table;};
// Named subsystem pointer: GameEngine::init supplies the exact store name.
Rva003EF328 *TheLivingWorldRegionEffectsManagerStore;
struct S3RegionInsertResult {void*node;void*table;bool inserted;};
struct S3RegionEntry {AsciiString name;LivingWorldRegionEffectsManager*manager;S3RegionEntry(const AsciiString&n,LivingWorldRegionEffectsManager*m):name(n),manager(m){}};
// ?Rva003EF328::insert absent-from-retail
// Typed bridge to the existing two-output-argument insertion ABI; fully inlined here.
__forceinline void Rva003EF328::insert(S3RegionInsertResult &result,const S3RegionEntry &entry){Rva003EF34AOwner &owner=table;owner.fwd((int)&result,(int)&entry);}
// ?parseLivingWorldRegionEffectsDefinition@@YAXPAVINI@@@Z
// Native3EF467..3EF584 block parser; WB10384A0 supplies the semantic spine.
// Temporary string and pair live through insertion; the named receiver reference
// preserves ADD ECX,0C before the output-buffer PUSH. Table bytes establish all6 entries.
void parseLivingWorldRegionEffectsDefinition(INI *ini)
{
 if(ini->getLoadType()!=1)throw INIException(8,"Cannot parse LivingWorldRegionEffects except during game load");
 const char *name=ini->getNextToken(0);
 LivingWorldRegionEffectsManager*manager=new LivingWorldRegionEffectsManager(AsciiString(name));
 S3RegionInsertResult result;
 TheLivingWorldRegionEffectsManagerStore->insert(result,S3RegionEntry(AsciiString(name),manager));
 if(!result.inserted)throw INIException(3,"Duplicate LivingWorldRegionEffects names '%s'",name);
 ini->initFromINI(manager,LivingWorldRegionEffectsManager::s_parseTable);
}
