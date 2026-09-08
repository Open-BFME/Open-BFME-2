#pragma once

// BFME2's CriticalSection object carries a vtable, a state/handle word, the
// Windows section at +8, and a disabled byte/flag at +0x20.  The scoped guard
// below is limited to the lock shape used by NameKeyGenerator; its helpers are
// byte-verified in the same TU.

class CriticalSection
{
public:
	virtual ~CriticalSection();

	void *m_handle;
	CRITICAL_SECTION m_windowsCriticalSection;
	bool m_disabled;
};

#pragma optimize("s", off)
class ScopedCriticalSection
{
	CriticalSection *m_cs;
	bool m_locked;

	__declspec(noinline) void Lock()
	{
		CriticalSection *cs = m_cs;
		if (!cs->m_disabled)
			EnterCriticalSection(&cs->m_windowsCriticalSection);
		m_locked = true;
	}

	__declspec(noinline) void Unlock()
	{
		CriticalSection *cs = m_cs;
		if (!cs->m_disabled)
			LeaveCriticalSection(&cs->m_windowsCriticalSection);
		m_locked = false;
	}

public:
	__forceinline ScopedCriticalSection(CriticalSection *cs) : m_cs(cs), m_locked(false)
	{
		Lock();
	}

	__forceinline ~ScopedCriticalSection()
	{
		if (m_locked)
			Unlock();
	}
};

#pragma optimize("s", on)
