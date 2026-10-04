// cl: /O1 /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// "Reload INI file" notifications (slot 4) of nine INI-backed stores, each
// in the vftable of the class its rowed deleting destructor names. When the
// store's slot 2 (the shared 0x001B5384 body) reports a reload, each puts a
// "RIF: ... reloaded" line on screen through TheInGameUI's varargs message
// (its slot 16, cdecl; the UnicodeString argument is built in place):
//
//   FXList (0x001E0DB9) and ObjectCreationList (0x001F04D9) then return
//   true; Armor, PlayerTemplate, Sciences, AttributeModifier, Upgrades and
//   Weapon (0x001D8FAD, 0x001FD57A, 0x001FF625, 0x0021494B, 0x0026F16D,
//   0x002CAE34) latch a static "reloaded" byte (.bss) and return it; GameData
//   (0x0023624A) skips the message without TheInGameUI.
//
// The store names come from the literals; the classes keep their
// address-derived ledger names, and the slot-2 and message meanings are
// inferred from the calls.

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

class RifStore
{
public:
	virtual void v00(); virtual void v01();
	virtual bool rva001B5384Slot2();
};

class Rva001E2AD9 : public RifStore
{
public:
	bool rva001E0DB9(int reason);
};

bool Rva001E2AD9::rva001E0DB9(int reason)
{
	if (rva001B5384Slot2())
	{
		TheInGameUI->message(UnicodeString(L"RIF: FXList reloaded"));
		return true;
	}
	return false;
}

class Rva001F092A : public RifStore
{
public:
	bool rva001F04D9(int reason);
};

bool Rva001F092A::rva001F04D9(int reason)
{
	if (rva001B5384Slot2())
	{
		TheInGameUI->message(UnicodeString(L"RIF: ObjectCreationList reloaded"));
		return true;
	}
	return false;
}

// g_Va00DFDBC8: VA 0x00DFDBC8 (.bss); retail initial byte 00.
bool g_Va00DFDBC8;

class Rva001D92C0 : public RifStore
{
public:
	bool rva001D8FAD(int reason);
};

bool Rva001D92C0::rva001D8FAD(int reason)
{
	if (rva001B5384Slot2())
	{
		TheInGameUI->message(UnicodeString(L"RIF: Armor reloaded"));
		g_Va00DFDBC8 = true;
	}
	return g_Va00DFDBC8;
}

// g_Va00DFE0D4: VA 0x00DFE0D4 (.bss); retail initial byte 00.
bool g_Va00DFE0D4;

class Rva001FDB55 : public RifStore
{
public:
	bool rva001FD57A(int reason);
};

bool Rva001FDB55::rva001FD57A(int reason)
{
	if (rva001B5384Slot2())
	{
		TheInGameUI->message(UnicodeString(L"RIF: PlayerTemplate reloaded"));
		g_Va00DFE0D4 = true;
	}
	return g_Va00DFE0D4;
}

// g_Va00DFE0E4: VA 0x00DFE0E4 (.bss); retail initial byte 00.
bool g_Va00DFE0E4;

class Rva001FF909 : public RifStore
{
public:
	bool rva001FF625(int reason);
};

bool Rva001FF909::rva001FF625(int reason)
{
	if (rva001B5384Slot2())
	{
		TheInGameUI->message(UnicodeString(L"RIF: Sciences reloaded (requires map restart if any were removed)"));
		g_Va00DFE0E4 = true;
	}
	return g_Va00DFE0E4;
}

// g_Va00DFE1D8: VA 0x00DFE1D8 (.bss); retail initial byte 00.
bool g_Va00DFE1D8;

class Rva0022CA95 : public RifStore
{
public:
	bool rva0021494B(int reason);
};

bool Rva0022CA95::rva0021494B(int reason)
{
	if (rva001B5384Slot2())
	{
		TheInGameUI->message(UnicodeString(L"RIF: AttributeModifier reloaded (requires map restart if any entries reordered)"));
		g_Va00DFE1D8 = true;
	}
	return g_Va00DFE1D8;
}

// g_Va00DFEB64: VA 0x00DFEB64 (.bss); retail initial byte 00.
bool g_Va00DFEB64;

class Rva0026F445 : public RifStore
{
public:
	bool rva0026F16D(int reason);
};

bool Rva0026F445::rva0026F16D(int reason)
{
	if (rva001B5384Slot2())
	{
		TheInGameUI->message(UnicodeString(L"RIF: Upgrades reloaded (ALL but the simplest of changes require a map restart)"));
		g_Va00DFEB64 = true;
	}
	return g_Va00DFEB64;
}

// g_Va00DFEFE0: VA 0x00DFEFE0 (.bss); retail initial byte 00.
bool g_Va00DFEFE0;

class Rva002CCD56 : public RifStore
{
public:
	bool rva002CAE34(int reason);
};

bool Rva002CCD56::rva002CAE34(int reason)
{
	if (rva001B5384Slot2())
	{
		TheInGameUI->message(UnicodeString(L"RIF: Weapon reloaded"));
		g_Va00DFEFE0 = true;
	}
	return g_Va00DFEFE0;
}

class Rva002376CC : public RifStore
{
public:
	bool rva0023624A(int reason);
};

bool Rva002376CC::rva0023624A(int reason)
{
	if (rva001B5384Slot2())
	{
		if (TheInGameUI)
			TheInGameUI->message(UnicodeString(L"RIF: GameData reloaded (changes are effective immediately)"));
		return true;
	}
	return false;
}
