// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva001FD404@Rva001FD404@@QAEPAU1@ABU1@@Z @0x001FD404 39B
// 0x10-byte assign helper: AsciiString at +0x00 via rowed operator= at 0x000366F0
// plus three dwords at +0x04/+0x08/+0x0C, returns this. Called from the big
// FX copy at 0x001FE924 for the subobject at +0x154 (neighbours there use plain
// AsciiString assign, this slot needs the extra words).
#include "ascii_string.h"

struct Rva001FD404
{
	Rva001FD404 *rva001FD404(const Rva001FD404 &that);
	AsciiString m_str;
	int m_4;
	int m_8;
	int m_c;
};

Rva001FD404 *Rva001FD404::rva001FD404(const Rva001FD404 &that)
{
	m_str = that.m_str;
	m_4 = that.m_4;
	m_8 = that.m_8;
	m_c = that.m_c;
	return this;
}
