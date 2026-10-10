// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD
// W3DScriptedModelDraw::getButtonImage 0x000B9C8C 92B (WorldBuilder name,
// W3DScriptedModelDraw.cpp line 3537: same compareNoCase/set/findImageByName
// refresh of the cached +0x2E0 image); a virtual inherited by seven draw vtables.
// Evidence: leaf slot 52 of W3D Draw vtables; cached-image refresh comparing AsciiString at data+0x5C against member at +0x2E4 via rowed compareNoCase then set; empty check on StringBase at data+0x60 via rowed isEmpty; else rowed findImageByName through g_00DFF078.

#include "ascii_string.h"

class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern class ImageCollection *TheMappedImageCollection;

struct Rva000B9C8CData
{
	unsigned char m_pad[0x5C];
	AsciiString m_a;
	StringBase<char> m_b;
};

class W3DScriptedModelDraw
{
public:
	virtual const Image *getButtonImage();
private:
	unsigned char m_pad04[0x14 - 4];
	Rva000B9C8CData *m_data;
	unsigned char m_pad18[0x2E0 - 0x18];
	const Image *m_img;
	AsciiString m_name;
};

const Image *W3DScriptedModelDraw::getButtonImage()
{
	Rva000B9C8CData *d = m_data;
	if (d != 0)
	{
		const AsciiString &a = d->m_a;
		if (((const StringBase<char> &)m_name).compareNoCase((const StringBase<char> &)a) != 0)
		{
			((StringBase<char> *)&m_name)->set(*(const StringBase<char> *)&a);
			if (!d->m_b.isEmpty())
				m_img = TheMappedImageCollection->findImageByName(a);
			else
				m_img = 0;
		}
	}
	return m_img;
}
