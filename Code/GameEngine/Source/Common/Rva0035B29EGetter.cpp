// cl: /DNDEBUG /MD /GX- /Ireference/shims/bfme2_ascii
// ?rva0035B29E@Rva0035B29E@@QAEPBVAsciiString@@H@Z retail 0x0035B29E 37B
// Bounds-checked AsciiString list getter over pointer pair at +0x64/+0x68;
// out of range yields AsciiString::TheEmptyString at 0x009E0878.
// Evidence: unlock lane, callers 0x0021CB1F 0x0056786B, sar-2 count shape.
#include "ascii_string.h"

class Rva0035B29E
{
public:
	const AsciiString *rva0035B29E(int index);

private:
	char m_pad[0x64];
	union {
		AsciiString *m_begin;
		AsciiString * volatile m_beginVolatile;
	};
	AsciiString *m_end;
};

const AsciiString *Rva0035B29E::rva0035B29E(int index)
{
	unsigned int count = (unsigned int)(((char *)m_end - (char *)m_begin) >> 2);
	if (index < 0 || (unsigned int)index >= count)
		return &AsciiString::TheEmptyString;
	return m_beginVolatile + index;
}
