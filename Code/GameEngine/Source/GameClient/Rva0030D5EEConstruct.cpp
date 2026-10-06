// cl: /Ireference/shims/bfme2_ascii
// ?Rva0030D5EEConstruct@@YA?AVAsciiString@@ABV1@@Z, retail 0x0030D5EE, 24B.
// Free copy-return wrapper: hidden-pointer return via AsciiString copy into StringBase copy 0x000365F0.
// Evidence: packet disasm; neighbours share // cl: /Ireference/shims/bfme2_ascii /O1; caller 0x0030DA25.
#include "ascii_string.h"

AsciiString Rva0030D5EEConstruct(const AsciiString &src)
{
	return src;
}
