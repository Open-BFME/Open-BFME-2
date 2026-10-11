// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// NameKeyGenerator lowercase-key wrappers, BFME2 retail:
//   ?Rva00148F02@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z @ 0x00148F02 (92B)
//   ?Rva002D91AF@NameKeyGenerator@@QAE?AW4NameKeyType@@ABVAsciiString@@@Z @ 0x002D91AF (29B)
//
// The 29B body is called with TheNameKeyGenerator (global 0xDF36A4) as this
// from ImageCollection::findImageByName (0x2D92F6) and addImage, exactly where
// the BFME1 donor (GameClient/System/Image.cpp) calls
// TheNameKeyGenerator->nameToLowercaseKey(name). It forwards ecx untouched and
// tail-calls the 92B body after inlining str(), mirroring the rowed
// nameToKey(AsciiString) 29B wrapper at 0x9FA65 (NameKeyGenerator_nameToKey_ascii.cpp).
//
// The 92B body builds a local AsciiString from the char*, lowercases it via
// the pinned toLower (0x36A70), and returns the rowed nameToKey(const char*)
// at 0x148E1A. Method names stay Rva-opaque: a second (this, const char*)
// lowercase path is already rowed as nameToLowercaseKey at 0x620500, and that
// identity dispute is deliberately left alone here.

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

template <typename T>
struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *nameString);
	NameKeyType Rva00148F02(const char *nameString);
	NameKeyType Rva002D91AF(const AsciiString &nameString);
};

NameKeyType NameKeyGenerator::Rva00148F02(const char *nameString)
{
	AsciiString lowered(nameString);
	((StringBase<char> &)lowered).toLower();
	return nameToKey(lowered.str());
}

NameKeyType NameKeyGenerator::Rva002D91AF(const AsciiString &nameString)
{
	return Rva00148F02(nameString.str());
}
