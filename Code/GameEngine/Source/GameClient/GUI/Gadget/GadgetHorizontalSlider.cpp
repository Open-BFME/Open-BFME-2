// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BFME2 horizontal slider callbacks. Reference semantics: Open-BFME-1
// GadgetHorizontalSlider.cpp (BFME1 retail 0x004B5530 system), with the same
// SliderData and message numbers as GadgetVerticalSlider.cpp.
//
// GadgetHorizontalSliderInput 0x00321B50 (780B, Ghidra boundary). Target
// facts: the slider size is read before the switch; entering and leaving
// also hilite a push-button thumb (winGetStyle & 1); Right steps the position
// down and Left up by 2, moving the thumb before sending 0x400C (BFME1 sends
// first); Tab picks GameWindowManager slot 43 or 42 by TheKeyboard's shift
// bit (+0xC & 0x10); a track click pages by a fifth of the width, clamps with
// the ZH x/y slip (x + size.y on the right edge), and sends GGM_LEFT_DRAG to
// itself and 0x4010 to the owner.
//
// GadgetHorizontalSliderSystem 0x00321E5C (779B, Ghidra boundary): as in
// BFME1, with a 13 pixel thumb (resize and set range subtract 0xD).
typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

enum
{
	GWM_CREATE = 1,
	GWM_DESTROY = 2,
	GWM_INPUT_FOCUS = 23,
	GWM_LEFT_DOWN = 5,
	GWM_LEFT_UP = 6,
	GWM_LEFT_DRAG = 8,
	GWM_MOUSE_ENTERING = 17,
	GWM_MOUSE_LEAVING = 18,
	GWM_CHAR = 21
};

enum
{
	GGM_LEFT_DRAG = 0x4000,
	GGM_FOCUS_CHANGE = 0x4003,
	GGM_RESIZED = 0x4004,
	GBM_SELECTED = 0x4008,
	GBM_MOUSE_ENTERING = 0x4006,
	GBM_MOUSE_LEAVING = 0x4007,
	GSM_SLIDER_TRACK = 0x400C,
	GSM_SET_SLIDER = 0x400D,
	GSM_SET_MIN_MAX = 0x400E,
	GSM_SLIDER_DONE = 0x400F,
	GSM_SLIDER_CLICKED = 0x4010
};

enum { HORIZONTAL_SLIDER_THUMB_WIDTH = 13 };

enum
{
	KEY_TAB = 0x0F,
	KEY_UP = 0xC8,
	KEY_LEFT = 0xCB,
	KEY_RIGHT = 0xCD,
	KEY_DOWN = 0xD0
};

enum { KEY_STATE_DOWN = 0x0002, KEY_STATE_LSHIFT = 0x0010 };
enum { WIN_STATE_HILITED = 0x02 };
enum { GWS_PUSH_BUTTON = 0x00000001, GWS_MOUSE_TRACK = 0x00000400 };

#define BitTest(x, i) (((x) & (i)) != 0)
#define BitSet(x, i) ((x) |= (i))
#define BitClear(x, i) ((x) &= ~(i))

// A user constructor makes cl order x + size.x with the scalar first, as
// retail does in both callbacks here (the vertical bodies match either way).
#define ICOORD2D_VIEW_DEFAULT_CTOR
#include "../../../../../Libraries/Include/Lib/ICoord2D.h"
#undef ICOORD2D_VIEW_DEFAULT_CTOR

#include "../../../../Include/GameClient/Bfme2GameWindow.h"


#include "../../../../Include/GameClient/GameWindowManager.h"

struct SliderData
{
	Int minVal;
	Int maxVal;
	Real numTicks;
	Int position;
};

#include "../../../../Include/GameClient/KeyboardClass.h"

extern GameWindowManager *TheWindowManager;
extern Keyboard *TheKeyboard;

WindowMsgHandledType GadgetHorizontalSliderInput(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	SliderData *sliderData = (SliderData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();
	ICoord2D size, childSize, childCenter;
	window->winGetSize(&size.x, &size.y);
	switch (msg)
	{
		case GWM_MOUSE_ENTERING:
		{
			if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
			{
				BitSet(instData->m_state, WIN_STATE_HILITED);
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GBM_MOUSE_ENTERING, (WindowMsgData)window, 0);
			}

			if (window->winGetChild() && BitTest(window->winGetChild()->winGetStyle(), GWS_PUSH_BUTTON))
			{
				WinInstanceData *instDataChild = window->winGetChild()->winGetInstanceData();
				BitSet(instDataChild->m_state, WIN_STATE_HILITED);
			}
			break;
		}

		case GWM_MOUSE_LEAVING:
		{
			if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
			{
				BitClear(instData->m_state, WIN_STATE_HILITED);
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GBM_MOUSE_LEAVING, (WindowMsgData)window, 0);
			}
			if (window->winGetChild() && BitTest(window->winGetChild()->winGetStyle(), GWS_PUSH_BUTTON))
			{
				WinInstanceData *instDataChild = window->winGetChild()->winGetInstanceData();
				BitClear(instDataChild->m_state, WIN_STATE_HILITED);
			}
			break;
		}

		case GWM_LEFT_DRAG:
			if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GGM_LEFT_DRAG, (WindowMsgData)window, mData1);
			break;

		case GWM_LEFT_DOWN:
			break;

		case GWM_LEFT_UP:
		{
			Int x, y;
			Int mousex = mData1 & 0xFFFF;

			GameWindow *child = window->winGetChild();
			Int pageClickSize, clickPos;

			window->winGetScreenPosition(&x, &y);

			child->winGetSize(&childSize.x, &childSize.y);
			child->winGetPosition(&childCenter.x, &childCenter.y);
			childCenter.x += childSize.x / 2;
			childCenter.y += childSize.y / 2;

			// when you click on the slider, but not the button, we will jump
			// the slider position up/down by this much
			pageClickSize = size.x / 5;

			clickPos = mousex - x;
			if (clickPos >= childCenter.x)
			{
				clickPos = childCenter.x + pageClickSize;
				if (clickPos > mousex - x)
					clickPos = mousex - x;
			}
			else
			{
				clickPos = childCenter.x - pageClickSize;
				if (clickPos < mousex - x)
					clickPos = mousex - x;
			}

			// keep it all valid to the window
			if (clickPos > x + size.x - childSize.x / 2)
				clickPos = x + size.y - childSize.x / 2;
			if (clickPos < childSize.x / 2)
				clickPos = childSize.x / 2;

			child->winSetPosition(clickPos - childSize.x / 2, 0);
			TheWindowManager->winSendSystemMsg(window, GGM_LEFT_DRAG, 0, mData1);
			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
				GSM_SLIDER_CLICKED, (WindowMsgData)window, 0);
			break;
		}

		case GWM_CHAR:
		{
			switch (mData1)
			{
				case KEY_RIGHT:
					if (BitTest(mData2, KEY_STATE_DOWN))
					{
						if (sliderData->position > sliderData->minVal + 1)
						{
							GameWindow *child = window->winGetChild();

							sliderData->position -= 2;

							// Translate to window coords
							child->winSetPosition((Int)((sliderData->position - sliderData->minVal) * sliderData->numTicks), 0);
							TheWindowManager->winSendSystemMsg(window->winGetOwner(),
								GSM_SLIDER_TRACK, (WindowMsgData)window, sliderData->position);
						}
					}
					break;

				case KEY_LEFT:
					if (BitTest(mData2, KEY_STATE_DOWN))
					{
						if (sliderData->position < sliderData->maxVal - 1)
						{
							GameWindow *child = window->winGetChild();

							sliderData->position += 2;

							// Translate to window coords
							child->winSetPosition((Int)((sliderData->position - sliderData->minVal) * sliderData->numTicks), 0);
							TheWindowManager->winSendSystemMsg(window->winGetOwner(),
								GSM_SLIDER_TRACK, (WindowMsgData)window, sliderData->position);
						}
					}
					break;

				case KEY_TAB:
					if (BitTest(mData2, KEY_STATE_DOWN))
					{
						if (TheKeyboard->getModifierFlags() & KEY_STATE_LSHIFT)
							TheWindowManager->winPrevTab(window);
						else
							TheWindowManager->winNextTab(window);
					}
					break;

				default:
					return MSG_IGNORED;
			}
			break;
		}

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}

WindowMsgHandledType GadgetHorizontalSliderSystem(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	SliderData *sliderData = (SliderData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();
	ICoord2D size, childSize, childCenter, childRelativePos;

	window->winGetSize(&size.x, &size.y);

	switch (msg)
	{
		case GBM_SELECTED:
			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
				GSM_SLIDER_CLICKED, (WindowMsgData)window, 0);
			break;

		case GGM_LEFT_DRAG:
		{
			Int mousex = mData2 & 0xFFFF;
			Int x, y, delta;
			GameWindow *child = window->winGetChild();

			window->winGetScreenPosition(&x, &y);

			child->winGetSize(&childSize.x, &childSize.y);
			child->winGetScreenPosition(&childCenter.x, &childCenter.y);
			child->winGetPosition(&childRelativePos.x, &childRelativePos.y);
			childCenter.x += childSize.x / 2;
			childCenter.y += childSize.y / 2;

			// ignore drag attempts when the mouse is right or left of slider
			// totally and put the dragging thumb back at the slider pos
			if (mousex > x + size.x)
			{
				TheWindowManager->winSendSystemMsg(window, GSM_SET_SLIDER, sliderData->maxVal, 0);
				// tell owner i moved
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GSM_SLIDER_TRACK, (WindowMsgData)window, sliderData->maxVal);
				break;
			}
			else if (mousex < x)
			{
				TheWindowManager->winSendSystemMsg(window, GSM_SET_SLIDER, sliderData->minVal, 0);
				// tell owner i moved
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GSM_SLIDER_TRACK, (WindowMsgData)window, sliderData->minVal);
				break;
			}

			if (childCenter.x < x + childSize.x / 2)
			{
				child->winSetPosition(0, 0);
				sliderData->position = sliderData->minVal;
			}
			else if (childCenter.x >= x + size.x - childSize.x / 2)
			{
				Int rightPos = size.x - childSize.x;
				child->winSetPosition(rightPos, 0);
				sliderData->position = sliderData->maxVal;
			}
			else
			{
				delta = childCenter.x - childSize.x / 2 - x;

				// Calc slider position
				sliderData->position = (Int)(delta / sliderData->numTicks) + sliderData->minVal;

				if (sliderData->position > sliderData->maxVal)
					sliderData->position = sliderData->maxVal;
				if (sliderData->position < sliderData->minVal)
					sliderData->position = sliderData->minVal;
			}

			// tell owner i moved
			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
				GSM_SLIDER_TRACK, (WindowMsgData)window, sliderData->position);
			break;
		}

		case GSM_SET_SLIDER:
		{
			Int newPos = (Int)mData1;
			GameWindow *child = window->winGetChild();

			if (newPos < sliderData->minVal || newPos > sliderData->maxVal)
				break;

			sliderData->position = newPos;

			// Translate to window coords
			newPos = (Int)((newPos - sliderData->minVal) * sliderData->numTicks);

			child->winSetPosition(newPos, 0);
			break;
		}

		case GSM_SET_MIN_MAX:
		{
			ICoord2D size;
			GameWindow *child = window->winGetChild();

			window->winGetSize(&size.x, &size.y);

			sliderData->minVal = (Int)mData1;
			sliderData->maxVal = (Int)mData2;
			sliderData->numTicks = (Real)(size.x - HORIZONTAL_SLIDER_THUMB_WIDTH)
				/ (Real)(sliderData->maxVal - sliderData->minVal);
			sliderData->position = sliderData->minVal;

			child->winSetPosition(0, 0);
			break;
		}

		case GWM_CREATE:
			break;

		case GWM_DESTROY:
			delete (SliderData *)window->winGetUserData();
			break;

		case GWM_INPUT_FOCUS:
		{
			if (mData1 == false)
				BitClear(instData->m_state, WIN_STATE_HILITED);
			else
				BitSet(instData->m_state, WIN_STATE_HILITED);

			TheWindowManager->winSendSystemMsg(window->winGetOwner(), GGM_FOCUS_CHANGE,
				mData1, window->winGetWindowId());
			*(Bool *)mData2 = true;
			break;
		}

		case GGM_RESIZED:
		{
			Int height = (Int)mData2;

			sliderData->numTicks = (Real)((Int)mData1 - HORIZONTAL_SLIDER_THUMB_WIDTH)
				/ (Real)(sliderData->maxVal - sliderData->minVal);

			GameWindow *thumb = window->winGetChild();
			if (thumb)
				thumb->winSetSize(HORIZONTAL_SLIDER_THUMB_WIDTH, height);
			break;
		}

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
