// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Eight Apt image setters, one shape:
//
//     if (image == m_image) return;
//     AsciiString key;
//     key.format("_level%u.%s_<Suffix>", m_level, m_name.str());
//     if (image) m_images.set(key, image); else m_images.clear(key);
//     m_image = image;
//
// Target facts per member: the format string (DIR32 push), the offsets of the
// level, name, image-list and image fields, the rowed clear 0x00524306 and the
// set 0x00524725 (pinned from these REL32s: it forwards key and image to
// TheRva00222A8BTarget's ?rva002239E2 and records the key in the list's
// AsciiString vector). The name field is read through StringBase<char>::str()
// (the null case is retail's TheNullChr at VA 0x00BBAC1C). The AsciiString
// local reuses the image argument's stack slot, which is why the argument is
// held in edi. Image and the six owning classes are unidentified; class and
// method names are address-derived, suffix names come from the strings.
//
// ?rva005C7BE1@Rva005C7BE1@@QAEXPBVImage@@@Z  @0x005C7BE1 124B  _Image
// ?rva005E0E1D@Rva005E0E1D@@QAEXPBVImage@@@Z  @0x005E0E1D 124B  _Image
// ?rva005F08C4@Rva005F08C4@@QAEXPBVImage@@@Z  @0x005F08C4 124B  _RegionFortressPortrait
// ?rva005F0940@Rva005F08C4@@QAEXPBVImage@@@Z  @0x005F0940 124B  _RegionFortressTypeImage
// ?rva005F6096@Rva005F6096@@QAEXPBVImage@@@Z  @0x005F6096 124B  _LeaderPortrait
// ?rva005F6112@Rva005F6096@@QAEXPBVImage@@@Z  @0x005F6112 124B  _LeaderTypeImage
// ?rva005FB666@Rva005FB666@@QAEXPBVImage@@@Z  @0x005FB666 124B  _PlayerIcon
// ?rva005FF2AC@Rva005FF2AC@@QAEXPBVImage@@@Z  @0x005FF2AC 124B  _Portrait
#include "ascii_string.h"

class Image;

class Rva00524306
{
public:
	void rva00524306(const StringBase<char> &key);
	void rva00524725(const AsciiString &key, const Image *image);
};

#define APT_IMAGE_KEY_SET( CLASS, METHOD, FORMAT, IMAGE )                 \
	void CLASS::METHOD(const Image *image)                                \
	{                                                                     \
		if (image == IMAGE)                                               \
			return;                                                       \
		AsciiString key;                                                  \
		key.format(FORMAT, m_level, m_name.str());                        \
		if (image)                                                        \
			m_images.rva00524725(key, image);                             \
		else                                                              \
			m_images.rva00524306(*(const StringBase<char> *)&key);        \
		IMAGE = image;                                                    \
	}

class Rva005C7BE1
{
public:
	void rva005C7BE1(const Image *image);
private:
	char m_pad00[8];
	unsigned int m_level;		// +0x08
	StringBase<char> m_name;	// +0x0C
	char m_pad10[0x24];
	Rva00524306 m_images;		// +0x34
	char m_pad35[0x27];
	const Image *m_image;		// +0x5C
};

APT_IMAGE_KEY_SET( Rva005C7BE1, rva005C7BE1, "_level%u.%s_Image", m_image )

class Rva005E0E1D
{
public:
	void rva005E0E1D(const Image *image);
private:
	char m_pad00[8];
	unsigned int m_level;		// +0x08
	StringBase<char> m_name;	// +0x0C
	char m_pad10[0x18];
	Rva00524306 m_images;		// +0x28
	char m_pad29[0x0B];
	const Image *m_image;		// +0x34
};

APT_IMAGE_KEY_SET( Rva005E0E1D, rva005E0E1D, "_level%u.%s_Image", m_image )

class Rva005F08C4
{
public:
	void rva005F08C4(const Image *image);
	void rva005F0940(const Image *image);
private:
	char m_pad00[4];
	unsigned int m_level;		// +0x04
	StringBase<char> m_name;	// +0x08
	char m_pad0C[0x10];
	Rva00524306 m_images;		// +0x1C
	char m_pad1D[0x27];
	const Image *m_portrait;	// +0x44
	const Image *m_typeImage;	// +0x48
};

APT_IMAGE_KEY_SET( Rva005F08C4, rva005F08C4, "_level%u.%s_RegionFortressPortrait", m_portrait )
APT_IMAGE_KEY_SET( Rva005F08C4, rva005F0940, "_level%u.%s_RegionFortressTypeImage", m_typeImage )

class Rva005F6096
{
public:
	void rva005F6096(const Image *image);
	void rva005F6112(const Image *image);
private:
	char m_pad00[4];
	unsigned int m_level;		// +0x04
	StringBase<char> m_name;	// +0x08
	char m_pad0C[0x0C];
	Rva00524306 m_images;		// +0x18
	char m_pad19[0x0B];
	const Image *m_portrait;	// +0x24
	const Image *m_typeImage;	// +0x28
};

APT_IMAGE_KEY_SET( Rva005F6096, rva005F6096, "_level%u.%s_LeaderPortrait", m_portrait )
APT_IMAGE_KEY_SET( Rva005F6096, rva005F6112, "_level%u.%s_LeaderTypeImage", m_typeImage )

class Rva005FB666
{
public:
	void rva005FB666(const Image *image);
private:
	char m_pad00[4];
	unsigned int m_level;		// +0x04
	StringBase<char> m_name;	// +0x08
	char m_pad0C[0x0C];
	Rva00524306 m_images;		// +0x18
	char m_pad19[0x17];
	const Image *m_icon;		// +0x30
};

APT_IMAGE_KEY_SET( Rva005FB666, rva005FB666, "_level%u.%s_PlayerIcon", m_icon )

class Rva005FF2AC
{
public:
	void rva005FF2AC(const Image *image);
private:
	char m_pad00[4];
	unsigned int m_level;		// +0x04
	StringBase<char> m_name;	// +0x08
	char m_pad0C[0x0C];
	Rva00524306 m_images;		// +0x18
	char m_pad19[0x0F];
	const Image *m_portrait;	// +0x28
};

APT_IMAGE_KEY_SET( Rva005FF2AC, rva005FF2AC, "_level%u.%s_Portrait", m_portrait )
