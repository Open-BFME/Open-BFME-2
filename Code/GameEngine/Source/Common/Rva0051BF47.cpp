// cl: /DNDEBUG /MD
// ?Rva0051BF47Run@@YAXXZ @0x0051BF47 46B
// evidence: unlock lane, caller 0x0051C160 (no args void), callees rowed enable 0x00222479 plus vslot 0x28 plus pin AptTimeLine 0x0051ED7E, globals g_00E04914 g_Va00A01E48 TheRva00222A8BTarget
extern int g_00E04914;

struct GlobalA01E48
{
    char _pad[0x54];
    unsigned char m_54;
};
extern class Shell *TheShell;

#include "../../Include/Common/Rva00222479ByteOneSetter.h"

#include "../../Include/Common/Rva00222A8BTarget.h"
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

void Rva0051ED7ETail();

void Rva0051BF47Run()
{
    if (g_00E04914 == 0)
        return;
    (*(GlobalA01E48 **)&TheShell)->m_54 = 1;
    ((Rva00222479ByteOneSetter *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->enable();
    (*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->v10();
    Rva0051ED7ETail();
}

// The retail call in this body reads 0x0051ED7E, an address the ledger already
// carries as ?rva0051ED7E@AptTimeLine@@QAEXXZ. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?Rva0051ED7ETail@@YAXXZ=?rva0051ED7E@AptTimeLine@@QAEXXZ")
