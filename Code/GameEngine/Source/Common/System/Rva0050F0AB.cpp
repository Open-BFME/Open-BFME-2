// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD
// ?rva0050F0AB@Rva0050F0AB@@QAEXXZ, retail 0x0050F0AB, 96 bytes.
// If m_7c null return; else format m_6c via UnicodeString::format L"%d" into
// local buf and GadgetTextEntrySetText(m_7c buf by value). Evidence: EH prolog
// 0x00629188; format 0x006CB5D0; StringBase-G copy 0x00037050; SetText
// 0x002C17EB; releaseBuffer 0x00036E70; callers 0x0050F297 0x0050F2EB
// 0x0050F416 0x0050F446 0x0050F4A0; neighbours RegistryAsciiPath /O1 /EHsc.
typedef unsigned short wchar_t;

#include "unicode_string.h"


class GameWindow;
class GameFont;
class BfmeKeyLC;

// The text entry's font, rebuilt at 0.8 of its size by TheFontLibrary.
class AsciiString;

struct GameFontView
{
	unsigned char m_pad00[0x08];
	unsigned char m_name[4]; // +0x08, an AsciiString
	float m_pointSize; // +0x0C
	unsigned char m_pad10[0x18 - 0x10];
	bool m_bold; // +0x18
};

#include "../../../Include/GameClient/FontLibrary.h"

extern FontLibrary *TheFontLibrary;

#include "../../../Include/GameClient/Bfme2GameWindow.h"

// GadgetUserDataOr0032060D.cpp's 0x0032060D and the text entry's maximum
// length setter 0x00433D07.
void GadgetTextEntrySetValidationFlags(GameWindow *window, int flags);
void GadgetTextEntrySetMaxChars(BfmeKeyLC *textEntry, unsigned short maxLength);

void GadgetTextEntrySetText(GameWindow *g, UnicodeString text);
UnicodeString __cdecl GadgetTextEntryGetText(GameWindow *g);
#include <stdlib.h>

// The money a player holds sits at Player+0x90 (canonical Rva003B0D7C, 12 bytes).
#include "../../../Include/GameLogic/Module/Rva003B0D7C.h"

class Player
{
public:
	Rva003B0D7C *getMoney() { return &m_money; }
private:
	char m_pad00[0x90];
	Rva003B0D7C m_money;
};

// TheSkirmishAIManager's per-player statistics: 0x002A8F24 returns the
// collector, whose +0x0C economy record holds an amount at +0x14 (WB
// 0x01357250 asserts statCollector and economyStats).
struct EconomyStats
{
	char m_pad00[0x14];
	int m_14;
};

struct StatCollector
{
	char m_pad00[0x0C];
	EconomyStats *m_economyStats;
};

struct Rva002A8AB1Record;

#include "../../../Include/GameLogic/Rva002A8F24.h"

extern Rva002A8F24 *TheSkirmishAIManager;

#include "../../../Include/Common/Rva0050F041.h"

class Rva0050F0AB
{
public:
	virtual void slot00();
	virtual int slot01();
	void rva0050F0AB();
	void rva0050F420(unsigned int val);
	void rva0050F290();
	void rva0050F306();
	void rva0050F450();
	void InitSlider(const char *name, void *userData, GameWindow *window);
	void InitTextEntry(const char *name, void *userData, GameWindow *window);
private:
	char m_pad04[0x64 - 0x04];
	Player *m_64;
	unsigned int m_68;
	unsigned int m_6c;
	int m_70;
	char m_pad74[0x78 - 0x74];
	GameWindow *m_78;
	GameWindow *m_7c;
};

void Rva0050F0AB::rva0050F0AB()
{
	if (m_7c == 0)
		return;
	UnicodeString buf;
	buf.format(L"%u", m_6c);
	GadgetTextEntrySetText(m_7c, buf);
}

int __cdecl Rva0050E776Send(GameWindow *window, int data);

void Rva0050F0AB::rva0050F420(unsigned int val)
{
	if (val == m_6c)
		return;
	if (val > m_68)
	{
		val = m_68;
		Rva0050E776Send(m_78, val);
	}
	m_6c = val;
	rva0050F0AB();
}

void Rva0050F0AB::rva0050F290()
{
	m_6c = 0;
	rva0050F0AB();
	GameWindow *win = m_78;
	if (win)
		Rva0050E776Send(win, 0);
}

// ?rva0050F306@Rva0050F0AB@@QAEXXZ @0x0050F306 154B. WB 0x01357250
// (AptPlayerTribute.cpp, TributeRow::UpdateMoney asserts at lines 744/747):
// the slot-1 amount plus the owner's money, plus its economy statistic when
// TheSkirmishAIManager tracks the owner; the text is refreshed through
// 0x0050F041 only when the total changed or was never shown (m_70 == -1).
void Rva0050F0AB::rva0050F306()
{
	int money = slot01();
	Rva003B0D7C *pMoney = m_64->getMoney();
	if (pMoney)
		money += pMoney->countMoney();
	if (TheSkirmishAIManager->rva002A8AB1(m_64))
	{
		StatCollector *statCollector = (StatCollector *)TheSkirmishAIManager->rva002A8F24(m_64);
		EconomyStats *economyStats = statCollector->m_economyStats;
		money += economyStats->m_14;
	}
	if (money != m_70 || m_70 == -1)
	{
		UnicodeString text;
		text.format(L"%u", money);
		((Rva0050F041 *)this)->rva0050F041(1, text);
		m_70 = money;
	}
}

void Rva0050F0AB::rva0050F450()
{
	UnicodeString tmp = GadgetTextEntryGetText(m_7c);
	int v = _wtoi(tmp.str());
	if (v < 0 || (unsigned int)v > m_68)
	{
		m_6c = (v < 0) ? 0 : m_68;
		rva0050F0AB();
	}
	else
		m_6c = (unsigned int)v;
	if (m_78)
		Rva0050E776Send(m_78, (int)m_6c);
}

#include "../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

class Rva0050F5A6
{
public:
	void rva0050F5A6(int unused);
private:
	char m_pad00[0x20];
	int m_20;
	char m_pad24[0x28 - 0x24];
	Rva0050F0AB *m_array28[1];
};

void Rva0050F5A6::rva0050F5A6(int unused)
{
	(void)unused;
	TheWindowManager->winSetFocus(0);
	for (int i = 0; i < m_20; ++i)
	{
		Rva0050F0AB *entry = *(Rva0050F0AB **)((char *)m_array28 + i * 8);
		if (entry)
			entry->rva0050F290();
	}
}

// The number of decimal digits in value. Retail 0x0050E8BF: the TU-static copy
// cl emits under its register convention (value in EAX); the one call folds.
static int countDigits(unsigned int value)
{
	int digits = 0;
	while (value)
	{
		++digits;
		value /= 10;
	}
	return digits;
}

// Retail 0x0050E889, 54 bytes: "_InitSlider", bound as a member pointer
// by the row's constructor 0x0050FC54: keeps the slider, ranges it
// 0..99999 and shows the amount.
void Rva0050F0AB::InitSlider(const char *name, void *userData, GameWindow *window)
{
	m_78 = window;
	TheWindowManager->winSendSystemMsg(window, 0x400E, 0, 99999);
	Rva0050E776Send(m_78, m_6c);
}

// Retail 0x0050F3A0, 128 bytes: "_InitTextEntry", bound alongside: keeps
// the text entry, shrinks its font, takes digits only up to the slider's
// width and shows the amount.
void Rva0050F0AB::InitTextEntry(const char *name, void *userData, GameWindow *window)
{
	m_7c = window;
	if (TheFontLibrary)
	{
		GameFontView *font = (GameFontView *)window->winGetFont();
		if (font)
		{
			GameFont *smaller = TheFontLibrary->getFont((const AsciiString *)font->m_name, font->m_pointSize * 0.8f, font->m_bold);
			if (smaller)
				m_7c->GameWindow::winSetFont(smaller);
		}
	}
	GadgetTextEntrySetValidationFlags(m_7c, 0x21);
	GadgetTextEntrySetMaxChars((BfmeKeyLC *)m_7c, countDigits(99999));
	rva0050F0AB();
}
