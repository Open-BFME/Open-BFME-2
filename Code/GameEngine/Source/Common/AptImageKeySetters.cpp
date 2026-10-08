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
// ?SetImage@Impl@InGameCommandButtonMovieClip@@QAEXPBVImage@@@Z  @0x005C7BE1 124B  _Image
// ?SetImage@Impl@CommandButtonMovieClip@StrategicHUD@@QAEXPBVImage@@@Z  @0x005E0E1D 124B  _Image
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

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

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

class InGameCommandButtonMovieClip
{
public:
	class Impl;
};

class InGameCommandButtonMovieClip::Impl
{
public:
	void SetImage(const Image *image);
	void SetProductionCount(int count);
	void SetState(int index);
private:
	char m_pad00[8];
	unsigned int m_level;		// +0x08
	StringBase<char> m_name;	// +0x0C
	char m_pad10[0x24];
	Rva00524306 m_images;		// +0x34
	char m_pad35[0x4C - 0x35];
	unsigned char m_stateEnabled;	// +0x4C
	char m_pad4D[3];
	int m_state;				// +0x50
	char m_pad54[0x58 - 0x54];
	int m_count;				// +0x58
	const Image *m_image;		// +0x5C
};

APT_IMAGE_KEY_SET( InGameCommandButtonMovieClip::Impl, SetImage, "_level%u.%s_Image", m_image )

namespace StrategicHUD {
class CommandButtonMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::CommandButtonMovieClip::Impl
{
public:
	void SetImage(const Image *image);
private:
	char m_pad00[8];
	unsigned int m_level;		// +0x08
	StringBase<char> m_name;	// +0x0C
	char m_pad10[0x18];
	Rva00524306 m_images;		// +0x28
	char m_pad29[0x0B];
	const Image *m_image;		// +0x34
};

APT_IMAGE_KEY_SET( StrategicHUD::CommandButtonMovieClip::Impl, SetImage, "_level%u.%s_Image", m_image )

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
// ?rva005F191E@Impl@RegionDetailsTerritoryMovieClip@StrategicHUD@@QAEXPBVImage@@@Z  @0x005F191E 123B  _MapPreview
// StrategicHUD::ArmyMemberIconMovieClip::Impl::SetTypeImage  @0x005FC7DE 124B  _TypeImage
// ?rva005EF181@Rva005EF181@@QAEXPBVImage@@@Z  @0x005EF181 129B  _IconSlotPortrait%d
// ?rva005EF202@Rva005EF181@@QAEXPBVImage@@@Z  @0x005EF202 129B  _IconSlotTypeImage%d
// ?rva005F07AD@Rva005F07AD@@QAEXPBVImage@@@Z  @0x005F07AD 133B  _IconSlotTypeImage%d
// ?rva005F6CA8@InProgressIconSlot@Impl@BuildQueueDetailsMovieClip@StrategicHUD@@QAEXPBVImage@@@Z  @0x005F6CA8 132B  _InProgressIconSlotPortrait
// ?rva005F6D2C@InProgressIconSlot@Impl@BuildQueueDetailsMovieClip@StrategicHUD@@QAEXPBVImage@@@Z  @0x005F6D2C 132B  _InProgressIconSlotTypeImage
// ?rva005F6FCC@QueuedIconSlot@Impl@BuildQueueDetailsMovieClip@StrategicHUD@@QAEXPBVImage@@@Z  @0x005F6FCC 135B  _QueuedIconSlotTypeImage%d

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

namespace StrategicHUD {
class RegionDetailsTerritoryMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::RegionDetailsTerritoryMovieClip::Impl
{
public:
	void rva005F191E(const Image *image);
	void SetTerritoryName(const UnicodeString &text);
	void SetTerritoryDescription(const UnicodeString &text);
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

APT_IMAGE_KEY_SET( StrategicHUD::RegionDetailsTerritoryMovieClip::Impl, rva005F191E, "_level%u.%s_MapPreview", m_image )

namespace StrategicHUD {
class ArmyMemberIconMovieClip
{
public:
	class Impl;
};
}

// WorldBuilder names 0x005FC7DE StrategicHUD::ArmyMemberIconMovieClip::Impl::SetTypeImage
// (its __FUNCTION__ string); 0x005FC85A shares its this and is unnamed in WB.
class StrategicHUD::ArmyMemberIconMovieClip::Impl
{
public:
	void SetTypeImage(const Image *image);
	void rva005FC85A(int quantity);
private:
	char m_pad00[8];
	unsigned int m_level;		// +0x08
	StringBase<char> m_name;	// +0x0C
	char m_pad10[0x0C];
	Rva00524306 m_images;		// +0x1C
	char m_pad1D[0x0F];
	const Image *m_image;		// +0x2C
	int m_quantity;				// +0x30
};

void StrategicHUD::ArmyMemberIconMovieClip::Impl::SetTypeImage(const Image *image)
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

namespace StrategicHUD {
class BuildQueueDetailsMovieClip
{
public:
	class Impl
	{
	public:
		class InProgressIconSlot;
		class QueuedIconSlot;
	};
};
}

class StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot
{
public:
	void rva005F6CA8(const Image *image);
	void rva005F6D2C(const Image *image);
	void SetQuantityString(int quantity);
	void SetProgressString(int unused, int turns);
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

APT_OWNER_IMAGE_KEY_SET( StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot, rva005F6CA8, "_level%u.%s_InProgressIconSlotPortrait", m_portrait )
APT_OWNER_IMAGE_KEY_SET( StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot, rva005F6D2C, "_level%u.%s_InProgressIconSlotTypeImage", m_typeImage )

class StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot
{
public:
	void rva005F6FCC(const Image *image);
	void SetQuantityString(int quantity);
	void SetNumTurnsString(int turns);
private:
	char m_pad00[0x0C];
	const Image *m_image;		// +0x0C
	char m_pad10[0x0C];
	Rva005F6CA8Owner *m_owner;	// +0x1C
	int m_index;				// +0x20
};

void StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot::rva005F6FCC(const Image *image)
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
// ?SetTerritoryName@Impl@RegionDetailsTerritoryMovieClip@StrategicHUD@@QAEXABVUnicodeString@@@Z @0x005F1BDC 134B  _TerritoryName
// ?SetTerritoryDescription@Impl@RegionDetailsTerritoryMovieClip@StrategicHUD@@QAEXABVUnicodeString@@@Z @0x005F1C62 134B  _TerritoryDescription
// ?SetQuantityString@InProgressIconSlot@Impl@BuildQueueDetailsMovieClip@StrategicHUD@@QAEXH@Z   @0x005F6E01 132B  _InProgressIconSlotQuantity
// ?SetProgressString@InProgressIconSlot@Impl@BuildQueueDetailsMovieClip@StrategicHUD@@QAEXHH@Z  @0x005F6E85 135B  _InProgressIconSlotTurnsRemaining
// ?SetQuantityString@QueuedIconSlot@Impl@BuildQueueDetailsMovieClip@StrategicHUD@@QAEXH@Z   @0x005F7053 135B  _QueuedIconSlotQuantity%d
// ?SetNumTurnsString@QueuedIconSlot@Impl@BuildQueueDetailsMovieClip@StrategicHUD@@QAEXH@Z   @0x005F70DA 135B  _QueuedIconSlotTurnsRemaining%d
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

APT_TEXT_KEY_SET( StrategicHUD::RegionDetailsTerritoryMovieClip::Impl, SetTerritoryName, "APT:_level%u.%s_TerritoryName", m_territoryName )
APT_TEXT_KEY_SET( StrategicHUD::RegionDetailsTerritoryMovieClip::Impl, SetTerritoryDescription, "APT:_level%u.%s_TerritoryDescription", m_description )

UnicodeString __cdecl Rva005F6B74Format(int quantity)
{
	UnicodeString tmp;
	if (quantity > 0)
		tmp.format(L"%d", quantity);
	return tmp;
}

UnicodeString __cdecl Rva005F6BD4Format(int turns)
{
	UnicodeString tmp;
	if (turns != 1) {
		bool exists;
		UnicodeString format = TheGameText->fetch("STRATEGICHUD:ConstructionTurnsRemaining", &exists);
		if (exists)
			tmp.format(format.str(), turns);
	} else {
		tmp.set(TheGameText->fetch("STRATEGICHUD:ConstructionOneTurnRemaining", 0));
	}
	return tmp;
}

void StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot::SetQuantityString(int quantity)
{
	AsciiString key;
	key.format("APT:_level%u.%s_InProgressIconSlotQuantity", m_owner->m_level, m_owner->m_name.str());
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, Rva005F6B74Format(quantity), true);
}

void StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot::SetProgressString(int unused, int turns)
{
	AsciiString key;
	key.format("APT:_level%u.%s_InProgressIconSlotTurnsRemaining", m_owner->m_level, m_owner->m_name.str());
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, Rva005F6C8EFormat(unused, turns), true);
}

void StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot::SetQuantityString(int quantity)
{
	AsciiString key;
	key.format("APT:_level%u.%s_QueuedIconSlotQuantity%d", m_owner->m_level, m_owner->m_name.str(), m_index);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, Rva005F6B74Format(quantity), true);
}

void StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot::SetNumTurnsString(int turns)
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

// StrategicHUD::StatsDisplayImpl::SetRowText @0x00579B17 106B (WorldBuilder
// name, its __FUNCTION__ string):
// indexed text key APT:_level%u.%s.%d_Text from level +4 and name +8.
namespace StrategicHUD {
class StatsDisplayImpl;
}

class StrategicHUD::StatsDisplayImpl
{
public:
	void SetRowText(int index, const UnicodeString &text);
private:
	char m_pad00[4];
	unsigned int m_level;		// +0x04
	StringBase<char> m_name;	// +0x08
};

void StrategicHUD::StatsDisplayImpl::SetRowText(int index, const UnicodeString &text)
{
	AsciiString key;
	key.format("APT:_level%u.%s.%d_Text", m_level, m_name.str(), index);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, false);
}

// StrategicHUD::ArmyMemberIconMovieClip::Impl::rva005FC85A @0x005FC85A 163B: the _TypeImage panel's
// quantity text. Unchanged counts are skipped, positive ones are formatted
// as L"%d" (empty otherwise) and set under APT:_level%u.%s_Quantity.
void StrategicHUD::ArmyMemberIconMovieClip::Impl::rva005FC85A(int quantity)
{
	if (quantity == m_quantity)
		return;
	UnicodeString text;
	if (quantity > 0)
		text.format(L"%d", quantity);
	AsciiString key;
	key.format("APT:_level%u.%s_Quantity", m_level, m_name.str());
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, true);
	m_quantity = quantity;
}

// ?SetProductionCount@Impl@InGameCommandButtonMovieClip@@QAEXH@Z @0x005C7AE1 181B: the _Image panel's
// production count text. Unchanged counts are skipped, positive ones are
// formatted as L"%d", others become L" " (VA 0x00BC26DC), and the text is set
// under APT:_level%u.%s_ProductionCount.
void InGameCommandButtonMovieClip::Impl::SetProductionCount(int count)
{
	if (count == m_count)
		return;
	UnicodeString text;
	if (count > 0)
		text.format(L"%d", count);
	else
		text = L" ";
	AsciiString key;
	key.format("APT:_level%u.%s_ProductionCount", m_level, m_name.str());
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, false);
	m_count = count;
}

// InGameCommandButtonMovieClip::Impl::SetState @0x005C7B96 75B (WorldBuilder
// name: WB's body tests the same +0x4C flag and +0x50 cached state, then calls
// the Apt "SetState" through 0x0050E9FE with the +0x0C name and +0x08 level).
// Evidence: flag at +0x4c plus cached index at +0x50 plus team ptr at +0x0c with +8 name or empty plus level at +0x08 plus table g_00C74A98 indexed by arg plus SetState plus TheRva00222A8BTarget; same shape as rowed Rva005FB6E2 eliminated/survived setters; caller jmp at 0x005C7C78.
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
// Retail's eight state-name pointers at VA 0x00C74A98. The following bytes
// belong to the separate "_level%u" format; the table ends after entry eight.
#pragma section(".rdata", read)
__declspec(allocate(".rdata")) const char *g_00C74A98[] = {
    "_unused", "_disabled", "_extraDisabled", "_cantAfford",
    "_static", "_notReady", "_up", "_visuallyEnabled"
};
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0);
struct Rva005C7B96Team
{
    char m_pad[8];
    char m_name[1];
};
void InGameCommandButtonMovieClip::Impl::SetState(int index)
{
    if (!m_stateEnabled)
        return;
    if (index == m_state)
        return;
    const Rva005C7B96Team *team = *(Rva005C7B96Team *const *)&m_name;
    const char *teamName;
    if (team)
        teamName = team->m_name;
    else
        teamName = "";
    Rva0050E9FEAptCall(TheRva00222A8BTarget, (void *)m_level, teamName, "SetState", &g_00C74A98[index]);
    m_state = index;
}
