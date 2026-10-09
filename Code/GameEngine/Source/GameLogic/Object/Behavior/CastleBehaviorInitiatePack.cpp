// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// BFME1 clean initiatePack guide at 874e38488c7d; target call graph and WB
// eba390 establish packing identity. Target offsets and masks below are retail
// facts; descriptive class/field labels from the donor remain structural guides.
// FPS is the existing mutable data-ledger owner; a double local preserves x87.
// Move helper receives Object* on stack and ignores its ECX receiver in retail.
// EVA callee396F2C matches WB CastleBehavior::playEvaEventsForCastlePacking.
#include <vector>
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"
class Drawable {public:void fadeOut(unsigned int);void rva00274176(bool);};
struct TemplateNameView {char prefix[0x64];AsciiString name;};
class Player {public:char prefix[0x4C];AsciiString name;};
enum ObjectStatusTypes {STATUS3=3,STATUS5=5};
struct NativeModelFlags {unsigned words[20];unsigned test(int bit)const{return words[bit>>5]&(1U<<(bit&31));}void set(int bit){words[bit>>5]|=1U<<(bit&31);}void clear(int bit){words[bit>>5]&=~(1U<<(bit&31));}};
class Object {public:Drawable*getDrawable()const;Player*getControllingPlayer()const;void rva0028AE6D();void setStatus(ObjectStatusTypes,bool);char prefix[4];TemplateNameView*tmplate;char pad08[0x6C];int id;char pad78[0x94];NativeModelFlags flags;};
class Rva0039A270MoveOwner {public:void rva0039A270Move(Object*);};
class Rva00395CEB {public:void rva0039611E();char storage[8];};
struct CastleData {char prefix[0x1C];float wait;};
struct LogicLogView {char prefix[0x1B4];int enabled;};
extern GameLogic*TheGameLogic;
// Existing data-ledger owner of the mutable FPS integer, RVA009BA4E8.
extern int g_009BA4E8;
extern "C" void*theLogicRandomLogFile;
extern "C" int __cdecl fprintf(void*,const char*,...);
class CastleBehavior {public:void initiatePack();void playEvaEventsForCastlePacking();void rva00397B03(ObjectStatusTypes,bool);
 char prefix[4];CastleData*data;Object*object;char pad0C[0x28];int state34;char pad38[8];float wait40;char pad44[0xC];
 _STL::vector<ObjectID>owned50,owned5C,owned68,owned74;char pad80[0x20];Rva00395CEB mapA0;
};
void CastleBehavior::initiatePack(){
 CastleData*moduleData=data;Object*self=object;if(!self)return;
 playEvaEventsForCastlePacking();state34=5;
 ((Rva0039A270MoveOwner*)this)->rva0039A270Move(self);
 double fps=g_009BA4E8;
 int delay=(int)(fps*moduleData->wait);
 for(_STL::vector<ObjectID>::iterator it=owned50.begin();it!=owned50.end();++it){Object*owned=TheGameLogic->findObjectByID(*it);if(owned)owned->getDrawable()->fadeOut(delay);}
 for(_STL::vector<ObjectID>::iterator it=owned74.begin();it!=owned74.end();++it){Object*owned=TheGameLogic->findObjectByID(*it);if(owned)owned->getDrawable()->fadeOut(delay);}
 for(_STL::vector<ObjectID>::iterator it=owned5C.begin();it!=owned5C.end();++it){Object*owned=TheGameLogic->findObjectByID(*it);if(owned)owned->getDrawable()->fadeOut(delay);}
 if(self->flags.test(218)){self->flags.clear(218);self->rva0028AE6D();}
 if(self->flags.test(96) || !self->flags.test(94)){self->flags.clear(96);self->flags.set(94);self->rva0028AE6D();}
 self->setStatus(STATUS3,false);self->getDrawable()->rva00274176(false);
 rva00397B03(STATUS5,true);wait40=moduleData->wait;mapA0.rva0039611E();
 if(((LogicLogView*)TheGameLogic)->enabled>0 && theLogicRandomLogFile){
  const char*caller=self->getControllingPlayer()->name.str();int id=self->id;const char*name=self->tmplate->name.str();
  fprintf(theLogicRandomLogFile,"CAMP: Frame %d: Castle %s(%d) ::initiatePack(aka:DIE) called by %s",TheGameLogic->getFrame(),name,id,caller);
 }
}
