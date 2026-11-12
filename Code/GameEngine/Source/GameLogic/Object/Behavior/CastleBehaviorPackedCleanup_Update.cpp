// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Split from CastleBehaviorPackedCleanup.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Native39A7D6..39AA0D has a 12-byte EH prefix split from Ghidra39A7E2.
// Castle packing completion: retail Packed diagnostic and WB ebad40 establish
// the same module owner and cleanup flow; original method name unresolved.
// BF1 packing transition donor874e384 supplies subsystem context, target bytes
// establish all offsets and calls here. Shared StringBase null char is crucial
// for the reused empty-name address in the log. All568 bytes and EH exact.
#include <stdio.h>
#include <vector>
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameClient/Drawable.h"
struct TemplateNameView {char prefix[0x64];AsciiString name;};
class Team;class Player {public:char prefix[0x4C];AsciiString name;char pad50[0x29C];Team*defaultTeam;};
enum ObjectStatusTypes {STATUS3=3,STATUS5=5,STATUS83=83};
struct NativeModelFlags {unsigned words[20];unsigned test(int bit)const{return words[bit>>5]&(1U<<(bit&31));}void set(int bit){words[bit>>5]|=1U<<(bit&31);}void clear(int bit){words[bit>>5]&=~(1U<<(bit&31));}};
class Object {public:Drawable*getDrawable()const;void rva0028BAC0();Player*getControllingPlayer()const;void rva0028AE6D();void setTeam(Team*);void rva0028DCC4();void rva0028D253();void rva0028DA28();void setStatus(ObjectStatusTypes,bool);char prefix[4];TemplateNameView*tmplate;char pad08[0x6C];int id;char pad78[0x94];NativeModelFlags flags;};
class Rva00395CEB {public:void rva0039611E();char storage[8];};
struct CastleData {char prefix[0x1C];float wait,packedWait,transitionWait;};
extern GameLogic*TheGameLogic;
// Existing data-ledger owner of the mutable FPS integer, RVA009BA4E8.
extern int BfmeClientFramesPerSecond;
extern "C" void*theLogicRandomLogFile;
enum UpdateSleepTime {UPDATE_SLEEP_NONE=1};
class CastleObjectModule {public:virtual ~CastleObjectModule();CastleData*data;Object*object;};
class CastleBehaviorInterface {public:virtual void behaviorSlot();};
class CastleBehavior:public CastleObjectModule,public CastleBehaviorInterface,public UpdateModuleInterface {public:virtual UpdateSleepTime update();void rva00398E9A();bool checkForInstantUnPack();bool checkForAutoPack();void initiatePack();void rva00398BC7();void teleportStragglersFromWallToGround(bool);Object*getObject()const{return object;}void rva0039A7D6();void rva00397D0A(bool);void rva00397B03(ObjectStatusTypes,bool);
 char pad14[0x20];int state34;char pad38[8];float wait40;char pad44[0xC];
 _STL::vector<ObjectID>owned50,owned5C,owned68,owned74;char pad80[0x20];Rva00395CEB mapA0;
};
enum NameKeyType{NAMEKEY_INVALID=0};
#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator*TheNameKeyGenerator;
#include "../../../../Include/Common/PlayerList.h"
extern PlayerList*ThePlayerList;
#include "../../../../Include/GameLogic/AIPathfind.h"
#include "../../../../Include/GameLogic/AI.h"
extern AI*TheAI;


#include <string.h>
#pragma function(memset)
extern int BfmeLogicFramesPerSecond;
#include "../../../../Include/GameLogic/Rva00399959.h"
class Rva003979FB {public:void rva003979FB(const int*,const int*);};
struct CastleConditions {unsigned words[19];void clear(){memset(words,0,sizeof(words));}void set(int n){words[n>>5]|=1U<<(n&31);}};
// Target constructor3983D4 and native secondary vtable slot0 establish the
// secondary UpdateModuleInterface receiver at primary+10. BF1 Castle units
// supply subsystem context only; WB EBF1C0 supplies the state/flag transitions.
// Native bits218/219 and all timer offsets are target facts. A common flag
// pair preserves their buffers across both opposite transition branches.
// Complete native39AA0E..39ABC5 RET439B; next33B INI parser is independent.
UpdateSleepTime CastleBehavior::update(){
 struct FlagPair {CastleConditions condition218,condition219;} flags;
 const CastleData*castleData=data;
 bool elapsed=false;
 if(wait40>0.0f){wait40-=1.0f/BfmeLogicFramesPerSecond;if(wait40<0.0f){wait40=0.0f;elapsed=true;}}
 switch(state34){
 case 0:
  if(checkForInstantUnPack())state34=4;
  rva00398E9A();
  return (UpdateSleepTime)BfmeLogicFramesPerSecond;
 case 1:
  state34=2;
  ((Rva00399959*)this)->unpack(false);
  wait40=castleData->wait;
  break;
 case 2:
  if(wait40+1.0f/BfmeLogicFramesPerSecond==castleData->wait)teleportStragglersFromWallToGround(false);
  if(elapsed){state34=3;flags.condition219.clear();flags.condition218.clear();flags.condition218.set(218);flags.condition219.set(219);((Rva003979FB*)this)->rva003979FB((const int*)flags.condition218.words,(const int*)flags.condition219.words);wait40=castleData->transitionWait;}
  break;
 case 3:
  if(elapsed){state34=4;flags.condition218.clear();flags.condition219.clear();flags.condition219.set(219);((Rva003979FB*)this)->rva003979FB((const int*)flags.condition219.words,(const int*)flags.condition218.words);rva00397B03(STATUS5,false);}
  break;
 case 4:
  if(checkForAutoPack())initiatePack();else rva00398BC7();
  break;
 case 5:
  if(elapsed){state34=0;rva0039A7D6();wait40=castleData->packedWait;}
  break;
 }
 return UPDATE_SLEEP_NONE;
}
