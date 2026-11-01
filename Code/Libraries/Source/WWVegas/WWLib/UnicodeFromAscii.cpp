// Reference: BFME1 unicode_string.cpp constructor and translation family,
// reconciled with BFME2's explicitly exported cross-charset constructor.
// Export ??0UnicodeString@@QAE@ABVAsciiString@@@Z identifies6CB6D0 (91B).
// Masked code also matches the reverse conversion at38250; the export and
// callee translate(const char*)6CB5F0 prove this identity independently.
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "ascii_string.h"
// StringBase<unsigned short>::StringBase() is otherwise emitted here as a
// losing COMDAT (string_base_clear.cpp owns the kept copy); TU-local
// dllimport+forceinline specialization of the same one-store body.
template <> __declspec(dllimport) __forceinline
StringBase<unsigned short>::StringBase() : m_data(0) {}
#include "unicode_string.h"
UnicodeString::UnicodeString(const AsciiString& text) {
    translate(text.str());
}
