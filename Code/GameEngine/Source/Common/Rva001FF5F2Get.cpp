// cl: /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc
// ?Rva001FF5F2Get@@YG?AVAsciiString@@W4NameKeyType@@@Z @0x001FF5F2 51B: free function returning AsciiString from NameKey; -1 -> AsciiString::TheEmptyString else keyToName pin 0x00148C95 via rowed StringBase copy ctor 0x000365F0. Evidence: ret 8 hidden-pointer shape callers 0x00306232 0x0037BE15 0x004F31B6.
enum NameKeyType
{
	NAMEKEY_INVALID = -1
};

#include "ascii_string.h"

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};

extern NameKeyGenerator *TheNameKeyGenerator;

AsciiString __stdcall Rva001FF5F2Get(NameKeyType key)
{
	if (key == NAMEKEY_INVALID)
		return AsciiString::TheEmptyString;
	return TheNameKeyGenerator->keyToName(key);
}
