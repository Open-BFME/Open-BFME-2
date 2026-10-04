// cl: /O1 /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// INI reload slots of the Locomotor store (vftable 0x00BDE970, class
// Rva001E72B4):
//
//   slot 4, 0x001E51AC  clear the "needs restart" byte; when the shared
//                       slot 2 (0x001B5384) reports a reload, put "RIF:
//                       Locomotor reloaded" on screen through TheInGameUI
//                       (slot 16, cdecl; skipped without TheInGameUI) and
//                       latch the "reloaded" byte; pass a pending restart out
//                       through the argument, clearing it; answer the latch.
//   slot 5, 0x001E3934  once after a reload latched its byte: run
//                       0x002CF1C9 on TheThingFactory, clear the latch and
//                       answer true.
//
// Both bytes (VA 0x00DFDC60 "reloaded", 0x00DFDC61 "needs restart") are
// file-static: slot 4 loads the vptr before it stores the restart byte,
// which MSVC 7.1 schedules that way only for a static it can prove `this`
// does not alias. Their only other user (around 0x001E8B6A) sits in the same
// address range. Names are address-derived; the byte meanings are inferred
// from their uses.

#include "unicode_string.h"

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void message(UnicodeString format, ...);
};
extern InGameUI *TheInGameUI;	// VA 0x00DFEDF0

class Rva002CF1C9
{
public:
	void rva002CF1C9();
};

// View: only the 0x002CF1C9 member is called here.
class ThingFactory : public Rva002CF1C9
{
};
extern ThingFactory *TheThingFactory;	// VA 0x00DFF000

// g_Va00DFDC60: VA 0x00DFDC60 (.bss); retail initial byte 00.
static bool g_Va00DFDC60;
// g_Va00DFDC61: VA 0x00DFDC61 (.bss); retail initial byte 00.
static bool g_Va00DFDC61;

class Rva001E72B4Base
{
public:
	virtual void v00();
	virtual void v01();
	virtual bool rva001B5384Slot2();
};

class Rva001E72B4 : public Rva001E72B4Base
{
public:
	bool rva001E51AC(bool *needsRestart);
	bool rva001E3934();
};

bool Rva001E72B4::rva001E51AC(bool *needsRestart)
{
	g_Va00DFDC61 = false;
	if (rva001B5384Slot2())
	{
		if (TheInGameUI)
			TheInGameUI->message(UnicodeString(L"RIF: Locomotor reloaded"));
		g_Va00DFDC60 = true;
	}
	if (g_Va00DFDC61)
	{
		*needsRestart = true;
		g_Va00DFDC61 = false;
	}
	return g_Va00DFDC60;
}

bool Rva001E72B4::rva001E3934()
{
	if (g_Va00DFDC60)
	{
		TheThingFactory->rva002CF1C9();
		g_Va00DFDC60 = false;
		return true;
	}
	return false;
}
