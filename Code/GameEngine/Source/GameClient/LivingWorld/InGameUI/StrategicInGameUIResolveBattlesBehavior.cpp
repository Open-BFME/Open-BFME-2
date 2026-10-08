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
