// cl: /Ireference/shims/bfme2_ascii /MD
#include "ascii_string.h"
// ?Rva0052192DInit@@YAXH@Z retail 0x0052192D 74B
// Evidence: chain via Shell::push 0x0035C74A; callers 0x00515C64; strings Skirmish.apt; globals g_00E04930 g_00DD179C g_Va00A01E48 TheRva00222A8BTarget; callees StringBase 0x00037BA0 Shell::push 0x0035C74A rva002233A6 0x002233A6; precedent Rva00434160Init same Shell push pattern.
extern int g_00E04930;
// g_00E04930: matched references place it at VA 0xe04930 (zero-filled .bss).
int g_00E04930;
extern int g_00DD179C;
// g_00DD179C: matched references place it at VA 0xdd179c (retail .data initial value -1).
int g_00DD179C = -1;
struct GlobalA01E48;
extern class Shell *TheShell;
class Shell {
public:
    void push(AsciiString s, bool flag);
};
class Rva00222A8BTarget {
public:
    void rva002233A6(int v);
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

void Rva0052192DInit(int a1)
{
    if (g_00E04930 != 0)
        return;
    g_00DD179C = a1;
    ((Shell *)(*(GlobalA01E48 **)&TheShell))->push(AsciiString("Skirmish.apt"), false);
    if (g_00E04930 == 0)
        return;
    (*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->rva002233A6(1);
}
