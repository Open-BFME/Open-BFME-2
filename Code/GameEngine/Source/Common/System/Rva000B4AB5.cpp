// cl: /Ireference/shims/bfme2_ascii /MD
// stlport
// ?rva000B4AB5@Rva000B4AB5@@QAEPBVAsciiString@@I@Z @0x000B4AB5 47B.
// Modulo-index into a vector<AsciiString> at +0x4C: empty table returns
// &AsciiString::TheEmptyString, single entry returns &m_strings[0],
// else &m_strings[index % size]. Evidence: sar esi 2 count,
// TheEmptyString data ref at VA 0x009E0878, div/lea element select,
// 8 callers in 0x0007A847/0x000BE245/0x000C4E23.
#include <vector>

#include "ascii_string.h"

class Rva000B4AB5
{
	char _pad[0x4C];
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_strings;
public:
	const AsciiString *rva000B4AB5(unsigned index);
};

const AsciiString *Rva000B4AB5::rva000B4AB5(unsigned index)
{
	unsigned count = m_strings.size();
	if (count == 0)
		return &AsciiString::TheEmptyString;
	if (count == 1)
		return &m_strings[0];
	return &m_strings[index % count];
}
