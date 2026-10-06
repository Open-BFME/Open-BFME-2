// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva0050BFFD@Rva0050BFFD@@QAEXVAsciiString@@@Z @0x0050BFFD (49B).
// AsciiString by-value setter with EH (leaf lane, called by the unclaimed
// 0x0050C02E/463 twice). Copies the by-value AsciiString at [ebp+8] into the
// AsciiString at +0x00 (this) through the pin-only
// ??4AsciiString@@QAEAAV0@ABV0@@Z (8 pins, rowed callee 0x000366F0 shape),
// then destroys the by-value copy via the rowed
// ?releaseBuffer@?$StringBase@D@@AAEXXZ at 0x00036410. EH prolog uses handler
// table code 0x007944D7 through the rowed __EH_prolog at 0x00629188 with state
// 0 around the assign and -1 after, matching the LifeEventModuleOpAssign.cpp
// AsciiString::operator= precedent (/EHsc, no stlport needed for ascii_string).

class AsciiString;

#include "ascii_string.h"


class Rva0050BFFD
{
public:
	void rva0050BFFD(AsciiString s);

private:
	AsciiString m_str;
};

void Rva0050BFFD::rva0050BFFD(AsciiString s)
{
	m_str = s;
}
