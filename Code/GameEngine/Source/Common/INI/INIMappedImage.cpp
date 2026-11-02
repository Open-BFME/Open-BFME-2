// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// INI::parseMappedImageDefinition @0x001ED63C (178B): Zero Hour
// INIMappedImage.cpp's body. Identity from the INI block table: the
// "MappedImage" token's entry names this address. The body reads the name
// token, returns without TheMappedImageCollection, looks the image up with
// the rowed findImageByName 0x002D92F6, and on a miss news a 0x34-byte Image
// (rowed ctor 0x002D8FE4), names it (the +0x04 AsciiString) and files it
// with the rowed addImage 0x002D9457. The image is filled from Image's
// field-parse table 0x00C036E8 (the ledger's g_00C036E8).
#include "ascii_string.h"

struct FieldParse;

#include "../../../Include/Common/INI/INI.h"

extern const FieldParse m_imageFieldParseTable[];

#include "../../../Include/GameClient/ImageClass.h"

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
	void addImage(Image *image);
};

extern ImageCollection *TheMappedImageCollection;

void INI::parseMappedImageDefinition(INI *ini)
{
	AsciiString name;

	const char *c = ini->getNextToken();
	name.set(c);

	if (!TheMappedImageCollection)
	{
		return;
	}
	Image *image = const_cast<Image *>(TheMappedImageCollection->findImageByName(name));

	if (image == 0)
	{
		image = new Image;
		image->setName(name);
		TheMappedImageCollection->addImage(image);
	}

	ini->initFromINI(image, image->getFieldParse());
}
