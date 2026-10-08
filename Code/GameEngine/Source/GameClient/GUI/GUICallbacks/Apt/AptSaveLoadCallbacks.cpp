// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// BFME2's save/load screen Apt callbacks, 0x00433DB1 onward, bound by these
// names ("AptSaveLoad::OnClosed" ...) as member pointers by the screen's
// registration; that binding is their only reference. The class is named
// for the strings' prefix. +0x27C is the screen's state.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "unicode_string.h"
#include "ascii_string.h"

extern "C" int __cdecl strcmp(const char *left, const char *right);

class GameWindow
{
public:
	int winEnable(bool enable);
};
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

extern struct GlobalA01E48 *g_Va00A01E48;

// The pending confirmation at +0x280 keeps its kind at +0x28.
struct AptSaveLoadPending
{
	unsigned char m_pad[0x28];
	int m_kind; // +0x28
};

class AptSaveLoad
{
public:
	void OnClosed(const char *unused);
	void Cancel(const char *unused);
	// Bound as "AptSaveLoad::OnInitialized" and
	// "AptSaveLoad::ConfirmationCancel" (and by the options screen as
	// "AptOptions::OnInitialized"): one body or several folded, so it keeps
	// its address.
	void rva00433DF1(const char *unused);
	// Bound without a name as the saved-game prompt's answer (0x00434EFA),
	// so it keeps its address.
	void rva00433D71(int button);
	void Delete(const char *unused);
	void Load(const char *unused);
	void ConfirmationOk(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);

	// Unrowed 0x00434AAE (220 bytes; fills the lists), pinned by address.
	void SetDefaultFileName();

	// Unrowed 0x0043448C, 0x00435224 and 0x00434B8A, pinned by address.
	void rva0043448C();
	void rva00435224();
	void rva00434B8A();

	// Unrowed 0x00433F7F (94 bytes; banked), pinned by address.
	int rva00433F7F();

	// Rowed 0x004340AC (Rva004340ACMethod.cpp's view of this screen).
	void rva004340AC();

	// 0x00434432 (90 bytes; chain from 0x004340AC).
	void rva00434432();
	// Ghidra 0x00436FF6 tail-calls the rowed 0x00434432 refresh.
	void rva00436FF6();
	// The 0x00436FF6 mode-4 branch calls this with ECX=this.
	void rva0043684C();

private:
	unsigned char m_pad000[0x27C];
	int m_state; // +0x27C
	AptSaveLoadPending *m_pending; // +0x280
	unsigned char m_pad284[0x288 - 0x284];
	GameWindow *m_gameList; // +0x288
	GameWindow *m_autoSaveList; // +0x28C
	GameWindow *m_fileName; // +0x290
	int m_294; // +0x294; compared with 3 at 0x00436FF6
	unsigned char m_pad298[0x29C - 0x298];
	bool m_29c; // +0x29C
	unsigned char m_pad29d[0x2A0 - 0x29D];
	int m_mode; // +0x2A0
	unsigned char m_pad2a4[0x2A8 - 0x2A4];
	int m_2a8; // +0x2A8
};

// The 0x00436FF6 else branch loads the singleton at 0x00DFF08C into ECX and
// passes the screen's two list pointers, the +0x294 comparison, and +0x2A0.
// This address-derived method view preserves its observed target ABI.
class GameState
{
public:
	void rva002DF3B0(GameWindow *gameList, GameWindow *autoSaveList,
		bool selected, int mode);
};
extern GameState *TheGameState;

// The rowed 0x00433FDD (Rva00433FDDSet.cpp's view of this screen).
class Rva00433FDD
{
public:
	void rva00433FDD();
};

// TheLivingWorldLogic (Rva003F03C9Fetch.cpp's g_00DFEF10); its rowed
// 0x002B2E77 (rowed as the stdcall Rva002B2E77Append) is called with the
// logic in ECX, so it is declared as a member and pinned under that name.
class RvaLogicHolder
{
public:
	void rva002B2E77(int value);
};

// TheGameLogic; its rowed 0x0023D30F (rowed as the stdcall
// Rva0023D30FCall) likewise.
class GameLogic
{
public:
	void rva0023D30F(int a, int b, UnicodeString *name);
};

extern GameLogic *TheGameLogic;

// The save name the multiplayer save prompt keeps (0x00E032E8).
extern UnicodeString g_Va00E032E8;

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
	if (!(*(RvaLogicHolder **)&TheLivingWorldLogic))
		return;
	if (button == 2)
		(*(RvaLogicHolder **)&TheLivingWorldLogic)->rva002B2E77(1);
	else if (button == 3)
		(*(RvaLogicHolder **)&TheLivingWorldLogic)->rva002B2E77(2);
}

// Retail 0x004341D8, 72 bytes. Name unknown: bound without a name as the
// answer to the "APT:SaveGameMultiplayerConfirmationTitle" prompt
// (0x00240BC9). With a game and a kept save name, button 2 passes
// (5, 0, name) and button 3 (2, 2, name) to TheGameLogic's 0x0023D30F; the
// name is then dropped.
void __cdecl Rva004341D8(int button)
{
	if (!TheGameLogic || unicodeIsEmpty(g_Va00E032E8))
		return;
	if (button == 2)
		TheGameLogic->rva0023D30F(5, 0, &g_Va00E032E8);
	else if (button == 3)
		TheGameLogic->rva0023D30F(2, 2, &g_Va00E032E8);
	g_Va00E032E8.clear();
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
GameSpyGameSlot *Rva00433FF3Get();

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

// Unrowed 0x004178C1 (421 bytes; sends a buddy request for a profile) and
// 0x00434EFA (525 bytes; shows the saved-game prompt), pinned by address.
void __cdecl Rva004178C1(int profileID, const AsciiString &name);
void __cdecl Rva00434EFA();

// Set while the saved-game prompt is up (0x00E032E0).
extern int g_Va00E032E0;

// Retail 0x00435107, 107 bytes. Name unknown: bound without a name as the
// answer to the "APT:AddFriendOnSaveTitle" prompt (0x004355B5/0x0043560D).
// Button 2 asks the first human GameSpy player for friendship; the
// saved-game prompt follows unless it is already up.
void __cdecl Rva00435107(int button)
{
	if (button == 2)
	{
		AptSaveLoadSlot *slot = (AptSaveLoadSlot *)Rva00433FF3Get();
		if (!slot || !TheGameSpyInfo)
			return;
		Rva004178C1(slot->getProfileID(), AsciiString(slot->m_name));
	}
	if (!g_Va00E032E0)
		Rva00434EFA();
}

// Retail 0x00433D71, 37 bytes. Name unknown. Keeps the answer to the
// "APT:MultiplayerGameSaved" prompt: button 2 gives 1, button 3 gives 2.
void AptSaveLoad::rva00433D71(int button)
{
	if (button == 2)
		m_2a8 = 1;
	else if (button == 3)
		m_2a8 = 2;
}

// Retail 0x00433DB1, 47 bytes: "AptSaveLoad::OnClosed" flags the shell
// unless a kind 6 confirmation closed it in state 6.
void AptSaveLoad::OnClosed(const char *unused)
{
	if (g_Va00A01E48)
	{
		if (m_state != 6 || !m_pending || m_pending->m_kind != 6)
			g_Va00A01E48->m_54 = true;
	}
	Rva00433D27Enable();
}

// Retail 0x00433DE0, 17 bytes: "AptSaveLoad::Cancel".
void AptSaveLoad::Cancel(const char *unused)
{
	if (m_state == 0)
		Rva00433D27Enable();
}

// Retail 0x00433DF1, 13 bytes: bound as "AptSaveLoad::OnInitialized",
// "AptSaveLoad::ConfirmationCancel" and "AptOptions::OnInitialized".
void AptSaveLoad::rva00433DF1(const char *unused)
{
	m_state = 1;
}

// Retail 0x00434318, 31 bytes: "AptSaveLoad::Delete".
void AptSaveLoad::Delete(const char *unused)
{
	if (m_state == 0 && rva00433F7F())
		m_state = 16;
}

// Retail 0x004348CA, 76 bytes: "AptSaveLoad::Load" takes the selected
// entry (0x00433F7F) and loads it: state 14 with +0x29C, 0x0043448C in mode
// 4, else state 3.
void AptSaveLoad::Load(const char *unused)
{
	if (m_state == 0)
	{
		m_pending = (AptSaveLoadPending *)rva00433F7F();
		if (m_29c)
			m_state = 14;
		else if (m_mode == 4)
			rva0043448C();
		else
			m_state = 3;
	}
}

// Retail 0x004357CF, 74 bytes: "AptSaveLoad::ConfirmationOk" finishes the
// confirmation the state (0x12..0x15) is waiting on.
void AptSaveLoad::ConfirmationOk(const char *unused)
{
	if (m_state == 0x12)
	{
		if (m_mode == 4)
			rva0043448C();
		else
			m_state = 3;
	}
	else if (m_state == 0x13)
		rva00435224();
	else if (m_state == 0x14)
		rva00434B8A();
	else if (m_state == 0x15)
		((Rva00433FDD *)this)->rva00433FDD();
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
		m_gameList = window;
		m_state = 2;
	}
	else if (strcmp(name, "AutoSaveList") == 0)
	{
		m_autoSaveList = window;
		m_state = 2;
	}
	else if (strcmp(name, "FileNameTextEntry") == 0)
	{
		m_fileName = window;
		GadgetTextEntrySetText(window, UnicodeString(L""));
		GadgetTextEntrySetMaxChars((BfmeKeyLC *)window, 40);
		GadgetTextEntrySetValidationFlags(window, 8);
		SetDefaultFileName();
		if (m_state == 0)
			m_state = 1;
	}
}

// ?rva00434432@AptSaveLoad@@QAEXXZ @ 0x00434432 90B: enable the three list boxes then refresh buttons
// Evidence: rowed winEnable 0x00313BEC and bfmeGoENK 0x00324992 on m_gameList +0x288 and m_autoSaveList +0x28C; winEnable on m_fileName +0x290; tail-jmp to rowed 0x004340AC; caller set 0x00435CA8 0x00437072 0x00437031.
void AptSaveLoad::rva00434432()
{
	if (m_gameList)
	{
		m_gameList->winEnable(true);
		bfmeGoENK((BfmeObjENK *)m_gameList, 1);
	}
	if (m_autoSaveList)
	{
		m_autoSaveList->winEnable(true);
		bfmeGoENK((BfmeObjENK *)m_autoSaveList, 1);
	}
	if (m_fileName)
		m_fileName->winEnable(true);
	return rva004340AC();
}

// Retail 0x00436FF6: mode 4 delegates to its screen helper; other modes pass
// the current lists and mode flags to the GameState singleton, then both paths
// tail-call the rowed list/button refresh at 0x00434432.
void AptSaveLoad::rva00436FF6()
{
	if (m_mode == 4)
		rva0043684C();
	else
		TheGameState->rva002DF3B0(
			m_gameList, m_autoSaveList, m_294 == 3, m_mode);

	return rva00434432();
}
