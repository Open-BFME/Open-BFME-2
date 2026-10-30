// ??0BuddyThreadClass@@QAE@PAVMutexClass@@@Z, retail 0x00550F01 (220B RET4).
// Constructed by the matched ?startThread@GameSpyBuddyMessageQueue@@UAEXXZ
// (0x00551022 `push 0xac; call operator new; ... call 0x00550F01`) on the
// queue's +0x68 mutex, so the size (0xAC), ctor address and MutexClass*
// argument are all caller-proven. Base ThreadClass(0) (rowed 0x00610430,
// 0x50-byte layout), vtable 0x00C6AC0C (deleting dtor row 0x00551323),
// five 12-byte default-constructed string members at +0x60 (rowed 0x00007850),
// the mutex at +0x9C, CriticalSectionClass at +0xA0 (rowed 0x00613AE0) and
// the lock owner at +0xA8 taking `new LockClass(m_lock)` (rowed 0x00613B60,
// setter 0x005509AF). The body store order is the retail-measured order.

// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Native 0x00550F01..0x00550FDA (220B, RET4). Constructed by the matched
// ?startThread@GameSpyBuddyMessageQueue@@UAEXXZ at 0x00551022:
// `push 0xac; call operator new; ... call 0x00550F01` on the queue's +0x68
// mutex. Base ThreadClass(0) (rowed 0x00610430, 0x50-byte layout), vtable
// 0x00C6AC0C (deleting dtor row 0x00551323), five 12-byte basic_string
// members at +0x60 (rowed 0x00007850), the mutex at +0x9C (<- +0x68),
// CriticalSectionClass at +0xA0 (rowed 0x00613AE0) and the lock owner at
// +0xA8 holding `new LockClass(m_lock)` (rowed 0x00613B60 + setter 0x005509AF).
#include <string>

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > BfmeStateString;

class MutexClass;

class CriticalSectionClass
{
public:
	CriticalSectionClass();
	~CriticalSectionClass();
	class LockClass
	{
	public:
		LockClass(CriticalSectionClass &owner);
	private:
		void *m_ptr;
	};
private:
	char m_pad[8];
};

class Rva00550995Owner
{
public:
	Rva00550995Owner() : m_ptr(0) {}
	~Rva00550995Owner();
	void rva005509AF(CriticalSectionClass::LockClass *lock);
private:
	CriticalSectionClass::LockClass *m_ptr;
};

class ThreadClass
{
public:
	ThreadClass(const char *name);
	virtual ~ThreadClass();
	virtual void Execute();
protected:
	virtual void Thread_Function() = 0;
private:
	char m_name[0x40];
	unsigned int m_threadId;
	void *m_handle;
	int m_priority;
};

class BuddyThreadClass : public ThreadClass
{
public:
	BuddyThreadClass(MutexClass *mutex);
	// Retail C6AC0C slot 1 inherits ThreadClass::Execute (6104B0).
protected:
	void Thread_Function();
private:
	bool m_isNewAccount;
	bool m_isConnecting;
	bool m_isConnected;
	int m_profileID;
	int m_lastErrorCode;
	bool m_isdeleting;
	BfmeStateString m_s0, m_s1, m_s2, m_s3, m_s4;
	MutexClass *m_mutex;
	CriticalSectionClass m_lock;
	Rva00550995Owner m_owner;
};

BuddyThreadClass::BuddyThreadClass(MutexClass *mutex)
	: ThreadClass(0), m_mutex(mutex)
{
	m_isConnected = false;
	m_isConnecting = false;
	m_isdeleting = false;
	m_isNewAccount = false;
	m_profileID = 0;
	m_lastErrorCode = 0;
	m_owner.rva005509AF(new CriticalSectionClass::LockClass(m_lock));
}
