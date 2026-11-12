// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?SetWidthAndComputeHeight@Impl@InGameCommandButtonHelp@@QAEHH@Z retail
// 0x0056CA31..0x0056CCE2 (689 bytes EH RET 4). WorldBuilder twin 0x0144ADD0
// InGameCommandButtonHelp::Impl::SetWidthAndComputeHeight
// (InGameCommandButtonHelp.cpp assert line 196) with the same callee graph;
// reached through the rowed help thunk 0x0056D2BD on the +0x08 Impl. It
// returns the computed height in EAX (cvttss2si then mov eax esi) so the
// address-derived void pin ?rva0056CA31@Rva0056CA31@@QAEXH@Z is wrong.
// Target evidence: stores the width at +0x18 and word-wraps the +0x1C and
// +0x2C display strings to it (slot 8); copies the +0x08 title and +0x0C
// description (rowed wide copy ctor) and swaps them when only the
// description has text; the rowed ComputeIconSizes 0x0056C7F1 gives the icon
// extents; each display string gets its text (slot 1) and its height is
// read back (slot 15): +0x1C the +0x04 name; +0x20 the title (at least the
// icon height when the title has text); +0x28 the shortcut line built from
// the +0x14 key through TheGameText slot 17 "TOOLTIP:Shortcut" and the rowed
// UnicodeString::format; +0x24 the description (at least the icon height);
// +0x2C the +0x10 cost text or L" " when empty (rowed isEmpty 0x00035740).
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;

#include "../../../../Include/Common/FloatPair.h"

#include "../../../../Include/GameClient/DisplayString.h"

#include "../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

struct IntPair;

// The header's inline length test, read as a 16-bit compare.
struct UnicodeStringHeaderView
{
	int ref_count;
	unsigned short length;
};
static __forceinline bool hasText(const UnicodeString &unicodeString)
{
	const UnicodeStringHeaderView *header = *(const UnicodeStringHeaderView *const *)&unicodeString;
	return header != 0 && header->length != 0;
}

#include "../../../../Include/GameClient/InGameCommandButtonHelp.h"


Int InGameCommandButtonHelp::Impl::SetWidthAndComputeHeight(Int width)
{
	m_18 = width;
	m_1C->setWordWrap(m_18);
	m_2C->setWordWrap(m_18);

	UnicodeString title = m_08;
	UnicodeString description = m_0C;
	if (!hasText(title) && hasText(description))
		title.swap(description);

	FloatPair icons;
	{
		FloatPair firstIcon;
		FloatPair secondIcon;
		ComputeIconSizes(&firstIcon, &secondIcon, &icons);
	}

	Int width2;
	Int height;
	m_1C->setText(m_04);
	m_1C->getSize(&width2, &height);
	float total = (float)height;

	Int titleHeightInt;
	m_20->setText(title);
	m_20->getSize(&width2, &titleHeightInt);
	float titleHeight = (float)titleHeightInt;
	if (hasText(title) && icons.y > titleHeight)
		titleHeight = icons.y;

	UnicodeString shortcut;
	if (m_14 != 0)
	{
		UnicodeString key(&m_14, 1);
		const void *keyData = *(const void *const *)&key;
		shortcut.format(TheGameText->fetchPtr("TOOLTIP:Shortcut"),
			keyData ? (const unsigned short *)((const char *)keyData + 8) : (const unsigned short *)L"");
	}
	Int shortcutHeightInt;
	m_28->setText(shortcut);
	m_28->getSize(&width2, &shortcutHeightInt);
	float shortcutHeight = (float)shortcutHeightInt;
	float lineHeight;
	if (m_14 != 0)
	{
		if (hasText(title))
			lineHeight = titleHeight > shortcutHeight ? titleHeight : shortcutHeight;
		else
			lineHeight = shortcutHeight;
	}
	else
	{
		lineHeight = titleHeight;
	}
	total += lineHeight;

	m_24->setText(description);
	if (hasText(description))
	{
		m_24->getSize(&width2, &height);
		float descriptionHeight = (float)height;
		if (icons.y > descriptionHeight)
			descriptionHeight = icons.y;
		total += descriptionHeight;
	}

	m_2C->setText(!m_10.isEmpty() ? m_10 : UnicodeString((const unsigned short *)L" "));
	m_2C->getSize(&width2, &height);
	total += (float)height;

	return (Int)total;
}
