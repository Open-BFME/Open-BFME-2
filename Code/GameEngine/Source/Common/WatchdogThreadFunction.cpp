// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// ?Thread_Function@Watchdog@@UAEXXZ @0x002254CA 227B
// Evidence: vtable slot 2 of 0x007E6FD8; BFME1 donor Code/GameEngine/Source/Common/Watchdog_Thread_Function.cpp; callees rowed Mutex LockClass; virtual call slot 3 reportWatchdog.

typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) long __cdecl time(long *value);
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void *section);

class MutexClass
{
public:
	~MutexClass();

	class LockClass
	{
	public:
		LockClass(MutexClass &mutex, int timeout);
		~LockClass();
		bool Failed() const { return m_failed; }

	private:
		MutexClass &m_mutex;
		bool m_failed;
	};

private:
	void *m_handle;
	unsigned int m_locked;
};

class WatchdogCriticalSection
{
public:
	void enter()
	{
		EnterCriticalSection(this);
	}

	void leave()
	{
		LeaveCriticalSection(this);
	}

private:
	char m_storage[0x18];
};

class ScopedWatchdogLock
{
public:
	ScopedWatchdogLock(WatchdogCriticalSection &section) : m_section(section)
	{
		m_section.enter();
	}

	~ScopedWatchdogLock()
	{
		m_section.leave();
	}

private:
	WatchdogCriticalSection &m_section;
};

class Rva0009990D
{
public:
	void clear();
	void set(void *p);

private:
	void *m_lock;
};

class ThreadClass
{
public:
	virtual ~ThreadClass();
	void Stop();
	virtual void Execute();
};

class Watchdog
{
public:
	virtual ~Watchdog();
	virtual void start();
	virtual void Thread_Function();
	virtual void reportWatchdog();
	void stop();

private:
	char m_threadClass[0x4c];
	UnsignedInt m_parentThreadId;
	long m_lastHeartbeat;
	int m_timeout;
	long m_previousWarning;
	long m_warningInterval;
	long m_warningDelay;
	long m_nextWarning;
	int m_suppressionCount;
	WatchdogCriticalSection m_criticalSection;
	char m_mutexStorage[8];
	Rva0009990D m_ownedLock;
};

void Watchdog::Thread_Function()
{
	for (;;)
	{
		MutexClass::LockClass lock(*(MutexClass *)&m_mutexStorage, 1000);
		if (!lock.Failed())
			break;

		long lastHeartbeat;
		int suppressionCount;
		{
			ScopedWatchdogLock criticalSectionLock(m_criticalSection);
			lastHeartbeat = m_lastHeartbeat;
			suppressionCount = m_suppressionCount;
		}

		long now;
		time(&now);
		if (suppressionCount < 0 && now >= m_nextWarning)
		{
			if (now - m_previousWarning > m_warningInterval)
			{
				long newWarning = now + m_warningDelay;
				m_nextWarning = newWarning;
				m_previousWarning = newWarning;
			}
			else
			{
				if (lastHeartbeat != 0 && lastHeartbeat < now)
				{
					long heartbeatDelta = now - lastHeartbeat;
					if (heartbeatDelta > m_timeout)
					{
						reportWatchdog();
					}
				}
				m_previousWarning = now;
			}
		}
	}
}

void Watchdog::stop(void)
{
	m_ownedLock.clear();
	((ThreadClass *)this)->Stop();
}

void Watchdog::start(void)
{
	MutexClass::LockClass *lock = new MutexClass::LockClass(*(MutexClass *)&m_mutexStorage, -1);
	m_ownedLock.set(lock);
	((ThreadClass *)this)->ThreadClass::Execute();
}

// BFME1 semantic donor 575ba2b04743f190f069805fbdc59936123c45da:
// game/GameEngine/Source/Common/WatchdogReport.cpp. Target slot 3 and
// WB12AB0C0 OnDeadThread independently establish the diagnostic/rethrow.
// Native2255AD..225616 proves parent id50, 512-byte format buffer and
// debug slots60/6C(three ints)/38/4C; original BFME2 class naming differs
// from the existing Watchdog view, retained here without an owner rename.
class Debug
{
public:
	class Format
	{
	public:
		explicit Format(const char *format, ...);
		operator const char *() const { return m_buffer; }

	private:
		char m_buffer[512];
	};
};

class BfmeAwakenLog
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual BfmeAwakenLog *slot4C(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second, int third);
};

// Existing owned pointer cell; the original singleton class type is unproven.
extern Debug *theDebug;
bool __cdecl bfmeRva000387C0();
extern void _bfme_debugRecordCallsite(int kind);


void Watchdog::reportWatchdog()
{
	if (bfmeRva000387C0())
	{
		_bfme_debugRecordCallsite(1);
		reinterpret_cast<BfmeAwakenDebug *>(theDebug)->slot60();
		BfmeAwakenLog *log = reinterpret_cast<BfmeAwakenDebug *>(theDebug)->slot6C(0, 0, 0);
		log->slot38(Debug::Format("Watchdog: Parent thread (ID %d) has stopped responding.\n\n"
			"I'm going to force a crash; please report it.", m_parentThreadId));
		log->slot4C(2);
	}
	throw;
}
