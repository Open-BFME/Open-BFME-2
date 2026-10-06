// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX-
// ?rva003F038E@Rva003F038E@@QAEPBVImage@@XZ, retail 0x003F038E, 43 bytes.
// __thiscall cached image load via AsciiString at +0x70: returns NULL when empty
// else TheMappedImageCollection->findImageByName stores to +0x19C and returns it.
// Evidence: rowed isEmpty 0x00001E2F rowed findImageByName 0x002D92F6 global
// 0x00DFF078 wrapper 0x003F03B9 cache check plus store.
#include "ascii_string.h"


class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &n);
};
extern ImageCollection *TheMappedImageCollection;


class Rva003F038E
{
public:
	const Image *rva003F038E();
	const Image *rva003F03B9();
private:
	char m_pad70[0x70];
	AsciiString m_name;
	char m_pad9C[0x19C - 0x74];
	const Image *m_cached;
};

const Image *Rva003F038E::rva003F03B9()
{
	if (m_cached)
		return m_cached;
	return rva003F038E();
}

const Image *Rva003F038E::rva003F038E()
{
	if (m_name.isEmpty())
		return 0;
	const Image *found = TheMappedImageCollection->findImageByName(m_name);
	m_cached = found;
	return found;
}
