// cl: /DNDEBUG /MD /EHsc /O1 /G7
//
// ?rva0010F70A@Rva0010F70A@@QAEXPAX@Z at 0x0010F70A, 86 bytes. Retail
// calls the address-derived global critical-section getter at 0x0010F011,
// acquires it through the rowed ScopedCriticalSection::Lock, decrements the
// dword at +0x10, signals the event at +0x14 when it reaches zero, and releases
// the guard through the rowed Unlock helper. The caller at 0x001164F5 passes
// its owner as the one stack argument; the callee does not read it. The
// surrounding owner and critical-section identities remain address-derived.

class CriticalSection;

class ScopedCriticalSection
{
	friend class Rva0010F70A;
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
	bool set();
};

class Rva0010F70A
{
	unsigned char m_pad00[0x10];
	volatile int m_refCount;
	Rva0040F9D m_event;

public:
	void rva0010F70A(void *owner);
};

extern void *__cdecl Rva0010F011Get(void);

void Rva0010F70A::rva0010F70A(void *owner)
{
	ScopedCriticalSection guard((CriticalSection *)Rva0010F011Get());
	m_refCount -= 1;
	if (m_refCount == 0)
		m_event.set();
}
