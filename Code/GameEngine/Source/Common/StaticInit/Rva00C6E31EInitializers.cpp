// cl: /O1 /Oi /MD /O1
//
// Ported from Open-BFME-1 GameEngine/Source/Common/StaticInit/Rva00C6E31EInitializers.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?Rva00C6E31EInitialize@@YAXXZ 0x007B556E (25B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
#include <new>
#include <string.h>

extern "C" int __cdecl atexit(void (__cdecl *callback)());
void Rva00C715CARelease();
void Rva00C715DERelease();

// Four DWORD slots at 0134FB38; cleanup 00C715CA tail-calls 009F6855,
// which walks the four slots and deletes each non-null Win32 DC.
struct Rva0134FB38Storage { unsigned long slots[4]; };
extern Rva0134FB38Storage g_rva0134FB38;

// CRT initializer table slot RVA 00EA5518 proves this entry independently
// of the preceding and following ATL initializers.
void Rva00C6E31EInitialize()
{
    memset(&g_rva0134FB38, 0, sizeof(g_rva0134FB38));
    atexit(Rva00C715CARelease);
}

// The retail constructor at 009F6ADB takes ECX, no stack arguments,
// returns ECX in EAX and ends with RET at 009F6B85. Its object is 60 bytes.
class Rva009F6ADBObject
{
public:
    Rva009F6ADBObject() throw();
private:
    unsigned char storage[60];
};
extern Rva009F6ADBObject g_rva0134FB48;

// CRT initializer table slot RVA 00EA551C proves the start.


