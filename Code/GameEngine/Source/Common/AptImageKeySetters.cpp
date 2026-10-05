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
#include "unicode_string.h"

class Image;

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &value, bool b);
};

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;

UnicodeString __cdecl Rva005F6B74Format(int quantity);
UnicodeString __cdecl Rva005F6BD4Format(int turns);
UnicodeString __cdecl Rva005F6C8EFormat(int unused, int turns);

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

// Nine more members of the same family, by layout:
//   direct      level/name/list/image all in this (0x005D3776, 0x005F191E,
//               0x005FC7DE, which stores the image before the set/clear)
//   owner       level and name read through an owner pointer, plus the
//               slot's own index for the %d (0x005EF181, 0x005EF202,
//               0x005F07AD, 0x005F6CA8, 0x005F6D2C, 0x005F6FCC); in the
//               last four the list is the owner's too, re-read after format
//
// ?rva005D3776@Rva005D3776@@QAEXPBVImage@@@Z  @0x005D3776 123B  _RegionImage
// ?rva005F191E@Rva005F191E@@QAEXPBVImage@@@Z  @0x005F191E 123B  _MapPreview
// ?rva005FC7DE@Rva005FC7DE@@QAEXPBVImage@@@Z  @0x005FC7DE 124B  _TypeImage
// ?rva005EF181@Rva005EF181@@QAEXPBVImage@@@Z  @0x005EF181 129B  _IconSlotPortrait%d
// ?rva005EF202@Rva005EF181@@QAEXPBVImage@@@Z  @0x005EF202 129B  _IconSlotTypeImage%d
// ?rva005F07AD@Rva005F07AD@@QAEXPBVImage@@@Z  @0x005F07AD 133B  _IconSlotTypeImage%d
// ?rva005F6CA8@Rva005F6CA8@@QAEXPBVImage@@@Z  @0x005F6CA8 132B  _InProgressIconSlotPortrait
// ?rva005F6D2C@Rva005F6CA8@@QAEXPBVImage@@@Z  @0x005F6D2C 132B  _InProgressIconSlotTypeImage
// ?rva005F6FCC@Rva005F6FCC@@QAEXPBVImage@@@Z  @0x005F6FCC 135B  _QueuedIconSlotTypeImage%d

class Rva005D3776
{
public:
	void rva005D3776(const Image *image);
private:
	unsigned int m_level;		// +0x00
	StringBase<char> m_name;	// +0x04
	Rva00524306 m_images;		// +0x08
	char m_pad09[0x0B];
	const Image *m_image;		// +0x14
};

APT_IMAGE_KEY_SET( Rva005D3776, rva005D3776, "_level%u.%s_RegionImage", m_image )

class Rva005F191E
{
public:
	void rva005F191E(const Image *image);
	void rva005F1BDC(const UnicodeString &text);
	void rva005F1C62(const UnicodeString &text);
private:
	unsigned int m_level;		// +0x00
	StringBase<char> m_name;	// +0x04
	char m_pad08[0x0C];
	Rva00524306 m_images;		// +0x14
	char m_pad15[0x0B];
	UnicodeString m_territoryName;	// +0x20
	UnicodeString m_description;	// +0x24
	const Image *m_image;		// +0x28
};

APT_IMAGE_KEY_SET( Rva005F191E, rva005F191E, "_level%u.%s_MapPreview", m_image )

class Rva005FC7DE
{
public:
	void rva005FC7DE(const Image *image);
private:
	char m_pad00[8];
	unsigned int m_level;		// +0x08
	StringBase<char> m_name;	// +0x0C
	char m_pad10[0x0C];
	Rva00524306 m_images;		// +0x1C
	char m_pad1D[0x0F];
	const Image *m_image;		// +0x2C
};

void Rva005FC7DE::rva005FC7DE(const Image *image)
{
	if (image == m_image)
		return;
	AsciiString key;
	key.format("_level%u.%s_TypeImage", m_level, m_name.str());
	m_image = image;
	if (image)
		m_images.rva00524725(key, image);
	else
		m_images.rva00524306(*(const StringBase<char> *)&key);
}

struct Rva005EF181Owner
{
	unsigned int m_level;		// +0x00
	StringBase<char> m_name;	// +0x04
};

class Rva005EF181
{
public:
	void rva005EF181(const Image *image);
	void rva005EF202(const Image *image);
private:
	char m_pad00[0x0C];
	Rva005EF181Owner *m_owner;	// +0x0C
	int m_index;				// +0x10
	char m_pad14[0x0C];
	Rva00524306 m_images;		// +0x20
	char m_pad21[0x17];
	const Image *m_portrait;	// +0x38
	const Image *m_typeImage;	// +0x3C
};

#define APT_SLOT_IMAGE_KEY_SET( CLASS, METHOD, FORMAT, IMAGE, IMAGES )    \
	void CLASS::METHOD(const Image *image)                                \
	{                                                                     \
		if (image == IMAGE)                                               \
			return;                                                       \
		AsciiString key;                                                  \
		key.format(FORMAT, m_owner->m_level, m_owner->m_name.str(), m_index); \
		if (image)                                                        \
			IMAGES.rva00524725(key, image);                               \
		else                                                              \
			IMAGES.rva00524306(*(const StringBase<char> *)&key);          \
		IMAGE = image;                                                    \
	}

APT_SLOT_IMAGE_KEY_SET( Rva005EF181, rva005EF181, "_level%u.%s_IconSlotPortrait%d", m_portrait, m_images )
APT_SLOT_IMAGE_KEY_SET( Rva005EF181, rva005EF202, "_level%u.%s_IconSlotTypeImage%d", m_typeImage, m_images )

struct Rva005F07ADOwner
{
	char m_pad00[4];
	unsigned int m_level;		// +0x04
	StringBase<char> m_name;	// +0x08
	char m_pad0C[0x10];
	Rva00524306 m_images;		// +0x1C
};

class Rva005F07AD
{
public:
	void rva005F07AD(const Image *image);
private:
	char m_pad00[0x0C];
	Rva005F07ADOwner *m_owner;	// +0x0C
	int m_index;				// +0x10
	char m_pad14[0x0C];
	const Image *m_image;		// +0x20
};

APT_SLOT_IMAGE_KEY_SET( Rva005F07AD, rva005F07AD, "_level%u.%s_IconSlotTypeImage%d", m_image, m_owner->m_images )

struct Rva005F6CA8Owner
{
	char m_pad00[4];
	unsigned int m_level;		// +0x04
	StringBase<char> m_name;	// +0x08
	char m_pad0C[0x14];
	Rva00524306 m_images;		// +0x20
};

class Rva005F6CA8
{
public:
	void rva005F6CA8(const Image *image);
	void rva005F6D2C(const Image *image);
	void rva005F6E01(int quantity);
	void rva005F6E85(int unused, int turns);
private:
	char m_pad00[8];
	const Image *m_portrait;	// +0x08
	const Image *m_typeImage;	// +0x0C
	char m_pad10[0x0C];
	Rva005F6CA8Owner *m_owner;	// +0x1C
};

#define APT_OWNER_IMAGE_KEY_SET( CLASS, METHOD, FORMAT, IMAGE )           \
	void CLASS::METHOD(const Image *image)                                \
	{                                                                     \
		const Image *current = IMAGE;                                     \
		if (image == current)                                             \
			return;                                                       \
		AsciiString key;                                                  \
		key.format(FORMAT, m_owner->m_level, m_owner->m_name.str());      \
		if (image)                                                        \
			m_owner->m_images.rva00524725(key, image);                    \
		else                                                              \
			m_owner->m_images.rva00524306(*(const StringBase<char> *)&key); \
		IMAGE = image;                                                    \
	}

APT_OWNER_IMAGE_KEY_SET( Rva005F6CA8, rva005F6CA8, "_level%u.%s_InProgressIconSlotPortrait", m_portrait )
APT_OWNER_IMAGE_KEY_SET( Rva005F6CA8, rva005F6D2C, "_level%u.%s_InProgressIconSlotTypeImage", m_typeImage )

class Rva005F6FCC
{
public:
	void rva005F6FCC(const Image *image);
	void rva005F7053(int quantity);
	void rva005F70DA(int turns);
private:
	char m_pad00[0x0C];
	const Image *m_image;		// +0x0C
	char m_pad10[0x0C];
	Rva005F6CA8Owner *m_owner;	// +0x1C
	int m_index;				// +0x20
};

void Rva005F6FCC::rva005F6FCC(const Image *image)
{
	const Image *current = m_image;
	if (image == current)
		return;
	AsciiString key;
	key.format("_level%u.%s_QueuedIconSlotTypeImage%d", m_owner->m_level, m_owner->m_name.str(), m_index);
	if (image)
		m_owner->m_images.rva00524725(key, image);
	else
		m_owner->m_images.rva00524306(*(const StringBase<char> *)&key);
	m_image = image;
}

// The text half of the same panels: "APT:"-prefixed keys handed to the Apt
// window manager's rowed bfmeSetText (0x00225301), either with the caller's
// text (kept in a UnicodeString field and skipped when unchanged) or with a
// number formatted by 0x005F6B74 (rowed below), 0x005F6BD4 or 0x005F6C8E.
//
// ?rva005F1BDC@Rva005F191E@@QAEXABVUnicodeString@@@Z @0x005F1BDC 134B  _TerritoryName
// ?rva005F1C62@Rva005F191E@@QAEXABVUnicodeString@@@Z @0x005F1C62 134B  _TerritoryDescription
// ?rva005F6E01@Rva005F6CA8@@QAEXH@Z   @0x005F6E01 132B  _InProgressIconSlotQuantity
// ?rva005F6E85@Rva005F6CA8@@QAEXHH@Z  @0x005F6E85 135B  _InProgressIconSlotTurnsRemaining
// ?rva005F7053@Rva005F6FCC@@QAEXH@Z   @0x005F7053 135B  _QueuedIconSlotQuantity%d
// ?rva005F70DA@Rva005F6FCC@@QAEXH@Z   @0x005F70DA 135B  _QueuedIconSlotTurnsRemaining%d
// ?Rva005F6B74Format@@YA?AVUnicodeString@@H@Z @0x005F6B74 96B, the
// Rva005FF207Format shape with a strictly positive test.

#define APT_TEXT_KEY_SET( CLASS, METHOD, FORMAT, FIELD )                  \
	void CLASS::METHOD(const UnicodeString &text)                         \
	{                                                                     \
		if (text.compare(FIELD) == 0)                                     \
			return;                                                       \
		AsciiString key;                                                  \
		key.format(FORMAT, m_level, m_name.str());                        \
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, false); \
		FIELD = text;                                                     \
	}

APT_TEXT_KEY_SET( Rva005F191E, rva005F1BDC, "APT:_level%u.%s_TerritoryName", m_territoryName )
APT_TEXT_KEY_SET( Rva005F191E, rva005F1C62, "APT:_level%u.%s_TerritoryDescription", m_description )

UnicodeString __cdecl Rva005F6B74Format(int quantity)
{
	UnicodeString tmp;
	if (quantity > 0)
		tmp.format(L"%d", quantity);
	return tmp;
}

void Rva005F6CA8::rva005F6E01(int quantity)
{
	AsciiString key;
	key.format("APT:_level%u.%s_InProgressIconSlotQuantity", m_owner->m_level, m_owner->m_name.str());
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, Rva005F6B74Format(quantity), true);
}

void Rva005F6CA8::rva005F6E85(int unused, int turns)
{
	AsciiString key;
	key.format("APT:_level%u.%s_InProgressIconSlotTurnsRemaining", m_owner->m_level, m_owner->m_name.str());
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, Rva005F6C8EFormat(unused, turns), true);
}

void Rva005F6FCC::rva005F7053(int quantity)
{
	AsciiString key;
	key.format("APT:_level%u.%s_QueuedIconSlotQuantity%d", m_owner->m_level, m_owner->m_name.str(), m_index);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, Rva005F6B74Format(quantity), true);
}

void Rva005F6FCC::rva005F70DA(int turns)
{
	AsciiString key;
	key.format("APT:_level%u.%s_QueuedIconSlotTurnsRemaining%d", m_owner->m_level, m_owner->m_name.str(), m_index);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, Rva005F6BD4Format(turns), true);
}

// ?Rva005F6C8EFormat@@YA?AVUnicodeString@@HH@Z @0x005F6C8E 26B: forwards the
// second argument to 0x005F6BD4 (pinned) and returns its string.
UnicodeString __cdecl Rva005F6C8EFormat(int unused, int turns)
{
	(void)unused;
	return Rva005F6BD4Format(turns);
}

// ?rva00579B17@Rva00579B17@@QAEXHABVUnicodeString@@@Z @0x00579B17 106B:
// indexed text key APT:_level%u.%s.%d_Text from level +4 and name +8.
class Rva00579B17
{
public:
	void rva00579B17(int index, const UnicodeString &text);
private:
	char m_pad00[4];
	unsigned int m_level;		// +0x04
	StringBase<char> m_name;	// +0x08
};

void Rva00579B17::rva00579B17(int index, const UnicodeString &text)
{
	AsciiString key;
	key.format("APT:_level%u.%s.%d_Text", m_level, m_name.str(), index);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, false);
}
