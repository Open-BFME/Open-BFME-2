// cl: /DNDEBUG /MD /GX- /Ireference/shims/bfme2_ascii
// ?rva0035B232@Rva0035B232@@QAEPBVAsciiString@@H@Z retail 0x0035B232 61B
// Override-or-list AsciiString getter: +0x7c non-empty returns itself, else bounds-checked list at +0x58/+0x5c or AsciiString::TheEmptyString at 0x009E0878.
// Evidence: unlock lane, callers 0x0021CB1F 0x0056786B 0x00567DA6, callee ?isEmpty@?$StringBase@D@@QBE_NXZ rowed, sar-2 count shape twins Rva0035B29E.
#include "ascii_string.h"

class Rva0035B232
{
public:
	const AsciiString *rva0035B232(int index);

private:
	char m_pad[0x58];
	union {
		AsciiString *m_begin;
		AsciiString * volatile m_beginVolatile;
	};
	AsciiString *m_end;
	char m_pad2[0x7c - 0x60];
	AsciiString m_str;
};

const AsciiString *Rva0035B232::rva0035B232(int index)
{
	if (!m_str.isEmpty())
		return &m_str;
	unsigned int count = (unsigned int)(((char *)m_end - (char *)m_begin) >> 2);
	if (index < 0 || (unsigned int)index >= count)
		return &AsciiString::TheEmptyString;
	return m_beginVolatile + index;
}
