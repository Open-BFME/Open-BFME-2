// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX
//
// ?parseStringAsNameKeyType@NameKeyGenerator@@SAXPAVINI@@PAX1PBX@Z, retail
// 0x00148FBE (68B), in the NameKeyGenerator.cpp run after nameToKey
// (0x00148E1A) and the lowercase-key body (0x00148F02). Zero Hour's static
// FieldParse proc; BFME 2 reads the token as an AsciiString through
// INI::getNextAsciiString (rowed 0x0002EA4F) and keys it through the
// out-of-line nameToKey(const AsciiString &) copy (rowed 0x0009FA65) on
// TheNameKeyGenerator (VA 0x00DF36A4), so the temporary is released under an
// EH state. Target evidence: fourteen FieldParse rows reference it, e.g.
// StratigicDefeatStatName (0x00BE68F8) .. WeaponGroupName (0x00BE6998).

#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class INI
{
public:
	AsciiString getNextAsciiString();
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
	static void parseStringAsNameKeyType(INI *ini, void *instance, void *store, const void *userData);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// ?parseStringAsNameKeyType@NameKeyGenerator@@SAXPAVINI@@PAX1PBX@Z
void NameKeyGenerator::parseStringAsNameKeyType(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	*(NameKeyType *)store = TheNameKeyGenerator->nameToKey(ini->getNextAsciiString());
}
