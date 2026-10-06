// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc
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

class FontLibrary
{
public:
	GameFont *getFont(const AsciiString *name, float size, bool bold);
};

extern FontLibrary *TheFontLibrary;

class GameWindow
{
public:
	GameFont *winGetFont();
	virtual void winSetFont(GameFont *font);
};

// GadgetUserDataOr0032060D.cpp's 0x0032060D and the text entry's maximum
// length setter 0x00433D07.
void GadgetTextEntrySetValidationFlags(GameWindow *window, int flags);
void GadgetTextEntrySetMaxChars(BfmeKeyLC *textEntry, unsigned short maxLength);

void GadgetTextEntrySetText(GameWindow *g, UnicodeString text);
UnicodeString __cdecl GadgetTextEntryGetText(GameWindow *g);
extern "C" __declspec(dllimport) int __cdecl _wtoi(const wchar_t *s);

class Rva0050F0AB
{
public:
	void rva0050F0AB();
	void rva0050F420(unsigned int val);
	void rva0050F290();
	void rva0050F450();
	void InitSlider(const char *name, void *argument, GameWindow *window);
	void InitTextEntry(const char *name, void *argument, GameWindow *window);
private:
	char m_pad00[0x68];
	unsigned int m_68;
	unsigned int m_6c;
	char m_pad70[0x78 - 0x70];
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

class GameWindowManager {
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	virtual void *winGetFocus();
#undef V
	virtual int winSetFocus(GameWindow *window);
#define W(n) virtual void pad##n() = 0;
	W(50) W(51) W(52) W(53) W(54) W(55) W(56) W(57)
#undef W
	virtual int winSendSystemMsg(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2);
};

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

// The number of decimal digits in value.
inline int countDigits(unsigned int value)
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
void Rva0050F0AB::InitSlider(const char *name, void *argument, GameWindow *window)
{
	m_78 = window;
	TheWindowManager->winSendSystemMsg(window, 0x400E, 0, 99999);
	Rva0050E776Send(m_78, m_6c);
}

// Retail 0x0050F3A0, 128 bytes: "_InitTextEntry", bound alongside: keeps
// the text entry, shrinks its font, takes digits only up to the slider's
// width and shows the amount.
void Rva0050F0AB::InitTextEntry(const char *name, void *argument, GameWindow *window)
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
