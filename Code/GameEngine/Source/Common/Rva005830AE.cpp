// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005830AE@Rva005830AE@@QAEXH@Z @0x005830AE 115B
// Free-standing progress tooltip updater: null-checked slot 0x40 on 0x9FEA28,
// empty-string Mouse tooltip via 0x37050/0x1EEA6D, then slots 0x5C 0x28 0x28 0x28 0x30.
// Evidence: callers 0x0044C629 0x0044C828 pass ecx+1 stack arg ret4; empty at 0xA0C898.

#include "unicode_string.h"


struct RGBColor { float red, green, blue; };

class Mouse {
public:
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);
};

class Dummy24 {
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16(int x);
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
};

extern class NetworkInterface *TheNetwork;
extern Mouse *TheMouse;
extern class GameEngine *TheGameEngine;
extern class GameWindowManager *TheWindowManager;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
extern class Display *TheDisplay;

class Rva005830AE {
public:
	void rva005830AE(int x);
};

void Rva005830AE::rva005830AE(int x)
{
	(void)x;
	if ((*(Dummy24 **)&TheNetwork) != 0)
		(*(Dummy24 **)&TheNetwork)->v16(0);
	TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
	(*(Dummy24 **)&TheGameEngine)->v23();
	(*(Dummy24 **)&TheWindowManager)->v10();
	(*(Dummy24 **)&g_bfmeAptWindowManager)->v10();
	(*(Dummy24 **)&TheDisplay)->v10();
	(*(Dummy24 **)&TheDisplay)->v12();
}

