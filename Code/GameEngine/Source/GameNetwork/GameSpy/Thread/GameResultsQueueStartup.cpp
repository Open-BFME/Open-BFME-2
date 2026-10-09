// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common
// stlport
//
// TheGameResultsQueue, the Zero Hour GameResultsThread.cpp queue bodies
// (createNewGameResultsInterface, the GameResultsQueue constructor and its
// startThreads, add/getRequest, add/getResponse, areGameResultsBeingSent):
//   ?Rva0041AA6FCreateGameResults@@YAPAVGameResultsInterface@@XZ  0x0041AA6F  53B
//   ??0Rva0041A644@@QAE@XZ                                       0x0041A754 135B
//   ?startThreads@Rva0041A644@@UAEXXZ                            0x00419F88 135B
//   ?addRequest@Rva0041A644@@...                                 0x0041ABCC  74B
//   ?getRequest@Rva0041A644@@...                                 0x0041AAA4  98B
//   ?addResponse@Rva0041A644@@...                                0x0041AC16  74B
//   ?getResponse@Rva0041A644@@...                                0x0041AB06  98B
//   ?areGameResultsBeingSent@Rva0041A644@@UAE_NXZ                0x00419D52  74B
//
// Target evidence: GameEngine::init (GameEngineInit.cpp) registers the
// factory's result as "TheGameResultsQueue". The factory news 0x84 bytes and
// runs 0x0041A754, which builds a SubsystemInterface (0x001B4E63) and installs
// vtable 0x00C3AD70. That vtable's slots 14-21 are Zero Hour's GameResults
// order: startThreads 0x00419F88, endThreads 0x0041A00F, areThreadsRunning
// 0x00419D2A, addRequest 0x0041ABCC, getRequest 0x0041AAA4, addResponse
// 0x0041AC16, getResponse 0x0041AB06, areGameResultsBeingSent 0x00419D52;
// slot 0 is the rowed deleting dtor ??_GRva0041A644 (0x0041A7DB), whose
// class name is kept here so the two agree. Offsets come from these bodies
// and destructor 0x0041A644: request/response mutexes +0x0C/+0x14, queues
// +0x1C/+0x44, counts +0x6C/+0x70, worker thread +0x74, thread mutex +0x78
// and the held thread lock +0x80. BFME's startThreads locks that mutex (new
// LockClass, handed to the +0x80 holder's set 0x000998EA) before starting
// the 0x54-byte worker 0x00419CFB, which Zero Hour does not. The get
// methods try-lock (time 0) and test the lock's failed flag at +4.
//
// Names are address-derived: the decorated createNewGameResultsInterface and
// GameResultsQueue names are rowed or pinned at 0x00551B28/0x00551A94, a
// non-subsystem 0x74-byte queue, so they are not reused here.
//
// The queue members are declared views. Retail's constructor calls the
// queue ctors rowed as queue<BfmePod28> 0x0041A6D0 and queue<BfmePod16>
// 0x0041A6E5; the destructor frees them through the rowed
// deque<BfmeNarrowRecord0041A5D2>/<...0041A617> dtors, and the push and pop
// helpers are rowed on further address-named views, so the 28- and 16-byte
// records carry several placeholder names in the ledger. Each call here uses
// the name its callee is rowed under.

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

// The request and response records (assignments 0x0041A7F7, 0x0041A820).
#include "BfmeNarrowRecord0041A5D2.h"
#include "BfmeNarrowRecord0041A617.h"
struct BfmePod28;
struct BfmePod16;

// Vtable 0x00C3AD08: slots 14-21 are pure.
class GameResultsInterface : public SubsystemInterface
{
public:
	virtual ~GameResultsInterface() {}
	virtual void startThreads() = 0;
	virtual void endThreads() = 0;
	virtual bool areThreadsRunning() = 0;
	virtual void addRequest(const BfmeNarrowRecord0041A5D2 &request) = 0;
	virtual bool getRequest(BfmeNarrowRecord0041A5D2 &request) = 0;
	virtual void addResponse(const BfmePod16 &response) = 0;
	virtual bool getResponse(BfmeNarrowRecord0041A617 &response) = 0;
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
		bool Failed() { return m_failed; }

	private:
		MutexClass &m_mutex;
		bool m_failed;
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

namespace _STL
{
template <class T> class allocator;
template <class T, class A> class deque
{
public:
	void push_back(const T &value);
};

// STLport queue over its deque: the start and finish iterators' current
// pointers are the first word of each (+0x00, +0x10).
template <class T, class C = deque<T, allocator<T> > >
class queue
{
public:
	queue();
	~queue();
	bool empty() const { return m_finishCur == m_startCur; }
	void push(const T &value) { reinterpret_cast<C *>(this)->push_back(value); }
	void *frontCur() const { return m_startCur; }

private:
	void *m_startCur;
	void *m_startIterator[3];
	void *m_finishCur;
	void *m_finishIterator[3];
	void **m_map;
	unsigned int m_mapSize;
};
}

// The request deque's push_back and both pop_front paths are rowed on
// address-named views of the same storage.
class Rva0041A96D
{
public:
	void rva0041AB68(const BfmeNarrowRecord0041A5D2 &request);	// 0x0041AB68
};
class Rva0041A3C4
{
public:
	void rva0041A486();	// 0x0041A486, request pop_front
};
class Rva0041A3F7
{
public:
	void rva0041A4A7();	// 0x0041A4A7, response pop_front
};

class Rva0041A644 : public GameResultsInterface
{
public:
	Rva0041A644();
	virtual ~Rva0041A644();			// 0x0041A644

	virtual void startThreads();
	virtual void endThreads();
	virtual bool areThreadsRunning();
	virtual void addRequest(const BfmeNarrowRecord0041A5D2 &request);
	virtual bool getRequest(BfmeNarrowRecord0041A5D2 &request);
	virtual void addResponse(const BfmePod16 &response);
	virtual bool getResponse(BfmeNarrowRecord0041A617 &response);
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

void Rva0041A644::addRequest(const BfmeNarrowRecord0041A5D2 &request)
{
	MutexClass::LockClass m(m_requestMutex);
	++m_requestCount;
	reinterpret_cast<Rva0041A96D *>(&m_requests)->rva0041AB68(request);
}

bool Rva0041A644::getRequest(BfmeNarrowRecord0041A5D2 &request)
{
	MutexClass::LockClass m(m_requestMutex, 0);
	if (m.Failed())
		return false;
	if (m_requests.empty())
		return false;
	request = *static_cast<BfmeNarrowRecord0041A5D2 *>(m_requests.frontCur());
	reinterpret_cast<Rva0041A3C4 *>(&m_requests)->rva0041A486();
	return true;
}

void Rva0041A644::addResponse(const BfmePod16 &response)
{
	MutexClass::LockClass m(m_responseMutex);
	++m_responseCount;
	m_responses.push(response);
}

bool Rva0041A644::getResponse(BfmeNarrowRecord0041A617 &response)
{
	MutexClass::LockClass m(m_responseMutex, 0);
	if (m.Failed())
		return false;
	if (m_responses.empty())
		return false;
	response = *static_cast<BfmeNarrowRecord0041A617 *>(m_responses.frontCur());
	reinterpret_cast<Rva0041A3F7 *>(&m_responses)->rva0041A4A7();
	return true;
}

bool Rva0041A644::areGameResultsBeingSent()
{
	MutexClass::LockClass m(m_requestMutex, 0);
	if (m.Failed())
		return true;
	return m_requestCount > 0;
}
