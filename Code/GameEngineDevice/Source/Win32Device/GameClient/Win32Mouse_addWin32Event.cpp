// cl: /DNDEBUG /MD /EHsc
// platformsdk
// Win32Mouse::addWin32Event, retail 0x00041A10 (115 bytes).
//
// The event ring sits immediately after the 0x5010-byte Mouse base
// (read off retail: index is at this+0x6010, slot i at this+0x5010+16*i).
// This TU keeps that known base layout local so the existing device sources
// need not pay a shared-header gate. Same shape as the BFME1 conversion,
// which matched verbatim apart from the base size.

#include <windows.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

struct MouseIO;

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

private:
	char m_base[0x5010 - 4];
};

class Win32Mouse : public Mouse
{
public:
	Win32Mouse(void);
	virtual ~Win32Mouse(void);
	virtual void update(void);
	virtual void initCursorResources(void);
	virtual void setCursor(MouseCursor cursor);
	void addWin32Event(UINT msg, WPARAM wParam, LPARAM lParam, DWORD time);

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

void Win32Mouse::addWin32Event(UINT msg, WPARAM wParam, LPARAM lParam, DWORD time)
{
	if (m_eventBuffer[m_nextFreeIndex].msg != 0)
		return;

	m_eventBuffer[m_nextFreeIndex].msg = msg;
	m_eventBuffer[m_nextFreeIndex].wParam = wParam;
	m_eventBuffer[m_nextFreeIndex].lParam = lParam;
	m_eventBuffer[m_nextFreeIndex].time = time;

	++m_nextFreeIndex;
	if (m_nextFreeIndex >= 256)
		m_nextFreeIndex = 0;
}
