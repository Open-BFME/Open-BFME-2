// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?rva0050C807@Rva0050C807@@QBE?AVAsciiString@@H@Z @ 0x0050C807 66B
// Bounds-checked AsciiString getter over the pointer pair at +0/+4; element
// size 0x14 with the string at +4, out of range yields the exported
// AsciiString::TheEmptyString at 0x009E0878. Evidence: frameless EBP ret-8
// sret shape; idiv-by-0x14 count; all callees rowed (StringBase copy
// 0x000365F0); caller 0x0050C984; owner class unproven (honest Rva name).
#include "ascii_string.h"

class Rva0050C807
{
public:
	char *m_start;
	char *m_end;
	AsciiString rva0050C807(int index) const;
};

AsciiString Rva0050C807::rva0050C807(int index) const
{
	unsigned int count = (m_end - m_start) / 0x14;
	if (index < 0 || (unsigned int)index >= count)
		return AsciiString::TheEmptyString;
	index *= 0x14;
	return *(const AsciiString *)(m_start + index + 4);
}
