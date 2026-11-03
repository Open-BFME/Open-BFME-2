// cl: /MD
// ?Rva00151ECDLen@@YAHPBD@Z at 0x00151ECD (21B).
// Free length helper via Rva000B3F84Pair::init: builds the 8-byte pair on
// the stack and returns its +4 length. Evidence: init row 0xB3F84 in
// WinMainPairUnicode, single caller 0x1529A6, EBP frame.

#include "../../Include/Common/Rva000B3F84Pair.h"

int Rva00151ECDLen(const char *src);

int Rva00151ECDLen(const char *src)
{
	Rva000B3F84Pair pair;
	return pair.init(src)->m_len;
}
