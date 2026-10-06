// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/sweep
//
// Win32Mouse bodies from Zero Hour's Win32Mouse.cpp (GeneralsMD), with the
// BFME 1 conversions in reference/open-bfme-1/game/GameEngineDevice/Source/
// Win32Device/GameClient/Win32Mouse_*.cpp as the shape donors.
//
//   0x00041839 translateEvent       317B  switch on msg-0x200, table after the ret
//   0x00041976 Win32Mouse            89B  Mouse ctor 0x001EEC97, memset, cursor table
//   0x000419E3 ~Win32Mouse           18B  clears TheWin32Mouse, tail jump to ~Mouse 0x001EE3DE
//   0x00041A0B update                 5B  tail jump to Mouse::update 0x001EDE3A
//   0x00041A83 setCursor             81B  Mouse::setCursor 0x001EEFD2, then SetCursor
//   0x00041B10 getMouseEvent         89B  calls translateEvent 0x00041839
//   0x00041BA6 initCursorResources  323B  "data\cursors\%s%d.%s" / "%s.%s", ".cur"
//
// Target layout, read off these bodies and the rowed addWin32Event/reset:
// Mouse holds CursorInfo m_cursorInfo[0x38] (stride 0x54) from +0x0C and
// m_currentCursor at +0x4FA4; Win32Mouse's event ring starts at +0x5010 and is
// followed by m_nextFreeIndex +0x6010, m_nextGetIndex +0x6014,
// m_currentWin32Cursor +0x6018, m_directionFrame +0x601C, m_lostFocus +0x6020.
// cursorResources[0x38][8] is the HCURSOR table at VA 0x00DE1418 (the outer
// loop of initCursorResources stops at 0x00DE1B18). TheGameClient's frame is
// its slot 0x7C virtual, as in the other BFME 2 users of 0x00DFE77C.
// BFME 2 tests the cursor through Mouse 0x001EDE26 where Zero Hour read
// m_visible, and keeps BFME 1's ani/cur extension choice.

#include <windows.h>
#include <stdio.h>
#include <string.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef short Short;
typedef bool Bool;
typedef float Real;

class Win32Mouse;

template<class T> class StringBase
{
	struct Header { int refs; unsigned short length, capacity; T data[1]; };
	Header *m_data;
	StringBase(const StringBase &);
	void releaseBuffer();
	friend class Win32Mouse;
public:
	~StringBase() { releaseBuffer(); }
	bool isEmpty() const;
	bool endsWithNoCase(const T *) const;
	void removeLastChar();
	const T *str() const { return m_data ? m_data->data : ""; }
};
typedef StringBase<char> AsciiString;

struct ICoord2D
{
	Int x;
	Int y;
};

struct RGBAColorInt
{
	Int red, green, blue, alpha;
};

struct CursorInfo
{
	AsciiString cursorName;
	AsciiString cursorText;
	RGBAColorInt cursorTextColor;
	RGBAColorInt cursorTextDropColor;
	AsciiString textureName;
	AsciiString imageName;
	AsciiString W3DModelName;
	AsciiString W3DAnimName;
	Real W3DScale;
	Bool loop;
	ICoord2D hotSpotPosition;
	Int numFrames;
	Real fps;
	Int numDirections;
};

enum MouseButtonState
{
	MBS_Up = 0,
	MBS_Down,
	MBS_DoubleClick
};

struct MouseIO
{
	ICoord2D pos;
	UnsignedInt time;
	Int wheelPos;
	ICoord2D deltaPos;
	MouseButtonState leftState;
	Int leftEvent;
	Int leftFrame;
	MouseButtonState rightState;
	Int rightEvent;
	Int rightFrame;
	MouseButtonState middleState;
	Int middleEvent;
	Int middleFrame;
};

#define MOUSE_NONE 0x00
#define MOUSE_OK 0x01

class GameClient
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E();
	virtual UnsignedInt getFrame();
};
extern GameClient *TheGameClient;
extern HWND ApplicationHWnd;

class Mouse
{
public:
	enum MouseCursor
	{
		NONE = 0,
		FIRST_CURSOR = 1,
		NUM_MOUSE_CURSORS = 0x38
	};
	enum { NUM_MOUSE_EVENTS = 256 };

	Mouse(void);
	virtual ~Mouse();
	virtual void update(void);
	virtual void setCursor(MouseCursor cursor);
	bool rva001EDE26() const;

protected:
	char m_pad004[0x0C - 4];
	CursorInfo m_cursorInfo[NUM_MOUSE_CURSORS];
	char m_pad126C[0x4FA4 - 0x126C];
	MouseCursor m_currentCursor;
	char m_pad4FA8[0x5010 - 0x4FA8];
};

HCURSOR cursorResources[Mouse::NUM_MOUSE_CURSORS][8];

class Win32Mouse : public Mouse
{
public:
	Win32Mouse(void);
	virtual ~Win32Mouse(void);
	virtual void update(void);
	virtual void initCursorResources(void);
	virtual void setCursor(MouseCursor cursor);

protected:
	virtual UnsignedByte getMouseEvent(MouseIO *result, Bool flush);
	void translateEvent(UnsignedInt eventIndex, MouseIO *result);

	struct Win32MouseEvent
	{
		UINT msg;
		WPARAM wParam;
		LPARAM lParam;
		DWORD time;
	};
	Win32MouseEvent m_eventBuffer[Mouse::NUM_MOUSE_EVENTS];
	UnsignedInt m_nextFreeIndex;
	UnsignedInt m_nextGetIndex;
	MouseCursor m_currentWin32Cursor;
	Int m_directionFrame;
	Bool m_lostFocus;
};

#define MAX_2D_CURSOR_DIRECTIONS 8

Win32Mouse::Win32Mouse(void)
{
	// zero our event list
	memset(&m_eventBuffer, 0, sizeof(m_eventBuffer));
	m_nextFreeIndex = 0;
	m_nextGetIndex = 0;
	m_currentWin32Cursor = NONE;
	for (Int i = 0; i < NUM_MOUSE_CURSORS; i++)
		for (Int j = 0; j < MAX_2D_CURSOR_DIRECTIONS; j++)
			cursorResources[i][j] = NULL;
	m_directionFrame = 0; // points up.
	m_lostFocus = FALSE;
}

extern Win32Mouse *TheWin32Mouse;

Win32Mouse::~Win32Mouse(void)
{
	// remove our global reference
	TheWin32Mouse = NULL;
}

UnsignedByte Win32Mouse::getMouseEvent(MouseIO *result, Bool flush)
{
	if (m_eventBuffer[m_nextGetIndex].msg == 0)
		return MOUSE_NONE;

	translateEvent(m_nextGetIndex, result);

	m_eventBuffer[m_nextGetIndex].msg = 0;

	m_nextGetIndex++;
	if (m_nextGetIndex >= Mouse::NUM_MOUSE_EVENTS)
		m_nextGetIndex = 0;

	return MOUSE_OK;
}

void Win32Mouse::translateEvent(UnsignedInt eventIndex, MouseIO *result)
{
	UINT msg = m_eventBuffer[eventIndex].msg;
	WPARAM wParam = m_eventBuffer[eventIndex].wParam;
	LPARAM lParam = m_eventBuffer[eventIndex].lParam;
	UnsignedInt frame;

	if (TheGameClient)
		frame = TheGameClient->getFrame();
	else
		frame = 1;

	result->leftState = result->middleState = result->rightState = MBS_Up;
	result->leftFrame = result->middleFrame = result->rightFrame = 0;
	result->pos.x = result->pos.y = result->wheelPos = 0;
	result->time = m_eventBuffer[eventIndex].time;

	switch (msg)
	{
		case WM_LBUTTONDOWN:
		{
			result->leftState = MBS_Down;
			result->leftFrame = frame;
			result->pos.x = LOWORD(lParam);
			result->pos.y = HIWORD(lParam);
			break;
		}

		case WM_LBUTTONUP:
		{
			result->leftState = MBS_Up;
			result->leftFrame = frame;
			result->pos.x = LOWORD(lParam);
			result->pos.y = HIWORD(lParam);
			break;
		}

		case WM_LBUTTONDBLCLK:
		{
			result->leftState = MBS_DoubleClick;
			result->leftFrame = frame;
			result->pos.x = LOWORD(lParam);
			result->pos.y = HIWORD(lParam);
			break;
		}

		case WM_MBUTTONDOWN:
		{
			result->middleState = MBS_Down;
			result->middleFrame = frame;
			result->pos.x = LOWORD(lParam);
			result->pos.y = HIWORD(lParam);
			break;
		}

		case WM_MBUTTONUP:
		{
			result->middleState = MBS_Up;
			result->middleFrame = frame;
			result->pos.x = LOWORD(lParam);
			result->pos.y = HIWORD(lParam);
			break;
		}

		case WM_MBUTTONDBLCLK:
		{
			result->middleState = MBS_DoubleClick;
			result->middleFrame = frame;
			result->pos.x = LOWORD(lParam);
			result->pos.y = HIWORD(lParam);
			break;
		}

		case WM_RBUTTONDOWN:
		{
			result->rightState = MBS_Down;
			result->rightFrame = frame;
			result->pos.x = LOWORD(lParam);
			result->pos.y = HIWORD(lParam);
			break;
		}

		case WM_RBUTTONUP:
		{
			result->rightState = MBS_Up;
			result->rightFrame = frame;
			result->pos.x = LOWORD(lParam);
			result->pos.y = HIWORD(lParam);
			break;
		}

		case WM_RBUTTONDBLCLK:
		{
			result->rightState = MBS_DoubleClick;
			result->rightFrame = frame;
			result->pos.x = LOWORD(lParam);
			result->pos.y = HIWORD(lParam);
			break;
		}

		case WM_MOUSEMOVE:
		{
			result->pos.x = LOWORD(lParam);
			result->pos.y = HIWORD(lParam);
			break;
		}

		case 0x020A:	// WM_MOUSEWHEEL
		{
			POINT p;

			p.x = LOWORD(lParam);
			p.y = HIWORD(lParam);
			ScreenToClient(ApplicationHWnd, &p);
			result->wheelPos = (Short)HIWORD(wParam);
			result->pos.x = p.x;
			result->pos.y = p.y;
			break;
		}
	}
}

void Win32Mouse::update(void)
{
	// extend
	Mouse::update();
}

void Win32Mouse::setCursor(MouseCursor cursor)
{
	// extend
	Mouse::setCursor(cursor);

	// if we're lost, don't do anything
	if (m_lostFocus)
		return;

	if (cursor == NONE || !rva001EDE26())
		SetCursor(NULL);
	else
		SetCursor(cursorResources[cursor][m_directionFrame]);

	m_currentWin32Cursor = m_currentCursor = cursor;
}

void Win32Mouse::initCursorResources(void)
{
	for (Int cursor = FIRST_CURSOR; cursor < NUM_MOUSE_CURSORS; cursor++)
	{
		for (Int direction = 0; direction < m_cursorInfo[cursor].numDirections; direction++)
		{
			if (!cursorResources[cursor][direction] && !m_cursorInfo[cursor].textureName.isEmpty())
			{
				char resourcePath[256];
				const char *extension = "ani";
				AsciiString baseName(m_cursorInfo[cursor].textureName);

				if (baseName.endsWithNoCase(".cur"))
				{
					extension = "cur";
					baseName.removeLastChar();
					baseName.removeLastChar();
					baseName.removeLastChar();
					baseName.removeLastChar();
				}

				if (m_cursorInfo[cursor].numDirections > 1)
					sprintf(resourcePath, "data\\cursors\\%s%d.%s", baseName.str(), direction, extension);
				else
					sprintf(resourcePath, "data\\cursors\\%s.%s", baseName.str(), extension);

				cursorResources[cursor][direction] = LoadCursorFromFile(resourcePath);
			}
		}
	}
}
