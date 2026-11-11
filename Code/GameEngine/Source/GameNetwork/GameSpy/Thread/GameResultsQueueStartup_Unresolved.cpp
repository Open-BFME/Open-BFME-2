// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Split from GameResultsQueueStartup.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// stlport
//
// TheGameResultsQueue, the Zero Hour GameResultsThread.cpp queue bodies
// (createNewGameResultsInterface, the GameResultsQueue constructor and
// destructor, startThreads, endThreads, add/getRequest, add/getResponse,
// areGameResultsBeingSent):
//   ?Rva0041AA6FCreateGameResults@@YAPAVGameResultsInterface@@XZ  0x0041AA6F  53B
//   ??0Rva0041A644@@QAE@XZ                                       0x0041A754 135B
//   ??1Rva0041A644@@UAE@XZ                                       0x0041A644 140B
//   ?startThreads@Rva0041A644@@UAEXXZ                            0x00419F88 135B
//   ?endThreads@Rva0041A644@@UAEXXZ                              0x0041A00F  56B
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
// the 0x54-byte worker 0x00419CFB, and endThreads clears that holder and
// stops the worker before the global delete, which Zero Hour does not. The get
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

// Tables 0x00C3AD08 and 0x00C3AD70 hold SubsystemInterface's fourteen slots
// before the queue's eight, so the base declares them.
#define BFME_SUBSYSTEM_SLOTS
#include "../../../../../Libraries/Source/subsystem/SubsystemInterface.h"

// The request and response records (assignments 0x0041A7F7, 0x0041A820).
#include "BfmeNarrowRecord0041A5D2.h"
#include "BfmeNarrowRecord0041A617.h"
struct BfmePod28;
struct BfmePod16;

// Vtable 0x00C3AD08: slots 14-21 are pure.
class GameResultsInterface : public SubsystemInterface
{
public:
	// Inline, as in Zero Hour: the queue constructor 0x0041A754 expands it
	// (SubsystemInterface 0x001B4E63, then its own vptr). The out-of-line copy
	// retail kept, 0x00419D18, is rowed in GameEngineDeletingBaseDerived.cpp;
	// this surface keeps cl from emitting a second definition here.
	__declspec(dllimport) __forceinline GameResultsInterface() {}
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

// The 0x54-byte worker thread (Rva00419CFBConstructor.cpp) on ThreadClass:
// slot 0 the virtual dtor, slot 1 Execute.
#include "../../../../../Libraries/Source/WWVegas/WWLib/ThreadClass.h"

class Rva00419CFB : public ThreadClass
{
public:
	Rva00419CFB(void *lock);	// 0x00419CFB
};

// The record each placeholder-named queue holds: the destructor frees the
// queues through the rowed deque<record> dtors 0x0041A51F and 0x0041A57B.
template <class T> struct Rva0041A644Record;
template <> struct Rva0041A644Record<BfmePod28> { typedef BfmeNarrowRecord0041A5D2 Type; };
template <> struct Rva0041A644Record<BfmePod16> { typedef BfmeNarrowRecord0041A617 Type; };

namespace _STL
{
template <class T> class allocator;
template <class T, class A> class deque
{
public:
	~deque();
	void push_back(const T &value);
};

// STLport queue over its deque: the start and finish iterators' current
// pointers are the first word of each (+0x00, +0x10).
template <class T, class C = deque<T, allocator<T> > >
class queue
{
public:
	queue();
	~queue()
	{
		typedef typename Rva0041A644Record<T>::Type R;
		reinterpret_cast<deque<R, allocator<R> > *>(this)->~deque();
	}
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
#include "../../../../Include/GameNetwork/Rva0041A96D.h"
class Rva0041A3C4
{
public:
	void rva0041A3C4();
	void rva0041A486();
	BfmeNarrowRecord0041A5D2 *_M_cur; // +0x00
	BfmeNarrowRecord0041A5D2 *_M_first; // +0x04
	BfmeNarrowRecord0041A5D2 *_M_last; // +0x08
	BfmeNarrowRecord0041A5D2 **_M_node; // +0x0C
};
#include "../../../../Include/GameNetwork/Rva0041A3F7.h"

class Rva0041A644 : public GameResultsInterface
{
public:
	Rva0041A644();
	virtual ~Rva0041A644();

	// Zero Hour's empty GameResultsQueue overrides: retail 0x00C3AD70 slots 1,
	// 9 and 10 are the shared bare RET 0x000B3FD0.
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}

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

GameResultsInterface *Rva0041AA6FCreateGameResults();

Rva0041A644::Rva0041A644() : m_requestCount(0), m_responseCount(0)
{
	for (int i = 0; i < 1; ++i)
		m_workerThreads[i] = 0;
	startThreads();
}

Rva0041A644::~Rva0041A644()
{
	endThreads();
}
