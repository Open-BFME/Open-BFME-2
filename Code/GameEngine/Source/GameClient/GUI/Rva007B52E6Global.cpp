// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// Target GUI-string global: startup 0x007B52E6 uses "UpgradeUnitButton",
// constructs the address-named object at VA0x00E06900 through rowed5E16DA,
// and registers the cleanup at0x007B9A05. Its application class name is unknown.
// Constructor and destructor ABI reuse the existing recovered Rva005E16DA
// bodies; their four post-vptr words cover the observed 20-byte object.
// The constructor's existing int declaration is a one-word ABI view. Retail
// passes the ADDRESS of an AsciiString temporary, not an integer identifier.

#include "ascii_string.h"
extern "C" int __cdecl atexit(void (__cdecl *callback)());

class Rva005E16DA {
public:
    Rva005E16DA(int argumentWord);
    virtual ~Rva005E16DA();
private:
    unsigned int opaqueWords[4];
};

extern Rva005E16DA g_rva00E06900;

void rva007B9A05()
{
    g_rva00E06900.~Rva005E16DA();
}

void rva007B52E6()
{
    {
        AsciiString label("UpgradeUnitButton");
        // MSVC's explicit constructor invocation also backs the shared
        // AsciiString adapter. This is static storage, with no allocation.
        g_rva00E06900.Rva005E16DA::Rva005E16DA(reinterpret_cast<int>(&label));
    }
    atexit(rva007B9A05);
}

extern Rva005E16DA g_rva00E068EC;
// Exact callback address registered by startup7B5299; mov-this/tail-jump
// spans7B99FB..7B9A04 and reaches the same rowed destructor5E16FD.
void rva007B99FB()
{
    g_rva00E068EC.~Rva005E16DA();
}

// Complete startup body7B5299..7B52E5, followed by initializer7B52E6.
void rva007B5299()
{
    {
        AsciiString label("CancelArmyMemberMoveButton");
        g_rva00E068EC.Rva005E16DA::Rva005E16DA(reinterpret_cast<int>(&label));
    }
    atexit(rva007B99FB);
}

extern Rva005E16DA g_rva00E06918;
// Callback7B9A0F..7B9A18 registered by startup7B5343.
void rva007B9A0F()
{
    g_rva00E06918.~Rva005E16DA();
}

// Complete startup7B5343..7B538F followed by a different initializer7B5390.
void rva007B5343()
{
    {
        AsciiString label("DisbandArmyMemberButton");
        g_rva00E06918.Rva005E16DA::Rva005E16DA(reinterpret_cast<int>(&label));
    }
    atexit(rva007B9A0F);
}

extern Rva005E16DA g_rva00E0675C;
// Callback7B998D..7B9996 registered by startup7B5134.
void rva007B998D()
{
    g_rva00E0675C.~Rva005E16DA();
}

// Ghidra77B startup7B5134..7B5180.
void rva007B5134()
{
    {
        AsciiString label("CancelArmyMoveButton");
        g_rva00E0675C.Rva005E16DA::Rva005E16DA(reinterpret_cast<int>(&label));
    }
    atexit(rva007B998D);
}
