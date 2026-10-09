// cl: /O1 /DNDEBUG /MD /EHsc
//
// TheGameResultsQueue's factory, constructor and startThreads, the Zero Hour
// GameResultsThread.cpp bodies (createNewGameResultsInterface, the
// GameResultsQueue constructor and GameResultsQueue::startThreads):
//   ?Rva0041AA6FCreateGameResults@@YAPAVGameResultsInterface@@XZ  0x0041AA6F  53B
//   ??0Rva0041A644@@QAE@XZ                                       0x0041A754 135B
//   ?startThreads@Rva0041A644@@UAEXXZ                            0x00419F88 135B
//
// Target evidence: GameEngine::init (GameEngineInit.cpp) registers the
// factory's result as "TheGameResultsQueue". The factory news 0x84 bytes and
// runs 0x0041A754, which builds a SubsystemInterface (0x001B4E63) and installs
// vtable 0x00C3AD70. That vtable's slots 14-21 are Zero Hour's GameResults
// order: startThreads 0x00419F88, endThreads 0x0041A00F, then six more queue
// bodies (0x00419D2A ... 0x00419D52); slot 0 is the rowed deleting dtor
// ??_GRva0041A644 (0x0041A7DB), whose class name is kept here so the two
// agree. Offsets come from the retail constructor, destructor 0x0041A644 and
// endThreads: request/response mutexes +0x0C/+0x14, queues +0x1C/+0x44,
// counts +0x6C/+0x70, worker thread +0x74, thread mutex +0x78 and the held
// thread lock +0x80. BFME's startThreads locks that mutex (new LockClass,
// handed to the +0x80 holder's set 0x000998EA) before starting the 0x54-byte
// worker 0x00419CFB, which Zero Hour does not.
//
// Names are address-derived: the decorated createNewGameResultsInterface and
// GameResultsQueue names are rowed or pinned at 0x00551B28/0x00551A94, a
// non-subsystem 0x74-byte queue, so they are not reused here.
//
// The queue members are declared views. Retail's constructor calls the
// queue ctors rowed as queue<BfmePod28> 0x0041A6D0 and queue<BfmePod16>
// 0x0041A6E5; the destructor frees them through the rowed
// deque<BfmeNarrowRecord0041A5D2>/<...0041A617> dtors, so the 28- and
// 16-byte element types carry two placeholder names in the ledger. The
// constructor's call names are used here.
void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *p);

class SubsystemInterface
{
public:
	SubsystemInterface();			// 0x001B4E63
	virtual ~SubsystemInterface();		// 0x001B4E74
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();

private:
	int m_04;
	int m_08;
};

// Vtable 0x00C3AD08: slots 14-21 are pure.
class GameResultsInterface : public SubsystemInterface
{
public:
	virtual ~GameResultsInterface() {}
	virtual void startThreads() = 0;
	virtual void endThreads() = 0;
	virtual bool areThreadsRunning() = 0;
	virtual void addRequest(const void *request) = 0;
	virtual bool getRequest(void *request) = 0;
	virtual void addResponse(const void *response) = 0;
	virtual bool getResponse(void *response) = 0;
	virtual bool areGameResultsBeingSent() = 0;
};

class MutexClass
{
public:
	MutexClass(const char *name = 0);	// 0x006139F0
	~MutexClass();				// 0x00613A20

	class LockClass
	{
	public:
		LockClass(MutexClass &mutex, int time = -1);	// 0x00613A70
		~LockClass();					// 0x00613AC0

	private:
		MutexClass &m_mutex;
		int m_failed;
	};

private:
	void *m_handle;
	int m_locked;
};

// The +0x80 lock holder (Rva0009990DSet.cpp); the destructor releases it
// through clear().
class Rva0009990D
{
public:
	Rva0009990D() : m_ptr(0) {}
	~Rva0009990D() { clear(); }
	void set(void *p);	// 0x000998EA
	void clear();		// 0x0009990D

private:
	MutexClass::LockClass *m_ptr;
};

// The 0x54-byte worker thread (Rva00419CFBConstructor.cpp); ThreadClass
// slot 1 is Execute.
class Rva00419CFB
{
public:
	Rva00419CFB(void *lock);	// 0x00419CFB
	virtual ~Rva00419CFB();
	virtual void Execute();

private:
	char m_storage[0x54 - 4];
};

struct BfmePod28;
struct BfmePod16;
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class deque;
template <class T, class C = deque<T, allocator<T> > >
class queue
{
public:
	queue();
	~queue();

private:
	char m_storage[0x28];
};
}

class Rva0041A644 : public GameResultsInterface
{
public:
	Rva0041A644();
	virtual ~Rva0041A644();			// 0x0041A644

	virtual void startThreads();
	virtual void endThreads();
	virtual bool areThreadsRunning();
	virtual void addRequest(const void *request);
	virtual bool getRequest(void *request);
	virtual void addResponse(const void *response);
	virtual bool getResponse(void *response);
	virtual bool areGameResultsBeingSent();

private:
	MutexClass m_requestMutex;			// +0x0C
	MutexClass m_responseMutex;			// +0x14
	_STL::queue<BfmePod28> m_requests;		// +0x1C
	_STL::queue<BfmePod16> m_responses;		// +0x44
	int m_requestCount;				// +0x6C
	int m_responseCount;				// +0x70
	Rva00419CFB *m_workerThreads[1];		// +0x74
	MutexClass m_threadMutex;			// +0x78
	Rva0009990D m_threadLock;			// +0x80
};

GameResultsInterface *Rva0041AA6FCreateGameResults()
{
	return new Rva0041A644;
}

Rva0041A644::Rva0041A644() : m_requestCount(0), m_responseCount(0)
{
	for (int i = 0; i < 1; ++i)
		m_workerThreads[i] = 0;
	startThreads();
}

void Rva0041A644::startThreads()
{
	endThreads();
	m_threadLock.set(new MutexClass::LockClass(m_threadMutex));
	for (int i = 0; i < 1; ++i)
	{
		m_workerThreads[i] = new Rva00419CFB(&m_threadMutex);
		m_workerThreads[i]->Execute();
	}
}
