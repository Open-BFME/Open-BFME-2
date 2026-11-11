// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
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
class Rva0039A270MoveOwner {public:void rva0039A270Move(Object*);};
class Rva00395CEB {public:void rva0039611E();char storage[8];};
struct CastleData {char prefix[0x1C];float wait,packedWait,transitionWait;};
struct LogicLogView {char prefix[0x1B4];int enabled;};
extern GameLogic*TheGameLogic;
// Existing data-ledger owner of the mutable FPS integer, RVA009BA4E8.
extern int BfmeClientFramesPerSecond;
extern "C" FILE*theLogicRandomLogFile;
enum UpdateSleepTime {UPDATE_SLEEP_NONE=1};
class CastleObjectModule {public:virtual ~CastleObjectModule();CastleData*data;Object*object;};
class CastleBehaviorInterface {public:virtual void behaviorSlot();};
class CastleBehavior:public CastleObjectModule,public CastleBehaviorInterface,public UpdateModuleInterface {public:virtual UpdateSleepTime update();void rva00398E9A();bool checkForInstantUnPack();bool checkForAutoPack();void initiatePack();void rva00398BC7();void teleportStragglersFromWallToGround(bool);Object*getObject()const{return object;}void rva0039A7D6();void rva00397D0A(bool);void rva00397B03(ObjectStatusTypes,bool);
 char pad14[0x20];int state34;char pad38[8];float wait40;char pad44[0xC];
 _STL::vector<ObjectID>owned50,owned5C,owned68,owned74;char pad80[0x20];Rva00395CEB mapA0;
};
#include "../../../../Include/GameLogic/Module/Rva00397E50.h"
enum NameKeyType{NAMEKEY_INVALID=0};
#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator*TheNameKeyGenerator;
#include "../../../../Include/Common/PlayerList.h"
extern PlayerList*ThePlayerList;
#include "../../../../Include/GameLogic/AIPathfind.h"
#include "../../../../Include/GameLogic/AI.h"
void CastleBehavior::rva0039A7D6(){
 Object*self=object;if(!self)return;
 {_STL::vector<ObjectID>*vec=&owned50;
 for(_STL::vector<ObjectID>::iterator it=vec->begin();it!=owned50.end();++it){Object*owned=TheGameLogic->findObjectByID(*it);if(owned)TheGameLogic->destroyObject(owned);}vec->erase(vec->begin(),vec->end());}
 {_STL::vector<ObjectID>*vec=&owned5C;
 for(_STL::vector<ObjectID>::iterator it=vec->begin();it!=owned5C.end();++it){Object*owned=TheGameLogic->findObjectByID(*it);if(owned){owned->setStatus(STATUS83,false);TheGameLogic->destroyObject(owned);}}vec->erase(vec->begin(),vec->end());}
 {_STL::vector<ObjectID>*vec=&owned74;
 for(_STL::vector<ObjectID>::iterator it=vec->begin();it!=owned74.end();++it){Object*owned=TheGameLogic->findObjectByID(*it);if(owned)TheGameLogic->destroyObject(owned);}vec->erase(vec->begin(),vec->end());}
 *(bool*)((char*)this+0x44)=false;
 rva00397D0A(true);
 ((Rva00397E50*)this)->rva00397E50();
 GameLogic*logic=TheGameLogic;Object*pending=logic->findObjectByID(*(ObjectID*)((char*)this+0x38));if(pending)logic->destroyObject(pending);
 *(ObjectID*)((char*)this+0x38)=INVALID_OBJECT_ID;
 Drawable*draw=self->getDrawable();if(draw){AsciiString empty("");draw->rva00272895(&empty);}
 Player*civilian=ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey("PlyrCivilian"));
 if(civilian &&civilian->defaultTeam){self->setTeam(civilian->defaultTeam);self->rva0028BAC0();self->rva0028DCC4();self->rva0028D253();}
 ((Rva0039A270MoveOwner*)this)->rva0039A270Move(self);
 self->rva0028DA28();TheAI->m_pathfinder->AddObjectToPathfindMap(self);
 getObject()->getDrawable()->rva00274176(false);
 if(((LogicLogView*)TheGameLogic)->enabled>0 && theLogicRandomLogFile){
  const char*caller=((StringBase<char>*)&self->getControllingPlayer()->name)->str();int id=self->id;const char*name=((StringBase<char>*)&self->tmplate->name)->str();
  fprintf(theLogicRandomLogFile,"CAMP: Frame %d: Castle %s(%d) Packed(aka:DIE) called by %s",TheGameLogic->getFrame(),name,id,caller);
 }
}

#include <string.h>
#pragma function(memset)
extern int BfmeLogicFramesPerSecond;
