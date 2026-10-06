// cl: /Ireference/shims/bfme2_ascii
// PlayerTemplate image getters via TheMappedImageCollection (0x00DFF078).
// ?rva001FD1FB@PlayerTemplate@@QBEPBVImage@@XZ @0x001FD1FB 19B (AsciiString at +0x170)
// ?rva001FD221@PlayerTemplate@@QBEPBVImage@@XZ @0x001FD221 19B (AsciiString at +0x174)
// ?rva001FD23F@PlayerTemplate@@QBEPBVImage@@XZ @0x001FD23F 19B (AsciiString at +0x1D8)
// BFME1 PlayerTemplate.cpp getHeadWaterMarkImage/getFlagWaterMarkImage/getSideIconImage/
// getGeneralImage/getEnabledImage all do TheMappedImageCollection->findImageByName(member).
// Retail class proven by callers derefing Player+0x34 (getPlayerTemplate): 0x001FD221 used by
// GadgetButtonSetEnabledImage at 0x0050E135/0x0050E321, 0x001FD1FB by winSetEnabledImage at
// 0x0050E66B, 0x001FD23F on PlayerTemplate from getControllingPlayer at 0x005294C7.
// Sibling offsets 0x170/0x174 are adjacent AsciiStrings and 0x1D8 closes the 0x1DC object.
#include "ascii_string.h"

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;


int Rva0033A3F4Lookup(const AsciiString &name);

class PlayerTemplate
{
public:
	const Image *rva001FD1FB() const;
	const Image *rva001FD221() const;
	int rva001FD234() const;
	const Image *rva001FD23F() const;

private:
	char m_pad00[0x18];
	AsciiString m_18;
	char m_pad1C[0x170 - 0x1C];
	AsciiString m_170;
	AsciiString m_174;
	char m_pad178[0x1D8 - 0x178];
	AsciiString m_1D8;
};

const Image *PlayerTemplate::rva001FD1FB() const
{
	return TheMappedImageCollection->findImageByName(m_170);
}

const Image *PlayerTemplate::rva001FD221() const
{
	return TheMappedImageCollection->findImageByName(m_174);
}

int PlayerTemplate::rva001FD234() const
{
	return Rva0033A3F4Lookup(m_18);
}

const Image *PlayerTemplate::rva001FD23F() const
{
	return TheMappedImageCollection->findImageByName(m_1D8);
}
