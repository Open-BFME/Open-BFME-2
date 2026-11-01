// cl: /DNDEBUG /MD /Ireference/shims/bfme2_thread /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// platformsdk
#include <windows.h>
#include "thread.h"

// BFME_DX8_Thread_Lock at 0x0011F520.  BFME guards DX8 buffer access with a
// real device mutex where Zero Hour had a thread assert that compiles to
// nothing: the lock waits up to twenty seconds on the handle at 0x00DEC598,
// crashes through the Debug singleton if another thread held it that long,
// then records the owning thread and bumps the recursion count at
// 0x00DEDA88/0x00DEDA8C under the critical section at 0x00DEC540.  The
// release half is BFME_DX8_Thread_Assert at 0x00120F50, in dx8wrapper.cpp.
//
// WaitForSingleObject and the critical-section pair use the import table.
// The thread ID comes from the WWLib wrapper at 0x006105D0.
// /G7 is the tell (add eax,1 for the recursion count).

// Slot layout as Log_DX8_ErrorCode.cpp models it; only the slots called here
// are named.
#include "../../../../GameEngine/Source/Common/debug.h"

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
	if (WaitForSingleObject(bfmeDX8DeviceMutex, 20000) == WAIT_TIMEOUT) {
		if (bfmeRva000387C0()) {
			Debug::SkipNext(true);
			theDebug->SkipNext();
			(theDebug->CrashBegin(0, 0, 0) << "A thread held onto DirectX for more than 20000msec.").CrashDone(2);
		}
	}
	EnterCriticalSection((LPCRITICAL_SECTION)bfmeDX8DeviceSection);
	bfmeDX8DeviceOwner = ThreadClass::_Get_Current_Thread_ID();
	++bfmeDX8DeviceRecursion;
	LeaveCriticalSection((LPCRITICAL_SECTION)bfmeDX8DeviceSection);
}

// 0x0011F5B0: the non-blocking twin -- wait up to the caller's timeout and
// report whether the mutex was taken, with the same owner and recursion
// bookkeeping as the lock.  No Zero Hour counterpart; address-derived name.
bool bfmeRva0011F5B0(unsigned long milliseconds)
{
	if (WaitForSingleObject(bfmeDX8DeviceMutex, milliseconds) == WAIT_TIMEOUT)
		return false;
	EnterCriticalSection((LPCRITICAL_SECTION)bfmeDX8DeviceSection);
	bfmeDX8DeviceOwner = ThreadClass::_Get_Current_Thread_ID();
	++bfmeDX8DeviceRecursion;
	LeaveCriticalSection((LPCRITICAL_SECTION)bfmeDX8DeviceSection);
	return true;
}

// 0x0011F600: whether the calling thread holds the device mutex.  The count
// compares unsigned (jbe).  Address-derived name.
int bfmeRva0011F600()
{
	if (ThreadClass::_Get_Current_Thread_ID() == bfmeDX8DeviceOwner && (unsigned)bfmeDX8DeviceRecursion > 0)
		return 1;
	return 0;
}

// The release half, BFME_DX8_Thread_Assert at 0x00120F50, is defined in
// dx8wrapper.cpp: DX8Wrapper::Init inlines it on its success exit.
bool BFME_DX8_Thread_Assert(void);

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?BFME_DX8_Thread_Assert@@YAXXZ=?BFME_DX8_Thread_Assert@@YA_NXZ")
