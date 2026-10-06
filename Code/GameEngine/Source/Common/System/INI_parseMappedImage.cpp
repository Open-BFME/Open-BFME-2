// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseMappedImage@INI@@SAXPAV1@PAX1PBX@Z, retail 0x003390B2, 87 bytes.
// Dedicated TU (same INI parser family as INI_parseFXList.cpp).
//
// Zero Hour's INI::parseMappedImage (Common/INI/INI.cpp): when
// TheMappedImageCollection (0x00DFF078) exists, store the image it finds by name.

class Image;

#include "ascii_string.h"


class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void parseMappedImage(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseMappedImage@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseMappedImage(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	if (TheMappedImageCollection)
		*(const Image **)store = TheMappedImageCollection->findImageByName(AsciiString(token));
}
