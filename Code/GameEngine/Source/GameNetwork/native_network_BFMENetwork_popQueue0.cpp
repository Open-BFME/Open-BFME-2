// cl: /DNDEBUG /MD /GX
//
// ?popQueue0@BFMENetwork@@QAE_NPAVBFMENetworkQueueItem@@@Z
// retail 0x00557D98, 99 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameNetwork/native_network.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
#include <new>

typedef bool Bool;

class BFMENetworkQueue;
class BFMENetworkQueue1;
class BFMENetwork;
struct BFMENetworkList;

namespace _STL
{
template <class T> class char_traits { };
template <class T> class allocator { };
template <class Char, class Traits, class Allocator>
class basic_string
{
public:
	 basic_string(const basic_string &that);
	 ~basic_string();
};

template <bool threads, int inst>
class __node_alloc
{
	friend struct ::BFMENetworkList;
	static void *_M_allocate(unsigned int bytes);

public:
	static void _M_deallocate(void *p, unsigned int bytes);
};

template <class T, class Allocator>
class deque
{
protected:
	void _M_push_back_aux_v(const T &value);
	friend class ::BFMENetworkQueue;
	friend class ::BFMENetworkQueue1;
	friend class ::BFMENetwork;
};

template <class T1, class T2>
inline void _Construct(T1 *destination, const T2 &value)
{
	new (destination) T1(value);
}
}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > BFMENetworkString;

class BFMENetworkLock;
void *BFMENetworkAllocate(unsigned int bytes);

struct BFMENetworkListNode
{
	Bool flag;
	int value;
	BFMENetworkListNode *next;
	BFMENetworkListNode *previous;
};

struct BFMENetworkList
{
	BFMENetworkList() : head(0)
	{
		head = new (_STL::__node_alloc<true, 0>::_M_allocate(0x18)) BFMENetworkListNode;
		size = 0;
		head->flag = false;
		head->value = 0;
		head->next = head;
		head->previous = head;
	}

	BFMENetworkListNode *head;
	int size;
	int allocatorStorage;
};

class ThreadClass
{
public:
    ThreadClass(const char *name);
    virtual ~ThreadClass();
    virtual void Execute();
    void Set_Priority(int priority);
    __declspec(noinline) bool Is_Running();
    __declspec(noinline) void Stop();

protected:
    virtual void Thread_Function() = 0;

private:
    char m_name[0x40];
    unsigned int m_threadId;
    void *m_handle;
    int m_priority;
};

class BFMENetworkBackend : public ThreadClass
{
public:
	BFMENetworkBackend(BFMENetworkLock *ownerLock);
	virtual ~BFMENetworkBackend();
	void *destroyAndMaybeDelete(unsigned int flags);
	virtual void Thread_Function();

private:
	Bool m_flag50;
	Bool m_flag51;
	char m_pad52[2];
	int m_value54;
	Bool m_flag58;
	char m_pad59[3];
	BFMENetworkList m_list;
	BFMENetworkLock *m_ownerLock;
};

class BFMENetworkBackendDestructorShim
{
public:
	void destroy();
};

class BFMENetworkLock
{
public:
	BFMENetworkLock(const char *name);
	~BFMENetworkLock();

	void *m_handle;
	int m_refCount;
};

class BFMEAutoLockRef
{
public:
	BFMEAutoLockRef(BFMENetworkLock *lock, unsigned int timeout);
	__declspec(noinline) ~BFMEAutoLockRef();
	Bool failed() const { return m_failed; }

private:
	BFMENetworkLock *m_lock;
	Bool m_failed;
};

class BFMENetworkLockRefOwner
{
public:
	~BFMENetworkLockRefOwner()
	{
		BFMEAutoLockRef *ref = m_ref;
		if (ref)
			delete ref;
	}

	BFMEAutoLockRef *m_ref;
};

class BFMENetworkQueueItem
{
public:
	BFMENetworkQueueItem(const BFMENetworkQueueItem &that);
	void copyFromQueueNode(void *node);
};

class BFMENetworkQueueItem1
{
public:
	BFMENetworkQueueItem1(const BFMENetworkQueueItem1 &that);
	void copyFromQueueNode(void *node);
};

struct BFMENetworkQueuePushFields
{
	char m_padding[0x10];
	char *m_end;
	char *m_first;
	char *m_storageEnd;
};

class BFMENetworkListPayload
{
private:
	char m_data[0x1c4];
};

class BFMENetworkQueue
{
public:
	BFMENetworkQueue()
	{
		m_begin = 0;
		m_04 = 0;
		m_08 = 0;
		m_0c = 0;
		m_end = 0;
		m_14 = 0;
		m_storageEnd = 0;
		m_1c = 0;
		m_20 = 0;
		m_24 = 0;
		finishConstruct(0);
	}
	~BFMENetworkQueue();

	Bool empty() const { return m_end == m_begin; }
	__forceinline void pushBack(const BFMENetworkQueueItem &item)
	{
		BFMENetworkQueuePushFields *fields = reinterpret_cast<BFMENetworkQueuePushFields *>(this);
		if (fields->m_end != fields->m_storageEnd - 0x210) {
			_STL::_Construct(reinterpret_cast<BFMENetworkQueueItem *>(fields->m_end), item);
			fields->m_end += 0x210;
		} else {
			reinterpret_cast<_STL::deque<BFMENetworkQueueItem, _STL::allocator<BFMENetworkQueueItem> > *>(this)->_M_push_back_aux_v(item);
		}
	}
	void popFront();
	void finishConstruct(void *unused);

	void *volatile m_begin;
	void *volatile m_04;
	void *volatile m_08;
	void *volatile m_0c;
	char *volatile m_end;
	void *volatile m_14;
	char *volatile m_storageEnd;
	void *volatile m_1c;
	void *volatile m_20;
	void *m_24;
};

class BFMENetworkQueue1
{
public:
	BFMENetworkQueue1()
	{
		m_begin = 0;
		m_04 = 0;
		m_08 = 0;
		m_0c = 0;
		m_end = 0;
		m_14 = 0;
		m_storageEnd = 0;
		m_1c = 0;
		m_20 = 0;
		m_24 = 0;
		finishConstruct(0);
	}
	~BFMENetworkQueue1();

	Bool empty() const { return m_end == m_begin; }
	__forceinline void pushBack(const BFMENetworkQueueItem1 &item)
	{
		BFMENetworkQueuePushFields *fields = reinterpret_cast<BFMENetworkQueuePushFields *>(this);
		if (fields->m_end != fields->m_storageEnd - 0x1f0) {
			_STL::_Construct(reinterpret_cast<BFMENetworkQueueItem1 *>(fields->m_end), item);
			fields->m_end += 0x1f0;
		} else {
			reinterpret_cast<_STL::deque<BFMENetworkQueueItem1, _STL::allocator<BFMENetworkQueueItem1> > *>(this)->_M_push_back_aux_v(item);
		}
	}
	void popFront();
	void finishConstruct(void *unused);

	void *volatile m_begin;
	void *volatile m_04;
	void *volatile m_08;
	void *volatile m_0c;
	char *volatile m_end;
	void *volatile m_14;
	char *volatile m_storageEnd;
	void *volatile m_1c;
	void *volatile m_20;
	void *volatile m_24;
};

class BFMENetworkState
{
public:
	BFMENetworkState();
	__forceinline ~BFMENetworkState()
	{
		char *start = m_start;
		unsigned int bytes = (unsigned int)(m_capacity - start);
		if (start != 0) {
			if (bytes > 128)
				::operator delete(start);
			else
				_STL::__node_alloc<true, 0>::_M_deallocate(start, bytes);
		}
	}

private:
	char *m_start;
	char *m_finish;
	char *m_capacity;
};

struct BFMENetworkPayloadList
{
	BFMENetworkPayloadList() : head(0)
	{
		head = static_cast<BFMENetworkListNode *>(BFMENetworkAllocate(0x1d8));
		size = 0;
		head->flag = false;
		head->value = 0;
		head->next = head;
		head->previous = head;
	}
	~BFMENetworkPayloadList();

	BFMENetworkListNode *head;
	int size;
	int allocatorStorage;
};

class BFMENetworkThreadRunner
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4c();
	virtual void v50();
	virtual void v54();
	virtual void threadTick();
};

class BFMENetworkBackendThreadRunner
{
public:
	virtual void v00();
	virtual void v04();
	virtual void dispatchEvents();
};

extern "C" const void *bfmeVftBFMENetworkInterfaceBase[];
#pragma comment(linker, "/alternatename:_bfmeVftBFMENetworkInterfaceBase=??_7Rva00651690Deleting@@6B@")

class BFMENetworkInterfaceBase
{
public:
	virtual ~BFMENetworkInterfaceBase()
	{
		*(const void **)this = bfmeVftBFMENetworkInterfaceBase;
	}
};

class BFMENetwork : public BFMENetworkInterfaceBase
{
public:
	BFMENetwork();
	virtual ~BFMENetwork();
	void *destroyAndMaybeDelete(unsigned int flags);
	void init();
	Bool backendHasLiveHandle();
	void destroyBackend();
	void pushQueue0(BFMENetworkQueueItem *item);
	Bool popQueue0(BFMENetworkQueueItem *item);
	void pushQueue1(BFMENetworkQueueItem1 *item);
	Bool popQueue1(BFMENetworkQueueItem1 *item);
	BFMENetworkString copyState6C();
	BFMENetworkString copyState78();
	BFMENetworkString copyState84();

private:
	BFMENetworkLock m_lock0;
	BFMENetworkLock m_lock1;
	BFMENetworkQueue m_queue0;
	BFMENetworkQueue1 m_queue1;
	BFMENetworkBackend *m_backend;
	void *m_unknown68;
	BFMENetworkState m_state6c;
	BFMENetworkState m_state78;
	BFMENetworkState m_state84;
	BFMENetworkPayloadList m_list90;
	BFMENetworkLock m_lock9c;
	BFMENetworkLockRefOwner m_backendLockRef;
};

class BFMENetworkDestructorShim
{
public:
	void destroy();
};

extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class BfmeAwakenDebug;
extern BfmeAwakenDebug *TheBfmeAwakenDebug;

Bool BFMENetwork::popQueue0(BFMENetworkQueueItem *item)
{
	BFMEAutoLockRef lock(&m_lock0, 2);

	if (lock.failed()) {
		return false;
	}

	BFMENetworkQueue *queue = &m_queue0;
	if (queue->empty()) {
		return false;
	}

	void *node = queue->m_begin;
	item->copyFromQueueNode(node);
	queue->popFront();
	return true;
}

