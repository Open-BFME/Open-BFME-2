// cl: /Ireference/shims/bfme2_ascii /MD
#include "ascii_string.h"
// ?OpenScreen@AptSaveLoad@@SAXHH_N@Z @0x00434160 120B: AptSaveLoad::OpenScreen (WorldBuilder AptSaveLoad.cpp:559 s_instance assert, same "SaveLoad.apt" push); static init storing 3 args into struct at AptSaveLoad::s_instance after Shell::push("SaveLoad.apt",false); evidence packet callees Shell::push pin and StringBase row, callers 0x00446443 0x00515C64, globals AptSaveLoad::s_instance g_Va00A01E48.
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
class AptSaveLoad
{
public:
	static AptSaveLoad *s_instance;
    static void OpenScreen(int a1, int flags, bool a3);
};
void AptSaveLoad::OpenScreen(int a1, int flags, bool a3)
{
    if (AptSaveLoad::s_instance != 0)
        return;
    ((Shell *)(*(GlobalA01E48 **)&TheShell))->push(AsciiString("SaveLoad.apt"), false);
    ((State00434160 *)AptSaveLoad::s_instance)->f294 = a1;
    ((State00434160 *)AptSaveLoad::s_instance)->f298 = flags;
    int c = 1;
    if (flags & c)
        ((State00434160 *)AptSaveLoad::s_instance)->f2a0 = c;
    else {
        c = 2;
        if (flags & c)
            ((State00434160 *)AptSaveLoad::s_instance)->f2a0 = c;
        else {
            c = 4;
            if (flags & c)
                ((State00434160 *)AptSaveLoad::s_instance)->f2a0 = c;
        }
    }
    ((State00434160 *)AptSaveLoad::s_instance)->f29c = a3;
}
