// cl: /DNDEBUG /MD /EHsc /O1 /Ob2
// Donor: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/BfmeCommandLookupYI.cpp, recompiled /O1.
// Target: complete 117B entry at RVA 005257F6, between a preceding RET
// and the next body at 0052586B. Retail independently names the literal
// NonCommand_SelectAllHeroes and loads the established TheControlBar global.
// Static string VA E0495C occupies one pointer before its guard at E04960;
// its registered destructor at 7B9220 tail-calls releaseBuffer at 36410.
// Original callback name and parameter meaning remain unknown.

class Rva005257F6String
{
public:
    Rva005257F6String(const char *text);
    ~Rva005257F6String();
private:
    void *buffer;
};

class Rva005257F6Registry
{
public:
    void *find(const Rva005257F6String &name);
    void use(int zero, void *entry);
};

class ControlBar;
extern ControlBar *TheControlBar;

// One-pointer string ABI and the two receiver calls are read from this
// retail body; all aliases bind existing byte-verified definitions.
#pragma comment(linker, "/alternatename:??0Rva005257F6String@@QAE@PBD@Z=??0?$StringBase@D@@AAE@PBD@Z")
#pragma comment(linker, "/alternatename:??1Rva005257F6String@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")
#pragma comment(linker, "/alternatename:?find@Rva005257F6Registry@@QAEPAXABVRva005257F6String@@@Z=?findCommandButton@ControlBar@@QAEPBVCommandButton@@ABVAsciiString@@@Z")
#pragma comment(linker, "/alternatename:?use@Rva005257F6Registry@@QAEXHPAX@Z=?rva004C1B60@ControlBar@@QAEXPAVGameWindow@@PAX@Z")

// ?rva005257F6@@YGXH@Z
void __stdcall rva005257F6(int unused)
{
    if (TheControlBar == 0)
        return;

    static Rva005257F6String name("NonCommand_SelectAllHeroes");
    void *entry = ((Rva005257F6Registry *)TheControlBar)->find(name);
    if (entry != 0)
        ((Rva005257F6Registry *)TheControlBar)->use(0, entry);
}
