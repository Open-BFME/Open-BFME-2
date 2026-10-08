// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?Rva0044C205Reset@@YAXXZ @0x0044C205 114B.
// Reset UI: Network slot 0x40 with 0, Mouse tooltip EmptyString -1 0 1.0f,
// GameEngine slot 0x5C, WindowManager slot 0x28, RvaTarget slot 0x28,
// Display slot 0x28 then tail Display slot 0x30. Evidence: caller at
// 0x0044C28E, callees Network 0x40 Mouse 0x1EEA6D StringBase copy 0x37050
// GameEngine 0x5C WindowManager 0x28 RvaTarget 0x28 Display 0x28/0x30,
// globals TheNetwork TheMouse TheGameEngine TheWindowManager
// TheRva00222A8BTarget TheDisplay UnicodeString::TheEmptyString.
#include "unicode_string.h"

class NetworkInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40(int x) = 0;
};
extern NetworkInterface *TheNetwork;

struct RGBColor
{
	float red;
	float green;
	float blue;
};
class Mouse
{
public:
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);
};
extern Mouse *TheMouse;

class GameEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5c() = 0;
};
extern GameEngine *TheGameEngine;

class GameWindowManager
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
};
extern GameWindowManager *TheWindowManager;

class Rva00222A8BTarget
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

class Display
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
};
extern Display *TheDisplay;

void Rva0044C205Reset()
{
	if (TheNetwork)
		TheNetwork->slot40(0);
	TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
	TheGameEngine->slot5c();
	TheWindowManager->slot28();
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->slot28();
	TheDisplay->slot28();
	TheDisplay->slot30();
}
