// cl: /DNDEBUG /MD /EHsc
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct ICoord2D
{
	int x;
	int y;
};

#pragma optimize("t", on)
class CriticalSectionLock
{
public:
	CRITICAL_SECTION *m_cs;
	CriticalSectionLock(CRITICAL_SECTION *cs) : m_cs(cs) { EnterCriticalSection(m_cs); }
	~CriticalSectionLock() { LeaveCriticalSection(m_cs); }
};
#pragma optimize("", on)

void regainFocus();

#pragma comment(linker, "/alternatename:?regainFocus@@YAXXZ=?regainFocusThunk@AudioManager@@QAEXXZ")

class Rva001DBAA4
{
public:
	char m_pad[0x20];
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_lockCount;
	CRITICAL_SECTION m_cs;
	bool m_isCsInitialized;
	char m_pad51[3];
	ICoord2D m_coord1;
	ICoord2D m_coord2;

	virtual void init();
	void lock();
	void unlock();
	void regainFocus();
	void setCoords(const ICoord2D *c1, const ICoord2D *c2);
};

void Rva001DBAA4::init()
{
	m_24 = 0;
	m_28 = 0;
	m_2C = 0;
	m_30 = 0;
	if (!m_isCsInitialized)
	{
		InitializeCriticalSection(&m_cs);
		m_isCsInitialized = true;
	}
}

void Rva001DBAA4::lock()
{
	EnterCriticalSection(&m_cs);
	++m_lockCount;
	LeaveCriticalSection(&m_cs);
}

void Rva001DBAA4::regainFocus()
{
	::regainFocus();
}

void Rva001DBAA4::unlock()
{
	CriticalSectionLock lock(&m_cs);
	--m_lockCount;
	if (m_lockCount <= 0)
		::regainFocus();
}

void Rva001DBAA4::setCoords(const ICoord2D *c1, const ICoord2D *c2)
{
	m_coord1 = *c1;
	m_coord2 = *c2;
}
