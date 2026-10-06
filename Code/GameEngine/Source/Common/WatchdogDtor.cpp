// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// ??1Watchdog@@UAE@XZ @0x0022576A 99B
// Evidence: vtable 0x007E6FD8 slot implied by ctor 0x00225616 and deleting dtor 0x002257CD; BFME1 donor Code/GameEngine/Source/Common/WatchdogDestructor.cpp; callees rowed stop 0x00225716 and Mutex 0x00613A20 plus pinned clear 0x0009990D and ThreadClass dtor 0x00610480; caller is deleting dtor at 0x002257D0.
typedef unsigned int UnsignedInt;

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

	private:
		MutexClass &m_mutex;
		bool m_failed;
	};

private:
	void *m_handle;
	unsigned int m_locked;
};

class Rva0009990D
{
public:
	void clear();
	void set(void *p);
	~Rva0009990D() { clear(); }

private:
	void *m_lock;
};

class ThreadClass
{
public:
	ThreadClass(const char *name);
	virtual ~ThreadClass();
	void Execute(void);
	void Stop(void);
	virtual void Thread_Function(void) = 0;

private:
	char m_name[0x40];
	volatile unsigned int m_running;
	volatile unsigned long m_handle;
	int m_priority;
};

class WatchdogCriticalSection
{
public:
	void enter(void);
	void leave(void);

private:
	char m_storage[0x18];
};

class Watchdog : public ThreadClass
{
public:
	Watchdog(int timeout, int warningInterval, int warningDelay);
	virtual ~Watchdog();
	virtual void start();
	virtual void Thread_Function();
	virtual void reportWatchdog();
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
	Rva0009990D m_ownedLock;
};

Watchdog::~Watchdog()
{
	stop();
	DeleteCriticalSection(&m_criticalSection);
}
