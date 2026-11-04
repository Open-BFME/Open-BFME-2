// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// "Reload INI file" notifications (slot 4) of ten INI-backed stores, each
// in the vftable of the class its rowed deleting destructor names. When the
// store's slot 2 (the shared 0x001B5384 body) reports a reload, each puts a
// "RIF: ... reloaded" line on screen through TheInGameUI's varargs message
// (its slot 16, cdecl; the UnicodeString argument is built in place):
//
//   FXList (0x001E0DB9) and ObjectCreationList (0x001F04D9) then return
//   true; Armor, PlayerTemplate, Sciences, AttributeModifier, Upgrades,
//   Weapon and Emotions (0x001D8FAD, 0x001FD57A, 0x001FF625, 0x0021494B,
//   0x0026F16D, 0x002CAE34, 0x004263CA) latch a static "reloaded" byte
//   (.bss/.data) and return it; GameData
//   (0x0023624A) skips the message without TheInGameUI.
//
// The store names come from the literals. WorldBuilder names slot 4
// UpgradeCenter::attemptReload (Upgrade.cpp:667) and slot 5
// PlayerTemplateStore::attemptRefresh (PlayerTemplate.cpp:500), so those two
// stores carry their real names and both slots; the other classes keep their
// address-derived ledger names, and the slot-2 and message meanings are
// inferred from the calls. The ten bodies above never touch their stack
// argument (typed int here; the banked Locomotor slot 4 0x001E51AC writes a
// "needs restart" Bool through it). The Weapon store's slot 5 (0x002CAE6C)
// reports "RIF: Weapons reloaded" once after a reload latched its byte,
// clearing it. Slot 5 of Sciences, AttributeModifier and Upgrades
// (0x001FF354, 0x002146E1, 0x0026EF1E) only consume the latch (clear it and
// answer whether it was set); PlayerTemplate's (0x001FD5B2) also tells the
// player to restart and appends message 0x70 to MessageStreamSubsystem (its
// slot 18). The message type's meaning is not recovered.

#include "unicode_string.h"

class GameMessage;

#include "../../Include/Common/MessageStream.h"
extern class MessageStream *TheMessageStream;	// VA 0x00E00950

#include "../../Include/GameClient/InGameUI.h"
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
		TheInGameUI->rva0029E846(UnicodeString(L"RIF: FXList reloaded"));
		return true;
	}
	return false;
}

class ObjectCreationListStore : public RifStore
{
public:
	virtual bool rva001F04D9(int reason);
};

bool ObjectCreationListStore::rva001F04D9(int reason)
{
	if (rva001B5384Slot2())
	{
		TheInGameUI->rva0029E846(UnicodeString(L"RIF: ObjectCreationList reloaded"));
		return true;
	}
	return false;
}

// Armor's notice (0x001D8FAD) lives in GameLogic/Object/ArmorStoreReload.cpp
// with the store's slot 5 (0x001D93CE), which shares its file-static latch.

// g_Va00DFE0D4: VA 0x00DFE0D4 (.bss); retail initial byte 00.
bool g_Va00DFE0D4;

class PlayerTemplateStore : public RifStore
{
public:
	virtual bool attemptRefresh();
	virtual bool attemptReload(int reason);
};

bool PlayerTemplateStore::attemptReload(int reason)
{
	if (rva001B5384Slot2())
	{
		TheInGameUI->rva0029E846(UnicodeString(L"RIF: PlayerTemplate reloaded"));
		g_Va00DFE0D4 = true;
	}
	return g_Va00DFE0D4;
}

// g_Va00DFE0E4: VA 0x00DFE0E4 (.bss); retail initial byte 00.
bool g_Va00DFE0E4;

class Rva001FF909 : public RifStore
{
public:
	bool rva001FF354();
	bool rva001FF625(int reason);
};

bool Rva001FF909::rva001FF625(int reason)
{
	if (rva001B5384Slot2())
	{
		TheInGameUI->rva0029E846(UnicodeString(L"RIF: Sciences reloaded (requires map restart if any were removed)"));
		g_Va00DFE0E4 = true;
	}
	return g_Va00DFE0E4;
}

// g_Va00DFE1D8: VA 0x00DFE1D8 (.bss); retail initial byte 00.
bool g_Va00DFE1D8;

class Rva0022CA95 : public RifStore
{
public:
	virtual bool rva002146E1();
	virtual bool rva0021494B(int reason);
};

bool Rva0022CA95::rva0021494B(int reason)
{
	if (rva001B5384Slot2())
	{
		TheInGameUI->rva0029E846(UnicodeString(L"RIF: AttributeModifier reloaded (requires map restart if any entries reordered)"));
		g_Va00DFE1D8 = true;
	}
	return g_Va00DFE1D8;
}

// g_Va00DFEB64: VA 0x00DFEB64 (.bss); retail initial byte 00.
bool g_Va00DFEB64;

class UpgradeCenter : public RifStore
{
public:
	virtual bool attemptRefresh();
	virtual bool attemptReload(int reason);
};

bool UpgradeCenter::attemptReload(int reason)
{
	if (rva001B5384Slot2())
	{
		TheInGameUI->rva0029E846(UnicodeString(L"RIF: Upgrades reloaded (ALL but the simplest of changes require a map restart)"));
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
	bool rva002CAE6C();
};

bool Rva002CCD56::rva002CAE34(int reason)
{
	if (rva001B5384Slot2())
	{
		TheInGameUI->rva0029E846(UnicodeString(L"RIF: Weapon reloaded"));
		g_Va00DFEFE0 = true;
	}
	return g_Va00DFEFE0;
}

bool Rva002CCD56::rva002CAE6C()
{
	if (g_Va00DFEFE0)
	{
		TheInGameUI->rva0029E846(UnicodeString(L"RIF: Weapons reloaded"));
		g_Va00DFEFE0 = false;
		return true;
	}
	return false;
}

bool Rva001FF909::rva001FF354()
{
	if (g_Va00DFE0E4)
	{
		g_Va00DFE0E4 = false;
		return true;
	}
	return false;
}

bool Rva0022CA95::rva002146E1()
{
	if (g_Va00DFE1D8)
	{
		g_Va00DFE1D8 = false;
		return true;
	}
	return false;
}

bool UpgradeCenter::attemptRefresh()
{
	if (g_Va00DFEB64)
	{
		g_Va00DFEB64 = false;
		return true;
	}
	return false;
}

bool PlayerTemplateStore::attemptRefresh()
{
	if (g_Va00DFE0D4)
	{
		TheInGameUI->rva0029E846(UnicodeString(L"Reloaded PlayerTemplates require a map RESTART."));
		TheInGameUI->rva0029E846(UnicodeString(L"Use the Pause menu to RESTART at any time.."));
		TheMessageStream->appendMessage(0x70);
		g_Va00DFE0D4 = false;
		return true;
	}
	return false;
}

// g_rva00426378Pending: VA 0x00E031E0 (retail .data tail init 00, zero-filled); retail latch for Emotions slot-4.
// Explicit =false documents retail init; MSVC 7.1 still emits all 7 latches in .bss
// (objdump sec 3, 7 bytes); DIR32 consistent, patcher copies retail slot, code unaffected.
bool g_rva00426378Pending = false;

class Rva004263CA : public RifStore
{
public:
	bool rva004263CA(int reason);
};

// ?rva004263CA@Rva004263CA@@QAE_NH@Z @0x004263CA 56B.
// 10th RIF slot-4 reload notice (Emotions store by RIF literal
// L"RIF: Emotions reloaded" at VA 0xC3C320). Same family as 9 matched rows
// in this TU. Address-derived owner/name only; exact bytes do not prove
// store class. Reuses target literal, provider StringBase G ctor 0x37E30,
// TheInGameUI message slot16, RifStore slot2, latch bool VA 0xE031E0,
// canonical types/flags/source provenance of this TU.
bool Rva004263CA::rva004263CA(int reason)
{
	if (rva001B5384Slot2())
	{
		g_rva00426378Pending = true;
		TheInGameUI->rva0029E846(UnicodeString(L"RIF: Emotions reloaded"));
	}
	return g_rva00426378Pending;
}
