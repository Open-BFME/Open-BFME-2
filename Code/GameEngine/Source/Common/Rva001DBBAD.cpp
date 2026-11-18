// cl: /DNDEBUG /MD /EHsc
// platformsdk
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "../../../Libraries/Include/Lib/ICoord2D.h"

// The scoped lock whose out-of-line pair retail keeps at 0x001DBA85 (constructor, rowed
// as Rva001DBA85 in GapBodiesGE49.cpp) and 0x001DBA9B (destructor: push [ecx]; call
// LeaveCriticalSection; ret). Retail's unwind funclets for this unit's guarded functions
// jump to 0x001DBA9B (0x00769881, 0x007698DC). It is not CriticalSectionLock, whose
// destructor 0x0061FC60 (mov eax,[ecx]; push eax) only the nine funclets at
// 0x007A7513..0x007A76C3 reach.
class Rva001DBA85
{
public:
	CRITICAL_SECTION *m_cs;
	Rva001DBA85(CRITICAL_SECTION *cs) : m_cs(cs) { EnterCriticalSection(m_cs); }
	~Rva001DBA85() { LeaveCriticalSection(m_cs); }
};

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
	Rva001DBA85 lock(&m_cs);
	--m_lockCount;
	if (m_lockCount <= 0)
		::regainFocus();
}

void Rva001DBAA4::setCoords(const ICoord2D *c1, const ICoord2D *c2)
{
	m_coord1 = *c1;
	m_coord2 = *c2;
}
