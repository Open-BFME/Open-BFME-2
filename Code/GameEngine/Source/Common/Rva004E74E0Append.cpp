// cl: /Ireference/shims/bfme2_ascii /MD
#include "unicode_string.h"

// ?Rva004E74E0Append@@YAXPAVUnicodeString@@PBV1@@Z @0x004E74E0 38B
// Unicode join: if dst non-empty append newline then concat src.
// Evidence: callees isEmpty 0x00035740 concat 0x00006A2A rowed plus operator+= 0x000066C0 rowed; 7 callers in 0x004E7506.
void Rva004E74E0Append(UnicodeString *dst, const UnicodeString *src)
{
	if (!dst->isEmpty())
		*dst += (unsigned short)10;
	dst->concat(*(const StringBase<unsigned short> *)src);
}
