// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva002D5711@Rva002D5711@@QAEXABVAsciiString@@@Z retail 0x002D5711 137B
// BFME1 donor AptPalantirResourceImage.cpp cacheResourceImage via ResourceBar_ plus suffix; caller 0x002D6A20; rowed isEmpty 0x1E2F plus StringBase ctor 0x37BA0 plus PlusString materializer 0xBC495 plus findImageByName 0x2D92F6 plus releaseBuffer 0x36410.
#include "ascii_string.h"

class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &n);
};
extern class ImageCollection *TheMappedImageCollection;

struct AsciiStringRef
{
	const AsciiString *m_string;
};

struct AsciiStringPlusString : AsciiStringRef
{
	operator AsciiString();
	AsciiStringRef m_second;
};

class Rva002D5711
{
public:
	void rva002D5711(const AsciiString &name);

private:
	char m_pad00[0x1C];
	const Image *m_image1C;
};

void Rva002D5711::rva002D5711(const AsciiString &name)
{
	if (!((const StringBase<char> &)name).isEmpty()) {
		AsciiString tmp("ResourceBar_");
		AsciiStringPlusString plus;
		plus.m_string = &tmp;
		plus.m_second.m_string = &name;
		m_image1C = TheMappedImageCollection->findImageByName(plus);
	} else
		m_image1C = 0;
}
