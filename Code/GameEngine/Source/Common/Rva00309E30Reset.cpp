// cl: /O1 /MD
// BFME1 donor: game/GameEngine/Source/Common/Bfme5TinyTwentySeven.cpp,
// revision 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24, bfmeReset().
// Target identity is address-based: Ghidra records the complete27B entry
// 0x00309E30, and native call0x0023B30A independently reaches that entry.
// Target copies36B from VA DBD7B8 to DBD7DC and sets byteDFF48C to1.
// Native initial bytes establish both full blocks and the initial false flag.
// The storage below preserves those bits; original record types, field
// meanings, global names and the function name remain unknown.

struct Rva00309E30Words
{
    unsigned int opaque00[9];
};

Rva00309E30Words g_Rva009BD7B8 = { {0, 17, 0x3F800000, 0x100, 0, 0, 0, 0, 0} };
Rva00309E30Words g_Rva009BD7DC = { {0, 17, 0x3F800000, 0x100, 0, 0, 0, 0, 0} };
bool g_Rva009FF48C = false;

void rva00309E30()
{
    g_Rva009BD7DC = g_Rva009BD7B8;
    g_Rva009FF48C = true;
}
