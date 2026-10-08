// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/stringinline -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
#include "StringInline.h"

// Open-BFME: transition-step function at retail 0x00565170 (96B). Same
// shape family as PreParchmentMapFade_LoadGame.cpp / SoloMordorFade_LoadGame.cpp:
// int f(int, bool start) -- on start, kick a transition group and poke two
// other singletons; on !start, poll isFinished(). Literal at 0x1109E30 is
// "FadeScreenToBlack". Callee 0x00042E6F pins isFinished@GameWindowTransitionsHandler,
// 0x00045C28 is the rowed GameWindowTransitionsHandler::setGroup, 0x0003D578
// the rowed Mouse::_bfme_setEngineVisibility (called on TheMouse), and the
// second TheTransitionHandler call (0x0000F1FF) the rowed
// Rva001DBB82OneSetter::enable (sets a flag byte at +0x55).

class GameWindowTransitionsHandler
{
public:
	bool isFinished();
	void setGroup(AsciiString name, bool immediate);
};

// The flag poke is the rowed Rva001DBB82OneSetter::enable.
class Rva001DBB82OneSetter
{
public:
	void enable();
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class BfmeRankTransitionHandler
{
public:
	void setGroup(AsciiString name, int immediate);
};

struct Rva004893C0ByteSetter
{
	char m_padding[0x55];
	unsigned char m_flag;

	void set();
};

class BfmeZ1100
{
public:
	void bfmeEnd1100(int h);
};
// Retail's singleton at 0x012F4C5C is EA's Mouse *TheMouse; (defined once in
// GameClient/Input/Mouse.cpp).  This TU keeps its own view of the layout and
// casts at the use so the reference links to the one global.
class Mouse
{
public:
	void _bfme_setEngineVisibility(bool visible);
};
extern Mouse *TheMouse;

// ?rva00565170@@YAHH_N@Z
int rva00565170(int, bool start)
{
	int result = 1;

	if (start)
	{
		TheTransitionHandler->setGroup(AsciiString("FadeScreenToBlack"), false);
		((Rva001DBB82OneSetter *)TheTransitionHandler)->enable();
		TheMouse->_bfme_setEngineVisibility(false);
	}
	else if (TheTransitionHandler->isFinished())
	{
		result = 3;
	}

	return result;
}
