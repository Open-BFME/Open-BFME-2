// cl: /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::CommonBehavior::Impl (WorldBuilder
// StrategicInGameUICommonBehavior.cpp names its translateGameMessage, align).
// Target facts for 0x00574910: offers the message to its +0x5C member (0x005CC26E), its +0x54 sub-translator (when set, vslot 2) and its +0x28 member (0x005C9BE3), consuming it
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

// The translators behind the behavior (ManualPhaseEnder.cpp's units).
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

// A nullable sub-translator viewed by slot: vslot 2 translates.
class Rva00574910SubTranslator
{
public:
	virtual void vslot0();
	virtual void vslot1();
	virtual GameMessageDisposition Translate(const GameMessage *msg);
};

// The +0x5C and +0x28 members' translate methods (0x005CC26E rowed and
// 0x005C9BE3 pinned, both address-named).
class Rva005CC26E
{
public:
	int rva005CC26E(void *msg);
};
class Rva005C9BE3
{
public:
	GameMessageDisposition Translate(const GameMessage *msg);
};

namespace StrategicInGameUI
{
class CommonBehavior
{
public:
	class Impl;
};
}

class StrategicInGameUI::CommonBehavior::Impl : public UserInputTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);

private:
	char m_pad04[0x28 - 0x04];
	Rva005C9BE3 m_translator28; // +0x28
	char m_pad29[0x54 - 0x29];
	Rva00574910SubTranslator *m_sub; // +0x54
	char m_pad58[0x5C - 0x58];
	Rva005CC26E m_translator5C; // +0x5C
};

GameMessageDisposition StrategicInGameUI::CommonBehavior::Impl::translateGameMessage(const GameMessage *msg)
{
	Rva00574910SubTranslator *sub;
	if (m_translator5C.rva005CC26E((void *)msg) == 1)
		return DESTROY_MESSAGE;
	if ((sub = m_sub) != 0 && sub->Translate(msg) == DESTROY_MESSAGE)
		return DESTROY_MESSAGE;
	if (m_translator28.Translate(msg) == DESTROY_MESSAGE)
		return DESTROY_MESSAGE;
	return UserInputTranslator::translateGameMessage(msg);
}
