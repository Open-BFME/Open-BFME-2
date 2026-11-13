// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BFME2 vertical slider callbacks. Reference semantics: the ZH/Open-BFME-1
// GadgetVerticalSlider.cpp bodies (BFME1 retail 0x004BF660 input).
//
// GadgetVerticalSliderInput 0x00321620 (656B, Ghidra boundary), slot 0x6C of
// the input table 0x9BCAD8. Target facts: SliderData minVal +0, maxVal +4,
// numTicks (float) +8, position +0xC; the arrow keys step the position by 2
// and send 0x400C, as in BFME1; Left, Right and Tab call the window's tab
// methods (one folded body at 0x000D43D0); a click off the thumb pages it by
// a fifth of the slider height toward the mouse.
//
// GadgetVerticalSliderSystem 0x003218B0 (672B, Ghidra boundary): messages
// 0x4004 (resized: the thumb is sized to the width by 16), 0x4008 (selected:
// 0x400F to the owner), GGM_LEFT_DRAG, 0x400D (set position) and 0x400E (set
// range, 16 pixels left for the thumb), as in BFME1.
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
	GSM_SLIDER_DONE = 0x400F
};

enum { GADGET_SIZE = 16 };

enum
{
	KEY_TAB = 0x0F,
	KEY_UP = 0xC8,
	KEY_LEFT = 0xCB,
	KEY_RIGHT = 0xCD,
	KEY_DOWN = 0xD0
};

enum { KEY_STATE_DOWN = 0x0002 };
enum { WIN_STATE_HILITED = 0x02 };
enum { GWS_MOUSE_TRACK = 0x00000400 };

#define BitTest(x, i) (((x) & (i)) != 0)
#define BitSet(x, i) ((x) |= (i))
#define BitClear(x, i) ((x) &= ~(i))

#include "../../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../../Include/GameClient/Bfme2GameWindow.h"


#include "../../../../Include/GameClient/GameWindowManager.h"

#include "../../../../Include/Common/SliderData.h"

extern GameWindowManager *TheWindowManager;

WindowMsgHandledType GadgetVerticalSliderInput(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	SliderData *sliderData = (SliderData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();

	switch (msg)
	{
		case GWM_MOUSE_ENTERING:
			if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
			{
				BitSet(instData->m_state, WIN_STATE_HILITED);
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GBM_MOUSE_ENTERING, (WindowMsgData)window, 0);
			}
			break;

		case GWM_MOUSE_LEAVING:
			if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
			{
				BitClear(instData->m_state, WIN_STATE_HILITED);
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GBM_MOUSE_LEAVING, (WindowMsgData)window, 0);
			}
			break;

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
			Int mousey = mData1 >> 16;
			ICoord2D size, childSize, childCenter;
			GameWindow *child = window->winGetChild();
			Int pageClickSize, clickPos;

			window->winGetScreenPosition(&x, &y);
			window->winGetSize(&size.x, &size.y);
			child->winGetSize(&childSize.x, &childSize.y);
			child->winGetPosition(&childCenter.x, &childCenter.y);
			childCenter.x += childSize.x / 2;
			childCenter.y += childSize.y / 2;

			// when you click on the slider, but not the button, we will jump
			// the slider position up/down by this much
			pageClickSize = size.y / 5;

			clickPos = mousey - y;
			if (clickPos >= childCenter.y)
			{
				clickPos = childCenter.y + pageClickSize;
				if (clickPos > mousey - y)
					clickPos = mousey - y;
			}
			else
			{
				clickPos = childCenter.y - pageClickSize;
				if (clickPos < mousey - y)
					clickPos = mousey - y;
			}

			// keep pos valid on window
			if (clickPos > y + size.y - childSize.y / 2)
				clickPos = y + size.y - childSize.y / 2;
			if (clickPos < childSize.y / 2)
				clickPos = childSize.y / 2;

			child->winSetPosition(0, clickPos - childSize.y / 2);
			TheWindowManager->winSendSystemMsg(window, GGM_LEFT_DRAG, 0, mData1);
			break;
		}

		case GWM_CHAR:
		{
			switch (mData1)
			{
				case KEY_UP:
					if (BitTest(mData2, KEY_STATE_DOWN))
					{
						if (sliderData->position < sliderData->maxVal - 1)
						{
							GameWindow *child = window->winGetChild();

							sliderData->position += 2;
							TheWindowManager->winSendSystemMsg(window->winGetOwner(),
								GSM_SLIDER_TRACK, (WindowMsgData)window, sliderData->position);
							// Translate to window coords
							child->winSetPosition(0, (Int)((sliderData->maxVal - sliderData->position) * sliderData->numTicks));
						}
					}
					break;

				case KEY_DOWN:
					if (BitTest(mData2, KEY_STATE_DOWN))
					{
						if (sliderData->position > sliderData->minVal + 1)
						{
							GameWindow *child = window->winGetChild();

							sliderData->position -= 2;
							TheWindowManager->winSendSystemMsg(window->winGetOwner(),
								GSM_SLIDER_TRACK, (WindowMsgData)window, sliderData->position);
							// Translate to window coords
							child->winSetPosition(0, (Int)((sliderData->maxVal - sliderData->position) * sliderData->numTicks));
						}
					}
					break;

				case KEY_RIGHT:
				case KEY_TAB:
					if (BitTest(mData2, KEY_STATE_DOWN))
						window->winNextTab();
					break;

				case KEY_LEFT:
					if (BitTest(mData2, KEY_STATE_DOWN))
						window->winPrevTab();
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

WindowMsgHandledType GadgetVerticalSliderSystem(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	SliderData *sliderData = (SliderData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();

	switch (msg)
	{
		case GBM_SELECTED:
		{
			// tell owner I've finished moving
			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
				GSM_SLIDER_DONE, (WindowMsgData)window, sliderData->position);
			break;
		}

		case GGM_LEFT_DRAG:
		{
			Int mousey = mData2 >> 16;
			Int x, y, delta;
			ICoord2D size, childSize, childPosition;
			GameWindow *child = window->winGetChild();

			window->winGetScreenPosition(&x, &y);
			window->winGetSize(&size.x, &size.y);
			child->winGetSize(&childSize.x, &childSize.y);
			child->winGetScreenPosition(&childPosition.x, &childPosition.y);

			// ignore drag attempts when the mouse is below or above the slider
			// totally and put the dragging thumb back at the slider pos
			if (mousey > y + size.y)
			{
				TheWindowManager->winSendSystemMsg(window, GSM_SET_SLIDER, sliderData->minVal, 0);
				// tell owner i moved
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GSM_SLIDER_TRACK, (WindowMsgData)window, sliderData->minVal);
				return MSG_HANDLED;
			}
			else if (mousey < y)
			{
				TheWindowManager->winSendSystemMsg(window, GSM_SET_SLIDER, sliderData->maxVal, 0);
				// tell owner i moved
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GSM_SLIDER_TRACK, (WindowMsgData)window, sliderData->maxVal);
				return MSG_HANDLED;
			}

			if (childPosition.y <= y)
			{
				child->winSetPosition(0, 0);
				sliderData->position = sliderData->maxVal;
			}
			else if (childPosition.y >= y + size.y - childSize.y)
			{
				child->winSetPosition(0, size.y - childSize.y);
				sliderData->position = sliderData->minVal;
			}
			else
			{
				delta = childPosition.y - y;

				// Calc slider position
				sliderData->position = (Int)(delta / sliderData->numTicks);

				if (sliderData->position > sliderData->maxVal)
					sliderData->position = sliderData->maxVal;

				// Invert slider position so that maxval is at the top
				sliderData->position = sliderData->maxVal - sliderData->position;
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
			newPos = (Int)((sliderData->maxVal - newPos) * sliderData->numTicks);

			child->winSetPosition(0, newPos);
			break;
		}

		case GSM_SET_MIN_MAX:
		{
			Int newPos;
			ICoord2D size;
			GameWindow *child = window->winGetChild();

			window->winGetSize(&size.x, &size.y);

			sliderData->minVal = (Int)mData1;
			sliderData->maxVal = (Int)mData2;
			sliderData->numTicks = (Real)(size.y - GADGET_SIZE) / (Real)(sliderData->maxVal - sliderData->minVal);
			sliderData->position = sliderData->minVal;

			// Translate to window coords
			newPos = (Int)((sliderData->maxVal - sliderData->minVal) * sliderData->numTicks);

			child->winSetPosition(0, newPos);
			break;
		}

		case GWM_CREATE:
			break;

		case GWM_DESTROY:
			delete (SliderData *)window->winGetUserData();
			break;

		case GWM_INPUT_FOCUS:
			// If we're losing focus
			if (mData1 == false)
				BitClear(instData->m_state, WIN_STATE_HILITED);
			else
				BitSet(instData->m_state, WIN_STATE_HILITED);

			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
				GGM_FOCUS_CHANGE, mData1, window->winGetWindowId());

			*(Bool *)mData2 = true;
			break;

		case GGM_RESIZED:
		{
			Int width = (Int)mData1;
			GameWindow *thumb = window->winGetChild();

			if (thumb)
			{
				thumb->winSetSize(width, GADGET_SIZE);
				thumb->winSetPosition(0, (Int)((sliderData->maxVal - sliderData->position) * sliderData->numTicks));
			}
			break;
		}

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
