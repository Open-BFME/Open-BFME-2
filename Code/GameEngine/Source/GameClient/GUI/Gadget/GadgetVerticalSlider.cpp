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

struct ICoord2D
{
	Int x;
	Int y;
};

class WinInstanceData
{
public:
	UnsignedInt getStyle() const { return m_style; }
	void *m_vtable;
	Int m_id;
	UnsignedInt m_state;
	UnsignedInt m_style;
};

class GameWindow
{
public:
	Int winSetPosition(Int x, Int y);
	Int winSetSize(Int width, Int height);
	Int winGetPosition(Int *x, Int *y);
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
	GameWindow *winGetChild();
	GameWindow *winGetOwner();
	Int winGetWindowId();
	Int winNextTab();
	Int winPrevTab();
	WinInstanceData *winGetInstanceData();
	void *winGetUserData();
};

class GameWindowManager
{
public:
#define V(n) virtual void slot##n() = 0;
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07)
	V(08) V(09) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57)
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window,
		UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2) = 0;
#undef V
};

struct SliderData
{
	Int minVal;
	Int maxVal;
	Real numTicks;
	Int position;
};

extern GameWindowManager *TheWindowManager;

WindowMsgHandledType GadgetVerticalSliderInput(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	SliderData *s = (SliderData *)window->winGetUserData();
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
						if (s->position < s->maxVal - 1)
						{
							GameWindow *child = window->winGetChild();

							s->position += 2;
							TheWindowManager->winSendSystemMsg(window->winGetOwner(),
								GSM_SLIDER_TRACK, (WindowMsgData)window, s->position);
							// Translate to window coords
							child->winSetPosition(0, (Int)((s->maxVal - s->position) * s->numTicks));
						}
					}
					break;

				case KEY_DOWN:
					if (BitTest(mData2, KEY_STATE_DOWN))
					{
						if (s->position > s->minVal + 1)
						{
							GameWindow *child = window->winGetChild();

							s->position -= 2;
							TheWindowManager->winSendSystemMsg(window->winGetOwner(),
								GSM_SLIDER_TRACK, (WindowMsgData)window, s->position);
							// Translate to window coords
							child->winSetPosition(0, (Int)((s->maxVal - s->position) * s->numTicks));
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
	SliderData *s = (SliderData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();

	switch (msg)
	{
		case GBM_SELECTED:
		{
			// tell owner I've finished moving
			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
				GSM_SLIDER_DONE, (WindowMsgData)window, s->position);
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
				TheWindowManager->winSendSystemMsg(window, GSM_SET_SLIDER, s->minVal, 0);
				// tell owner i moved
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GSM_SLIDER_TRACK, (WindowMsgData)window, s->minVal);
				return MSG_HANDLED;
			}
			else if (mousey < y)
			{
				TheWindowManager->winSendSystemMsg(window, GSM_SET_SLIDER, s->maxVal, 0);
				// tell owner i moved
				TheWindowManager->winSendSystemMsg(window->winGetOwner(),
					GSM_SLIDER_TRACK, (WindowMsgData)window, s->maxVal);
				return MSG_HANDLED;
			}

			if (childPosition.y <= y)
			{
				child->winSetPosition(0, 0);
				s->position = s->maxVal;
			}
			else if (childPosition.y >= y + size.y - childSize.y)
			{
				child->winSetPosition(0, size.y - childSize.y);
				s->position = s->minVal;
			}
			else
			{
				delta = childPosition.y - y;

				// Calc slider position
				s->position = (Int)(delta / s->numTicks);

				if (s->position > s->maxVal)
					s->position = s->maxVal;

				// Invert slider position so that maxval is at the top
				s->position = s->maxVal - s->position;
			}

			// tell owner i moved
			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
				GSM_SLIDER_TRACK, (WindowMsgData)window, s->position);
			break;
		}

		case GSM_SET_SLIDER:
		{
			Int newPos = (Int)mData1;
			GameWindow *child = window->winGetChild();

			if (newPos < s->minVal || newPos > s->maxVal)
				break;

			s->position = newPos;

			// Translate to window coords
			newPos = (Int)((s->maxVal - newPos) * s->numTicks);

			child->winSetPosition(0, newPos);
			break;
		}

		case GSM_SET_MIN_MAX:
		{
			Int newPos;
			ICoord2D size;
			GameWindow *child = window->winGetChild();

			window->winGetSize(&size.x, &size.y);

			s->minVal = (Int)mData1;
			s->maxVal = (Int)mData2;
			s->numTicks = (Real)(size.y - GADGET_SIZE) / (Real)(s->maxVal - s->minVal);
			s->position = s->minVal;

			// Translate to window coords
			newPos = (Int)((s->maxVal - s->minVal) * s->numTicks);

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
				thumb->winSetPosition(0, (Int)((s->maxVal - s->position) * s->numTicks));
			}
			break;
		}

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
