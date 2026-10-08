// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva005F0152@Rva005F0152@@QAEPBVImage@@H@Z retail 0x005F0152 51B
// Cached image fetch by index through AsciiString names at +8 and Image
// slots at +0x3C via ImageCollection::findImageByName. Evidence: unlock lane
// plus 2 callers plus prev Rva005F002CImageFind donor TU and flags.

#include "ascii_string.h"


class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &n);
};
extern ImageCollection *TheMappedImageCollection;


class Rva005F0152
{
public:
	const Image *rva005F0152(int index);

private:
	char m_pad[8];
	AsciiString m_names[13];
	const Image *volatile m_images[13];
};

const Image *Rva005F0152::rva005F0152(int index)
{
	const Image *volatile *slot = &m_images[index];
	if (*slot)
		return *slot;
	const AsciiString &name = m_names[index];
	if (name.isEmpty())
		return *slot;
	*slot = TheMappedImageCollection->findImageByName(name);
	return *slot;
}

// Rva00A06858: matched references place it at VA 0xe06858 (zero-filled; a plain-data view).
Rva005F0152 Rva00A06858;

const Image *Rva005F01B8Get(int index)
{
	return Rva00A06858.rva005F0152(index);
}

struct Rva005F020BMid
{
	char m_pad[0x2C];
	int m_index;
};

struct Rva005F020BIn
{
	char m_pad[0x28];
	Rva005F020BMid *m_mid;
};

const Image *Rva005F020BGet(Rva005F020BIn *in)
{
	return Rva00A06858.rva005F0152(in->m_mid->m_index);
}

struct Rva005F0220In
{
	char m_pad[0x20];
	Rva005F020BIn *m_in;
};

const Image *Rva005F0220Get(Rva005F0220In *in)
{
	Rva005F020BIn *p = in->m_in;
	if (p)
		return Rva005F020BGet(p);
	return 0;
}

class Rva005F0185
{
public:
	const Image *rva005F0185(int index);

private:
	char m_pad[0x1C];
	AsciiString m_names[13];
	const Image *volatile m_images[13];
};

const Image *Rva005F0185::rva005F0185(int index)
{
	const Image *volatile *slot = &m_images[index];
	if (*slot)
		return *slot;
	const AsciiString &name = m_names[index];
	if (name.isEmpty())
		return *slot;
	*slot = TheMappedImageCollection->findImageByName(name);
	return *slot;
}

const Image *Rva005F01C7Get(int index)
{
	return ((Rva005F0185 *)&Rva00A06858)->rva005F0185(index);
}

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern class ThingFactory *TheThingFactory;

struct Rva005F01D6Payload
{
	char m_pad[0x5C4];
	int m_imageIndex;
};

struct Rva005F01D6In
{
	char m_pad[4];
	AsciiString m_name;
};

#define Rva00DFF000 ((Rva002D06CA *)TheThingFactory)

const Image *Rva005F01D6Get(Rva005F01D6In *in)
{
	AsciiString *name = &in->m_name;
	if (!name->isEmpty()) {
		void *found = Rva00DFF000->rva002D06CA(name);
		if (found != 0)
			return Rva005F01C7Get(((Rva005F01D6Payload *)found)->m_imageIndex);
	}
	return 0;
}
