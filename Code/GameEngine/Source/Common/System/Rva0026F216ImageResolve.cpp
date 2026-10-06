// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0026F216@Rva0026F216@@QAEXXZ @0x0026F216 87B
// Evidence: between UpgradeTemplate 0x0026F1A5 and UpgradeCenter 0x0026F26D; two image-name slots +0x6c/+0x70 and +0x8c/+0x90 via rowed isEmpty 0x00001E2F plus rowed findImageByName 0x002D92F6 plus releaseBuffer 0x00036410 plus global 0x00DFF078; caller 0x0026FBD6.
#include "ascii_string.h"


class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

class Rva0026F216
{
public:
	void rva0026F216();
private:
	char m_pad00[0x6c];
	AsciiString m_6c;
	const Image *m_70;
	char m_pad74[0x18];
	AsciiString m_8c;
	const Image *m_90;
};

void Rva0026F216::rva0026F216()
{
	if (!m_6c.isEmpty())
	{
		m_70 = TheMappedImageCollection->findImageByName(m_6c);
		m_6c.clear();
	}
	if (!m_8c.isEmpty())
	{
		m_90 = TheMappedImageCollection->findImageByName(m_8c);
		m_8c.clear();
	}
}
