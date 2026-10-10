// ?rva002AD25B@Player@@QAEXABVAsciiString@@@Z
// partial score=0.9338287601626016 date=2026-10-10
// ?rva002AD25B@Player@@QAEXABVAsciiString@@@Z
// partial score=0.9181676807455106 date=2026-10-10
// ?rva002AD25B@Player@@QAEXABVAsciiString@@@Z
// partial score=0.8414959012337859 date=2026-10-09
// ?rva002AD25B@Player@@QAEXABVAsciiString@@@Z
// partial score=0.75642 date=2026-10-09
// cl: /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// BFME2 Player skirmish setup; reference ZH Player.cpp copy/qualify teams section.
// Native2AD25B..2AD4EC657B and WB C13D00 define BFME2 merge/discard behavior and team-name remapping.
#include "ascii_string.h"
#include <vector>

enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);}; extern NameKeyGenerator *TheNameKeyGenerator;
class Rva00148F5ECache {public:NameKeyType get();private:NameKeyType value;const char *name;};
extern Rva00148F5ECache TheKey_playerName;
extern Rva00148F5ECache TheKey_teamOwner;
extern Rva00148F5ECache TheKey_teamName;
inline __declspec(noinline) NameKeyType Rva00148F5ECache::get(){if(value==NAMEKEY_INVALID){if(TheNameKeyGenerator!=0)value=TheNameKeyGenerator->nameToKey(name);}return value;}
class Dict {
public:
 Dict(const Dict &src):data(src.data) {if (data) ++*(unsigned short*)data;}
 ~Dict(){releaseData();}
 AsciiString getAsciiString(int key,bool *exists=0) const;
 void setAsciiString(int key,const AsciiString &value);
private:
 void releaseData();void *data;
};
class ScriptList {
public:
 ScriptList(const ScriptList &src);
 virtual ~ScriptList();
 void rva003B693A();
private: char data[0x48];
};
struct BfmeSubGE;
class BfmeThingGE {public:void rva003B89A7(BfmeSubGE *other);};
class SidesInfo {
public:
 Dict *getDict(){return &dict;}
 ScriptList *getScriptList(){return &scripts;}
 void setScriptList(ScriptList *list);
private:
 void *buildList;Dict dict;ScriptList scripts;char tail[0x60-0x54];
};
struct TeamsInfoEntry {short next,previous,reserved,free;int generation;Dict dict;};
class TeamsInfoRec {
public:
 int getFirstTeamID() const{return teams[0].next;}
 int getNextTeamID(int id) const{return teams[id].next;}
 Dict *getTeamInfo(int id){return &teams[id].dict;}
 void removeTeam(int id);
 int addTeam(const Dict *dict);
private:
 char index[0xC];_STL::vector<TeamsInfoEntry> teams;short count,freeHead;
};
class SidesList {
public:
 SidesInfo *getSkirmishSideInfo(int index);
 SidesInfo *getSideInfo(int index);
 TeamsInfoRec *getTeams(){return &teams;}
 TeamsInfoRec *getSkirmishTeams(){return &skirmishTeams;}
public:
 char pad[0x7C0];int skirmishCount;SidesInfo skirmishSides[20];TeamsInfoRec teams;TeamsInfoRec skirmishTeams;
};
extern SidesList *TheSidesList;
class Rva0019C520Owner {public:int forward(AsciiString name,int extra);};
struct Rva000B3F84Pair {const char *text;int len;};
struct AsciiStringRef {const AsciiString *string;};
struct AsciiStringPlusText : AsciiStringRef {AsciiStringPlusText(){}Rva000B3F84Pair right;};
struct Rva002226E5TextPlusString {Rva002226E5TextPlusString(){}Rva000B3F84Pair left;AsciiStringRef right;operator AsciiString();};
struct AptTextPlusStringPlusString : Rva002226E5TextPlusString {AsciiStringRef third;};
struct Rva0020F58E {AsciiStringPlusText first;AsciiStringRef second;operator AsciiString();};
Rva002226E5TextPlusString operator+(const char *left,const AsciiString &right);
AsciiStringPlusText operator+(const AsciiString &left,const char *right);
AptTextPlusStringPlusString operator+(const Rva002226E5TextPlusString &left,const AsciiString &right);
bool Rva002ACFC1Equal(int a,int b);
static __forceinline bool equalTeamNode(const AsciiString &a,const Rva002226E5TextPlusString &b) {return Rva002ACFC1Equal((int)&a,(int)&b);}
class Player {
public:
 bool rva002AC43F(int *index);
 void rva002AD25B(const AsciiString &playerName);
private:
 char pad0[0x4C];AsciiString name;int nameKey;int index;
};

inline __declspec(noinline) SidesInfo *SidesList::getSkirmishSideInfo(int i){return i>=0 && i<skirmishCount?&skirmishSides[i]:0;}

inline __declspec(noinline) bool Player::rva002AC43F(int *out){
 int count=TheSidesList->skirmishCount;*out=0;
 for(int i=0;i<count;++i){Dict *dict=TheSidesList->getSkirmishSideInfo(i)->getDict();AsciiString n=dict->getAsciiString(TheKey_playerName.get());if(n.compare(name)==0){*out=i;return true;}}
 return false;
}
void Player::rva002AD25B(const AsciiString &playerName)
{
 int skirmishIndex;
 if (!rva002AC43F(&skirmishIndex)) return;
 {
  ScriptList scripts(*TheSidesList->getSkirmishSideInfo(skirmishIndex)->getScriptList());
  SidesInfo *side=TheSidesList->getSideInfo(index);
  ((BfmeThingGE*)&scripts)->rva003B89A7((BfmeSubGE*)side->getScriptList());
  scripts.rva003B693A();
  side->setScriptList(&scripts);
 }
 Dict *sideDict=TheSidesList->getSkirmishSideInfo(skirmishIndex)->getDict();
 AsciiString originalPlayerName=sideDict->getAsciiString(TheKey_playerName.get());
 int teamID=(TheSidesList ? TheSidesList : TheSidesList)->getSkirmishTeams()->getFirstTeamID();if(teamID)do {
  if ((TheSidesList ? TheSidesList : TheSidesList)->getSkirmishTeams()->getTeamInfo(teamID)->getAsciiString(TheKey_teamOwner.get())==originalPlayerName) {
   Dict teamDict(*(TheSidesList ? TheSidesList : TheSidesList)->getSkirmishTeams()->getTeamInfo(teamID));
   AsciiString teamName=teamDict.getAsciiString(TheKey_teamName.get());
   if (equalTeamNode(teamName,"team"+originalPlayerName))
    teamDict.setAsciiString(TheKey_teamName.get(),"team"+playerName);
   teamDict.setAsciiString(TheKey_teamOwner.get(),playerName);
   int existingTeam;
   if (((Rva0019C520Owner*)TheSidesList)->forward(((Rva0020F58E*)&(*(const Rva002226E5TextPlusString*)&(playerName+"/")+teamName))->operator AsciiString(),(int)&existingTeam))
    TheSidesList->getTeams()->removeTeam(existingTeam);
   TheSidesList->getTeams()->addTeam(&teamDict);
  }
 teamID=(TheSidesList ? TheSidesList : TheSidesList)->getSkirmishTeams()->getNextTeamID(teamID); }while(teamID);
}
