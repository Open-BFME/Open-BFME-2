// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
#include <stdlib.h>
// Retail576C39 frees through the existing C++-linkage game allocator30830.
// Its throwing declaration retains the native exception-state reset.
namespace _STL { void __cdecl free(void *); }
// Bind before STLport imports ::free into the same namespace.
static __forceinline void releaseDisputeStorage(void *storage)
{
	_STL::free(storage);
}
#include <vector>
class Rva00576BDDDispute;
namespace _STL {
template<> inline void allocator<Rva00576BDDDispute *>::deallocate(Rva00576BDDDispute **__p, size_type) const
{
	if (__p != 0) releaseDisputeStorage((void *)__p);
}
}
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

#include "../../../../../Libraries/Include/Lib/ICoord2D.h"

// WB calls IRegion2D::width/height on the click region; retail inlines both
// (the region.cpp rows 0x00004D4B/0x00004D51 are the out-of-line copies), so
// the extents are spelled out in the handler rather than defining second
// copies of those members.
#include "../../../../../Libraries/Include/Lib/IRegion2D.h"

// The translator base (WB UserInputTranslator.cpp): translateGameMessage in
// slot 0, a deleting dtor in slot 1, then the input handlers, whose
// defaults are the shared stubs 0x005748B2 (slot 2 and slots 18..25) and
// 0x005748AD (slots 3..17). Only the slots this unit needs are named.
#include "../../../../Include/GameClient/UserInputTranslator.h"

// The translators behind the behavior (ManualPhaseEnder.cpp's and
// PlayerStatusDisplayer.cpp's units).
#include "../../../../Include/GameLogic/ManualPhaseEnder.h"
namespace StrategicInGameUI
{
}
#include "../../../../Include/GameClient/PlayerStatusDisplayer.h"
namespace StrategicInGameUI
{
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
 void Update();
 void CreateResolveRegionOwnershipChecklistItems();
 virtual int OnMouseLeftClick(const IRegion2D &region, int modifiers);

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
#include "../../../../Include/GameLogic/LivingWorldRegionManager.h"
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
#include "../../../../Include/Common/Rva00575674.h"
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

#include "../../../../Include/Common/PendingBattleVisitor.h"
#include "../../../../Include/GameClient/Rva0020E7E8Callback.h"
class Rva005766B3 : public PendingBattleVisitor {
public:
 Rva005766B3(int,int,int);
 ~Rva005766B3() {}
 virtual bool Visit(LivingWorldPendingBattle *);
private:
 int a,b,c;
};


struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
namespace StrategicInGameUI {
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

class Rva00DFE1C8Host;
// g_00DFE1C8 is only an alias of the owned global TheLivingWorldManager (ledger names column); this unit reads the owner through its own view type.
extern class LivingWorldManager *TheLivingWorldManager;
#define g_00DFE1C8 (*(Rva00DFE1C8Host * *)&TheLivingWorldManager)
struct Rva002B5C5EVal;
// The two native owning state holders share the38-byte reset at575674.
// Distinct typed instantiations preserve the native caller's two EH paths;
// each emitted reset is proved byte-and-relocation identical to the owner.
// Slot0 returns the allocation after flags0 destruction. The original class
// identities remain unresolved; these views only express the witnessed ABI.
template<class T> class ResolveClickHolder { public:
 T *p;
 __declspec(noinline) void reset(T *value) {
  if(value==p) return;
  T *old=p; p=value;
  void *released=old ? old->deleteInstance(0) : 0;
  ::operator delete(released);
 }
};
class Rva0057539C { public: void rva0057539C(); };
