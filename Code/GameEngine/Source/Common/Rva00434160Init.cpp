// cl: /Ireference/shims/bfme2_ascii /MD
#include "ascii_string.h"
// ?Rva00434160Init@@YAXHH_N@Z @0x00434160 120B: free init storing 3 args into struct at g_Va00E032E0 after Shell::push("SaveLoad.apt",false); evidence packet callees Shell::push pin and StringBase row, callers 0x00446443 0x00515C64, globals g_Va00E032E0 g_Va00A01E48.
extern int g_Va00E032E0;
struct GlobalA01E48;
extern class Shell *TheShell;
class Shell {
public:
    void push(AsciiString s, bool flag);
};
struct State00434160 {
    char pad[0x294];
    int f294;
    int f298;
    unsigned char f29c;
    char pad2[3];
    int f2a0;
};
void Rva00434160Init(int a1, int a2, bool a3)
{
    if (g_Va00E032E0 != 0)
        return;
    ((Shell *)(*(GlobalA01E48 **)&TheShell))->push(AsciiString("SaveLoad.apt"), false);
    ((State00434160 *)g_Va00E032E0)->f294 = a1;
    ((State00434160 *)g_Va00E032E0)->f298 = a2;
    int c = 1;
    if (a2 & c)
        ((State00434160 *)g_Va00E032E0)->f2a0 = c;
    else {
        c = 2;
        if (a2 & c)
            ((State00434160 *)g_Va00E032E0)->f2a0 = c;
        else {
            c = 4;
            if (a2 & c)
                ((State00434160 *)g_Va00E032E0)->f2a0 = c;
        }
    }
    ((State00434160 *)g_Va00E032E0)->f29c = a3;
}
