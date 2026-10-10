// ?rva0010F8D0@Rva0010F8D0@@QAEXPAVRva001164D3@@@Z
// partial score=0.9 date=2026-10-10
// cl: /DNDEBUG /MD /EHsc /O1 /G7
//
// ?rva0010F8D0@Rva0010F8D0@@QAEXPAVRva001164D3@@@Z at 0x0010F8D0 146 bytes
// RET 4. Retail takes the address-derived global critical section from the
// rowed getter at 0x0010F011 and holds it through the rowed
// ScopedCriticalSection Lock/Unlock pair while it bumps the pending count at
// +0x10 and resets the event at +0x14 (rowed 0x00040FCD) when that count was
// zero; this mirrors the decrement sibling at 0x0010F70A. Outside the lock it
// wraps the incoming event in an AudioEventInfoRef (rowed ctor 0x00051914):
// with no queue at +0x0C the reference is dropped at once (inlined
// Release_Ref 0x00050ED3); otherwise the reference is passed by value to the
// queue method at 0x0010F873 whose STLport list iterator result (hidden
// return pointer) is discarded. The ten event factories in
// Rva0010FA6BFactoryBatch.cpp call this helper. Owner identities remain
// address-derived.
//
// NEAR (not exact): every instruction matches but the frame. Retail keeps an
// 8-byte frame (lock at ebp-0x14 with the arg esp-save packed into its flag
// slot) and packs both the null-branch ref and the discarded iterator return
// into the dead parameter slot ebp+8. cl here gives the return temp its own
// slot at ebp-0x10 and moves the lock to ebp-0x18 (sub esp 0xC). Writing the
// queue branch first gives the 8-byte frame but swaps block order and still
// keeps the return temp out of ebp+8. Without the EH lock (or with a plain
// local in its place) cl packs exactly like retail. Tried: inline helpers
// for either part; goto/early return; temp vs named ref; by-value discard
// helper; ret type shapes (base/dtor/copy/opassign); nothrow ctor/dtor;
// post/pre increment; cs local; comma-expression temp guard; for-scope guard;
// /EHs /GX /arch:SSE /G6.

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

class AudioEventInfo;

class AudioEventInfoRef
{
public:
	AudioEventInfoRef(const AudioEventInfo *info);
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
