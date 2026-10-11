// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <memory>

// Retail42C261 and WB12BC370 CreateTurnPhaseBehavior show a four-byte
// pooled owner transferring its pointer into an STLport auto_ptr. The native
// helper42C23A..42C261 clears the owner and constructs the return buffer;
// the factory then uses auto_ptr_ref's two-word release and virtual deletion.
// The pointee and holder retain address-derived names pending their contract.
class Rva0042C23APointee
{
public:
    virtual ~Rva0042C23APointee();
};

class Rva000AD6F4 {public:void clear();};
class Object;
class Rva00575674 {public:void rva00575674(Object *);};

class Rva0042C23AHolder
{
public:
    __declspec(noinline) _STL::auto_ptr<Rva0042C23APointee> release();
    Rva0042C23AHolder():ptr(0){}
    ~Rva0042C23AHolder(){reinterpret_cast<Rva000AD6F4*>(this)->clear();}
    void reset(Rva0042C23APointee *p){reinterpret_cast<Rva00575674*>(this)->rva00575674(reinterpret_cast<Object*>(p));}
    Rva0042C23APointee *ptr;
};

_STL::auto_ptr<Rva0042C23APointee> Rva0042C23AHolder::release()
{
    _STL::auto_ptr<Rva0042C23APointee> result(ptr);
    ptr = 0;
    return result;
}

// Native42C993..42C9BA is a distinct transfer instantiation for the factory
// at42C9BA. That factory allocates the eight-byte Rva00577838, whose rowed
// constructor and vtable differ from the three turn-phase allocations above.
class Rva0042C993Pointee
{
public:
    virtual ~Rva0042C993Pointee();
};

class Rva0042C993Holder
{
public:
    _STL::auto_ptr<Rva0042C993Pointee> release();
    Rva0042C993Pointee *ptr;
};

_STL::auto_ptr<Rva0042C993Pointee> Rva0042C993Holder::release()
{
    _STL::auto_ptr<Rva0042C993Pointee> result(ptr);
    ptr = 0;
    return result;
}

// Native42C261..42C342 and WB12BC370 name CreateTurnPhaseBehavior.
// It creates phase0/2/4's already-owned 12-byte behavior, transfers the pooled
// owner into vendored STLport auto_ptr, then clears the emptied owner.
// Local helper context matters: the real Update caller below makes the
// compiler retain its hidden result in EDI at entry; external emission loads
// ESI only at the transfer and does not match. Original pointee names remain
// address-derived; constructor identities/layouts are those existing rows.
// Native42C342..42C5BC and WB12BBAF0 identify InGameUI::Impl::Update.
// WB's state1 write precedes the turn-number reset; the original frame is
// reconstructed with cached HUD/wait-slot views and ownership-transfer copy.
// Native proves fieldsC/14/1C/24/28/2C/30/34/38, the world-state views,
// two 8-byte wait-message allocations, and all calls/virtual slots.
// TheLivingWorldLogic is the established global used by sibling recoveries.
// Original field/auxiliary class names beyond the WB identities are unknown.
class Rva00575D45 : public Rva0042C23APointee {public:Rva00575D45(void *,int);char data[8];};
class Rva00576B5E : public Rva0042C23APointee {public:Rva00576B5E(void *,int);char data[8];};
class Rva005772BF : public Rva0042C23APointee {public:Rva005772BF(void *,int);char data[8];};

namespace StrategicInGameUI {
static __declspec(noinline) _STL::auto_ptr<Rva0042C23APointee> CreateTurnPhaseBehavior(int phase,void *held,int argument){
 Rva0042C23AHolder behavior;
 switch(phase){
 case 0:behavior.reset(new Rva00575D45(held,argument));break;
 case 2:behavior.reset(new Rva00576B5E(held,argument));break;
 case 4:behavior.reset(new Rva005772BF(held,argument));break;
 }
 return behavior.release();
}
}

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class BfmeSelectionState {public:bool isSelectionLocked()const;};
class Rva002BA8F1Logic {public:int rva002B5256(bool);};
class Rva002B2405 {public:int rva002B2405();};
struct WorldView {char pad[0x98];Rva002B2405 *localPlayer;char pad9C[0xF4-0x9C];int phase;char padF8[0x168-0xF8];bool closing;};
class Rva0042D6C0PtrChaseField {public:int get()const;};
class Rva0042D71A {public:int get()const;};
class Rva005750C7 {public:void rva005750C7();char data[4];};
namespace StrategicHUD {class HUD {public:void FadeOut();void rva0042D5D6();void *impl;};}
class NewTurn {public:virtual bool update();virtual void play(int);};
class TurnDisplay {public:virtual void s0();virtual void s1();virtual void s2();virtual void phase(int);};
class Rva0057416B {public:Rva0057416B();char data[8];};
class Rva0057417E;
class Rva00574192 {public:void rva00574192();};
class Rva0042C1DF {public:void clear();};
class Rva0042C1BC {public:void reset(Rva0057417E*);};

class Rva005CB260 {public:void rva005CB260();};

struct Rva0042C1F9Helper {virtual void *virt0(int);};
struct Holder0042C1F9 {
 Rva0042C1F9Helper *p;
 Holder0042C1F9(_STL::auto_ptr_ref<Rva0042C23APointee> ref):p(reinterpret_cast<Rva0042C1F9Helper*>(ref.release())){}
 Holder0042C1F9(Holder0042C1F9 &ref):p(ref.p){ref.p=0;}
 ~Holder0042C1F9(){if(p)::operator delete(p);}
};
class Rva0042C1F9 {public:Rva0042C1F9 *rva0042C1F9(Holder0042C1F9);};
struct ClientView {char pad[0x94];bool flag;};
namespace StrategicInGameUI {

namespace InGameUI {
class Impl {
public:void Update();
private:
 char pad[0xC];Rva005750C7 turn;char pad10[4];StrategicHUD::HUD hud;char pad18[4];int client;char pad20[4];int state;NewTurn *newTurn;int turnNumber;int currentPhase;Rva0042C23APointee *behavior;Rva00574192 *wait;
};
void Impl::Update(){
 if(!TheLivingWorldLogic)return;
 ((ClientView*)client)->flag=false;
 StrategicHUD::HUD *h=&hud;
 if(state!=3){
  if(((WorldView*)TheLivingWorldLogic)->closing){
   ((Rva0042C1DF*)&wait)->clear();((Rva000AD6F4*)&behavior)->clear();currentPhase=-1;h->FadeOut();state=3;
  }
 }
 if(state==3){h->rva0042D5D6();return;}
 Rva00574192 **waitSlot=&wait;
 if(wait)wait->rva00574192();
 if(state==0){newTurn=(NewTurn*)((Rva0042D6C0PtrChaseField*)h)->get();if(newTurn)state=2;}
 if(state!=0){
  if(state==2 && turnNumber>=0){
   ((Rva0042C1DF*)waitSlot)->clear();((Rva000AD6F4*)&behavior)->clear();currentPhase=-1;int nextTurn=turnNumber+1; NewTurn *indicator=newTurn; indicator->play(nextTurn);state=1;turnNumber=-1;
  }
  if(state==1){if(!newTurn->update())state=2;}
  if(state==2){
   if(((BfmeSelectionState*)TheLivingWorldLogic)->isSelectionLocked()){
    int phase=((WorldView*)TheLivingWorldLogic)->phase;
    if(phase!=currentPhase){
     ((Rva0042C1DF*)waitSlot)->clear();((Rva000AD6F4*)&behavior)->clear();
     ((Rva0042C1F9*)&behavior)->rva0042C1F9(Holder0042C1F9(static_cast<_STL::auto_ptr_ref<Rva0042C23APointee> >(CreateTurnPhaseBehavior(phase,&turn,client))));currentPhase=phase;
    }
   }else{
    ((Rva000AD6F4*)&behavior)->clear();currentPhase=-1;
    if(!*waitSlot && ((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B5256(false)>1)
     ((Rva0042C1BC*)waitSlot)->reset((Rva0057417E*)new Rva0057416B);
   }
  }
 }
 TurnDisplay *display=(TurnDisplay*)((Rva0042D71A*)h)->get();if(display){int phase=currentPhase; display->phase(phase);}
 if(behavior)((Rva005CB260*)behavior)->rva005CB260();else turn.rva005750C7();
 h->rva0042D5D6();
 LivingWorldLogic *world=TheLivingWorldLogic;
 if(((BfmeSelectionState*)world)->isSelectionLocked() && !*waitSlot && ((Rva002BA8F1Logic*)world)->rva002B5256(false)>1 && ((WorldView*)TheLivingWorldLogic)->localPlayer->rva002B2405()){
  ((Rva000AD6F4*)&behavior)->clear();((Rva0042C1BC*)waitSlot)->reset((Rva0057417E*)new Rva0057416B);
 }
}
}}
