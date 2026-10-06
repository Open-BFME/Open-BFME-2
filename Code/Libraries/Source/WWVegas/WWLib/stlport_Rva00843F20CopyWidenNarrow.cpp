// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 range copies, two of the six bodies in the BFME1 donor
// game/stlport/Rva00843F20CopyWidenNarrow.cpp (b1 0x00843FB0..0x008440C2):
// three wchar_t->char and three char->wchar_t copies that lotrbfme.exe
// ICF-folded onto two bodies. Both land in game.dat as the two addresses
// above, each compiling byte-exact from STLport's random-access _STL::copy.
//
// Retail was linked without identical-COMDAT folding, so each of these two
// addresses has exactly ONE identity, and no caller, vtable slot or symbol
// says which of the donor's three twins it is. Neither row therefore spends a
// twin's name: each keeps the donor's address token under the ?dup_ parking
// convention (the same call as the ?dup_00843ef0@@YAHPBG0PAD@Z row next door
// in Rva008403A0GuardTail.cpp), and the BFME2 RVA is the identity.
//
// Code/stlport/ is not an allowed root for a new source, so the donor bodies
// live in WWLib with the rest of the STLport units (same reason
// stlport_CodecvtWideNarrow.cpp, which owns the neighbouring 0x000174F0
// do_out body, records).
//
// The donor's other four twins are not denied here: they are these same two
// bodies at these same two addresses.

#include <algorithm>

#define WIDEN(NAME) \
wchar_t *NAME(const char *first, const char *last, wchar_t *result) \
{ \
    return _STL::copy(first, last, result); \
}

#define NARROW(NAME) \
char *NAME(const wchar_t *first, const wchar_t *last, char *result) \
{ \
    return _STL::copy(first, last, result); \
}

// ?dup_00843fb0@@YAPADPBG0PAD@Z -- retail 0x00017490, 36B.
// wchar_t -> char copy: source stride 2, byte store, sar ecx,1 count.
NARROW(dup_00843fb0)

// ?dup_00843fe0@@YAPAGPBD0PAG@Z -- retail 0x000174C0, 35B.
// char -> wchar_t copy: movsx sign-extends each source byte into the word.
WIDEN(dup_00843fe0)
