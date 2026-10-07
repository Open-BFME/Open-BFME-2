// cl: /DNDEBUG /MD

// BFME_DX8_Thread_Lock at 0x0011F520.  BFME guards DX8 buffer access with a
// real device mutex where Zero Hour had a thread assert that compiles to
// nothing: the lock waits up to twenty seconds on the handle at 0x00DEC598,
// crashes through the Debug singleton if another thread held it that long,
// then records the owning thread and bumps the recursion count at
// 0x00DEDA88/0x00DEDA8C under the critical section at 0x00DEC540.  The
// release half is BFME_DX8_Thread_Assert at 0x00120F50, in dx8wrapper.cpp.
//
// The imports are declared by hand: WaitForSingleObject and the critical
// section pair go through the import table, while GetCurrentThreadId is called
// through its direct thunk at 0x006105D0, which a dllimport declaration would
// not reach.  /G7 is the tell (add eax,1 for the recursion count).

extern "C" {
__declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long milliseconds);
__declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
__declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);
__declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
unsigned long __stdcall GetCurrentThreadId(void);
}

enum { BFME_WAIT_TIMEOUT = 0x102 };

// Slot layout as Log_DX8_ErrorCode.cpp models it; only the slots called here
// are named.
class Debug
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual Debug &operator<<(const char *text);
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void CrashDone(int mode);
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual void _M_slot_5c();
	virtual void SkipNext();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
	virtual Debug &CrashBegin(const char *file, int line, const char *group);

	static bool SkipNext(bool set);

	char m_bfme0004[0x9F53];
	bool m_bfme9F57;
};

extern Debug *theDebug;

// 0x000387C0: reads the Debug singleton's flag at +0x9F57.
bool bfmeRva000387C0();

// The device mutex and its recursion bookkeeping.
extern void *bfmeDX8DeviceMutex;				// 0x00DEC598
// bfmeDX8DeviceMutex: matched references place it at VA 0xdec598 (zero-filled .bss).
void * bfmeDX8DeviceMutex;
// bfmeDX8DeviceSection: matched references place it at VA 0xdec540 (zero-filled).
unsigned char bfmeDX8DeviceSection[24] = { 0 };
// Volatile like the count: the try-lock stores the owner before it reads the
// count, where a plain store is scheduled after the volatile read.
// Defined here (zero-filled .bss, 4 bytes); this unit's lock/unlock pair are
// among its referencing functions (data_xrefs).
volatile unsigned long bfmeDX8DeviceOwner = 0;		// 0x00DEDA88
// Volatile: retail loads, adds and stores the count as three instructions
// with the next push scheduled between them, where a plain int is a single
// add to memory.
volatile int bfmeDX8DeviceRecursion = 0;			// 0x00DEDA8C

void BFME_DX8_Thread_Lock(void)
{
	if (WaitForSingleObject(bfmeDX8DeviceMutex, 20000) == BFME_WAIT_TIMEOUT) {
		if (bfmeRva000387C0()) {
			Debug::SkipNext(true);
			theDebug->SkipNext();
			(theDebug->CrashBegin(0, 0, 0) << "A thread held onto DirectX for more than 20000msec.").CrashDone(2);
		}
	}
	EnterCriticalSection(bfmeDX8DeviceSection);
	bfmeDX8DeviceOwner = GetCurrentThreadId();
	++bfmeDX8DeviceRecursion;
	LeaveCriticalSection(bfmeDX8DeviceSection);
}

// 0x0011F5B0: the non-blocking twin -- wait up to the caller's timeout and
// report whether the mutex was taken, with the same owner and recursion
// bookkeeping as the lock.  No Zero Hour counterpart; address-derived name.
bool bfmeRva0011F5B0(unsigned long milliseconds)
{
	if (WaitForSingleObject(bfmeDX8DeviceMutex, milliseconds) == BFME_WAIT_TIMEOUT)
		return false;
	EnterCriticalSection(bfmeDX8DeviceSection);
	bfmeDX8DeviceOwner = GetCurrentThreadId();
	++bfmeDX8DeviceRecursion;
	LeaveCriticalSection(bfmeDX8DeviceSection);
	return true;
}

// 0x0011F600: whether the calling thread holds the device mutex.  The count
// compares unsigned (jbe).  Address-derived name.
int bfmeRva0011F600()
{
	if (GetCurrentThreadId() == bfmeDX8DeviceOwner && (unsigned)bfmeDX8DeviceRecursion > 0)
		return 1;
	return 0;
}

// The release half, BFME_DX8_Thread_Assert at 0x00120F50, is defined in
// dx8wrapper.cpp: DX8Wrapper::Init inlines it on its success exit.
bool BFME_DX8_Thread_Assert(void);

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?BFME_DX8_Thread_Assert@@YAXXZ=?BFME_DX8_Thread_Assert@@YA_NXZ")

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?W3DRadarResetLock@@YAXXZ=?BFME_DX8_Thread_Lock@@YAXXZ")
