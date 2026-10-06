// Reference: BFME1 unicode_string.cpp constructor and translation family,
// reconciled with BFME2's explicitly exported cross-charset constructor.
// Export ??0UnicodeString@@QAE@ABVAsciiString@@@Z identifies6CB6D0 (91B).
// Masked code also matches the reverse conversion at38250; the export and
// callee translate(const char*)6CB5F0 prove this identity independently.
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "ascii_string.h"
#include "unicode_string.h"
// LINK-COMDAT: StringBase<G> default ctor kept as /O1 (and) from
// unicode_string.cpp; file is /O1 so the COMDAT matches, row below forced to
// /O2 via t on / s off to keep its 91B match.
#pragma optimize("t", on)
#pragma optimize("s", off)
UnicodeString::UnicodeString(const AsciiString& text) {
    translate(text.str());
}
#pragma optimize("", on)
