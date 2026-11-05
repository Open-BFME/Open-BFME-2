// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?cacheButtonImage@UpgradeTemplate@@QAEXXZ @0x0026F216 87B
// Evidence: between UpgradeTemplate 0x0026F1A5 and UpgradeCenter 0x0026F26D; two image-name slots +0x6c/+0x70 and +0x8c/+0x90 via rowed isEmpty 0x00001E2F plus rowed findImageByName 0x002D92F6 plus releaseBuffer 0x00036410 plus global 0x00DFF078; caller 0x0026FBD6.
#include "ascii_string.h"
#include "../../../Include/Common/Upgrade.h"

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

void UpgradeTemplate::cacheButtonImage()
{
	if (!m_buttonImageName.isEmpty())
	{
		m_buttonImage = TheMappedImageCollection->findImageByName(m_buttonImageName);
		m_buttonImageName.clear();
	}
	if (!field8C.isEmpty())
	{
		field90 = TheMappedImageCollection->findImageByName(field8C);
		field8C.clear();
	}
}
