// ?handle@Gen0002857E@@QAEXXZ
// partial score=0.97 date=2026-10-05
// cl: /O1 /G7 /MD
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

class Gen0002857EOwner
{
public:
	char m_pad[0x50];
	void *m_mutex;
};

class Gen0002857E
{
public:
	void handle();
private:
	char m_pad0[4];
	Gen0002857EOwner *m_owner;
	char m_pad1[0x34 - 8];
	int m_count;
};

void Gen0002857E::handle()
{
	MilesMutexGuard guard(m_owner->m_mutex, 0);
	m_count = m_count + 1;
}
