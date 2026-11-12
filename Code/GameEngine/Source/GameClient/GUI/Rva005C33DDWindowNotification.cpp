// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native 5C33DD..5C3427 RET0; matched5C3586 tail-calls this method on
// its +08 child. Original owner/method identity unresolved. Window+0C,
// rowed instance getter314046 and id getter5C4AE9, instance owner+14 and
// canonical globals establish the data/call ABI. Slot E8 forwards four words.
class GameWindow;
class WinInstanceData
{
public:
    char prefix[0x14];
    GameWindow *owner;
};
class GameWindow
{
public:
    WinInstanceData *winGetInstanceData();
    int winGetWindowId();
    bool winIsHidden(); unsigned winGetStatus();
    char prefix[0x48]; const class Image *image;
};
class ControlBar
{
public:
    __declspec(noinline) void rva00405D77();
};
extern ControlBar *TheControlBar;
#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Include/GameClient/GameWindowManager.h"
extern GameWindowManager *TheWindowManager;
class Rva005C33DD
{
public:
    void rva005C33DD();
private:
    char prefix[0x0C];
    GameWindow *window;
};
void Rva005C33DD::rva005C33DD()
{
    WinInstanceData *instance = window->winGetInstanceData();
    if (instance == 0)
        return;
    TheControlBar->rva00405D77();
    GameWindow *owner = instance->owner;
    TheWindowManager->winSendSystemMsg(owner, 0x4008,
                            (unsigned int)window,
                            window->winGetWindowId());
}

// Native 5C3453..5C349D RET0; the matched 5C3596 slot tail-calls this
// method on its +08 child. The same target getters, receiver field and
// owner field as 5C33DD dispatch message 4009 instead of 4008. The existing
// address-derived callee name preserves the unresolved application identity.
class Rva005C3453
{
public:
    void rva005C3453();
private:
    char prefix[0x0C];
    GameWindow *window;
};
void Rva005C3453::rva005C3453()
{
    WinInstanceData *instance = window->winGetInstanceData();
    if (instance == 0)
        return;
    TheControlBar->rva00405D77();
    GameWindow *owner = instance->owner;
    TheWindowManager->winSendSystemMsg(owner, 0x4009,
                            (unsigned int)window,
                            window->winGetWindowId());
}

// The native 405D77 wrapper tail-jumps to the already verified 34-byte
// cleanup at 405AA7 with the same receiver. Supply that provider rather
// than leaving the notification bound only through a pin.
class Rva00405AA7
{
public:
    void rva00405AA7();
};
void ControlBar::rva00405D77()
{
    reinterpret_cast<Rva00405AA7 *>(this)->rva00405AA7();
}

// WB1557CC0 identifies the right-click dispatcher adjacent to the named
// ParasiticInGameCommandButton::Impl::DoOnRightClicked. Target118B proves
// activation-bit1C and enable-byte10C in GadgetButtonGetData, with BFME2's
// offsets taking precedence over WB's 20/110. Original method spelling unknown.
#include "../../../Include/GameClient/Rva00005C792CPtrChaseField.h"
void *GadgetButtonGetData(GameWindow *);
void PlaySound(const char *);
struct Rva005C349DButtonData {
 char unknown00[0x1C];unsigned flags;
 char unknown20[0x10C-0x20];bool enabled;
};
class Rva005C349D {
public:void rva005C349D();
private:char prefix[0x0C];GameWindow *window;
};
void Rva005C349D::rva005C349D()
{
 int state=reinterpret_cast<const Rva00005C792CPtrChaseField *>(this)->get();
 if(state==1 || state==3) {
  Rva005C349DButtonData *data=static_cast<Rva005C349DButtonData *>(GadgetButtonGetData(window));
  if(!data || !(data->flags&0x80000000)) {
   PlaySound("Gui_PalantirCommandButtonDisabledClick");
   return;
  }
 }
 reinterpret_cast<Rva005C3453 *>(this)->rva005C3453();
 if(state==5) {
  Rva005C349DButtonData *data=static_cast<Rva005C349DButtonData *>(GadgetButtonGetData(window));
  PlaySound(data && data->enabled ? "Gui_PalantirCommandButtonClick":"Gui_PalantirCommandButtonDisabledClick");
 } else if(state==1 || state==3) PlaySound("Gui_PalantirCommandButtonClick");
}

// WB15574B0 names ParasiticInGameCommandButton::Impl::Update in its own
// source. Native5C36F3..5C38EF RET0 independently proves window0C/objectID10,
// progress14/count18 and command options1C/override44/countF8; WB offsets
// differ and are not imported. The one-pass state block preserves priority
// while producing retail's shared constant-assignment POP tail. Natural
// static key initialization owns guardE065B0; its exact parent EH graph
// places the 13-byte reset at7A08F0, replacing the old manual global clearer.
class Rva000B3FD0Empty {public:void rva000B3FD0Empty();};
#include "../../Common/GameLogicObjectLookupView.h"
enum NameKeyType { NAMEKEY_INVALID=0 };
class Module;
class ParasiticInGameCommandButton {public:class Impl;};
class Object {friend class ParasiticInGameCommandButton::Impl;public:bool isLocallyControlled()const;protected:Module *findModule(NameKeyType)const;};
extern GameLogic *TheGameLogic;
class PlayerList;extern PlayerList *ThePlayerList;
#include "../../../Include/Common/BfmeMemberRV.h"
struct ParasiticPlayerView {char prefix[0x10];BfmeMemberRV *local;};
#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
#include "../../../Include/Common/Overridable.h"
class AsciiString;
struct Rva0045A63FObject;class Rva0045A63FModule;
Rva0045A63FModule *Rva0045A63F(const Rva0045A63FObject *,const AsciiString &);
struct Rva0045A6D3Arg;
#include "../../../Include/GameLogic/Module/AutoAbilityBehavior.h"
class Rva005C7C7D {public:void rva005C7C7D(const Image *);};
class Rva005C7C75 {public:void rva005C7C75(int);};
class Rva005C7C5D {public:void rva005C7C5D(bool);void rva005C7C65(bool);};
class Rva005C7C6D {public:void rva005C7C6D(int);};
class BfmeKeyLC;int bfmeGo924B(BfmeKeyLC *);
class BfmeObjEHA;void *bfmeGoEHAb(BfmeObjEHA *);
bool Rva00327E0EGet(GameWindow *);void *Rva00327DD8Get(GameWindow *);
struct ParasiticCommandView {char pad[0x1C];unsigned flags;unsigned getOptions()const{return flags;}char pad20[0x44-0x20];const Overridable *override44;char pad48[0xF8-0x48];int count;};
class ParasiticInGameCommandButton::Impl {public:void Update();char prefix[0xC];GameWindow *window;ObjectID objectID;float progress;int count;};
void ParasiticInGameCommandButton::Impl::Update()
{
 reinterpret_cast<Rva000B3FD0Empty *>(this)->rva000B3FD0Empty();
 ParasiticCommandView *cmd=static_cast<ParasiticCommandView *>(GadgetButtonGetData(window));
 if(!cmd)return;
 Object *object=0;if(objectID)object=TheGameLogic->findObjectByID(objectID);
 reinterpret_cast<Rva005C7C7D *>(this)->rva005C7C7D(window->image);
 bool foreign=object && !object->isLocallyControlled() && reinterpret_cast<ParasiticPlayerView *>(ThePlayerList)->local->bfmeAskRV();
 float amount=1.0f;int countValue=0;int state=0;
 if(!window->winIsHidden()) {
  unsigned flags=window->winGetStatus();
  do {
   if(flags&0x400000){state=5;break;}
   if(flags&8){state=(cmd->getOptions()&0x10000000)?4:6;break;}
   if(flags&0x40000000){state=7;break;}
   if(Rva00327E0EGet(window)){state=2;break;}
   state=((flags&0x1000000)|0x800000)>>23;
  }while(false);
  if(!foreign){amount=bfmeGo924B(reinterpret_cast<BfmeKeyLC *>(window))*.01f;countValue=reinterpret_cast<int>(bfmeGoEHAb(reinterpret_cast<BfmeObjEHA *>(window)));}
 }
 reinterpret_cast<Rva005C7C75 *>(this)->rva005C7C75(state);
 progress=amount;count=countValue;
 if(foreign)return;
 Module *module=0;
 if(object) {
  if(cmd->override44)module=reinterpret_cast<Module *>(Rva0045A63F(reinterpret_cast<Rva0045A63FObject *>(object),*reinterpret_cast<const AsciiString *>(reinterpret_cast<const char *>(cmd->override44->friend_getFinalOverride())+0x10)));
  if(!module) {
   static NameKeyType key=TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");
   module=object->findModule(key);
  }
 }
 bool automatic=false;
 if(state && module && static_cast<unsigned char>(reinterpret_cast<AutoAbilityBehavior *>(module)->isAutoAbilityCommand(reinterpret_cast<const Rva0045A6D3Arg *>(cmd))))automatic=true;
 reinterpret_cast<Rva005C7C5D *>(this)->rva005C7C5D(automatic);
 reinterpret_cast<Rva005C7C5D *>(this)->rva005C7C65(cmd->count>0);
 reinterpret_cast<Rva005C7C6D *>(this)->rva005C7C6D(reinterpret_cast<int>(Rva00327DD8Get(window)));
}
