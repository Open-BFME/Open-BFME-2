// cl: /O2 /DNDEBUG /MD
// Target reconstruction: complete Ghidra boundary 0x007B9A50, 40B,
// registered through CRT atexit by the 12B body at 0x007B5410.
// The global head's original name and node payload are unknown. Retail
// saves each first-word next pointer, frees the node through the matched
// game allocator _free (0x00030830), then updates the global at VA E07C08.
// Retail calls free (the game allocator at 0x00030830) and atexit through
// their direct-call thunks, not the IAT: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

struct RvaCleanupNode
{
    RvaCleanupNode *next;
};
// g_chainHeadAtE07C08: matched references place it at VA 0xe07c08 (retail .data initial value 0).
RvaCleanupNode * g_chainHeadAtE07C08 = 0;
// g_chainHeadAtE1D060: matched references place it at VA 0xe1d060 (retail .data initial value 0).
RvaCleanupNode * g_chainHeadAtE1D060 = 0;

void rva007B9A50()
{
    while (g_chainHeadAtE07C08) {
        RvaCleanupNode *next = g_chainHeadAtE07C08->next;
        free(g_chainHeadAtE07C08);
        g_chainHeadAtE07C08 = next;
    }
}

// Independently proven 40B boundary at 0x007B9C80 and atexit registration
// at 0x007B67F0. This is a second list, with its own global at VA E1D060.
void rva007B9C80()
{
    while (g_chainHeadAtE1D060) {
        RvaCleanupNode *next = g_chainHeadAtE1D060->next;
        free(g_chainHeadAtE1D060);
        g_chainHeadAtE1D060 = next;
    }
}

// 12B registration body, bounded by int3 at 7B540F and after ret7B541B.
void rva007B5410()
{
    atexit(rva007B9A50);
}

// Independent 12B registration bounded by int3 and ret at 0x007B67FB.
void rva007B67F0()
{
    atexit(rva007B9C80);
}

// Three more lists of the same shape, each with its own 40-byte cleanup and
// 12-byte atexit registration (byte-identical to the pairs above but for the
// head and cleanup operands). Each head is zero-filled .bss that only its
// cleanup references, so it is defined here.

RvaCleanupNode *g_chainHeadAtDF3680;

void rva007B7130()
{
    while (g_chainHeadAtDF3680) {
        RvaCleanupNode *next = g_chainHeadAtDF3680->next;
        free(g_chainHeadAtDF3680);
        g_chainHeadAtDF3680 = next;
    }
}

// 12B registration at 0x007ACE10, bounded by int3/ret on both sides.
void rva007ACE10()
{
    atexit(rva007B7130);
}

RvaCleanupNode *g_chainHeadAtDF3694;

void rva007B7160()
{
    while (g_chainHeadAtDF3694) {
        RvaCleanupNode *next = g_chainHeadAtDF3694->next;
        free(g_chainHeadAtDF3694);
        g_chainHeadAtDF3694 = next;
    }
}

// 12B registration at 0x007ACE20, bounded by int3/ret on both sides.
void rva007ACE20()
{
    atexit(rva007B7160);
}

RvaCleanupNode *g_chainHeadAtDFCEC8;

void rva007B74C0()
{
    while (g_chainHeadAtDFCEC8) {
        RvaCleanupNode *next = g_chainHeadAtDFCEC8->next;
        free(g_chainHeadAtDFCEC8);
        g_chainHeadAtDFCEC8 = next;
    }
}

// 12B registration at 0x007ACF90, bounded by int3/ret on both sides.
void rva007ACF90()
{
    atexit(rva007B74C0);
}

// The 24-byte-node pool at VA 0x00DB424C (built at static-init time by
// Rva007ABEF3ArgCtorInits::rva007ABEF3 through 0x0006EFC8(0, -1)) gets the
// same cleanup/registration pair: 0x007B70F0 (51B) pops every block off the
// pool's allocated-block list (+4) and hands each to the pool's free
// callback (+0x10, context +0x14) -- the six-word layout Rva002E8548Pool.h
// documents for the sibling pools at DB9440 / DBD4C8 -- and the 12B body at
// 0x007ACE00 registers it. Address names.
struct Rva007B70F0Pool
{
    int m_count;
    void *m_blocks;
    void *m_head;
    void *(__cdecl *m_alloc)(int size, int context);
    void (__cdecl *m_free)(void *block, int context);
    int m_context;
};

class Rva0006EFC8;
extern Rva0006EFC8 g_BfmeSceneNodePool; // owned by Rva0006EFC8Grow.cpp (VA 0xDB424C)

void rva007B70F0()
{
    Rva007B70F0Pool *pool = (Rva007B70F0Pool *)&g_BfmeSceneNodePool;
    void *block = pool->m_blocks;
    while (block != 0) {
        pool->m_blocks = *(void **)block;
        pool->m_free(block, pool->m_context);
        block = pool->m_blocks;
    }
}

void rva007ACE00()
{
    atexit(rva007B70F0);
}

// Zero Hour profile.cpp's namespace-scope initializers as BFME2 runs them from
// the startup strip, written (like the bodies above) as explicit
// address-named functions storing their globals:
//
//   static ProfileCmdInterface &cmd=*(ProfileCmdInterface *)new
//       (ProfileAllocMemory(sizeof(ProfileCmdInterface))) ProfileCmdInterface();
//   static bool __RegisterDebugCmdGroup_Profile=Debug::AddCommands("profile",&cmd);
//   int profileTracerInit=atexit(ProfileShutdown);
//
// BFME2 keeps `cmd` as a pointer (0x00E0C1F8, defined in profile.cpp),
// registers it through slot 0x84 of the Debug object at theDebug (0x00DE0880)
// into the byte at 0x00E0C1FC, and keeps the atexit result at 0x00E0C208.
// The command interface comes from internal_cmd.h (vtable, numResFunc,
// resFunc) and theDebug from debug.h.
inline void *operator new(unsigned int, void *where) throw() { return where; }

class ProfileResultInterface;
// This unit uses the interface only as ProfileCmdInterface's abstract base.
// Its two-slot header view must not emit a stand-alone DebugCmdInterface table.
#define DebugCmdInterface __declspec(dllimport) __declspec(novtable) DebugCmdInterface
#include "../../../../Libraries/Source/debug/debug.h"
#undef DebugCmdInterface
#include "../../../../Libraries/Source/profile/internal_cmd.h"
#include "../../../../Libraries/Source/profile/profile.h"

// Slot 0x84 of the Debug object: the command-group registration debug.h
// leaves unnamed.
class Rva007B66C0DebugCommands
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
    virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
    virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
    virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
    virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
    virtual void slot80();
    virtual bool AddCommands(const char *cmdgroup, DebugCmdInterface *cmdif); // +0x84
};

void *ProfileAllocMemory(unsigned numBytes);
void ProfileShutdown(void);
extern ProfileCmdInterface *cmd;

bool __RegisterDebugCmdGroup_Profile;
int profileTracerInit;

// 0x007B6690 (42B): the command interface, placement-built in profile memory.
void rva007B6690()
{
    // Zero Hour's reference form; assigning the new-expression directly
    // stores the null path from ecx instead of retail's fresh xor eax.
    ProfileCmdInterface &ref = *(ProfileCmdInterface *)new (ProfileAllocMemory(sizeof(ProfileCmdInterface))) ProfileCmdInterface();
    cmd = &ref;
}

// 0x007B66C0 (32B): register it as the "profile" command group.
void rva007B66C0()
{
    __RegisterDebugCmdGroup_Profile = ((Rva007B66C0DebugCommands *)theDebug)->AddCommands("profile", cmd);
}

// 0x007B66E0 (17B): Zero Hour's `__int64 Profile::m_clockCycles=GetClockCyclesFast();`
// (the static is defined in profile.cpp at 0x00E0C200), between the command
// registration and the atexit entry in the startup strip, as in Zero Hour's
// profile.cpp.
__int64 GetClockCyclesFast(void);
void rva007B66E0()
{
    Profile::m_clockCycles = GetClockCyclesFast();
}

// 0x007B6700 (19B): profileTracerInit = atexit(ProfileShutdown).
void rva007B6700()
{
    profileTracerInit = atexit(ProfileShutdown);
}

// 0x007B77EC (16B): atexit cleanup of the reference-counted pointer at
// VA 0x00DFEBE4 -- the inline RefCountPtr release, tail-calling the rowed
// OpaqueRefCounted::Release_Ref (0x00050ED3) when it is set. Address names.
#include "../../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"
// Native loader-zero pointer, released by the registered cleanup below.
OpaqueRefCounted *g_Va00DFEBE4;

void rva007B77EC()
{
    if (g_Va00DFEBE4)
        g_Va00DFEBE4->Release_Ref();
}
