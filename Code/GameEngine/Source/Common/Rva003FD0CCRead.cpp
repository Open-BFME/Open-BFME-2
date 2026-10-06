// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva003FD0CC@Rva003FD0CC@@QAEXPADHH@Z RVA 0x003FD0CC size 129: composite string+text slice copy; caller 0x003FD05E passes PlusText prefix, length via AsciiStringPlusText 0x002DBF50, empty fallback g_Rva0107301CEmptyString, memcpy 0x006291A8.
#include "ascii_string.h"
extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int n);
extern const char g_Rva0107301CEmptyString[];
class Rva003FD0CC
{
public:
	void rva003FD0CC(char *dst, int offset, int count);
	const AsciiString *m_string;
	const char *m_extra;
	int m_extraLen;
};
void Rva003FD0CC::rva003FD0CC(char *dst, int offset, int count)
{
	int len = m_string->getLength();
	if (offset < len) {
		int chunk = count;
		if (offset + count > len)
			chunk = len - offset;
		const char *base = *(const char *const *)m_string ? *(const char *const *)m_string + 8 : g_Rva0107301CEmptyString;
		memcpy(dst, base + offset, chunk);
		count -= chunk;
		if (count <= 0)
			return;
		dst += chunk;
		offset += chunk;
	}
	memcpy(dst, m_extra + offset - len, count);
}
