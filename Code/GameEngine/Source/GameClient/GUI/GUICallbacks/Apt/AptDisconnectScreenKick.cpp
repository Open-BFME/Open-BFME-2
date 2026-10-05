// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// BFME2's disconnect screen Apt callbacks "AptDisconnectScreen::Kick"
// (0x00512D55; votes to kick the player in the given slot),
// "DisconnectScreen::InitGadgets" (0x0051321A), "AptDisconnectScreen::Quit"
// (0x005132D2) and "AptDisconnectScreen::Chat::OnBttnEnterText"
// (0x00513382), bound by those names as member pointers by the screen's
// registration; that binding is their only reference.

#include "unicode_string.h"

extern "C" int __cdecl strcmp(const char *left, const char *right);

class GameWindow;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);
UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);
void GadgetListBoxReset(GameWindow *listBox);
void BfmeGadgetListBoxSetAudioFeedback(GameWindow *listBox, bool enable);
int GadgetListBoxAddEntryText(GameWindow *listBox, UnicodeString text, int color, int row, int column, bool overwrite);

extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);

// Rva0066B3E0Adj.cpp's slot translation (0x004D39F0).
int rva0066b3e0(int slot, int localSlot);

class LanguageFilter
{
public:
	void filterLine(UnicodeString &line);
};

extern LanguageFilter *TheLanguageFilter;

// Zero Hour's TheNetwork: vslot 46 is the local slot, vslot 47 a slot's
// player name, vslot 38 votes, vslot 37 quits, vslot 65 tells whether a
// slot is connected and vslot 27 sends disconnect chat.
class NetworkInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26();
	virtual void v27(UnicodeString text);
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38(int slot);
	virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42();
	virtual void v43(); virtual void v44(); virtual void v45();
	virtual int v46();
	virtual UnicodeString v47(int slot);
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64();
	virtual bool v65(int slot);
};

extern NetworkInterface *TheNetwork;

class AptDisconnectScreen
{
public:
	void Kick(const char *slot);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void Quit(const char *unused);
	void OnBttnEnterText(const char *unused);

	// Zero Hour's DisconnectMenu::sendChat, filtered. Name unknown.
	void rva005130E2(UnicodeString text);

private:
	unsigned char m_pad000[0x27C];
	GameWindow *m_chatBox; // +0x27C
	GameWindow *m_chatEntry; // +0x280
	unsigned char m_pad284[0x285 - 0x284];
	bool m_quit; // +0x285
};

static inline bool unicodeIsEmpty(const UnicodeString &text)
{
	const unsigned char *data = *(const unsigned char *const *)&text;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

// Retail 0x00512D55, 66 bytes: "AptDisconnectScreen::Kick".
void AptDisconnectScreen::Kick(const char *slot)
{
	if (slot && *slot)
	{
		int index = atoi(slot);
		int target = rva0066b3e0(index, TheNetwork->v46());
		TheNetwork->v38(target);
	}
}

// Retail 0x0051321A, 184 bytes: bound as "DisconnectScreen::InitGadgets";
// keeps "ChatBox" and the emptied "ChatEntry", and fills "RulesBox" with
// the localized APT:DisconnectRules.
void AptDisconnectScreen::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (strcmp(name, "ChatBox") == 0)
		m_chatBox = window;
	else if (strcmp(name, "ChatEntry") == 0)
	{
		m_chatEntry = window;
		GadgetTextEntrySetText(window, UnicodeString::TheEmptyString);
	}
	else if (strcmp(name, "RulesBox") == 0)
	{
		GadgetListBoxReset(window);
		BfmeGadgetListBoxSetAudioFeedback(window, true);
		GadgetListBoxAddEntryText(window, TheGameText->fetch("APT:DisconnectRules"), -1, -1, -1, true);
	}
}

// Retail 0x005130E2, 84 bytes. Name unknown. Zero Hour's
// DisconnectMenu::sendChat with the line passed through the language filter
// first.
void AptDisconnectScreen::rva005130E2(UnicodeString text)
{
	if (TheLanguageFilter)
		TheLanguageFilter->filterLine(text);
	TheNetwork->v27(text);
}

// Retail 0x005132D2, 176 bytes: "AptDisconnectScreen::Quit" announces the
// local player's leaving, votes out every unconnected slot and quits.
void AptDisconnectScreen::Quit(const char *unused)
{
	m_quit = true;
	UnicodeString text = TheNetwork->v47(TheNetwork->v46());
	text.concat(L" has left the game.");
	rva005130E2(text);
	for (int slot = 0; slot < 8; ++slot)
	{
		if (!TheNetwork->v65(slot))
			TheNetwork->v38(slot);
	}
	TheNetwork->v37();
}

// Retail 0x00513382, 171 bytes: "AptDisconnectScreen::Chat::OnBttnEnterText"
// takes and clears the chat entry and sends the trimmed line.
void AptDisconnectScreen::OnBttnEnterText(const char *unused)
{
	UnicodeString text;
	if (!m_chatEntry)
		return;
	text.set(GadgetTextEntryGetText(m_chatEntry));
	GadgetTextEntrySetText(m_chatEntry, UnicodeString::TheEmptyString);
	text.trim();
	if (!unicodeIsEmpty(text))
		rva005130E2(text);
}
