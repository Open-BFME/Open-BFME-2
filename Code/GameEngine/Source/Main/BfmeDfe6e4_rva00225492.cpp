// cl: /DNDEBUG /MD /EHsc /Oy-
// ?rva00225492@BfmeDfe6e4@@QAEXXZ
// retail 0x00225492, 60 bytes. Dedicated TU: refresh the class timestamp
// when called on the owning thread (GetCurrentThreadId gate at +0x50), via
// time() under the class critical section. GetCurrentThreadId reaches its
// import through the E8 thunk at 0x6105D0 (pinned C-name import thunk);
// time() binds its IAT slot directly (retail calls it FF15, like the TU).

#ifndef NULL
#define NULL 0
#endif

typedef long time_t;

struct CRITICAL_SECTION
{
    unsigned char data[24];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *section);
extern "C" unsigned long __stdcall GetCurrentThreadId(void);
extern "C" __declspec(dllimport) long __cdecl time(time_t *tod);

class BfmeDfe6e4
{
public:
	void rva00225492();

private:
	// Retail layout: owning thread id at +0x50, timestamp at +0x54,
	// guarded counter at +0x6C, critical section at +0x70.
	unsigned char m_unreconstructed_00[0x50];
	unsigned long m_threadId; // +0x50
	long m_timestamp; // +0x54
	unsigned char m_unreconstructed_58[0x6C - 0x58];
	int m_refCount; // +0x6C
	CRITICAL_SECTION m_cs; // +0x70
};

// ?rva00225492@BfmeDfe6e4@@QAEXXZ
void BfmeDfe6e4::rva00225492()
{
	if (GetCurrentThreadId() != m_threadId) {
		return;
	}
	time_t now;
	time(&now);
	EnterCriticalSection(&m_cs);
	m_timestamp = now;
	LeaveCriticalSection(&m_cs);
}
