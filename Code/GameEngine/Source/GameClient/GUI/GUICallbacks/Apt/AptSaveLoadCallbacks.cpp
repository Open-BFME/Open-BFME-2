// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// BFME2's save/load screen Apt callbacks, 0x00433DB1 onward, bound by these
// names ("AptSaveLoad::OnClosed" ...) as member pointers by the screen's
// registration; that binding is their only reference. The class is named
// for the strings' prefix. +0x27C is the screen's state.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include <string.h>
#include "unicode_string.h"
#include "ascii_string.h"

#include "../../../../../Include/GameClient/Bfme2GameWindow.h"
class BfmeKeyLC;

void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);
void GadgetTextEntrySetMaxChars(BfmeKeyLC *textEntry, unsigned short maxLength);
void GadgetTextEntrySetValidationFlags(GameWindow *textEntry, int value);

// Rowed callees for 0x00434432 (declared only; definitions live in their rows).
class BfmeObjENK;
void bfmeGoENK(BfmeObjENK *o, char v);

// Rva00433D27Enable.cpp's 0x00433D27.
void Rva00433D27Enable();

// TheShell (VA 0x00E01E48, the ledger's g_Va00A01E48).
struct GlobalA01E48
{
	unsigned char m_pad[0x54];
	bool m_54; // +0x54
	unsigned char m_pad55[0x5D - 0x55];
	bool m_5d; // +0x5D
};

class Shell;
extern Shell *TheShell;

// The pending confirmation at +0x280 keeps its kind at +0x28.
struct AptSaveLoadPending
{
	unsigned char m_pad[0x28];
	int m_kind; // +0x28
};

class GameSpyGameSlot;
#include "../../../../../Include/GameClient/AptSaveLoad.h"

// The 0x00436FF6 else branch loads the singleton at 0x00DFF08C into ECX and
// passes the screen's two list pointers, the +0x294 comparison, and +0x2A0
// to populateSaveGameListbox (rowed in GameStateAutoSave.cpp).
#include "../../../../../Include/Common/GameState.h"
extern GameState *TheGameState;

// TheLivingWorldLogic (Rva003F03C9Fetch.cpp's g_00DFEF10); its rowed
// 0x002B2E77 is called with the logic in ECX, so it is a member.
#include "../../../../../Include/GameLogic/LivingWorldLogic.h"

// TheGameLogic; its rowed 0x0023D30F (rowed as the stdcall
// Rva0023D30FCall) likewise.
#include "../../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

// The save name the multiplayer save prompt keeps (0x00E032E8).
extern unsigned int g_Va00E032E8;

// Retail expands UnicodeString::isEmpty inline as the header test
// (m_data == 0 || m_data->length == 0); the shared shim keeps it out of
// line (as MpGameSetupSlots.cpp notes).
static inline bool unicodeIsEmpty(const UnicodeString &text)
{
	const unsigned char *data = *(const unsigned char *const *)&text;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

// Retail 0x00433D4D, 36 bytes. Name unknown: bound without a name as an
// answer to the "APT:MultiplayerGameSaved" prompt (0x00435090), it hands
// TheLivingWorldLogic 1 for button 2 and 2 for button 3.
void __cdecl Rva00433D4D(int button)
{
	if (!TheLivingWorldLogic)
		return;
	if (button == 2)
		TheLivingWorldLogic->rva002B2E77(1);
	else if (button == 3)
		TheLivingWorldLogic->rva002B2E77(2);
}

// Retail 0x004341D8, 72 bytes. Name unknown: bound without a name as the
// answer to the "APT:SaveGameMultiplayerConfirmationTitle" prompt
// (0x00240BC9). With a game and a kept save name, button 2 passes
// (5, 0, name) and button 3 (2, 2, name) to TheGameLogic's 0x0023D30F; the
// name is then dropped.
void __cdecl Rva004341D8(int button)
{
	UnicodeString &name = *reinterpret_cast<UnicodeString *>(&g_Va00E032E8);
	if (!TheGameLogic || unicodeIsEmpty(name))
		return;
	if (button == 2)
		TheGameLogic->rva0023D30F(5, 0, &name);
	else if (button == 3)
		TheGameLogic->rva0023D30F(2, 2, &name);
	name.clear();
}

// Rva00433FF3.cpp's 0x00433FF3: the first human GameSpy slot; its player's
// name at +0x30 and profile id at +0x1AC.
struct AptSaveLoadSlot
{
	int getProfileID() const { return m_profileID; }

	unsigned char m_pad000[0x30];
	UnicodeString m_name; // +0x30
	unsigned char m_pad034[0x1AC - 0x34];
	int m_profileID; // +0x1AC
};

class GameSpyGameSlot;

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

// Unrowed 0x004178C1 (421 bytes; sends a buddy request for a profile) and
// 0x00434EFA (525 bytes; shows the saved-game prompt), pinned by address.
void __cdecl Rva004178C1(int profileID, const AsciiString &name);
void __cdecl Rva00434EFA();

// Set while the saved-game prompt is up (0x00E032E0).

// Retail 0x00435107, 107 bytes. Named WB12AD800/371 and assertions755/757
// identify AptSaveLoad::AddFriendConfirmationHandler. The complete WB/native
// bodies agree on the static cdecl answer to the "APT:AddFriendOnSaveTitle"
// prompt (0x004355B5/0x0043560D), opponent getter and temporary string cleanup.
// Button 2 asks the first human GameSpy player for friendship; the
// saved-game prompt follows unless it is already up.
void __cdecl AptSaveLoad::AddFriendConfirmationHandler(int button)
{
	if (button == 2)
	{
		AptSaveLoadSlot *slot = (AptSaveLoadSlot *)GetOpponentSlotData();
		if (!slot || !TheGameSpyInfo)
			return;
		Rva004178C1(slot->getProfileID(), AsciiString(slot->m_name));
	}
	if (!AptSaveLoad::s_instance)
		Rva00434EFA();
}

// Retail 0x00433D71, 37 bytes. Name unknown. Keeps the answer to the
// "APT:MultiplayerGameSaved" prompt: button 2 gives 1, button 3 gives 2.
void AptSaveLoad::rva00433D71(int button)
{
	if (button == 2)
		field2A8 = 1;
	else if (button == 3)
		field2A8 = 2;
}

// Retail 0x00433DB1, 47 bytes: "AptSaveLoad::OnClosed" flags the shell
// unless a kind 6 confirmation closed it in state 6.
void AptSaveLoad::OnClosed(const char *unused)
{
	if (TheShell)
	{
		if (field27C != 6 || !field280 || field280->m_kind != 6)
			((GlobalA01E48 *)TheShell)->m_54 = true;
	}
	Rva00433D27Enable();
}

// Retail 0x00433DE0, 17 bytes: "AptSaveLoad::Cancel".
void AptSaveLoad::Cancel(const char *unused)
{
	if (field27C == 0)
		Rva00433D27Enable();
}

// Retail 0x00433DF1, 13 bytes: bound as "AptSaveLoad::OnInitialized",
// "AptSaveLoad::ConfirmationCancel" and "AptOptions::OnInitialized".
void AptSaveLoad::rva00433DF1(const char *unused)
{
	field27C = 1;
}

// Retail 0x00434318, 31 bytes: "AptSaveLoad::Delete".
void AptSaveLoad::Delete(const char *unused)
{
	if (field27C == 0 && rva00433F7F())
		field27C = 16;
}

// Retail 0x004348CA, 76 bytes: "AptSaveLoad::Load" takes the selected
// entry (0x00433F7F) and loads it: state 14 with +0x29C, 0x0043448C in mode
// 4, else state 3.
void AptSaveLoad::Load(const char *unused)
{
	if (field27C == 0)
	{
		field280 = (AptSaveLoadPending *)rva00433F7F();
		if (field29C)
			field27C = 14;
		else if (field2A0 == 4)
			rva0043448C();
		else
			field27C = 3;
	}
}

// Retail 0x004357CF, 74 bytes: "AptSaveLoad::ConfirmationOk" finishes the
// confirmation the state (0x12..0x15) is waiting on.
void AptSaveLoad::ConfirmationOk(const char *unused)
{
	if (field27C == 0x12)
	{
		if (field2A0 == 4)
			rva0043448C();
		else
			field27C = 3;
	}
	else if (field27C == 0x13)
		rva00435224();
	else if (field27C == 0x14)
		rva00434B8A();
	else if (field27C == 0x15)
		rva00433FDD();
}

// Retail 0x00435172, 178 bytes: "AptSaveLoad::InitGadgets" keeps the
// "GameList" and "AutoSaveList" boxes (state 2) and sets up the emptied
// "FileNameTextEntry" (40 characters), then fills the lists.
void AptSaveLoad::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (!window)
		return;
	if (strcmp(name, "GameList") == 0)
	{
		field288 = window;
		field27C = 2;
	}
	else if (strcmp(name, "AutoSaveList") == 0)
	{
		field28C = window;
		field27C = 2;
	}
	else if (strcmp(name, "FileNameTextEntry") == 0)
	{
		field290 = window;
		GadgetTextEntrySetText(window, UnicodeString(L""));
		GadgetTextEntrySetMaxChars((BfmeKeyLC *)window, 40);
		GadgetTextEntrySetValidationFlags(window, 8);
		SetDefaultFileName();
		if (field27C == 0)
			field27C = 1;
	}
}

// ?rva00434432@AptSaveLoad@@QAEXXZ @ 0x00434432 90B: enable the three list boxes then refresh buttons
// Evidence: rowed winEnable 0x00313BEC and bfmeGoENK 0x00324992 on m_gameList +0x288 and m_autoSaveList +0x28C; winEnable on m_fileName +0x290; tail-jmp to rowed 0x004340AC; caller set 0x00435CA8 0x00437072 0x00437031.
void AptSaveLoad::rva00434432()
{
	if (field288)
	{
		field288->winEnable(true);
		bfmeGoENK((BfmeObjENK *)field288, 1);
	}
	if (field28C)
	{
		field28C->winEnable(true);
		bfmeGoENK((BfmeObjENK *)field28C, 1);
	}
	if (field290)
		field290->winEnable(true);
	return rva004340AC();
}

// Retail 0x00436FF6: mode 4 delegates to its screen helper; other modes pass
// the current lists and mode flags to the GameState singleton, then both paths
// tail-call the rowed list/button refresh at 0x00434432.
void AptSaveLoad::rva00436FF6()
{
	if (field2A0 == 4)
		rva0043684C();
	else
		TheGameState->populateSaveGameListbox(
			field288, field28C, field294 == 3, field2A0);

	return rva00434432();
}

// Native434A2F..434AAE complete127B. Same screen290 name entry as the
// owned callbacks; trimmed text presence is forwarded as SaveButtonEnable.
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);
#include "../../../../../../Libraries/Source/Apt/AptPlayerClass.h"
int __cdecl Rva002D4531Invoke(Rva00222A8BTarget *,void *,const char *,const int &);

void AptSaveLoad::rva00434A2F()
{
	UnicodeString text = GadgetTextEntryGetText(field290);
	text.trim();
	int hasText;
	if (unicodeIsEmpty(text))
		hasText = 0;
	else
		hasText = 1;
	// The retained address-derived invoke wrapper uses a void* ABI view of
	// this 32-bit level argument; the query itself returns the proven integer.
	Rva002D4531Invoke(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager), reinterpret_cast<void *>(AptPlayer::GetLevelIndex((GameWindow *)this)),
		"SaveButtonEnable", hasText);
}
