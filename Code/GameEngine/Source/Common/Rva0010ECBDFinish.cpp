// ?handle@Gen0002857E@@QAEXXZ
// partial score=0.97 date=2026-10-05
// cl: /MD
// ?handle@Gen0002857E@@QAEXXZ at 0x0010ECBD (39B).
// Mutex-guarded increment of the counter at +0x34 via MilesMutexGuard over owner mutex at +0x50.
// Evidence: BFME1 donor game/GameEngine/Source/Common/Gen0002857EHandle.cpp; retail pushes 0 and [eax+0x50] into ctor 0x0004120E and calls dtor 0x0004122F; LINK BONUS caller in Rva00690FF0Handle.cpp.

class MilesMutexGuard
{
public:
	MilesMutexGuard(void *m, int x);
	~MilesMutexGuard();
private:
	void *m_mutex;
	bool m_flag;
};

class Gen0002857E;

class Gen0002857EOwner
{
public:
	char m_pad[0x50];
	void *m_mutex;
	void rva000A8127(void *entry);
};

class Gen0002857E
{
public:
	void handle();
	void release();
private:
	char m_pad0[4];
	Gen0002857EOwner *m_owner;
	char m_pad1[0x34 - 8];
	// volatile so the read-modify-write is not strength-reduced to `inc`.
	volatile int m_count;
	unsigned int m_lastReleaseTime;
};

void Gen0002857E::handle()
{
	MilesMutexGuard guard(m_owner->m_mutex, 0);
	m_count = m_count + 1;
}

extern "C" __declspec(dllimport) unsigned int __stdcall AIL_ms_count(void);

void Gen0002857E::release()
{
	void *mutex = m_owner->m_mutex;
	MilesMutexGuard guard(mutex, 0);
	m_count -= 1;
	if (m_count == 0)
	{
		m_lastReleaseTime = AIL_ms_count();
		m_owner->rva000A8127(this);
	}
}
