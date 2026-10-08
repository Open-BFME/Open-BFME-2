// cl: /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl (WorldBuilder
// StrategicInGameUIPlanRetreatsPhaseBehavior.cpp names its translateGameMessage, callgraph).
// Target facts for 0x005771F4: offers the message to its +0x14 retreat planner (when set, 0x005D1FD3), its ManualPhaseEnder +0x18 and its PlayerStatusDisplayer (0x005CD690) +0x28, consuming it
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
