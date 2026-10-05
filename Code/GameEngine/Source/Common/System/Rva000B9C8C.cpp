// cl: /Ireference/shims/bfme2_ascii /O1 /GX- /DNDEBUG /MD
// ?rva000B9C8C@Rva000B9C8C@@QAEPBVImage@@XZ 0x000B9C8C 92B
// Evidence: leaf slot 52 of W3D Draw vtables; cached-image refresh comparing AsciiString at data+0x5C against member at +0x2E4 via rowed compareNoCase then set; empty check on StringBase at data+0x60 via rowed isEmpty; else rowed findImageByName through g_00DFF078.

#include "ascii_string.h"

class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *g_00DFF078;

struct Rva000B9C8CData
{
	unsigned char m_pad[0x5C];
	AsciiString m_a;
	StringBase<char> m_b;
};

class Rva000B9C8C
{
public:
	const Image *rva000B9C8C();
private:
	unsigned char m_pad[0x14];
	Rva000B9C8CData *m_data;
	unsigned char m_pad18[0x2E0 - 0x18];
	const Image *m_img;
	AsciiString m_name;
};

const Image *Rva000B9C8C::rva000B9C8C()
{
	Rva000B9C8CData *d = m_data;
	if (d != 0)
	{
		const AsciiString &a = d->m_a;
		if (m_name.compareNoCase(a) != 0)
		{
			((StringBase<char> *)&m_name)->set(*(const StringBase<char> *)&a);
			if (!d->m_b.isEmpty())
				m_img = g_00DFF078->findImageByName(a);
			else
				m_img = 0;
		}
	}
	return m_img;
}
