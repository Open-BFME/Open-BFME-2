// cl: /O2 /DNDEBUG /MD /EHs-c-
// Reference: Open-BFME-1@6583b3c1ff21db4a561285717028fdafc780b7db,
// game/Libraries/Source/Apt/Apt.cpp, whole three-function donor. Normal whole
// unit placement finds only this new 34-byte body; the query has an existing
// target recovery at 0x006CD6F0 whose assertion names Apt.cpp independently.
// Target 0x006CD030 is aligned after RET/int3 and ends in RET/int3. It reads
// two stack words, writes the first to VA E176D4 and E176D8, the second to
// E176DC, then clears E176E4. Native consumers use four-byte accesses at all
// four addresses; their initial bytes are zero, and no existing pin/provider
// was found. These are four address-qualified scalar storage providers, with
// no claim about their original names, logical roles or intervening storage.
// No direct/absolute entry reference was observed. The unsigned-word cdecl
// spelling represents the observed stack transport, not original argument
// types, formal count, calling-convention spelling or function identity.
unsigned int g_rva00A176D4 = 0;
unsigned int g_rva00A176D8 = 0;
unsigned int g_rva00A176DC = 0;
unsigned int g_rva00A176E4 = 0;

void __cdecl rva006CD030Store(unsigned int first, unsigned int second)
{
    g_rva00A176D4 = first;
    g_rva00A176D8 = first;
    g_rva00A176DC = second;
    g_rva00A176E4 = 0;
}
