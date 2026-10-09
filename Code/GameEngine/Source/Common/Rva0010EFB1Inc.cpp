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

// Clean BF1 f98983a7 Common/Rva009587C0Increment.cpp is the whole source
// lead. Native176B50..176B5F/15 is independently INT3-bounded. It passes
// receiver+8 to the actual InterlockedIncrement import at IAT BBA214, then
// reads that same word after the call and returns it; it does not return the
// import's result. Eight-section direct/address scans found no witnesses.
// The Win32 API establishes a 32-bit long operand, but the original owner and
// full object size are unknown. This independent accessed-prefix counter
// view shares only the existing real import declaration, not an owner/layout.
class Rva00176B50Counter {
public:
    long incrementAndRead();
private:
    char prefix[8];
    long count;
};
long Rva00176B50Counter::incrementAndRead() {
    InterlockedIncrement(&count);
    return count;
}
