// cl: /O1 /MD
//
// ?Rva005BC4CEStart@@YAHH@Z
// retail 0x005BC4CE, 135 bytes (Ghidra FUN_009bc4ce, bytes-to-next 168 trust gate).
// Thread starter waiting on flag 0x00DD3C7C via Sleep(5); callers 0x005BD82E
// support identity. CreateThread/Sleep via dllimport; thread proc at 0x005BC4AE
// pushed as start address; globals use VA names.

extern "C" __declspec(dllimport) void *__stdcall CreateThread(void *attrs, unsigned long stack, unsigned long (__stdcall *start)(void *), void *param, unsigned long flags, unsigned long *tid);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long ms);
extern "C" __declspec(dllimport) void *__stdcall gethostbyname(const char *name);

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// Native accesses establish these widths and addresses; the loaded retail
// initial values are zero except the one-byte completion flag at DD3C7C.
// Their application names follow the BFME 1 donor, not recovered target names.
int g_00E06584;
unsigned long g_00E06580;
unsigned char g_00DD3C7C = 1;
void *g_00E06578;
unsigned char g_00E06575;
unsigned char g_00E06576;

unsigned long __stdcall Rva005BC4AEThread(void *param);

int __cdecl Rva005BC4CEStart(int param)
{
    if (g_00E06584 == 0) {
        g_00DD3C7C = 0;
        g_00E06578 = CreateThread(0, 0, Rva005BC4AEThread, (void *)param, 0, &g_00E06580);
        if (g_00E06578 == 0) {
            return 1;
        }
        g_00E06584 = 1;
    }
    while (g_00DD3C7C == 0) {
        Sleep(5);
    }
    if (g_00E06584 != 1 || g_00DD3C7C == 0)
        return 0;
    _ReadWriteBarrier();
    int result = (g_00E06575 != 0) ? 1 : 0;
    g_00E06584 = 0;
    g_00E06576 = 0;
    g_00E06578 = 0;
    return result + 1;
}

// BFME 1 MainMenuUtils.cpp at 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24
// supplies asyncGethostbynameThreadFunc's semantics. Native 005BC4CE passes
// this callback to CreateThread; 005BC4AE's full 32-byte boundary proves the
// stdcall argument, gethostbyname IAT BBA978, and the two one-byte flag stores.
unsigned long __stdcall Rva005BC4AEThread(void *param)
{
    g_00E06575 = gethostbyname((const char *)param) != 0;
    g_00DD3C7C = 1;
    return 0;
}
