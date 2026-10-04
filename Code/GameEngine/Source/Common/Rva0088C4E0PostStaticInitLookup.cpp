// cl: /O1 /DNDEBUG /MD /EHsc
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/Rva0088C4E0PostStaticInitLookup.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// rva0088C4E0PostStaticInitLookup 0x0003B7F0 (31B). Callee addresses are read
// off retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// RVA 0x0088C4E0: resolve the debug initializer and tail-call it.
#include "../../../../reference/open-bfme-1/game/GameEngine/Source/Common/debug.h"

extern "C" __declspec(dllimport) void *__stdcall GetModuleHandleA(const char *moduleName);
extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(void *module, const char *symbolName);

typedef int (__cdecl *Rva0088C4E0Initializer)();

int rva0088C4E0PostStaticInitLookup()
{
    void *module = GetModuleHandleA(0);
    Rva0088C4E0Initializer initializer =
        (Rva0088C4E0Initializer)GetProcAddress(module, "?PostStaticInit@Debug@@CAXXZ");
    if (!initializer)
        initializer = (Rva0088C4E0Initializer)&Debug::PostStaticInit;
    return initializer();
}
