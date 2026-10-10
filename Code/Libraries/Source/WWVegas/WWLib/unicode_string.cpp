// cl: /O1 /Ireference/shims/bfme2_ascii

typedef unsigned short wchar_t;
// Upstream implementation and layout: Open-BFME-1 unicode_string.h; the class is the shared
// one in reference/shims/bfme2_ascii/unicode_string.h.
#include "unicode_string.h"

// Zero Hour's UnicodeString.cpp defines the shared empty string here; retail
// keeps it in .bss at VA 0x00E0C898, the address every reader in the ledger
// loads (GadgetTextEntryGetText, GameInfo::clearSlotList, ...).
UnicodeString UnicodeString::TheEmptyString;

// Every member unicode_string.h defines in its class is a header inline in retail
// (game.dat calls none of these copies; 161+ units emit them as select-any
// COMDATs), so a plain definition here collided with those copies at link time.
// Retail keeps one out-of-line copy of each for the exports; this anchor only
// makes this unit emit its copy for the ledger rows. It is not retail code.
#pragma inline_depth(0)
// ?_bfmeUnicodeStringInlineAnchor@@YAXPAVUnicodeString@@PBG@Z absent-from-retail
void _bfmeUnicodeStringInlineAnchor(UnicodeString *string, const wchar_t *text)
{
    string->UnicodeString::UnicodeString();
    string->UnicodeString::UnicodeString(*string);
    string->UnicodeString::UnicodeString(*text);
    string->UnicodeString::UnicodeString(text);
    string->UnicodeString::UnicodeString(text, 0);
    string->UnicodeString::UnicodeString(*string, 0, 0);
    *string = *string;
    *string = *text;
    *string = text;
    *string += *string;
    *string += *text;
    *string += text;
    string->UnicodeString::~UnicodeString();
}
#pragma inline_depth()

// Whole9B retail387DCF..387DD8: cdecl receiver to owned UnicodeString dtor5B804E.
// Adjacent owned lower_bound ends387DCF and mapfind begins387DD8; original
// wrapper/record spelling unknown. BF1575ba2b04 UnicodeStringListCtorNothrow
// supplies the clean destruction-forward lead, not target template identity.
void __cdecl rva00387DCFUnicodeDestroy(void *receiver)
{
    static_cast<UnicodeString *>(receiver)->~UnicodeString();
}
