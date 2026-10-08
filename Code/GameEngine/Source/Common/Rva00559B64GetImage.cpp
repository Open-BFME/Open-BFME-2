// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
// ?Rva00559B64GetImage@@YAPBVImage@@HH@Z, retail 0x00559B64, 193 bytes.
// Free-function Apt rank icon lookup with side-name table and fallback.
// Evidence: BFME1 donor Rva0046F910RankDisplay.cpp same sprintf shapes "AptRankIcon%s%d" and "AptRankIcon%d" via rowed StringBase ctor 0x00037BA0 releaseBuffer 0x00036410 and rowed findImageByName 0x002D92F6; IAT sprintf; global g_00DFF078 ?g_00DFF078@@3PAVImageCollection@@A; table g_00DBE9B0; callers 0x00559C25 0x0043A5F6 0x005DD48C.
#include "ascii_string.h"
#include <stdio.h>

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

// ?g_00DFF078@@3PAVImageCollection@@A: the global at this VA is ?TheMappedImageCollection@@3PAVImageCollection@@A; this name is an alias for it.
extern class ImageCollection *TheMappedImageCollection;
extern const char *g_00DBE9B0[];

const Image *__cdecl Rva00559B64GetImage(int side, int rank)
{
	char imageNameBuffer[256];
	const Image *image;

	sprintf(imageNameBuffer, "AptRankIcon%s%d", g_00DBE9B0[side], rank);
	{
		AsciiString imageName(imageNameBuffer);
		image = TheMappedImageCollection->findImageByName(imageName);
	}
	if (image == 0) {
		sprintf(imageNameBuffer, "AptRankIcon%d", rank);
		AsciiString fallbackImageName(imageNameBuffer);
		image = TheMappedImageCollection->findImageByName(fallbackImageName);
	}
	return image;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00DBE9B0@@3PAPBDA=?g_rva0033A3F4Table@@3PAPBDA")
