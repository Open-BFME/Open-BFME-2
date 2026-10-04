// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
#include "../../../Include/GameClient/BfmeAptScreenBaseLayout.h"

class Rva005211D1
{
public:
	~Rva005211D1();
};

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	BfmeAptScreenBaseLayout<> m_primaryStorage;
};

class BfmeAptFunctorMarker
{
public:
	virtual void marker() = 0;
};

extern int g_Va00E0492C;

class __multiple_inheritance Rva00521206
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	virtual ~Rva00521206();
private:
	char m_pad[0x27C - 0x21C];
	Rva005211D1 m_27C;
};

// ??1Rva00521206@@UAE@XZ @0x00521206 79B: Apt-screen dtor clearing global then member at +0x27C then base. Evidence: stores vtables 0x00867720/+0x218 0x0086771C; calls rowed 0x005211D1 and pin-only AptGameWindow 0x005126F5; caller 0x005212E0 deleting dtor; unlocks 0x005212E0.
Rva00521206::~Rva00521206()
{
	g_Va00E0492C = 0;
}
