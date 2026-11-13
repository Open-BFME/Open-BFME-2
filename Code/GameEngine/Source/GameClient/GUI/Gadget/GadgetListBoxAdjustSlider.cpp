// cl: /O1 /arch:SSE /DNDEBUG /MD
// platformsdk
// ?Rva003249D2@@YAXPAVGameWindow@@_N@Z @0x003249D2 275B: the list box slider
// refresh run after every display change (0x00324AE5 and
// GadgetListBoxSetBottomVisibleEntry call it). Reference semantics: the
// slider half of Zero Hour GadgetListBox.cpp adjustDisplay, which BFME2 splits
// out; the address name is kept. Target facts: with a slider (+0x24) the
// slider data range becomes [0, totalHeight (+0x28) - displayHeight (short
// +0x3C)] clamped at 0; when the thumb's push button flag (0x00327DF6, user
// data byte +0x20) is set, the thumb height follows displayHeight/totalHeight
// (at most 1) of the slider height, at least 10; numTicks is the free track
// over the range; with the flag argument the slider is set (GSM_SET_SLIDER
// 0x400D through manager slot 58) to range - displayPos (short +0x44), at
// least 0; a set byte at +0x11 shows the scroll bar through 0x003248F5 only
// while the rows overflow the display.
typedef int Int;
typedef short Short;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;

enum { GSM_SET_SLIDER = 0x400D };

#include "../../../../Include/GameClient/Bfme2GameWindow.h"

#include <windows.h>
#include "../../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../../Include/Common/SliderData.h"

struct ListboxData
{
	unsigned char m_pad00[0x11];
	Bool m_autoScrollBar;
	unsigned char m_pad12[0x24 - 0x12];
	GameWindow *slider;
	Int totalHeight;
	unsigned char m_pad2C[0x3C - 0x2C];
	Short displayHeight;
	unsigned char m_pad3E[0x44 - 0x3E];
	Short displayPos;
};

#include "../../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

// Push button user data byte +0x20, rowed under an address-derived name.
class BfmeObjEBN;
char bfmeGoEBNb(BfmeObjEBN *o);

void Rva003248F5Show(GameWindow *listBox, Bool hide);

void Rva003249D2(GameWindow *window, Bool updateSlider)
{
	ListboxData *list = (ListboxData *)window->winGetUserData();

	if (list->slider != NULL)
	{
		ICoord2D sliderSize, sliderChildSize;
		GameWindow *child;

		SliderData *sData = (SliderData *)list->slider->winGetUserData();
		list->slider->winGetSize(&sliderSize.x, &sliderSize.y);
		sData->minVal = 0;
		sData->maxVal = list->totalHeight - list->displayHeight;
		if (sData->maxVal < 0)
			sData->maxVal = 0;

		child = list->slider->winGetChild();
		child->winGetSize(&sliderChildSize.x, &sliderChildSize.y);
		if (bfmeGoEBNb((BfmeObjEBN *)child))
		{
			Real ratio = (Real)list->displayHeight / (Real)list->totalHeight;
			if (ratio > 1.0f)
				ratio = 1.0f;
			Int height = (Int)(sliderSize.y * ratio);
			if (height < 10)
				height = 10;
			child->winSetSize(sliderChildSize.x, height);
		}
		sData->numTicks = (Real)(sliderSize.y - sliderChildSize.y) / (Real)sData->maxVal;

		if (updateSlider)
		{
			Int position = sData->maxVal - list->displayPos;
			if (position < 0)
				position = 0;
			TheWindowManager->winSendSystemMsg(list->slider, GSM_SET_SLIDER, position, 0);
		}

		if (list->m_autoScrollBar)
			Rva003248F5Show(window, list->totalHeight <= list->displayHeight);
	}
}
