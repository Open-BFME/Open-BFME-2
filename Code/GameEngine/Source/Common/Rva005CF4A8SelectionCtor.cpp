// cl: /O1 /G7 /arch:SSE /MD /EHs /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include
// stlport
// ??0Rva005CEF2F@@QAE@PAURva005CF22CBig@@H@Z, retail 0x005CF4A8, 525 bytes: selection-command constructor.
// Codegen levers: the building lookup is an equal-arm conditional on the iterator (it ? call : call), which
// keeps the iterator in ebx ahead of the slot counter and fixes the frame slot order; /Oy- frame.
#include <vector>
#include "Lib/ICoord3DCtorView.h"
//
// Wave-3 F78 shape family: throwing-new plus final. Each body allocates its
// POD helper with operator new, constructs it in place with (member, arg)
// (the null-checked call some shapes mistake for a cond call), then passes
// the helper (or null when allocation failed) to a thiscall final on the
// member's +0x1C subobject. The throwing new plus the in-place ctor is what
// requires the EH prologue and its 0/-1 state transitions. Callees pinned
// under their addresses; identities unproven.
//

struct Rva005CF22CBig;

class Rva00575674Sub
{
public:
	void rva00575674(void *h);
};

struct Rva005CF22CBig
{
	char m_pad[0x10];
	void *m_view10;
	char m_pad14[8];
	Rva00575674Sub m_sub;
};


struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva005773DB {
public:
    Rva005773DB(const int *);
    ~Rva005773DB() { if (m_impl) ReleaseTreeHintRef00217D4C(m_impl); }
private:
    TargetRef00217D4C *m_impl;
};
class Rva005CEA74 {
public:
    struct Payload { int v[2]; };
};
template <class T> class RvaCloneResult {
    TargetRef00217D4C *pointer;
public:
    ~RvaCloneResult() { if (pointer) ReleaseTreeHintRef00217D4C(pointer); }
};
RvaCloneResult<Rva005CEA74> Rva005CEC5DCreate(const Rva005CEA74::Payload *);
class Image;
struct Rva005D2355In;
const Image *Rva005D2355Get(Rva005D2355In *);
int GetMaxCommandPoints(void *);
class Rva0042D703PtrChaseField { public: int get() const; };
#include "../../Include/Common/Rva0042D69DPtrChaseField.h"
#include "../../Include/Common/Rva0042D6B4PtrChaseField.h"
struct Rva005CF37DPortrait {
    virtual void slot0();
    virtual void setImage(const Image *);
    virtual void slot2();
    virtual void setCounts(int current, int maximum);
    virtual void slot4();
    virtual void slot5();
    virtual void setArmy(const Rva005773DB &);
    virtual void slot7();
    virtual void refresh();
};
struct Rva005CF37DCommandUI {
    virtual void slot0();
    virtual void createButton(int slot, const RvaCloneResult<Rva005CEA74> &);
};
struct Rva002BA8F1Listener;
#include "../../Include/Common/Rva005A0B4CList.h"
class Rva005CE8F5 {
public:
    Rva005CE8F5(Rva005CF22CBig *b) : m_owner(b) {}
    virtual ~Rva005CE8F5() {}
    // Retail table 0x00C751A8 slot 1: the shared empty `ret` (0x000B3FD0).
    virtual void slot1() {}
    Rva005CF22CBig *m_owner;
};
// Existing one-vptr observer-base view: its emitted vtable is retail C3702C.
#include "../../Include/Common/Rva004FC275.h"
struct Rva005D23BBSelection;
namespace StrategicInGameUI {const Image *__cdecl GetSelectionPortrait(const Rva005D23BBSelection *);}
class Rva005CED37 {
public:Rva005CED37(const int*);
 ~Rva005CED37(){if(pointer)ReleaseTreeHintRef00217D4C(pointer);}
 TargetRef00217D4C *pointer;
};
enum ScienceType { SCIENCE_INVALID=0 };
enum NameKeyType { NAMEKEY_INVALID=0,FORCE_NAMEKEYTYPE_LONG=0x7fffffff };
class ArmorTemplate;
class Rva002E02F0 {public:void rva002E02F0(int,_STL::vector<ScienceType>*);};
class Rva002B6498 {public:ArmorTemplate *rva002B6498(NameKeyType);};
class Rva0022C0CDSubsystem;
extern Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct LivingWorldActivePlayerView {char gap[0x98];void *player;};
struct LivingWorldPlayerKeyView {char gap[0x40];int key;int getKey()const{return key;}};
class Rva002E2903Player;
#include "../../Include/GameLogic/Rva002BA8F1Logic.h"
#include "../../Include/Common/Rva0042D6E6PtrChaseField.h"

class Rva005CEAE6 {public:struct Payload{int v[3];};};
class Rva005CEC8F {public:TargetRef00217D4C *pointer;
 ~Rva005CEC8F(){if(pointer)ReleaseTreeHintRef00217D4C(pointer);}
};
Rva005CEC8F __cdecl Rva005CEC8FCreate(const Rva005CEAE6::Payload*);
class Rva005E8F50;
struct Rva005E8FECOwner;
struct Rva005E8FECSource;
class Rva005E90EC {public:Rva005E90EC(void*,int,void*,Rva005E8FECOwner*,Rva005E8FECSource*);void *pointer;};
class Rva005CEA51 {public:
 Rva005CEA51():pointer(0){}
 ~Rva005CEA51();
 void rva005CEA51(Rva005E8F50*);
 void rva005CE7EA();
 Rva005E8F50 *pointer;
};
// The Link constructor is rowed in Rva0023A128Ctor.cpp (0x00238DDB); inlined here, so no copy.
class Rva0023A128Link {public:__declspec(dllimport) __forceinline Rva0023A128Link(){}~Rva0023A128Link(){}virtual void rva00239B94(int);virtual void v01(int);};
class Rva005CEF2F: public Rva005CE8F5,public Rva0023A128Link {
public:Rva005CEF2F(Rva005CF22CBig*,int);virtual ~Rva005CEF2F();virtual void slot1();
 int selection;Rva005CEA51 secondary;
};

Rva005CEF2F::Rva005CEF2F(Rva005CF22CBig*b,int value):Rva005CE8F5(b),selection(value) {
 ((Rva004FC275*)selection)->rva004FC299();
 void *view=m_owner->m_view10;
 Rva005CF37DPortrait *portrait=(Rva005CF37DPortrait*)((Rva0042D703PtrChaseField*)view)->get();
 if(portrait){
  portrait->setImage(StrategicInGameUI::GetSelectionPortrait((const Rva005D23BBSelection*)selection));
  {int copy=selection;Rva005CED37 ref(&copy);portrait->setArmy((const Rva005773DB&)ref);}
  portrait->refresh();
 }
 Rva005CF37DCommandUI *commands=(Rva005CF37DCommandUI*)((Rva0042D69DPtrChaseField*)view)->get();
 if(commands){
  int button=((Rva0042D6B4PtrChaseField*)view)->get();
  if(button){
   _STL::vector<ScienceType> keys;
   void *player=((LivingWorldActivePlayerView*)TheLivingWorldLogic)->player;
   ((Rva002E02F0*)TheLivingWorldBuildingTemplateStore)->rva002E02F0(((LivingWorldPlayerKeyView*)player)->getKey(),&keys);
   int slot=1;
   _STL::vector<ScienceType>::iterator end=keys.end();
   for(_STL::vector<ScienceType>::iterator it=keys.begin();it!=end;++it){
    ArmorTemplate *building=(it)?((Rva002B6498*)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)*it):((Rva002B6498*)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)*it);
    if(building){
     commands->createButton(slot,(const RvaCloneResult<Rva005CEA74>&)Rva005CEC8FCreate((const Rva005CEAE6::Payload*)&ICoord3D(button,selection,(int)building)));
     if(++slot>=6)break;
    }
   }
  }
 }
 int alternate=((Rva0042D6E6PtrChaseField*)view)->get();
 if(alternate){
  int button=((Rva0042D6B4PtrChaseField*)view)->get();
  if(button){
   Rva002E2903Player*player=((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(*(int*)((char*)m_owner+0xc),0);
   if(player){
    Rva005E90EC *item=new Rva005E90EC((void*)alternate,button,*(void**)((char*)m_owner+8),(Rva005E8FECOwner*)selection,(Rva005E8FECSource*)player);
    secondary.rva005CEA51((Rva005E8F50*)item);
   }
  }
 }
 ((Rva005A0B4CList*)((char*)selection+8))->append((Rva002BA8F1Listener*)static_cast<Rva0023A128Link*>(this));
}
