// ?CreateChecklistItems@Impl@PlanRetreatsPhaseBehavior@StrategicInGameUI@@QAEXXZ
// partial score=0.99 date=2026-10-08
// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
//
// StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl (WorldBuilder
// StrategicInGameUIPlanRetreatsPhaseBehavior.cpp names its translateGameMessage, callgraph).
// Target facts for 0x005771F4: offers the message to its +0x14 retreat planner (when set, 0x005D1FD3), its ManualPhaseEnder +0x18 and its PlayerStatusDisplayer (0x005CD690) +0x28, consuming it
// (1) when one does, else defers to the base
// UserInputTranslator::translateGameMessage 0x005CBC95 (WorldBuilder name,
// pinned). Member types are the callees' views (inference).

#include <stdlib.h>
namespace _STL { void __cdecl free(void *); }
#define free _STL::free
#include <vector>
#undef free

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

// The retreat planner (rowed address-named, 0x005D1FD3).
class Rva005D1F45
{
public:
	int rva005D1FD3(GameMessage *msg);
};

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

GameMessageDisposition StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl::translateGameMessage(const GameMessage *msg)
{
	if ((m_planner && m_planner->rva005D1FD3((GameMessage *)msg) == 1)
		|| m_phaseEnder.Translate(msg) == DESTROY_MESSAGE
		|| m_statusDisplayer.rva005CD690(msg) == DESTROY_MESSAGE)
		return DESTROY_MESSAGE;
	return UserInputTranslator::translateGameMessage(msg);
}

class ModuleData;
struct Rva002B85ECFilter;
class Rva002BA8F1Logic { public: void rva002B85EC(Rva002B85ECFilter *,_STL::vector<const ModuleData *> *); };
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct RetreatWorldView { char unknown[0x98]; Rva002B85ECFilter *localPlayer; };
class Rva00576FD3 {
public:
 Rva00576FD3(StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl *,const ModuleData *);
 char nativeStorage[28];
};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
namespace StrategicInGameUI {
struct ChecklistItemRef {
 Rva00576FD3 *ptr;
 ChecklistItemRef(Rva00576FD3 *p):ptr(p) { if(p) ++*(int *)((char *)p+4); }
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
  StrategicInGameUI::ChecklistItemRef item(new Rva00576FD3(this,army));
  ((StrategicInGameUI::Checklist *)((char *)this+4))->AddItem(item);
 }
}
