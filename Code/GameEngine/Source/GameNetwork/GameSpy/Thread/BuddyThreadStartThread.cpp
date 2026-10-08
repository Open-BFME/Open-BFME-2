// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?startThread@GameSpyBuddyMessageQueue@@UAEXXZ, retail 0x00550FDD..0x0055106D
// (144 bytes, EH): Zero Hour's GameSpyBuddyMessageQueue::startThread
// (BuddyThread.cpp) in its BFME 2 form, slot 1 of the queue's vtable. Only a
// queue without a thread acts: the +0x70 holder (rowed set 0x000998EA) takes
// a new lock on the +0x68 mutex with no timeout (rowed MutexClass::LockClass
// 0x00613A70), the thread is created on that mutex (0x00550F01, not yet
// rowed; pinned), executed (its slot 1) and started (rowed 0x005505E3). The
// unit BuddyThread.cpp keeps Zero Hour's thread class without the mutex
// argument, so this body lives apart with a minimal view.

class MutexClass
{
public:
	class LockClass
	{
	public:
		LockClass(MutexClass &mutex, int time);
	private:
		MutexClass *m_mutex;
		int m_failed;
	};
private:
	void *m_handle;
	int m_locked;
};

class Rva0009990D
{
public:
	void set(void *lock);
};

class Rva005505E3
{
public:
	void rva005505E3();
};

class BuddyThreadClass
{
public:
	BuddyThreadClass(MutexClass *mutex);
	virtual void t0();
	virtual void Execute();
private:
	unsigned char m_pad04[0xAC - 0x04];
};

class GameSpyBuddyMessageQueue
{
public:
	virtual ~GameSpyBuddyMessageQueue();
	virtual void startThread();
private:
	unsigned char m_pad04[0x64 - 0x04];
	BuddyThreadClass *m_thread;				// +0x64
	MutexClass m_mutex68;					// +0x68
	Rva0009990D m_lock70;					// +0x70
};

void GameSpyBuddyMessageQueue::startThread()
{
	if (!m_thread)
	{
		m_lock70.set(new MutexClass::LockClass(m_mutex68, -1));
		m_thread = new BuddyThreadClass(&m_mutex68);
		m_thread->Execute();
		reinterpret_cast<Rva005505E3 *>(m_thread)->rva005505E3();
	}
}
