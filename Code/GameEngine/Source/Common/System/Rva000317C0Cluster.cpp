// platformsdk
// Companion of Rva00031790 in memory_pool.cpp: the release half of the
// lock-holder setter. It reads the held critical section at +0, drops the use
// count at +0x18 and leaves the section. The class is address-derived because
// the near file's owner is likewise unproven; LeaveCriticalSection reaches this
// unit through the same dllimport IAT slot as the neighbours.
#include <windows.h>

class Rva000317C0
{
public:
	void *m_0000;
	void rva000317c0();
};

void Rva000317C0::rva000317c0()
{
	char *held = (char *)m_0000;
	if (held != 0)
	{
		int count = *(volatile int *)(held + 0x18);
		*(volatile int *)(held + 0x18) = count - 1;
		LeaveCriticalSection((CRITICAL_SECTION *)held);
	}
}

// Native cleanup 0x007A7D50 of Rva006C3840Cluster jumps to this same
// 21-byte release at 0x000317C0. The single-pointer guard is a structural
// view; its original class name is unknown. Keep this out-of-line copy in
// the release home while the allocator consumers retain their inline view.
class Rva00030DD0Guard
{
public:
    ~Rva00030DD0Guard();
private:
    void *m_lock;
};

// ??1Rva00030DD0Guard@@QAE@XZ present-unmatched
inline __declspec(noinline) Rva00030DD0Guard::~Rva00030DD0Guard()
{
    char *held = (char *)m_lock;
    if (held != 0)
    {
        int count = *(volatile int *)(held + 0x18);
        *(volatile int *)(held + 0x18) = count - 1;
        LeaveCriticalSection((CRITICAL_SECTION *)held);
    }
}

// ?bfmeAnchorCountedGuardDtor absent-from-retail
void bfmeAnchorCountedGuardDtor(Rva00030DD0Guard *guard)
{
    guard->Rva00030DD0Guard::~Rva00030DD0Guard();
}
