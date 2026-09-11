// ?BFME_DX8_Thread_Assert@@YA_NXZ
// partial score=0.85 date=2026-09-10
// ?BFME_DX8_Thread_Assert@@YA_NXZ
// partial score=0.85 date=2026-09-10
// cl: /O1 /MD
//
// BFME_DX8_Thread_Assert, retail 0x00120F50, 90 bytes. Reloc names it
// YAXXZ (void) but the body returns the last-unlock flag in al.
// Prologue through push-ebx matches: GetCurrentThreadId thunk at
// 0x6105D0 then owner compare and a dead recurse load. Leftover:
// /O1 hoists the CS pointer into esi; uses dec eax not sub ecx,1;
// and-zero the owner not mov-imm; push [handle] not mov edx / push edx.

struct CRITICAL_SECTION
{
	int _s[6];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *);
extern "C" __declspec(dllimport) int __stdcall SetEvent(void *);
extern "C" unsigned __stdcall GetCurrentThreadId();

#define g_owner (*(unsigned *)0x00DEDA88)
#define g_recurse (*(unsigned *)0x00DEDA8C)
#define g_cs ((CRITICAL_SECTION *)0x00DEC540)
#define g_event (*(void **)0x00DEC598)

bool BFME_DX8_Thread_Assert()
{
	unsigned tid = GetCurrentThreadId();
	if (tid == g_owner)
		tid = *(volatile unsigned *)0x00DEDA8C;
	EnterCriticalSection(g_cs);
	unsigned rec = g_recurse - 1;
	bool last = rec == 0;
	g_recurse = rec;
	if (last)
		g_owner = 0;
	LeaveCriticalSection(g_cs);
	SetEvent(g_event);
	return last;
}
