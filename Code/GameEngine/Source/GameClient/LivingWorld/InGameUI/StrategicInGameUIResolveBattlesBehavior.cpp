// cl: /O1 /DNDEBUG /MD /EHsc
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
class LivingWorldRegionManager
{
public:
    LivingWorldPendingBattle *rva0020E6C0();
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
