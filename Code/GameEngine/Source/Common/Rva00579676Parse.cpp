// cl: /MD
// ?Rva00579676Parse@@YA_NPBDPAH@Z @0x00579676 (32B): atoi range check 0<=v<6
// (unlock lane, missing callee of 0x00579B81/0x00579C00 delegate methods).
// Parses int via IAT atoi, rejects <0 or >=6, stores to *out and returns true.
// Evidence: callers at 0x00579B95 and 0x00579C0D (push value then address,
// caller cleans via pop ecx pop ecx, so __cdecl); IAT FF15 atoi needs
// dllimport; pop ecx cleanup and xor-al false indicate /O1. Free-function
// honest Rva name with Parse verb.
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);

bool __cdecl Rva00579676Parse(const char *s, int *out)
{
    int v = atoi(s);
    if (v < 0 || v >= 6)
        return false;
    *out = v;
    return true;
}
