// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// cl: /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
//
// StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl (WorldBuilder
// StrategicInGameUIPlanRetreatsPhaseBehavior.cpp names its translateGameMessage, callgraph).
// Target facts for 0x005771F4: offers the message to its +0x14 retreat planner (when set, 0x005D1FD3), its ManualPhaseEnder +0x18 and its PlayerStatusDisplayer (0x005CD690) +0x28, consuming it
// (1) when one does, else defers to the base
// UserInputTranslator::translateGameMessage 0x005CBC95 (WorldBuilder name,
// pinned). Member types are the callees' views (inference).

#include <stdlib.h>
#include <vector>

enum GameMessageDisposition
{
	KEEP_MESSAGE,
	DESTROY_MESSAGE
};

class GameMessage;

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

// The retreat planner (rowed address-named, 0x005D1FD3).
#include "../../../../Include/Common/Rva005D1F45.h"

namespace StrategicInGameUI
{
class PlanRetreatsPhaseBehavior
{
public:
	class Impl;
};
}

class StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl : public UserInputTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	void CreateChecklistItems();

private:
	char m_pad04[0x14 - 0x04];
	Rva005D1F45 *m_planner; // +0x14
	StrategicInGameUI::ManualPhaseEnder m_phaseEnder; // +0x18
	StrategicInGameUI::PlayerStatusDisplayer m_statusDisplayer; // +0x28
};


class ModuleData;
struct Rva002B85ECFilter;
#include "../../../../Include/GameLogic/Rva002BA8F1Logic.h"
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct RetreatWorldView { char unknown[0x98]; Rva002B85ECFilter *localPlayer; };
class Rva005770F2 {
public:
 Rva005770F2(StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl *,const ModuleData *);
 char nativeStorage[28];
};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
namespace StrategicInGameUI {
struct ChecklistItemRef {
 Rva005770F2 *ptr;
 ChecklistItemRef(Rva005770F2 *p):ptr(p) { if(p) ++*(int *)((char *)p+4); }
 ~ChecklistItemRef() { if(ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)ptr); }
};
class Checklist { public: void AddItem(const ChecklistItemRef &); };
}
void StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl::CreateChecklistItems() {
 Rva002B85ECFilter *player=((RetreatWorldView *)TheLivingWorldLogic)->localPlayer;
 _STL::vector<const ModuleData *> armies;
 ((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B85EC(player,&armies);
 const ModuleData **end=armies.end();
 for(const ModuleData **it=armies.begin();it!=end;++it) {
  const ModuleData *army=*it;
  StrategicInGameUI::ChecklistItemRef item(new Rva005770F2(this,army));
  ((StrategicInGameUI::Checklist *)((char *)this+4))->AddItem(item);
 }
}
