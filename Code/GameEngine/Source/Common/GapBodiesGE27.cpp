// cl: /O2 /G7 /arch:SSE /MD /DNDEBUG
// platformsdk
// Small bodies from .text gaps no Ghidra function covers (twenty-seventh
// batch; see GapBodiesGE01.cpp), the ones whose retail shape is the /O2 form
// (byte loads tested in a register, read-modify-write split through a
// register, stack words pushed through a register). Each begins after its
// neighbour's padding or ret and ends in its own ret. Retail bytes establish
// every shape; owning classes are not recovered, so each keeps an
// address-derived name and a view of only the members it touches.

#include <windows.h>

// --- 0x00032AC0 (64B): under the heap's optional counted lock (+0x4E4: a
// critical section with a depth word at +0x18), read the chunk size word
// ahead of a user pointer (allocator run 0x00030D10..0x00031BF0).
struct GapCountedLock
{
	CRITICAL_SECTION m_section;
	volatile int m_depth;									// +0x18
};

class Rva00032AC0
{
public:
	unsigned int rva00032AC0(const void *block, int unused);
private:
	char m_pad00[0x4E4];
	GapCountedLock *m_lock;									// +0x4E4
};

unsigned int Rva00032AC0::rva00032AC0(const void *block, int unused)
{
	GapCountedLock *lock = m_lock;
	if (lock)
	{
		EnterCriticalSection(&lock->m_section);
		++lock->m_depth;
	}
	unsigned int size = ((const unsigned int *)block)[-1] & 0x7FFFFFF8;
	if (lock)
	{
		--lock->m_depth;
		LeaveCriticalSection(&lock->m_section);
	}
	return size;
}

// --- 0x000355E0 / 0x00035600 (18B each): enter / leave the +8 critical
// section unless the +0x20 single-thread flag is set; 0x00035880 (48B): the
// scoped guard over it (lock unless told it is already held).
class Rva000355E0
{
public:
	__forceinline void enter()
	{
		if (!m_singleThreaded)
			EnterCriticalSection(&m_section);
	}
	void rva000355E0();
	void rva00035600();
private:
	char m_pad00[8];
	CRITICAL_SECTION m_section;									// +0x08
	bool m_singleThreaded;									// +0x20
};

void Rva000355E0::rva000355E0()
{
	enter();
}

void Rva000355E0::rva00035600()
{
	if (!m_singleThreaded)
		LeaveCriticalSection(&m_section);
}

class Rva00035880
{
public:
	Rva00035880(Rva000355E0 *mutex, int held);
private:
	Rva000355E0 *m_mutex;
	bool m_locked;											// +0x04
};

Rva00035880::Rva00035880(Rva000355E0 *mutex, int held)
{
	m_mutex = mutex;
	m_locked = false;
	if (!held)
	{
		mutex->enter();
		m_locked = true;
	}
}

// --- 0x00038390 (27B): forward three words to theDebug's slot 27 (+0x6C).
class Debug;
extern Debug *theDebug;

class GapDebugView
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26();
	virtual void slot27(int a, int b, int c);
};

void rva00038390(int a, int b, int c)
{
	((GapDebugView *)theDebug)->slot27(a, b, c);
}
