// cl: /MD
// Target 24B at 532C..5344 forwards three 32-bit stack arguments to
// MSVCR71.dll!_memicmp, target PE IAT VA BBA690 (DIR32 offset 14).
// Boundary: verified WideCharCompare at 52F8+52 ends exactly here;
// next verified compareNoCase starts at 5344. No E8/E9 or VA callers found.
// A BFME1 xsurface.cpp BlitBackward masked match supplied the lead, but
// its memmove identity is refuted by the target import, not carried over.
// This address-labelled stdcall view preserves the 12B callee stack pop
// and comparison result in EAX; ECX is unused. Original name, member/free
// distinction, return contract and reachability remain unknown.
// These declarations preserve the two actual call forms: the existing
// case-insensitive worker calls its IAT, while memcmp uses the CRT thunk.
extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *, const void *, unsigned);
extern "C" int __cdecl memcmp(const void *, const void *, unsigned);
int __stdcall rva0000532CCompareBytes(const void *left, const void *right, unsigned count)
{
 return _memicmp(left, right, count);
}

// Clean BF1 f989 xsurface.cpp O1/SSE2/G7 supplied the 23-byte forwarder
// shape through BlitPlain<unsigned char>::BlitForward; that blit identity
// is refuted by the target call to the real memcmp thunk at 0x62929E
// (IAT VA 0xBBA694), not memcpy. Native 0x52E1..0x52F8 starts after RET
// 0x52E0 and ends in RET12 before WideCharCompare's prologue at 0x52F8.
// The three stack words pass unchanged and the comparison result remains
// in EAX. ECX is unused; original owner, member/free role and name unknown.
// Reuse the adjacent comparison family and its physical callee-pop ABI.
int __stdcall rva000052E1CompareBytes(const void *left, const void *right, unsigned count)
{
    return memcmp(left, right, count);
}
