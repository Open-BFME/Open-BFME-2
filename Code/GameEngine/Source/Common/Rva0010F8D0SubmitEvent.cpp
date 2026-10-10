// cl: /DNDEBUG /MD /EHsc /O1 /G7
//
// ?rva0010F8D0@Rva0010F8D0@@QAEXPAVRva001164D3@@@Z at 0x0010F8D0, 146 bytes.
// RET 4 submission helper called by the ten event factories in
// Rva0010FA6BFactoryBatch.cpp. Under an inline ScopedCriticalSection on the
// address-derived lock from the rowed getter 0x0010F011 (rowed Lock 0x00035620
// / Unlock 0x00035640) it resets the event at +0x14 (rowed 0x00040FCD) when
// the pending count at +0x10 is zero and bumps that count; this mirrors the
// decrement sibling at 0x0010F70A. Outside the lock it wraps the incoming
// event in an AudioEventInfoRef (rowed ctor 0x00051914): with no queue at
// +0x0C the reference is dropped at once (inlined Release_Ref 0x00050ED3);
// otherwise it is passed by value to the rowed queue forwarder 0x0010F873
// whose STLport list-iterator result (hidden return pointer) is discarded.
// Owner identities remain address-derived.
//
// Frame note: retail packs both the null-branch reference and the discarded
// iterator return into the dead parameter slot [ebp+8]. In a function with
// an earlier EH region cl only lets a then-arm object whose address goes to an
// opaque thiscall share that slot with else-arm temporaries when it can see
// the callee does not keep `this`. The AudioEventInfoRef constructor is
// therefore written below with its real body as an in-class never-inlined
// definition (it still emits the retail 29-byte body of 0x00051914 and stays a
// call, as in retail).

class CriticalSection;

class ScopedCriticalSection
{
	friend class Rva0010F8D0;
	CriticalSection *m_cs;
	bool m_locked;
	void Lock();
	void Unlock() throw();
public:
	__forceinline ScopedCriticalSection(CriticalSection *cs)
	{
		m_cs = cs;
		m_locked = false;
		Lock();
	}

	__forceinline ~ScopedCriticalSection()
	{
		if (m_locked)
			Unlock();
	}
};

class Rva0040F9D
{
	void *m_vtable;
	void *m_handle;

public:
	bool reset();
};

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

typedef long Long;
extern "C" __declspec(dllimport) Long __stdcall InterlockedIncrement(Long volatile *addend);

class AudioEventInfo
{
public:
	void *m_vtable;
	Long m_refCount;
};

class AudioEventInfoRef
{
public:
	__declspec(noinline) AudioEventInfoRef(const AudioEventInfo *info)
		: m_item((void *)info)
	{
		if (m_item)
			InterlockedIncrement(&((AudioEventInfo *)m_item)->m_refCount);
	}
	AudioEventInfoRef(const AudioEventInfoRef &other);
	~AudioEventInfoRef()
	{
		if (m_item)
			((OpaqueRefCounted *)m_item)->Release_Ref();
	}

	void *m_item;
};

struct Rva0073EEE0ListValue;

namespace _STL
{
template <class _Tp> struct _Nonconst_traits;
template <class _Tp, class _Traits> struct _List_iterator
{
	void *_M_node;
	_List_iterator();
};
}

class AsyncServiceQueue
{
public:
	_STL::_List_iterator<Rva0073EEE0ListValue,
		_STL::_Nonconst_traits<Rva0073EEE0ListValue> >
		rva0010F873(AudioEventInfoRef ref);
};

class Rva001164D3;

extern void *__cdecl Rva0010F011Get(void);

class Rva0010F8D0
{
	unsigned char m_pad00[0x0C];
	AsyncServiceQueue *m_queue;
	volatile int m_pending;
	Rva0040F9D m_event;

public:
	void rva0010F8D0(Rva001164D3 *eventInfo);
};

void Rva0010F8D0::rva0010F8D0(Rva001164D3 *eventInfo)
{
	{
		ScopedCriticalSection guard((CriticalSection *)Rva0010F011Get());
		if (m_pending == 0)
			m_event.reset();
		m_pending += 1;
	}
	if (m_queue == 0)
		AudioEventInfoRef ref((const AudioEventInfo *)eventInfo);
	else
		m_queue->rva0010F873(AudioEventInfoRef((const AudioEventInfo *)eventInfo));
}
