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

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/buddythread /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork/GameSpy/Thread /Ireference/shims/bfmealloc
// stlport
// Native 0x00550F01..0x00550FDA (220B, RET4). Constructed by the matched
// ?startThread@GameSpyBuddyMessageQueue@@UAEXXZ at 0x00551022:
// `push 0xac; call operator new; ... call 0x00550F01` on the queue's +0x68
// mutex. Base ThreadClass(0) (rowed 0x00610430, 0x50-byte layout), vtable
// 0x00C6AC0C (deleting dtor row 0x00551323), five 12-byte basic_string
// members at +0x60 (rowed 0x00007850), the mutex at +0x9C (<- +0x68),
// CriticalSectionClass at +0xA0 (rowed 0x00613AE0) and the lock owner at
// +0xA8 holding `new LockClass(m_lock)` (rowed 0x00613B60 + setter 0x005509AF).
#define THREAD_H
class ThreadClass
{
public:
	ThreadClass(const char *name);
	void Stop();
	virtual ~ThreadClass();
	virtual void Execute();
protected:
	virtual void Thread_Function() = 0;
private:
	char m_name[0x40]; // +0x04
	unsigned int m_threadId; // +0x44
	void *m_handle; // +0x48
	int m_priority; // +0x4C
};

#define _STLP_USE_NEWALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <string>

// Use the existing byte-matched narrow-string constructor.
namespace _STL {
template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string();
// Bind constructor unwind cleanup to the existing native string destructor.
template <> basic_string<char, char_traits<char>, allocator<char> >::~basic_string();
}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > BfmeStateString;

class MutexClass;

#include "PreRTS.h"
#include "GameNetwork/GameSpy/BuddyThread.h"
#include "mutex.h"
class Rva00550995Owner
{
public:
	Rva00550995Owner() : m_lock(0) {}
	void clearLock();
public:
	void rva005509AF(CriticalSectionClass::LockClass *newLock);
private:
	CriticalSectionClass::LockClass *m_lock;
public:
	~Rva00550995Owner() { clearLock(); }
};


class BuddyThreadClass : public ThreadClass
{

public:
	BuddyThreadClass(MutexClass *mutex);
	// Retail C6AC0C slot 1 inherits ThreadClass::Execute (6104B0).

protected:
	void Thread_Function();
public:

	void errorCallback( GPConnection *con, GPErrorArg *arg );
	void messageCallback( GPConnection *con, GPRecvBuddyMessageArg *arg );
	void connectCallback( GPConnection *con, GPConnectResponseArg *arg );
	void requestCallback( GPConnection *con, GPRecvBuddyRequestArg *arg );
	void statusCallback( GPConnection *con, GPRecvBuddyStatusArg *arg );
	void rva00550720( GPConnection *con, GPRecvBuddyRequestArg *arg );

	Bool isConnecting( void ) { return m_isConnecting; }
	Bool isConnected( void ) { return m_isConnected; }

	GPProfile getLocalProfileID( void ) { return m_profileID; }

private:
	Bool m_isNewAccount;
	Bool m_isConnecting;
	Bool m_isConnected;
	GPProfile m_profileID;
	Int m_lastErrorCode;
	Bool m_isdeleting;
	std::string m_nick, m_email, m_pass;
	std::string m_s3, m_s4;
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
