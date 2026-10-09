// cl: /O1 /DNDEBUG /MD /EHsc
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
