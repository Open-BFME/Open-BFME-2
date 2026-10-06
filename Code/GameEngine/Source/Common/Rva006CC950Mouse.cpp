// cl: /DNDEBUG /MD /EHs-c-
// ?Rva006CC950SetMousePos@@YAXHH@Z @0x006CC950 65B.
// Forwards mouse position to Apt when initialized; warns via log tail-jump
// otherwise. Evidence: chain lane packet; globals E17700/E176D4/E176D0;
// callee rva006E3580 rowed; warning string pinned by string_xrefs.
void __cdecl Rva006CC110Log(int level, const char *fmt, ...);
class Rva006E34D0
{
public:
    void rva006E3580(int x, int y);
};
extern int g_bfmeAptInitAtE17700;
// g_bfmeAptInitAtE17700: matched references place it at VA 0xe17700 (zero-filled .bss).
int g_bfmeAptInitAtE17700;
extern int g_bfmeAptFlagAtE176D4;
// g_bfmeAptFlagAtE176D4: matched references place it at VA 0xe176d4 (zero-filled .bss).
int g_bfmeAptFlagAtE176D4;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
// g_bfmeAptPtrAtE176D0: matched references place it at VA 0xe176d0 (zero-filled .bss).
Rva006E34D0 * g_bfmeAptPtrAtE176D0;
void __cdecl Rva006CC950SetMousePos(int x, int y)
{
    if (!g_bfmeAptInitAtE17700)
        return Rva006CC110Log(0, "WARNING: trying to set mouse position when Apt not initalized\n");
    if (g_bfmeAptFlagAtE176D4)
        return;
    Rva006E34D0 *p = g_bfmeAptPtrAtE176D0;
    if (!p)
        return;
    p->rva006E3580(x, y);
}
