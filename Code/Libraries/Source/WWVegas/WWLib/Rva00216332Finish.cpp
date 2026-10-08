// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// class-gate: allow AsciiString shared str uses local empty vs retail global empty 0x00216332
// ?Rva00216332Call@@YAHPAX0PBDPBIPBQAX@Z @0x00216332 104B uint-keyed Apt invoke with AsciiString temp.
// Evidence: uint deref at 0x14 via rowed Rva0022288EGet 0x0022288E extra ptr double-deref at 0x18 rowed invoke 0x00222A8B caller 0x00216850.
// Twin of landed Rva00216517Fire 0x00216517. The forceinline helper takes the
// AsciiString temporary by reference and performs the *extra load between the
// hidden-return m_data read and the empty-string ternary, which is the exact
// retail evaluation order; reading s.m_data from a named local instead emits
// [ebp-0x10] where retail keeps the sret pointer in EAX.
#include "ascii_string.h"

AsciiString Rva0022288EGet(unsigned int val);

class Rva00222A8BTarget
{
public:
    int invoke(void *level, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};


__forceinline const char *GetStr00216332(const AsciiString &s, void *const *extra, void **a1)
{
	char *t = *(char **)(void *)&s;
	*a1 = *(void **)extra;
	return t ? t + 8 : "";
}

int __cdecl Rva00216332Call(void *target, void *level, const char *func, const unsigned int *val, void *const *extra)
{
    void *a1;
    return ((Rva00222A8BTarget *)target)->invoke(level, func, 2, GetStr00216332(Rva0022288EGet(*val), extra, &a1), a1, 0, 0, 0);
}
