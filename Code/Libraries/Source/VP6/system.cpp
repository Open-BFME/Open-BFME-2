// cl: /O2 /G6 /MD
// Clean-room implementation from reverse/vp6_cleanroom/specs/001b9000.md,
// 001b9020.md and 001b9030.md. Names come from the reviewed specifications;
// retail establishes each cdecl boundary, argument and Windows import.
// No decoder source was consulted.
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(
    void *, const char *, const char *, unsigned int);
extern "C" __declspec(dllimport) void *__stdcall GlobalAlloc(
    unsigned int, unsigned int);
extern "C" __declspec(dllimport) void *__stdcall GlobalFree(void *);

// RVA 0x001B9000..0x001B9015: caller-owned message; task-modal warning.
extern "C" void __cdecl VP6_IssueWarning(const char *message)
{
    MessageBoxA(0, message, 0, 0x2030);
}

// RVA 0x001B9020..0x001B902E: fixed zero-initialized allocation.
// The spelling Sytem is the name carried by the reviewed specification.
extern "C" void *__cdecl VP6_SytemGlobalAlloc(unsigned int size)
{
    return GlobalAlloc(0x40, size);
}

// RVA 0x001B9030..0x001B903C: preserve GlobalFree's return value.
extern "C" void *__cdecl VP6_SystemGlobalFree(void *pointer)
{
    return GlobalFree(pointer);
}
