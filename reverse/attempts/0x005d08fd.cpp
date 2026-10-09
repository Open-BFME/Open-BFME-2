// ?Update@WaitForBattleStateHandler@Impl@BattleResolver@StrategicInGameUI@@UAEXXZ
// partial score=0.7201644958876028 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
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
 class WaitForBattleStateHandler;

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
private: int m_04;
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

#include "ascii_string.h"
#include "unicode_string.h"
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class GameTextInterface {public:
 virtual ~GameTextInterface(){};
 virtual void s00()=0;virtual void s04()=0;virtual void s08()=0;virtual void s0c()=0;virtual void s10()=0;virtual void s14()=0;virtual void s18()=0;virtual void s1c()=0;virtual void s20()=0;virtual void s24()=0;virtual void s28()=0;virtual void s2c()=0;virtual void s30()=0;
 virtual UnicodeString fetch(const char*,bool * =0)=0;
 virtual UnicodeString fetch(const AsciiString&,bool * =0)=0;
};
extern GameTextInterface *TheGameText;

class AptStrategicMessageBox {private:static AptStrategicMessageBox *s_instance;friend class StrategicInGameUI::BattleResolver::Impl::WaitForBattleStateHandler;};
class Rva0054D2DDTarget {public:void method(int,const UnicodeString&,const UnicodeString&);};
class Rva005CFA87 {public:Rva005CFA87(void*,bool);char data[16];};
class Rva0056A989 {public:bool rva0056A989();};
class Rva002BA8F1Logic {public:int rva002B5256(bool);};
class LivingWorldLogic;extern LivingWorldLogic *TheLivingWorldLogic;
UnicodeString Rva005D0100Get(int);
class Rva005D087F {public:operator UnicodeString();};
struct Pair8 {int a;int b;};
struct Triple12 {int a,b,c;};
Triple12 __cdecl Rva0037BA97Init(const Pair8*,int);
struct S3WidePair {const UnicodeString *text;unsigned short sep;S3WidePair(const UnicodeString&t,unsigned short c):text(&t),sep(c){}};
class StrategicInGameUI::BattleResolver::Impl::WaitForBattleStateHandler {
 public:virtual ~WaitForBattleStateHandler();virtual void Update();
 Impl *owner;char pad08[8];unsigned long started;int battleType;bool shown;
};
void StrategicInGameUI::BattleResolver::Impl::WaitForBattleStateHandler::Update() {
 if(((Rva0056A989*)owner->m_veterancyData)->rva0056A989()){
  bool change=shown;shown=false;
  Rva005CFA87 *next=new Rva005CFA87(owner,change);
  owner->m_state.rva00575674((Object*)next);
 }else if(((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B5256(false)>1&&!shown){
  AptStrategicMessageBox *prompt=AptStrategicMessageBox::s_instance;
  if(prompt&&timeGetTime()-started>=200){
   UnicodeString wait=TheGameText->fetch("STRATEGICHUD:WaitMessage",0);
   ((Rva0054D2DDTarget*)prompt)->method(4,UnicodeString(L""),((Rva005D087F*)&Rva0037BA97Init((const Pair8*)&S3WidePair(Rva005D0100Get(battleType),'\n'),(int)&wait))->operator UnicodeString());
   shown=true;
  }
 }
}
