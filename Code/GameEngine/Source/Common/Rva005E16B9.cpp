// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva005E16B9@Rva005E16B9@@QAEPBVImage@@XZ @0x005E16B9 33B leaf image lookup through member AsciiString at +8.
// Evidence: retail lea esi [ecx+8] then rowed isEmpty 0x00001E2F then rowed findImageByName 0x002D92F6 through g_00DFF078; empty returns NULL.
#include "ascii_string.h"

class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern class ImageCollection *TheMappedImageCollection;

class Rva005E16B9
{
	char m_pad[8];
	AsciiString m_8;
public:
	const Image *rva005E16B9();
};

const Image *Rva005E16B9::rva005E16B9()
{
	if (!((const StringBase<char> *)&m_8)->isEmpty())
		return TheMappedImageCollection->findImageByName(m_8);
	return 0;
}
