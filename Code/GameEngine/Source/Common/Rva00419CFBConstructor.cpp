// cl: /O1 /arch:SSE /G7 /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ??0Rva00419CFB@@QAE@PAX@Z at 0x00419CFB (29 bytes). The caller allocates
// 0x54 bytes and passes its LockClass address; retail calls the ThreadClass
// null-name constructor, stores that pointer at +0x50, and installs vtable
// 0x0083AD60. The class identity is unknown; its base and layout follow the
// target constructor and caller rather than donor naming.
// The retail table at RVA 0x0083AD60: 3 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva00419E38@@UAEPAXI@Z")();
void __identifier("?Execute@ThreadClass@@UAEXXZ")();
void __identifier("?Thread_Function@GameResultsThreadClass@@UAEXXZ")();
}
extern const void *const g_00C3AD60[3] = {
	(const void *)&__identifier("??_GRva00419E38@@UAEPAXI@Z"), // slot 0 0x00419E1C
	(const void *)&__identifier("?Execute@ThreadClass@@UAEXXZ"), // slot 1 0x006104B0
	(const void *)&__identifier("?Thread_Function@GameResultsThreadClass@@UAEXXZ"), // slot 2 0x0041A843
};

#include "../../../Libraries/Source/WWVegas/WWLib/ThreadClass.h"

class __declspec(novtable) Rva00419CFB : public ThreadClass
{
public:
    Rva00419CFB(void *lock);

private:
    void *m_lock;
};

Rva00419CFB::Rva00419CFB(void *lock) : ThreadClass(0)
{
    m_lock = lock;
    *(const void **)this = g_00C3AD60;
}
