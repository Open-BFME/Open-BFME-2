// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// BFME2's disconnect screen Apt callbacks "AptDisconnectScreen::Kick"
// (0x00512D55; votes to kick the player in the given slot) and
// "DisconnectScreen::InitGadgets" (0x0051321A), bound by those names as
// member pointers by the screen's registration; that binding is their only
// reference.

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
void GadgetListBoxReset(GameWindow *listBox);
void BfmeGadgetListBoxSetAudioFeedback(GameWindow *listBox, bool enable);
int GadgetListBoxAddEntryText(GameWindow *listBox, UnicodeString text, int color, int row, int column, bool overwrite);

extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);

// Rva0066B3E0Adj.cpp's slot translation (0x004D39F0).
int rva0066b3e0(int slot, int localSlot);

// Zero Hour's TheNetwork: vslot 46 is the local slot, vslot 38 votes.
class NetworkInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37();
	virtual void v38(int slot);
	virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42();
	virtual void v43(); virtual void v44(); virtual void v45();
	virtual int v46();
};

extern NetworkInterface *TheNetwork;

class AptDisconnectScreen
{
public:
	void Kick(const char *slot);
	void InitGadgets(const char *name, void *argument, GameWindow *window);

private:
	unsigned char m_pad000[0x27C];
	GameWindow *m_chatBox; // +0x27C
	GameWindow *m_chatEntry; // +0x280
};

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
