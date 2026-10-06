// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva00207DF4@Rva00207DF4@@QAEXHABVAsciiString@@PAVImage@@@Z, retail 0x00207DF4 50B.
// Unlock lane: thiscall store of an Image* into the ImageSubscriptMap at
// this+0x1a164[index] under the CRC key of an AsciiString name. Evidence: rowed
// callee ?Rva003ECA13Get@@YAKABVAsciiString@@@Z at 0x003ECA13 and rowed
// ??AImageSubscriptMap@@QAEAAPAVImage@@ABI@Z at 0x002077D6; caller 0x003E9EB0.
#include "ascii_string.h"

class Image;

class ImageSubscriptMap
{
public:
	Image *&operator[](const unsigned int &key);
private:
	// Retail indexes these with stride 12 (imul eax,0xc); the rowed
	// definition holds one 12B ImageNameMap, so pad to that size here.
	unsigned char m_pad[12];
};

unsigned long Rva003ECA13Get(const AsciiString &s);

class Rva00207DF4
{
public:
	void rva00207DF4(int index, const AsciiString &name, Image *image);
private:
	unsigned char m_pad[0x1a164];
	ImageSubscriptMap m_maps[1];
};

void Rva00207DF4::rva00207DF4(int index, const AsciiString &name, Image *image)
{
	unsigned int key = Rva003ECA13Get(name);
	m_maps[index][key] = image;
}
