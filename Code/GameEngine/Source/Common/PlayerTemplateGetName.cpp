// cl: /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc
// ?getName@PlayerTemplate@@QBE?AVAsciiString@@XZ @0x23E95E (30B):
// PlayerTemplate::getName, NameKey lookup of the key at +0x10 through the
// pinned keyToName at 0x148C95 into the hidden return pointer via the rowed
// copy-ctor at 0x365F0. Called from GameLogic populate-report for the Slot
// display line. Leaf, no new pins.
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

class PlayerTemplate
{
public:
	unsigned char m_pad[0x10];
	NameKeyType m_key;
	AsciiString getName() const;
};

// ?getName@PlayerTemplate@@QBE?AVAsciiString@@XZ
AsciiString PlayerTemplate::getName() const
{
	return TheNameKeyGenerator->keyToName(m_key);
}
