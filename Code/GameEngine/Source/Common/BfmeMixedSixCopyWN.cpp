// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /Ob2
//
// Open-BFME5: the mixed copy constructor at retail 0x00415FAB,
// 125 bytes: a word, three narrow strings, a word and two wide strings.
// Callees are the rowed StringBase copy ctors 0x000365F0 (narrow) and
// 0x00037050 (wide) via the shared AsciiString/UnicodeString inline copies.
#include "ascii_string.h"
#include "unicode_string.h"

class Gen_004E9FD0
{
public:
	Gen_004E9FD0(const Gen_004E9FD0 &other);

	int m_bfmeKind;						// +0x00
	AsciiString m_bfmeFirst;					// +0x04
	AsciiString m_bfmeSecond;					// +0x08
	AsciiString m_bfmeThird;					// +0x0C
	int m_bfmeCount;					// +0x10
	UnicodeString m_bfmeText;					// +0x14
	UnicodeString m_bfmeHint;					// +0x18
};

// ??0Gen_004E9FD0@@QAE@ABV0@@Z
Gen_004E9FD0::Gen_004E9FD0(const Gen_004E9FD0 &other)
	: m_bfmeKind(other.m_bfmeKind),
	  m_bfmeFirst(other.m_bfmeFirst),
	  m_bfmeSecond(other.m_bfmeSecond),
	  m_bfmeThird(other.m_bfmeThird),
	  m_bfmeCount(other.m_bfmeCount),
	  m_bfmeText(other.m_bfmeText),
	  m_bfmeHint(other.m_bfmeHint)
{
}
