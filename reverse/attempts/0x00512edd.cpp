// ?rva00512EDD@Rva00512EDD@@QAEXHVUnicodeString@@@Z
// partial score=0.97 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /EHsc /MD /Oy-
// ?rva00512EDD@Rva00512EDD@@QAEXHVUnicodeString@@@Z @0x00512EDD 355B: disconnect screen player update.
// Target evidence: literals DisconnectScreen::PlayerName%d DisconnectScreen::VotesReceived%d Network:PlayerLeftGame,
// compiler wides L" " (0x7C26DC) and L"" (0x7BB5C4), rowed AsciiString::format 0x00038150,
// StringBase PBG 0x00037E30, bfmeSetText 0x00225301, TheGameText slot 0x44, UnicodeString::format 0x006CB660,
// StringBase copy 0x00037050, GadgetListBoxAddEntryText 0x00326BEC, rva00512CE9 0x00512CE9,
// releaseBuffers 0x00036E70 0x00036410; this+0x27c listbox as in AptDisconnectScreen::InitGadgets;
// callers 0x004D4250 0x005137E6; unblocks 0x00513558.
#include "ascii_string.h"
#include "unicode_string.h"

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &text, bool usePlaceholder);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class GameTextInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual void v16();
	virtual const UnicodeString *slot44(const char *label, bool *exists);
};

extern GameTextInterface *TheGameText;

class GameWindow;

int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, int color, int row, int column, bool overwrite);

extern int g_00DD1488;

class Rva00512CE9
{
public:
	void rva00512CE9(int slot, bool show);
};

static inline bool Rva00512EDDIsEmpty(const UnicodeString &s)
{
	const char *data = *(const char *const *)&s;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

class Rva00512EDD
{
public:
	void rva00512EDD(int slot, UnicodeString name);
private:
	char m_pad[0x27C];
	GameWindow *m_chatBox;
};

void Rva00512EDD::rva00512EDD(int slot, UnicodeString name)
{
	AsciiString key;
	key.format("DisconnectScreen::PlayerName%d", slot);
	if (Rva00512EDDIsEmpty(name))
	{
		g_bfmeAptWindowManager->bfmeSetText(key, UnicodeString(L" "), false);
	}
	else
	{
		g_bfmeAptWindowManager->bfmeSetText(key, name, false);
		if (m_chatBox)
		{
			UnicodeString msg;
			const char *data = *(const char *const *)&name;
			const unsigned short *nameText = data ? (const unsigned short *)(data + 8) : L"";
			msg.format(TheGameText->slot44("Network:PlayerLeftGame", 0), nameText);
			GadgetListBoxAddEntryText(m_chatBox, msg, g_00DD1488, -1, -1, true);
		}
	}
	((Rva00512CE9 *)this)->rva00512CE9(slot, false);
	key.format("DisconnectScreen::VotesReceived%d", slot);
	UnicodeString votes(L" ");
	g_bfmeAptWindowManager->bfmeSetText(key, votes, false);
}
