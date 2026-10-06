// cl: /MD
// ?Rva0010EFB1Inc@@YAJXZ at 0x0010EFB1 (12B).
// Free wrapper over InterlockedIncrement on the global at 0x009EC38C.
// Evidence: retail push 0x009EC38C; call IAT InterlockedIncrement 0x00BBA214;
// caller at 0x0010F09F stores eax to +0x20; landing this unblocks 0x0010F058.
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *value);

long volatile g_rva0010EFB1Counter;

long Rva0010EFB1Inc()
{
	return InterlockedIncrement(&g_rva0010EFB1Counter);
}
