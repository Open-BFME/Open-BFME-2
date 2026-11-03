// cl: /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Target 0x0006577F: pool lock with an atomic test-and-set and a yield on contention.

// The ObjectPool/WWLib callers spell this body as the pool-domain
// FastCriticalSectionClass::LockClass::spin(unsigned*), __fastcall with the
// lock word in ECX -- the same register this thiscall takes -- and its
// symbols.csv pin is this address. Bind that spelling here.
#pragma comment(linker, "/alternatename:?spin@LockClass@FastCriticalSectionClass@@CIXPAI@Z=?Lock@BFMEPoolCriticalSection@@QAEXXZ")
#include "bfme_pool_critical_section.h"

#include "ThreadClass.h"

void BFMEPoolCriticalSection::Lock()
{
    volatile unsigned int *lockWord = &m_locked;
    __asm mov ebx, lockWord
    __asm lock bts dword ptr [ebx], 0
    __asm jc retry
    __asm jmp acquired
retry:
    ThreadClass::Switch_Thread();
    __asm mov ebx, lockWord
    __asm lock bts dword ptr [ebx], 0
    __asm jc retry
acquired:
    ;
}
