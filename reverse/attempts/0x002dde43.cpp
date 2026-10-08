// ?rva002DDE43@GameState@@QAEXABVUnicodeString@@0HH@Z
// partial score=0.97 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Address-derived AptSaveLoad callback at 0x00435819 (738 bytes). The
// retail body reads the filename text entry at +0x290, game list +0x288,
// replay mode +0x2A0 and flag +0x29C, then sets screen state +0x27C to 9.
// Strings and helper calls are named by their target addresses where their
// semantic identities are unresolved.
#include "unicode_string.h"

class GameWindow;
UnicodeString GadgetTextEntryGetText(GameWindow *entry);

UnicodeString Rva0037BA48Get();
UnicodeString GetLastReplayDisplayName();
void __cdecl Rva00437E9C(int value);
void __cdecl Rva00437EAC(int flags, const UnicodeString &title,
	const UnicodeString &message);

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
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
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

class InGameUI
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void message(UnicodeString text, ...);
};
extern InGameUI *TheInGameUI;

class GameState
{
public:
	int rva002DBE62Get();
	void *rva002DBC97Get(int mode);
	void rva002DDE43(const UnicodeString &name, const UnicodeString &text,
		int save, int confirm);
	int saveGame(UnicodeString name, const UnicodeString &text, int save, bool confirmOrig, int confirm);
};
extern GameState *TheGameState;

struct Bfme939Helper
{
	bool rva0037D6E8(const UnicodeString &name, const UnicodeString &text);
};
extern Bfme939Helper *g_bfme939Helper;

struct BFME2WideConcatPair
{
	const UnicodeString *a;
	const UnicodeString *b;
	BFME2WideConcatPair(const UnicodeString &left, const UnicodeString &right)
	{
		b = &right;
		a = &left;
	}
	operator UnicodeString();
};
#pragma comment(linker, "/alternatename:??BBFME2WideConcatPair@@QAE?AVUnicodeString@@XZ=??BBFME2WideConcatPair@@QAE?AV?$StringBase@G@@XZ")
inline BFME2WideConcatPair operator+(const UnicodeString &left,
	const UnicodeString &right)
{
	return BFME2WideConcatPair(left, right);
}

bool __cdecl Rva0037D96B(const UnicodeString &path,
	const UnicodeString &name, const UnicodeString &text);

class AptSaveLoad
{
public:
	void rva00435819();

private:
	unsigned char m_pad000[0x27C];
	int m_state;
	unsigned char m_pad280[0x288 - 0x280];
	GameWindow *m_gameList;
	GameWindow *m_autoSaveList;
	GameWindow *m_fileName;
	unsigned char m_pad294[0x29C - 0x294];
	bool m_29c;
	unsigned char m_pad29d[0x2A0 - 0x29D];
	int m_mode;
};

static bool unicodeIsEmpty(const UnicodeString &text)
{
	const unsigned char *data = *(const unsigned char *const *)&text;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

void AptSaveLoad::rva00435819()
{
	if (!m_fileName || !m_gameList)
		return;

	UnicodeString text = GadgetTextEntryGetText(m_fileName);
	UnicodeString name;
	name = text;
	name.trim();

	if (m_mode == 4)
	{
		if (!unicodeIsEmpty(name))
			name += Rva0037BA48Get();

		if (m_29c)
		{
			bool complete = g_bfme939Helper->rva0037D6E8(name, text);
			Rva00437E9C(0);
			UnicodeString message;
			if (complete)
				message.set(TheGameText->fetch("GUI:ReplaySaveComplete", 0));
			else
				message.set(TheGameText->fetch("GUI:ReplaySaveError", 0));
			TheInGameUI->message(message);
		}
		else
		{
			bool complete = Rva0037D96B(
				GetLastReplayDisplayName() + Rva0037BA48Get(), name, text);
			UnicodeString message;
			if (complete)
				message.set(TheGameText->fetch(
					"APT:ReplaySaveCompleteMessageBox", 0));
			else
				message.set(TheGameText->fetch(
					"APT:ReplaySaveErrorMessageBox", 0));
			Rva00437EAC(0,
				TheGameText->fetch("APT:SaveGameProgress", 0), message);
		}
	}
	else
	{
		if (!unicodeIsEmpty(name))
		{
			name += (const unsigned short *)TheGameState->rva002DBC97Get(
				TheGameState->rva002DBE62Get());
		}
		TheGameState->rva002DDE43(name, text, 0, 1);
		Rva00437EAC(0,
			TheGameText->fetch("APT:SaveGameProgress", 0),
			TheGameText->fetch("GUI:GameSaved", 0));
	}

	m_state = 9;
}

// ?rva002DDE43@GameState@@QAEXABVUnicodeString@@0HH@Z @0x002DDE43 43B
// Leaf forwarding to saveGame with original confirm false. Evidence:
// callers 0x002408F5 0x00435A6F (this TU 0x00435A6F calls with 0 1),
// callees StringBase wide copy saveGame pin, pin class proof.
void GameState::rva002DDE43(const UnicodeString &name, const UnicodeString &text, int save, int confirm)
{
	saveGame(name, text, save, false, confirm);
}
