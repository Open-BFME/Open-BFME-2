// The complete native parents and every EH code/data relocation prove
// the naturally emitted handler at 0x007775C2. One primary owner covers
// the shared native body; no second name or pin is introduced.
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?copyToBuffer@Rva002D4688@@QAEHPAD@Z @ 0x002D4688 (37B).
// Writes buffer via WinMainTitlePair at +0 then Rva000B3F84Pair at +0x10
// advancing by the first count. Callees rowed 0x00109D3A and 0x000B44F0.
// Caller 0x002D5155. Layout from WinMainPairUnicode pair sizes.

#include "ascii_string.h"

struct Rva000B3F84Pair
{
	const char *m_ptr;
	int m_len;
	int write(char *dst);
	int length() const { return m_len; }
};

struct WinMainTitlePair : Rva000B3F84Pair
{
	Rva000B3F84Pair m_secondPair;
	int write(char *dst);
	int length() const { return Rva000B3F84Pair::length() + m_secondPair.length(); }
};

class Rva002D4688
{
public:
	int copyToBuffer(char *buffer);
	operator AsciiString();

private:
	WinMainTitlePair m_left;
	Rva000B3F84Pair m_right;
};

int Rva002D4688::copyToBuffer(char *buffer)
{
	int first = m_left.write(buffer);
	int second = m_right.write(buffer + first);
	return first + second;
}

// WB F4AD70 and native2D511E..2D5188 sum the three text lengths,
// materialize through the existing copy worker and return a counted string.
// Retain the established address-derived node view; no template name asserted.
Rva002D4688::operator AsciiString()
{
	AsciiString result;
	char *buffer = ((StringBase<char> *)&result)->getBufferForRead(m_left.length() + m_right.length());
	copyToBuffer(buffer);
	return result;
}

// The unadjusted cdecl materializer at2D56C3..2D5711 copies the
// conversion result and releases its temporary, as WB F4A440 also does.
AsciiString Rva002D56C3Construct(Rva002D4688 &value)
{
	return value;
}
