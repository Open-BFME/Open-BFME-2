// cl: /Ireference/shims/bfme2_ascii
// ??0Rva005F91F3@@QAE@ABURva005F91F3Src@@@Z, RVA 0x005F91F3, 36 bytes.
// Converting copy: dest {word0 +0, word1 +4, UnicodeString +8} from src
// {header +0, word0 +4, word1 +8, UnicodeString +0xC}. Retail copies
// [eax+4]->[esi], [eax+8]->[esi+4], then StringBase<ushort> copy 0x37050
// from eax+0xC to esi+8, returning this. Evidence: layout matches sibling
// BfmeStringRecord005F93E3/BfmeContainerRecord005FDEC7 (word word wide-string
// stride 12) with source displaced by one leading dword; callers 0x005FA205
// and 0x005FA2CC build a 12-byte temp at ebp-0x24 and destroy its string
// at ebp-0x1C via releaseBuffer 0x36E70.
#include "unicode_string.h"
struct Rva005F91F3Src {
    unsigned int header;
    unsigned int word0;
    unsigned int word1;
    UnicodeString text;
};
struct Rva005F91F3 {
    unsigned int word0;
    unsigned int word1;
    UnicodeString text;
    Rva005F91F3(const Rva005F91F3Src &o);
};
Rva005F91F3::Rva005F91F3(const Rva005F91F3Src &o) : word0(o.word0), word1(o.word1), text(o.text) {}
