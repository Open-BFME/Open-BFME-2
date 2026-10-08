// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
#include <stdlib.h>
// Retail576C39 frees through the existing C++-linkage game allocator30830.
// Its throwing declaration retains the native exception-state reset.
namespace _STL { void __cdecl free(void *); }
#define free _STL::free
#include <vector>
#undef free
//
// StrategicInGameUI::ResolveBattlesBehavior::Impl (WorldBuilder
// StrategicInGameUIResolveBattlesBehavior.cpp names its translateGameMessage, vtable match).
// Target facts for 0x0057667D: offers the message to its ManualPhaseEnder +0x20 and its PlayerStatusDisplayer (0x005CD690) +0x30, consuming it
// (1) when one does, else defers to the base
// UserInputTranslator::translateGameMessage 0x005CBC95 (WorldBuilder name,
// pinned). Member types are the callees' views (inference).

enum GameMessageDisposition
{
	KEEP_MESSAGE,
	DESTROY_MESSAGE
};

class GameMessage;

class UserInputTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
};

// The translators behind the behavior (ManualPhaseEnder.cpp's and
// PlayerStatusDisplayer.cpp's units).
namespace StrategicInGameUI
{
class ManualPhaseEnder
{
public:
	GameMessageDisposition Translate(const GameMessage *msg); // 0x005CD8F7

private:
	char m_data[0x10];
};
}
namespace StrategicInGameUI
{
class PlayerStatusDisplayer
{
public:
	GameMessageDisposition rva005CD690(const GameMessage *msg); // 0x005CD690
};
}

namespace StrategicInGameUI
{
class ResolveBattlesBehavior
{
public:
	class Impl;
};
}

class StrategicInGameUI::ResolveBattlesBehavior::Impl : public UserInputTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	void rva00576AF3();
 void CreateResolveRegionOwnershipChecklistItems();
 int rva00576946(void *, unsigned);

private:
	char m_pad04[0x20 - 0x04];
	StrategicInGameUI::ManualPhaseEnder m_phaseEnder; // +0x20
	StrategicInGameUI::PlayerStatusDisplayer m_statusDisplayer; // +0x30
};

GameMessageDisposition StrategicInGameUI::ResolveBattlesBehavior::Impl::translateGameMessage(const GameMessage *msg)
{
	if (m_phaseEnder.Translate(msg) == DESTROY_MESSAGE
		|| m_statusDisplayer.rva005CD690(msg) == DESTROY_MESSAGE)
		return DESTROY_MESSAGE;
	return UserInputTranslator::translateGameMessage(msg);
}

class LivingWorldPendingBattle;
class PendingBattleVisitor;
class Rva0020E7E8Callback;
class LivingWorldRegionManager
{
public:
    LivingWorldPendingBattle *rva0020E6C0();
    LivingWorldPendingBattle *rva0020E501(int);
    void EnumeratePendingBattles(PendingBattleVisitor &) const;
    void EnumerateCompletedBattles(Rva0020E7E8Callback *);
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct ResolveBattleWorldView
{
    char unknown00[0xB0];
    LivingWorldRegionManager *regionManager;
};
struct ResolveBattleResultView
{
    char unknown00[0x3C];
    int state;
};
class Object;
class Rva00575674 { public: void rva00575674(Object *); };
class Rva00576591
{
public:
    Rva00576591(void *owner);
private:
    char nativeStorage[12];
};

// Native576AF3..576B5E: when the selected pending/completed battle's +3C
// state is2, install a twelve-byte state object in the receiver's +1C holder.
// The rowed constructor's vtable/dtor prove its identity; field purpose is
// unresolved. WB supplies CheckCompletedTacticalGame as a semantic lead.
void StrategicInGameUI::ResolveBattlesBehavior::Impl::rva00576AF3()
{
    ResolveBattleWorldView *world = reinterpret_cast<ResolveBattleWorldView *>(TheLivingWorldLogic);
    if (world && world->regionManager) {
        LivingWorldPendingBattle *battle = world->regionManager->rva0020E6C0();
        if (battle && reinterpret_cast<ResolveBattleResultView *>(battle)->state == 2)
            reinterpret_cast<Rva00575674 *>(reinterpret_cast<char *>(this) + 0x1C)->rva00575674(
                reinterpret_cast<Object *>(new Rva00576591(this)));
    }
}

class Rva00576BDDDispute;
class Rva002B8817 { public: void rva002B8817(void *, void *); };
class Rva005768CBCall { public: void rva005768CB(void *); };

// WB14D0CB0 names this method and its dispute/checklist loop. Retail576BDD
// proves the12-byte pointer vector and receiver+18 filter; original payload
// class identity remains unresolved. The two callees retain their rowed ABI.
void StrategicInGameUI::ResolveBattlesBehavior::Impl::CreateResolveRegionOwnershipChecklistItems()
{
    _STL::vector<Rva00576BDDDispute *> disputes;
    reinterpret_cast<Rva002B8817 *>(TheLivingWorldLogic)->rva002B8817(
        *reinterpret_cast<void **>(reinterpret_cast<char *>(this) + 0x18), &disputes);
    Rva00576BDDDispute **end = disputes.end();
    for (Rva00576BDDDispute **it = disputes.begin(); it != end; ++it)
        reinterpret_cast<Rva005768CBCall *>(this)->rva005768CB(*it);
}

class PendingBattleVisitor {
public:
 virtual bool Visit(LivingWorldPendingBattle *) = 0;
 ~PendingBattleVisitor() {}
};
class Rva0020E7E8Callback { public: virtual bool invoke(void *) = 0; };
class Rva005766B3 : public PendingBattleVisitor {
public:
 Rva005766B3(int,int,int);
 ~Rva005766B3() {}
 virtual bool Visit(LivingWorldPendingBattle *);
private:
 int a,b,c;
};


class LivingWorldBattle { public: bool rva003F48EF(void *); };
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva005D1DCB {
public:
 Rva005D1DCB(void *, LivingWorldPendingBattle *);
 char storage[24];
};
namespace StrategicInGameUI {
struct ChecklistItemRef {
 Rva005D1DCB *m_ptr;
 ChecklistItemRef(Rva005D1DCB *p) : m_ptr(p) { if(p) ++*(int *)((char *)p+4); }
 ~ChecklistItemRef() { if(m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr); }
};
class Checklist { public: void AddItem(const ChecklistItemRef &); };
}
// Native vtable86E7D0 slot0 reaches5766D3; pending/completed enumerators
// invoke it with one battle pointer and inspect AL. WB14CFA70 confirms the
// filtered checklist allocation and counted reference. Fields4/8/C remain
// opaque pointer words, matching the existing constructor ABI.
bool Rva005766B3::Visit(LivingWorldPendingBattle *battle) {
 if(((LivingWorldBattle *)battle)->rva003F48EF((void *)a)) {
  StrategicInGameUI::ChecklistItemRef item(new Rva005D1DCB((void *)c,battle));
  ((StrategicInGameUI::Checklist *)b)->AddItem(item);
 }
 return true;
}

// Native576753..5767A4 and WB14D05B0 construct one16-byte visitor for both
// lists. Slot0 is the rowed callback5766D3; inline nonvirtual cleanup preserves
// the native EH scope without adding the false virtual-destructor call.
// Original helper name and argument types remain unresolved pointer words.
void Rva00576753Func(int a, int b, int c)
{
    LivingWorldRegionManager *manager =
        reinterpret_cast<ResolveBattleWorldView *>(TheLivingWorldLogic)->regionManager;
    Rva005766B3 visitor(a, b, c);
    manager->EnumeratePendingBattles(visitor);
    manager->EnumerateCompletedBattles(reinterpret_cast<Rva0020E7E8Callback *>(&visitor));
}

class Rva002C025AViewer { public: void *rva002C025A(void *, unsigned, bool); };
class Rva00212728 { public: void *rva00212728(void *); };
class Rva00DFE1C8Host;
extern Rva00DFE1C8Host *g_00DFE1C8;
class Rva00328A83PtrChaseField { public: int get() const; };
class Rva0042D6BAPtrChaseField { public: int get() const; };
class Rva0057C22FByteChaseField { public: unsigned char get() const; };
struct Rva002B5C5EVal;
class Rva002B5C5E { public: Rva002B5C5EVal *rva002B5C5E(int); };
class RegionAwardDispute { public: int GetResolvableBy(); };
// The two native owning state holders share the38-byte reset at575674.
// Distinct typed instantiations preserve the native caller's two EH paths;
// each emitted reset is proved byte-and-relocation identical to the owner.
// Slot0 returns the allocation after flags0 destruction. The original class
// identities remain unresolved; these views only express the witnessed ABI.
class ResolveClickState { public: virtual void *deleteInstance(int); };
class Rva0057647E : public ResolveClickState { public: Rva0057647E(void *,LivingWorldPendingBattle *); char data[8]; };
class Rva005765D1 : public ResolveClickState { public: Rva005765D1(void *,int,int); char data[8]; };
template<class T> class ResolveClickHolder { public:
 T *p;
 __declspec(noinline) void reset(T *value) {
  if(value==p) return;
  T *old=p; p=value;
  void *released=old ? old->deleteInstance(0) : 0;
  ::operator delete(released);
 }
};
struct ResolveClickPoint { int x,y; };
struct ResolveClickRegion { int x,y,right,bottom; };
struct ResolveClickUI { void *unknown0; Rva00328A83PtrChaseField *impl; };
struct ResolveClickPlayer { char unknown0[0x14]; int id; };
struct ResolveClickObject { char unknown0[0x10]; void *key; };
struct ResolveClickView {
 char unknown0[0x10]; ResolveClickUI *ui; Rva002C025AViewer *viewer;
 ResolveClickPlayer *player; ResolveClickHolder<Rva0057647E> battle; char unknown20[0x20]; ResolveClickHolder<Rva005765D1> ownership;
};
// Native576946..576ACB and WB14D0EE0 (OnMouseLeftClick) independently show
// the point-pick, battle lookup and dispute-resolution branches. The first
// argument points to a four-int region; the second stack word is unused.
// Original parameter types and return enum are unproven, so retain an
// address-derived method with their observed pointer/word ABI. Point temporaries
// end immediately after picking, allowing retail's subsequent allocation reuse.
int StrategicInGameUI::ResolveBattlesBehavior::Impl::rva00576946(void *regionWord,unsigned unused) {
 ResolveClickRegion *region=(ResolveClickRegion *)regionWord;
 ResolveClickView *state=(ResolveClickView *)this;
 if(region->right-region->x>0 || region->bottom-region->y>0) return 0;
 if(!state->battle.p) {
  ResolveClickObject *object;
  {
   ResolveClickPoint point; point.x=region->x; point.y=region->y;
   object=(ResolveClickObject *)state->viewer->rva002C025A(&point,1,false);
  }
  if(object) {
   int id=(int)((Rva00212728 *)g_00DFE1C8)->rva00212728(object->key);
   if(id>=0) {
    LivingWorldRegionManager *manager=((ResolveBattleWorldView *)TheLivingWorldLogic)->regionManager;
    LivingWorldPendingBattle *battle=manager->rva0020E501(id);
    if(battle) {
     state->battle.reset(new Rva0057647E(this,battle));
     return 1;
    }
   }
  }
 }
 int hud=state->ui->impl->get();
 Rva0057C22FByteChaseField *dialog=(Rva0057C22FByteChaseField *)((Rva0042D6BAPtrChaseField *)hud)->get();
 if(dialog && !dialog->get()) {
  ResolveClickObject *object;
  {
   ResolveClickPoint point; point.x=region->x; point.y=region->y;
   object=(ResolveClickObject *)state->viewer->rva002C025A(&point,2,false);
  }
  if(object) {
   int id=(int)((Rva00212728 *)g_00DFE1C8)->rva00212728(object->key);
   if(id>=0) {
    RegionAwardDispute *dispute=(RegionAwardDispute *)((Rva002B5C5E *)TheLivingWorldLogic)->rva002B5C5E(id);
    if(dispute) {
     int playerId=state->player->id;
     if(dispute->GetResolvableBy()!=playerId) return 0;
     state->ownership.reset(new Rva005765D1(this,(int)dialog,(int)dispute));
     return 1;
    }
   }
  }
 }
 return 0;
}
