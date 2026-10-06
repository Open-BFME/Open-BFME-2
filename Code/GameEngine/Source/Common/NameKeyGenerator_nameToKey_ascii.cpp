// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// NameKeyGenerator::nameToKey(const AsciiString&), retail 0x0009FA65, 29 bytes.
// Thin wrapper over the landed char* overload at 0x00148E1A. Header text
// lives at +8; empty strings go through the "" literal.

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "ascii_string.h"

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *nameString);
	NameKeyType nameToKey(const AsciiString &nameString);
};

inline NameKeyType NameKeyGenerator::nameToKey(const AsciiString &nameString)
{
	return nameToKey(nameString.str());
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
static NameKeyType (NameKeyGenerator::*const _bfmeInlineAnchor0_nameToKey)(const AsciiString &nameString) = &NameKeyGenerator::nameToKey;
