// cl: /DNDEBUG /MD /GX /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// platformsdk
//
// ?popQueue0@BFMENetwork@@UAE_NPAVBFMENetworkQueueItem@@@Z
// retail 0x00557D98, 99 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameNetwork/native_network.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
#include <new>
#include <windows.h>

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
public:
	void push_back(const T &value);
	void pop_front();
};
}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > BFMENetworkString;

class MutexClass;
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

#include "../../../Libraries/Source/WWVegas/WWLib/ThreadClass.h"

class BFMENetworkBackend : public ThreadClass
{
public:
	BFMENetworkBackend(MutexClass *ownerLock);
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
	MutexClass *m_ownerLock;
};

class MutexClass
{
public:
	MutexClass(const char *name);
	~MutexClass();

	// WWLib's scoped lock (mutex.h). The queue members' lock calls land on
	// its rowed ctor 0x00613A70 and dtor 0x00613AC0 (WWLib/mutex.cpp), and
	// retail's deleting copy is ??_GLockClass@MutexClass 0x00099203.
	class LockClass
	{
	public:
		LockClass(MutexClass &mutex, int time);
		~LockClass();
		Bool Failed() { return m_failed; }

	private:
		MutexClass &m_mutex;
		Bool m_failed;
	};

	void *m_handle;
	int m_refCount;
};

class BFMENetworkLockRefOwner
{
public:
	~BFMENetworkLockRefOwner()
	{
		MutexClass::LockClass *ref = m_ref;
		if (ref)
			delete ref;
	}

	MutexClass::LockClass *m_ref;
};

// The queue records and their STLport deques. Retail's queue 0 calls land on
// the rowed assignment of BfmeOpaqueOwnedRecord1432 (0x005565C5) and on its
// deque's pop_front 0x0055628F and push_back 0x00558F8A; queue 1's on
// BfmeOpaqueOwnedRecord1408's (0x00556132) and on 0x005562B6 and 0x00558FBC
// (WWLib/StlportOwnedRecordDeque.cpp). The queue members call those through
// the casts below; only those member ABIs are used here.
struct BfmeOpaqueOwnedRecord1432
{
	BfmeOpaqueOwnedRecord1432 &operator=(const BfmeOpaqueOwnedRecord1432 &that);
};

struct BfmeOpaqueOwnedRecord1408
{
	BfmeOpaqueOwnedRecord1408 &operator=(const BfmeOpaqueOwnedRecord1408 &that);
};

typedef _STL::deque<BfmeOpaqueOwnedRecord1432, _STL::allocator<BfmeOpaqueOwnedRecord1432> > BFMENetworkRecordDeque;
typedef _STL::deque<BfmeOpaqueOwnedRecord1408, _STL::allocator<BfmeOpaqueOwnedRecord1408> > BFMENetworkRecordDeque1;

class BFMENetworkQueueItem
{
public:
	BFMENetworkQueueItem(const BFMENetworkQueueItem &that);
};

#include "../../Include/GameNetwork/BFMENetworkQueueItem1.h"

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

extern "C" const void *bfmeVftBFMENetworkInterfaceBase[];

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
	// Slots 4-7 of the vftable 0x00C6B318 that the ctor installs: virtual.
	virtual void pushQueue0(BFMENetworkQueueItem *item);
	virtual Bool popQueue0(BFMENetworkQueueItem *item);
	virtual void pushQueue1(BFMENetworkQueueItem1 *item);
	virtual Bool popQueue1(BFMENetworkQueueItem1 *item);
	BFMENetworkString copyState6C();
	BFMENetworkString copyState78();
	BFMENetworkString copyState84();

private:
	MutexClass m_lock0;
	MutexClass m_lock1;
	BFMENetworkQueue m_queue0;
	BFMENetworkQueue1 m_queue1;
	BFMENetworkBackend *m_backend;
	void *m_unknown68;
	BFMENetworkState m_state6c;
	BFMENetworkState m_state78;
	BFMENetworkState m_state84;
	BFMENetworkPayloadList m_list90;
	MutexClass m_lock9c;
	BFMENetworkLockRefOwner m_backendLockRef;
};

class BfmeAwakenDebug;
extern BfmeAwakenDebug *TheBfmeAwakenDebug;

Bool BFMENetwork::popQueue0(BFMENetworkQueueItem *item)
{
	MutexClass::LockClass lock(m_lock0, 2);

	if (lock.Failed()) {
		return false;
	}

	BFMENetworkQueue *queue = &m_queue0;
	if (queue->empty()) {
		return false;
	}

	void *node = queue->m_begin;
	*reinterpret_cast<BfmeOpaqueOwnedRecord1432 *>(item) = *static_cast<const BfmeOpaqueOwnedRecord1432 *>(node);
	reinterpret_cast<BFMENetworkRecordDeque *>(queue)->pop_front();
	return true;
}
