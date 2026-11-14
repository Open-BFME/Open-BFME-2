// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ??0Rva00448089@@QAE@ABVUnicodeString@@0@Z, retail 0x004480BE, 57 bytes.
// Ctor for the two-wide-string class between rowed dtor 0x00448089 and deleting dtor 0x004480F7: inits member at +0 from first arg then member at +4 from second arg via rowed StringBase copy ctor 0x00037050 with EH prolog. Evidence: neighbour layout plus caller at 0x0044920E constructing stack temp from caller arg and empty wide string local.
#include "unicode_string.h"

#include "../../Include/Common/Rva00448089.h"

Rva00448089::Rva00448089(const UnicodeString &unicodeString, const UnicodeString &b) : m_00(unicodeString), m_04(b)
{
}
