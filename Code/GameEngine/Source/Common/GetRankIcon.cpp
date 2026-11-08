// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
// stlport
// ?GetRankIcon@@YAPBVImage@@HH@Z, retail 0x00559B64, 193 bytes.
// Free-function Apt rank icon lookup with side-name table and fallback.
// Evidence: BFME1 donor Rva0046F910RankDisplay.cpp same sprintf shapes "AptRankIcon%s%d" and "AptRankIcon%d" via rowed StringBase ctor 0x00037BA0 releaseBuffer 0x00036410 and rowed findImageByName 0x002D92F6; IAT sprintf; global g_00DFF078 ?g_00DFF078@@3PAVImageCollection@@A; table g_00DBE9B0; callers 0x00559C25 0x0043A5F6 0x005DD48C.
#include "ascii_string.h"
#include <stdio.h>

#include "../../Include/GameClient/Image.h"

// ?g_00DFF078@@3PAVImageCollection@@A: the global at this VA is ?TheMappedImageCollection@@3PAVImageCollection@@A; this name is an alias for it.
extern const char *g_rva0033A3F4Table[];

const Image *__cdecl GetRankIcon(int side, int rank)
{
	char imageNameBuffer[256];
	const Image *image;

	sprintf(imageNameBuffer, "AptRankIcon%s%d", g_rva0033A3F4Table[side], rank);
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
