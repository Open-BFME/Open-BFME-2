// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/buddythread /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork/GameSpy/Thread /Ireference/shims/bfmealloc
// stlport
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

#include "PreRTS.h"
#include "GameNetwork/GameSpy/BuddyThread.h"
#include "mutex.h"
#include <queue>
typedef std::queue<BuddyRequest> RequestQueue;
typedef std::queue<BuddyResponse> ResponseQueue;

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

class Rva0009990D
{
public:
	void clear();
	~Rva0009990D(){clear();}
	void set(void *p);
	MutexClass::LockClass *m_ptr; // +0x00
};

class Rva005505E3
{
public:
	void rva005505E3();
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

class GameSpyBuddyMessageQueue : public GameSpyBuddyMessageQueueInterface
{
public:
	virtual ~GameSpyBuddyMessageQueue();
	GameSpyBuddyMessageQueue();
	virtual void startThread( void );
	virtual void endThread( void );
	virtual Bool isThreadRunning( void );
	virtual Bool isConnected( void );
	virtual Bool isConnecting( void );

	virtual void addRequest( const BuddyRequest& req );
	virtual Bool getRequest( BuddyRequest& req );

	virtual void addResponse( const BuddyResponse& resp );
	virtual Bool getResponse( BuddyResponse& resp );

	virtual GPProfile getLocalProfileID( void );

	BuddyThreadClass* getThread( void ) { return m_thread; }

private:
	MutexClass m_requestMutex;
	MutexClass m_responseMutex;
	RequestQueue m_requests;
	ResponseQueue m_responses;
	BuddyThreadClass *m_thread;
	MutexClass m_bfme_rva0063e080_mutex68;
	Rva0009990D m_bfme_lock70;
};

void GameSpyBuddyMessageQueue::startThread()
{
	if (!m_thread)
	{
		m_bfme_lock70.set(new MutexClass::LockClass(m_bfme_rva0063e080_mutex68, -1));
		m_thread = new BuddyThreadClass(&m_bfme_rva0063e080_mutex68);
		m_thread->Execute();
		reinterpret_cast<Rva005505E3 *>(m_thread)->rva005505E3();
	}
}
