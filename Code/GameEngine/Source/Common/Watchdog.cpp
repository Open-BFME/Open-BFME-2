// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX -ICode/Libraries/Source/WWVegas/WW3D2 -ICode/Libraries/Source/WWVegas/WWLib -ICode/Libraries/Source/WWVegas/WWMath -ICode/Libraries/Source/WWVegas/WWSaveLoad -ICode/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/shims/sweep

typedef unsigned long UnsignedInt;

// platformsdk
#include <windows.h>
#undef near
#undef far
#include <time.h>

class WatchdogCriticalSection
{
private:
	char m_storage[0x18];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/thread.h
// Destructor-only base view; the complete Watchdog primary table is declared
// below from retail BE6FD8, independently of provisional base method names.
#include "../../../Libraries/Source/WWVegas/WWLib/ThreadClass.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/mutex.h
class MutexClass
{
public:
	MutexClass(const char *name);

	class LockClass
	{
	public:
		LockClass(MutexClass &mutex, int timeout);
		~LockClass();

private:
		MutexClass &m_mutex;
		bool m_failed;
	};

private:
	void *m_handle;
	unsigned int m_locked;
};

class Watchdog : public ThreadClass
{
public:
	Watchdog(int timeout, int warningInterval, int warningDelay);
	virtual ~Watchdog();
	virtual void start(void);
	virtual void Thread_Function(void);
	virtual void reportWatchdog(void);
	void stop(void);

private:
	UnsignedInt m_parentThreadId;
	long m_lastHeartbeat;
	int m_timeout;
	UnsignedInt m_previousWarning;
	UnsignedInt m_warningInterval;
	UnsignedInt m_warningDelay;
	UnsignedInt m_nextWarning;
	int m_suppressionCount;
	WatchdogCriticalSection m_criticalSection;
	MutexClass m_mutex;
	MutexClass::LockClass *m_ownedLock;
};

Watchdog *createWatchdog(int timeout, int warningInterval, int warningDelay)
{
	return new Watchdog(timeout, warningInterval, warningDelay);
}

Watchdog::Watchdog(int timeout, int warningInterval, int warningDelay) :
	ThreadClass(0),
	m_parentThreadId(ThreadClass::_Get_Current_Thread_ID()),
	m_timeout(timeout),
	m_previousWarning(0),
	m_warningInterval(warningInterval),
	m_warningDelay(warningDelay),
	m_nextWarning(0),
	m_suppressionCount(0),
	m_mutex((*(volatile long *)&m_lastHeartbeat = 0, (const char *)0))
{
	*(MutexClass::LockClass *volatile *)&m_ownedLock = 0;
	if (*(volatile int *)&m_timeout <= 0)
	{
		m_timeout = 1;
	}
	InitializeCriticalSection((CRITICAL_SECTION *)&m_criticalSection);
}

// Counter suppression and heartbeat refresh (0x00225476, 0x00225492,
// 0x00225699) are rowed in Main/BfmeDfe6e4.cpp under a placeholder class
// identity that remains to be reconciled with Watchdog.
// Watchdog::stop: defined in Main/BfmeDfe6e4.cpp (its row's unit).
