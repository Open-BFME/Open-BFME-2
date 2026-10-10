// cl: /O1 /G7 /DNDEBUG /MD /EHsc
#include <new>
//
// StrategicInGameUI::BattleResolver::Impl (WorldBuilder
// StrategicInGameUIBattleResolver.cpp). Target facts for
// OnLivingWorldAutoResolveBattleCompleted 0x005CFB9E (virtual, pointer at
// 0x00875584; ret 0xC):
// unless veterancy data is already held (+0x14, WorldBuilder
// m_veterancyData) it builds the auto-resolve data from the event's three
// arguments (0x005ED15D in StrategicVeterancy.cpp). Argument types are
// passed through untyped.
class StrategicVeterancy
{
public:
	class Data;
};

StrategicVeterancy::Data *__cdecl Rva005ED15DCreateAutoResolve(void *a, void *b, void *c);

namespace StrategicInGameUI
{
class BattleResolver
{
public:
	class Impl;
};
}


class Object;
class Rva00575674 {public: void rva00575674(Object *); Object *m_ptr;};
class Rva0042D6BAPtrChaseField {public: int get() const;};
class Rva0042D6B4PtrChaseField {public: int get() const;};
class Rva0042D703PtrChaseField {public: int get() const;};
class Rva0042D6FDPtrChaseField {public: int get() const;};

class StrategicInGameUI::BattleResolver::Impl
{
public:
	virtual void OnLivingWorldAutoResolveBattleCompleted(void *a, void *b, void *c);
 class StartUpStateHandler;
 class WaitForEndOfAutoResolveBattleStateHandler;

public:
	char m_pad04[8];
 void *m_context;
 int m_unknown10;
	StrategicVeterancy::Data *m_veterancyData; // +0x14
 int m_unknown18;
 Rva00575674 m_state;
};

void StrategicInGameUI::BattleResolver::Impl::OnLivingWorldAutoResolveBattleCompleted(void *a, void *b, void *c)
{
	if (!m_veterancyData)
		m_veterancyData = Rva005ED15DCreateAutoResolve(a, b, c);
}

// These are the existing provider's two 8-byte base views from
// Rva005CFDA6Dtor.cpp. Only primary slot1 is called here. The native ctor
// installs C752C4 at +0 and C752B0 at +8, and its rowed dtor/scalar dtor
// already own the Rva005CFDA6 spelling; no second class identity is minted.
class Rva005CF872 {
public:
 virtual ~Rva005CF872();
 virtual void slot1();
 virtual void slot2();
protected: void *m_04;
};
class Rva005E9F3F {
public: virtual ~Rva005E9F3F();
private: void *m_04;
};
class Rva005CFDA6 : public Rva005CF872, public Rva005E9F3F {
public:
 Rva005CFDA6(StrategicInGameUI::BattleResolver::Impl *,int,int,int,int);
 virtual void slot1();
 virtual void slot2();
};
// The existing79B constructor and48B destructor own this12B state identity.
class Rva005CFEDF : public Rva005CF872 {
public:
 Rva005CFEDF(void *);
 virtual ~Rva005CFEDF();
private: void *m_08;
};
class Rva005CFE6EObserver {
public:
 virtual void OnLivingWorldAutoResolveBattleCompleted(void *,void *,void *);
};
class StrategicInGameUI::BattleResolver::Impl::WaitForEndOfAutoResolveBattleStateHandler
 : public Rva005CF872, public Rva005CFE6EObserver {
public:
 virtual void OnLivingWorldAutoResolveBattleCompleted(void *,void *,void *);
};
// WB15B9BC0 names the callback at BattleResolver.cpp984; native5CFE6E..
// 5CFEC3 is85B RET12, with its virtual pointer at875564. The observer this
// is the second interface at+8, hence base owner4 is read at this-4. Keep
// event arguments opaque, consistent with the existing Impl observer body.
void StrategicInGameUI::BattleResolver::Impl::WaitForEndOfAutoResolveBattleStateHandler::OnLivingWorldAutoResolveBattleCompleted(void *,void *battle,void *)
{
 if(battle==static_cast<Impl *>(m_04)->m_veterancyData)
  static_cast<Impl *>(m_04)->m_state.rva00575674(
   reinterpret_cast<Object *>(new Rva005CFEDF(m_04)));
}
class StrategicInGameUI::BattleResolver::Impl::StartUpStateHandler {
public:
 virtual void *rvaSlot0(int);
 virtual void Update();
 Impl *m_owner;
};
// Target identity: WB15B74E0 names StartUpStateHandler::Update at
// StrategicInGameUIBattleResolver.cpp:501. Native5CFCED..5CFD8A is157B;
// vtable8752A0 has scalar dtor5CFCD1 then this Update, proving slot1.
// Four already rowed getters on owner+0x0C gate the state transition.
// The constructor5CF937 returns a16B next state using the existing
// destructor-owned Rva005CFDA6 class; the original state name stays unknown.
// Setter575674 and the next state's primary slot1 supply the final calls.
// Constructor and getter argument meanings stay opaque. No applicable
// clean BFME1/ZH body exists for this BFME2-specific battle UI.
void StrategicInGameUI::BattleResolver::Impl::StartUpStateHandler::Update()
{
 void *context=m_owner->m_context;
 int a=static_cast<Rva0042D6BAPtrChaseField *>(context)->get();
 if(a) {
  int b=static_cast<Rva0042D6B4PtrChaseField *>(context)->get();
  if(b) {
   int c=static_cast<Rva0042D703PtrChaseField *>(context)->get();
   if(c) {
    int d=static_cast<Rva0042D6FDPtrChaseField *>(context)->get();
    if(d) {
     Impl *owner=m_owner;
     Rva005CFDA6 *next=new Rva005CFDA6(owner,a,b,c,d);
     owner->m_state.rva00575674(reinterpret_cast<Object *>(next));
     reinterpret_cast<Rva005CFDA6 *>(owner->m_state.m_ptr)->slot1();
    }
   }
  }
 }
}

// Native5D0EB8..5D0F95/221B Update and5D0F95..5D1007/114B callback.
// C75540slot04 proves true callback entry; queue5D0FA0 missed11B prologue.
// WB15B8DD0 names ShowStartingAutoResolveBattleMessageStateHandler::Update;
// WB15B9880 supplies the third-base callback. Target measures owner4,
// argument8/startC and callback owner this-8/flag this+8 independently.
// A bool initialized true then assigned from GameInfo's84 predicate keeps
// native SETE/TEST and dialog-first layout. Owner is reloaded after new.
// delay is targetA0663C's mutable zero-filled DWORD (sole code xref here).
// Its class/static spelling is structural; no original data name claimed.
// C752CCslot04 ties Update to existing Rva005CF9FF ctor/dtor.
// The callback overrides the existing Rva005D06CB third base atC.
// Real MI generates native secondary-this owner-8/flag+8 accesses.
// Code only is credited; existing providers reused, no pins/hatches.
class Rva005D073A{public:Rva005D073A(void*);virtual ~Rva005D073A();char fields[8];};
extern "C" __declspec(dllimport) unsigned __stdcall timeGetTime();
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class Rva002BA8F1Logic{public:int rva002B5256(bool);};
class GameInfo;extern GameInfo*TheGameInfo;
struct ResolveGameInfoView{char unknown[0x84];int field84;bool isEmpty()const{return field84==0;}};
class GameMessage{public:void appendIntegerArgument(int);};
class MessageStream{public:virtual ~MessageStream();
 virtual void v01();virtual void v02();virtual void v03();virtual void v04();virtual void v05();virtual void v06();virtual void v07();virtual void v08();virtual void v09();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void v14();virtual void v15();virtual void v16();virtual void v17();virtual GameMessage*CreateMessage(int);};
extern MessageStream*MessageStreamSubsystem;
struct Rva005D06CBOwner;
class Rva005D06CBB2{public:virtual ~Rva005D06CBB2();};
class Rva005EB753{public:Rva005EB753(void*,void*,void*);virtual ~Rva005EB753();virtual void veterancySlot04();void*member04;};
class Rva005D06CB:public Rva005CF872,public Rva005D06CBB2,public Rva005EB753{public:Rva005D06CB(Rva005D06CBOwner*,void*,void*);virtual ~Rva005D06CB();virtual void veterancySlot04();bool flag14;};
struct ResolveBattleIDView{char unknown[0x34];int id;};
struct ResolvePlanView{char unknown[0xc];Rva0042D6BAPtrChaseField*argument;void*unknown10;ResolveBattleIDView*battle;void*unknown18;Rva00575674 state;};
class Rva005CF9FF:public Rva005CF872{public:Rva005CF9FF(void*,int,int,bool);virtual ~Rva005CF9FF();virtual void slot1();static unsigned delay;int m_08;unsigned m_0C;bool m_flag;};
unsigned Rva005CF9FF::delay;
void Rva005CF9FF::slot1(){
 if(((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B5256(false)>1 && timeGetTime()-m_0C<delay)return;
 bool showDialog=true;if(TheGameInfo)showDialog=((ResolveGameInfoView*)TheGameInfo)->isEmpty();
 if(showDialog){
  int value=((ResolvePlanView*)m_04)->argument->get();
  Object*next=(Object*)new Rva005D06CB((Rva005D06CBOwner*)m_04,(void*)value,(void*)m_08);
  ((ResolvePlanView*)m_04)->state.rva00575674(next);
 }else{
  GameMessage*message=MessageStreamSubsystem->CreateMessage(0x6be);
  message->appendIntegerArgument(((ResolvePlanView*)m_04)->battle->id);
  Object*next=(Object*)new Rva005D073A(m_04);
  ((ResolvePlanView*)m_04)->state.rva00575674(next);
 }
}

void Rva005D06CB::veterancySlot04(){
 if(flag14)((ResolvePlanView*)m_04)->state.rva00575674((Object*)new Rva005CFEDF(m_04));
 else ((ResolvePlanView*)m_04)->state.rva00575674((Object*)new Rva005D073A(m_04));
}
