// cl: /O1 /DNDEBUG /MD /EHsc
// Win32Mouse::addWin32Event, retail 0x00041A10 (115 bytes).
//
// The event ring sits immediately after the 0x5010-byte Mouse base
// (read off retail: index is at this+0x6010, slot i at this+0x5010+16*i).
// This TU keeps that known base layout local so the existing device sources
// need not pay a shared-header gate. Same shape as the BFME1 conversion,
// which matched verbatim apart from the base size.

typedef unsigned int UINT;
typedef unsigned int WPARAM;
typedef long LPARAM;
typedef unsigned long DWORD;

class Mouse
{
public:
	virtual ~Mouse();

private:
	char m_base[0x5010 - 4];
};

class Win32Mouse : public Mouse
{
public:
	void addWin32Event(UINT msg, WPARAM wParam, LPARAM lParam, DWORD time);

private:
	struct Win32MouseEvent
	{
		UINT msg;
		WPARAM wParam;
		LPARAM lParam;
		DWORD time;
	};

	Win32MouseEvent m_eventBuffer[256];
	unsigned int m_nextFreeIndex;
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
