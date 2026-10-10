// ?newMap@ScriptEngine@@QAEXXZ
// partial score=0.98169166 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// stlport
#include <vector>
#include "ascii_string.h"
enum NameKeyType { NAMEKEY_INVALID=0 };
enum ScienceType { SCIENCE_UNKNOWN=0 };
class Script;
class Rva0023DAA5List {public:void clear();void*head;};
class Rva00206593 {public:void rva00206EC7();int header,count,compare;};
class Rva002065C8 {public:void rva00206EF0();int header,count,compare;};
class Rva002065FD {public:void rva00206F19();int header,count,compare;};
class Rva00206632 {public:void rva00206F42();int header,count,compare;};
class Player {public:char opaque[0x50];NameKeyType nameKey;};
class PlayerList {public:Player*getNthPlayer(int);};extern PlayerList*ThePlayerList;
class NameKeyGenerator {public:const AsciiString&keyToName(NameKeyType);};extern NameKeyGenerator*TheNameKeyGenerator;
struct Rva002048A2 {virtual~Rva002048A2();AsciiString old;AsciiString*target;Rva002048A2(AsciiString*,const AsciiString&);};
struct ScriptNodePayload {char prefix[4];char scriptStorage[1];__forceinline Script*script(){return reinterpret_cast<Script*>(scriptStorage);}};
struct ScriptEntry {int next;int word4;AsciiString name;int wordC;ScriptNodePayload*payload;};
class ScriptList {public:char prefix[0x38];ScriptEntry*entries;char opaque3C[0xC];int first;};
class SidesInfo {public:char prefix[8];ScriptList scripts;};
class SidesList {public:SidesInfo*getSideInfo(int);char prefix[0x3C];int count;};extern SidesList*TheSidesList;
namespace _STL {template<>ScienceType*vector<ScienceType>::erase(ScienceType*,ScienceType*);}
class ScriptEngine {public:void newMap();void checkConditionsForTeamNames(Script*,const AsciiString&);
char prefix[0x190A0];Rva00206593 counters;Rva002065C8 flags;Rva002065FD mapB8;Rva00206632 mapC4;
char opaque190D0[0x1A104-0x190D0];int endTimer,closeTimer;AsciiString playerName;
char opaque110[0x1C];bool firstUpdate;char pad12D[3];Player*currentPlayer;int word134,fadeMode;bool flag13C;char pad13D[3];
float minFade,maxFade,curFade;int curFrame,fadeIncrease,fadeHold,fadeDecrease,word15C,word160;
char playerMapHeaders[20*12];Rva0023DAA5List completedVideo,testingSpeech,testingAudio,completedSound,uiInteractions;
Rva0023DAA5List triggered[20],midway[20],finished[20],upgrades[20];_STL::vector<ScienceType>sciences[20];
char opaque498[0x1A4E0-0x1A498];double totalUpdateTime,maxUpdateTime,numFrames,otherTime;
};
void ScriptEngine::newMap(){
counters.rva00206EC7();flags.rva00206EF0();mapB8.rva00206F19();mapC4.rva00206F42();
endTimer=-1;closeTimer=-1;totalUpdateTime=0;maxUpdateTime=0;numFrames=0;
completedVideo.clear();completedSound.clear();testingSpeech.clear();testingAudio.clear();uiInteractions.clear();
for(int i=0;i<20;++i){triggered[i].clear();midway[i].clear();finished[i].clear();sciences[i].erase(sciences[i].begin(),sciences[i].end());upgrades[i].clear();}
for(int i=0;i<TheSidesList->count;++i){
currentPlayer=ThePlayerList->getNthPlayer(i);Rva002048A2 playerScope(&playerName,TheNameKeyGenerator->keyToName(currentPlayer->nameKey));
ScriptList*list=&TheSidesList->getSideInfo(i)->scripts;
if(list){for(int slot=list->first;slot!=-1;slot=list->entries[slot].next){const AsciiString&name=list->entries[slot].name;checkConditionsForTeamNames(list->entries[slot].payload->script(),name);}}
}
firstUpdate=true;fadeMode=4;curFrame=0;minFade=1;maxFade=0;fadeIncrease=0;fadeHold=0;fadeDecrease=0;curFade=0;
}
