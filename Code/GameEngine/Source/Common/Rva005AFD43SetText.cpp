// cl: /Ireference/shims/bfme2_ascii /MD /Oy-
//
// ?rva005AFD43@Rva005AFD43@@QAEXPAVGameWindow@@ABVUnicodeString@@@Z, retail 0x005AFD43, 70 bytes.
// Unlock method: stores GameWindow* at +8; if null return; else
// TheWindowManager->winSetFocus(g) via slot 0xC4, GadgetTextEntrySetMaxChars as BfmeKeyLC
// with 0x6e, then GadgetTextEntrySetText(g, s) via temp UnicodeString copy
// (StringBase-G copy ctor). Evidence: global 0x009FEF1C, virtual 0xC4,
// callees rowed, callers 0x0051195F 0x0051197A 0x00511A40 0x0057FE5D.
// Finish from stash reverse/attempts/0x005afd43.cpp score 0.93; shared
// UnicodeString header for inline copy-ctor order (shape lever mov ecx,esp
// vs mov [esp+N],esp).
#include "unicode_string.h"

class GameWindow;

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	virtual void windowHiding(GameWindow *window) = 0;
	V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	virtual GameWindow *winGetFocus() = 0;
	virtual int winSetFocus(GameWindow *window) = 0;
	V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57)
#undef V
	virtual int winSendSystemMsg(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2) = 0;
};

extern GameWindowManager *TheWindowManager;

class BfmeKeyLC;
void GadgetTextEntrySetMaxChars(BfmeKeyLC *k, unsigned short w);

class GameWindow;
void GadgetTextEntrySetText(GameWindow *g, UnicodeString text);

class Rva005AFD43
{
public:
	void rva005AFD43(GameWindow *g, const UnicodeString &s);
private:
	char m_00[8];
	GameWindow *m_08;
};

void Rva005AFD43::rva005AFD43(GameWindow *g, const UnicodeString &s)
{
	m_08 = g;
	if (g == 0)
		return;
	TheWindowManager->winSetFocus(m_08);
	GadgetTextEntrySetMaxChars((BfmeKeyLC *)(void *)m_08, 0x6e);
	GadgetTextEntrySetText(m_08, s);
}
