// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /MD
// ?rva00433403@Rva004EC166@@QAEXABVAsciiString@@@Z
// retail 0x00433403, 49 bytes. The receiver class is identified by its call to the rowed Rva004EC166 wrapper; its string at +8 and cached string at +0xC8 are supported by retail offsets.
#include "ascii_string.h"

class Rva004EC166
{
public:
	void rva004EC166(const AsciiString &s);
	void rva00433403(const AsciiString &s);
private:
	char m_pad[8];
	AsciiString m_str;
	char m_pad18[0xB8];
	unsigned int m_flags;
	AsciiString m_cachedString;
};

void Rva004EC166::rva00433403(const AsciiString &s)
{
	if ((m_flags & 1) == 0)
	{
		((StringBase<char> &)m_cachedString).set((const StringBase<char> &)m_str);
		m_flags |= 1;
	}
	rva004EC166(s);
}
