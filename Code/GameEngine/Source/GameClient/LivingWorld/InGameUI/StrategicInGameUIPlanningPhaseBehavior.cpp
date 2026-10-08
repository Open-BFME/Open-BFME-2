// cl: /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::PlanningPhaseBehavior::Impl (WorldBuilder
// StrategicInGameUIPlanningPhaseBehavior.cpp names its translateGameMessage, vtable match).
// Target facts for 0x00575C15: offers the message to its +0x28 sub-translator (when set, vslot 2), its ManualPhaseEnder +0x30 and its PlayerStatusDisplayer (0x005CD690) +0x40, consuming it
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

// A nullable sub-translator viewed by slot: vslot 2 translates.
class Rva00575C15SubTranslator
{
public:
	virtual void vslot0();
	virtual void vslot1();
	virtual GameMessageDisposition Translate(const GameMessage *msg);
};

namespace StrategicInGameUI
{
class PlanningPhaseBehavior
{
public:
	class Impl;
};
}

class StrategicInGameUI::PlanningPhaseBehavior::Impl : public UserInputTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);

private:
	char m_pad04[0x28 - 0x04];
	Rva00575C15SubTranslator *m_sub; // +0x28
	char m_pad2C[0x30 - 0x2C];
	StrategicInGameUI::ManualPhaseEnder m_phaseEnder; // +0x30
	StrategicInGameUI::PlayerStatusDisplayer m_statusDisplayer; // +0x40
};

GameMessageDisposition StrategicInGameUI::PlanningPhaseBehavior::Impl::translateGameMessage(const GameMessage *msg)
{
	Rva00575C15SubTranslator *sub;
	if (((sub = m_sub) != 0 && sub->Translate(msg) == DESTROY_MESSAGE)
		|| m_phaseEnder.Translate(msg) == DESTROY_MESSAGE
		|| m_statusDisplayer.rva005CD690(msg) == DESTROY_MESSAGE)
		return DESTROY_MESSAGE;
	return UserInputTranslator::translateGameMessage(msg);
}
