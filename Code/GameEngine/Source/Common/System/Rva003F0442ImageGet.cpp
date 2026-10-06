// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX-
// LivingWorldRegion::GetFortressPortrait (WorldBuilder name, LivingWorldRegion.cpp line 1470: findImageByName of the +0x120 name unless empty).
// was ?rva003F0442@Rva003F0442@@QAEPBVImage@@XZ, retail 0x003F0442, 36 bytes.
// __thiscall image getter via AsciiString at +0x120: returns NULL when empty
// else TheMappedImageCollection->findImageByName. Evidence: rowed isEmpty
// 0x00001E2F, rowed findImageByName 0x002D92F6, global 0x00DFF078, caller 0x005E2B45.
#include "ascii_string.h"


class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &n);
};
extern ImageCollection *TheMappedImageCollection;


class LivingWorldRegion
{
public:
	const Image *GetFortressPortrait();
private:
	char m_pad[0x120];
	AsciiString m_name;
};

const Image *LivingWorldRegion::GetFortressPortrait()
{
	if (!m_name.isEmpty())
		return TheMappedImageCollection->findImageByName(m_name);
	return 0;
}
