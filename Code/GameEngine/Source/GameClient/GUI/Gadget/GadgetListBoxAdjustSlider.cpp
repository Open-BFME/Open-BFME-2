// cl: /O1 /arch:SSE /DNDEBUG /MD
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

#ifndef NULL
#define NULL 0
#endif

class GameWindow
{
public:
	void *winGetUserData();
	Int winGetSize(Int *width, Int *height);
	Int winSetSize(Int width, Int height);
	GameWindow *winGetChild();
};

struct ICoord2D
{
	Int x;
	Int y;
};

struct SliderData
{
	Int minVal;
	Int maxVal;
	Real numTicks;
	Int position;
};

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

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57)
#undef V
	virtual Int winSendSystemMsg(GameWindow *window, UnsignedInt msg,
		WindowMsgData mData1, WindowMsgData mData2) = 0;
};

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
