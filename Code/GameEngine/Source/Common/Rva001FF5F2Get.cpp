// cl: /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc
// Native callers306273 and37C0B7 load TheScienceStore intoECX; the donor
// ScienceStore::getInternalNameForScience supports the unused receiver.
// The neutral method preserves the established key enum and51B body.
// RET8 accounts for the hidden return pointer and key, not a free ABI.
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

class ScienceStore {public:AsciiString rva001FF5F2(NameKeyType);};

AsciiString ScienceStore::rva001FF5F2(NameKeyType key)
{
	if (key == NAMEKEY_INVALID)
		return AsciiString::TheEmptyString;
	return TheNameKeyGenerator->keyToName(key);
}
