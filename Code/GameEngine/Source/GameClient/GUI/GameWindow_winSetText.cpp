// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?winSetText@GameWindow@@UAEHVUnicodeString@@@Z, retail 0x0031484A, 88 bytes.
//
// GameWindow caption setter: copies the by-value text into the instance data,
// then notifies the window callback (slot 0x0C) with the parameter address.
// Ported from Open-BFME-1
// Code/GameEngine/Source/GameClient/GUI/GameWindowTextAndHitTest.cpp
// (BFME1 0x00479660, 114B; BFME2 trims to 88B under /O1).
// BFME2 facts (all retail-measured):
// - WinInstanceData lives at +0x30 (same TU family as
//   WinInstanceDataDisplayStrings.cpp); its setText is the rowed 0x3223B3.
// - The callback sits at +0x04; onTextChanged is its slot 0x0C.
// - The by-value UnicodeString parameter is copied once (StringBase copy
//   0x37050 into a stack temp for the setText argument) and destroyed here
//   at the end (releaseBuffer 0x36E70 on [ebp+8]); the callback borrows
//   [ebp+8] by address, so no second copy exists.

typedef int Int;
typedef unsigned short wchar_t;

#ifndef NULL
#define NULL 0
#endif

#include "unicode_string.h"


class DisplayString;

class WinInstanceData
{
public:
	void setText(UnicodeString text);
	void setTooltipText(UnicodeString text);

private:
	char m_pad[0x19C];
	DisplayString *m_text;
	DisplayString *m_tooltip;
};

class GameWindowCallback
{
public:
	virtual void callbackSlot0();
	virtual void callbackSlot1();
	virtual void callbackSlot2();
	virtual void onTextChanged(UnicodeString *text);
};

class GameWindow
{
public:
	virtual int winSetText(UnicodeString text);
	void rva003148A2(UnicodeString text);
	unsigned char rva003147F6(int x, int y);
	int winGetScreenPosition(int *x, int *y);
	int winGetSize(int *width, int *height);

	GameWindowCallback *m_callback; // this+0x04
	unsigned int m_status; // this+0x08
	unsigned char m_pad[0x30 - 0x0C];
	WinInstanceData m_instData; // this+0x30
};

// ?winSetText@GameWindow@@UAEHVUnicodeString@@@Z
int GameWindow::winSetText(UnicodeString text)
{
	m_instData.setText(text);

	if (m_callback != NULL)
		m_callback->onTextChanged(&text);

	return 0;
}

void GameWindow::rva003148A2(UnicodeString text)
{
	m_instData.setTooltipText(text);
}

unsigned char GameWindow::rva003147F6(int x, int y)
{
	int sx, sy, w, h;
	winGetScreenPosition(&sx, &sy);
	winGetSize(&w, &h);
	if (x < sx)
		return 0;
	if (x > sx + w)
		return 0;
	if (y < sy || y > sy + h)
		return 0;
	return 1;
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?winSetText@GameWindow@@QAEHVUnicodeString@@@Z=?winSetText@GameWindow@@UAEHVUnicodeString@@@Z")
