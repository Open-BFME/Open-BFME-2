// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// Retail 0x003821E2..0x00382216 (52 bytes), Ghidra FUN_007821e2.
// Native callers include 0x00383980, 0x005A2A2B and 0x005A2CC6.
// Assigns the by-value UnicodeString to the field at +4, then releases
// the argument. Target calls prove StringBase<unsigned short>::set and
// releaseBuffer. The ZH GameSlot::setName body supplied the source pattern,
// but its class identity is contradicted by the matched GameSlot layout:
// GameSlot::isPlayer uses +4 as state and +0x30 as its name. Keep the owner
// and field purpose unknown; only this body's +4 string storage is proven.
#include "unicode_string.h"

class Rva003821E2
{
    char prefix[4];
    UnicodeString value;
public:
    void assign(UnicodeString text);
};

void Rva003821E2::assign(UnicodeString text)
{
    value = text;
}
