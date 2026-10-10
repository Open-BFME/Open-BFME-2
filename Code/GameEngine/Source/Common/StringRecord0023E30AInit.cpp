// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// Native 0x0023E30A..0x0023E323, 25 bytes, RET8.
// Target facts: this at ECX; genuine StringBase<char> copy365F0 constructs
// the first four-byte member from argument1; argument2 is copied unchanged
// into offset4; the receiver is returned. Only this eight-byte prefix is
// established. The original application record and the second word's role
// are unknown. No registration-table or donor-record identity is asserted.
// AsciiString member semantics follow the canonical BFME1 StringBase source.
#include "ascii_string.h"
struct Rva0023E30A {
 AsciiString text;
 unsigned word;
 Rva0023E30A(const AsciiString &,unsigned);
};
Rva0023E30A::Rva0023E30A(const AsciiString &s,unsigned w) : text(s),word(w) {}
