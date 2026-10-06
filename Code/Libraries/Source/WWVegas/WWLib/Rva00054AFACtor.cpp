// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva00054AFA@@QAE@ABVAsciiString@@ABVUnicodeString@@@Z @0x00054AFA 57B
// Two-string ctor: AsciiString at +0 via rowed StringBase<char> copy 0x000365F0,
// UnicodeString at +4 via rowed StringBase<ushort> copy 0x00037050, under an
// __EH_prolog frame (and [ebp-4],0 after the first member); ret 8, two refs.
// Evidence: callees are the pinned StringBase copy ctors; caller 0x0005B708 passes
// two string refs; no vptr store so non-virtual class; layout mirrors
// Rva0022304ACopy.cpp which emits the same frame for AsciiString + second member.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva00054AFA
{
public:
	Rva00054AFA(const AsciiString &a, const UnicodeString &w);
private:
	AsciiString m_head;
	UnicodeString m_tail;
};

Rva00054AFA::Rva00054AFA(const AsciiString &a, const UnicodeString &w) : m_head(a), m_tail(w)
{
}
