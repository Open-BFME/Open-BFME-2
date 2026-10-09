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

struct FloatPair
{
	float x;
	float y;
};

class DisplayString
{
public:
	virtual void v00();
	virtual void setText(UnicodeString text);	// slot 1
	virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07();
	virtual void setWordWrap(Int wordWrap);	// slot 8
	virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual void getSize(Int *width, Int *height);	// slot 15
};

class GameTextInterface
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11) V(12) V(13) V(14)
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);		// +0x3C
	V(16)
	virtual const UnicodeString &fetchRef(const char *label, Bool *exists = 0);	// +0x44
#undef V
};
extern GameTextInterface *TheGameText;

struct IntPair;

// The header's inline length test, read as a 16-bit compare.
struct UnicodeStringHeaderView
{
	int ref_count;
	unsigned short length;
};
static __forceinline bool hasText(const UnicodeString &s)
{
	const UnicodeStringHeaderView *header = *(const UnicodeStringHeaderView *const *)&s;
	return header != 0 && header->length != 0;
}

class InGameCommandButtonHelp
{
public:
	class Impl;
};

class InGameCommandButtonHelp::Impl
{
public:
	void ComputeIconSizes(FloatPair *a, FloatPair *b, FloatPair *out);
	Int SetWidthAndComputeHeight(Int width);

private:
	void *m_owner;                     // +0x00
	UnicodeString m_name;              // +0x04
	UnicodeString m_title;             // +0x08
	UnicodeString m_description;       // +0x0C
	UnicodeString m_cost;              // +0x10
	unsigned short m_shortcutKey;      // +0x14
	Int m_width;                       // +0x18
	DisplayString *m_nameString;       // +0x1C
	DisplayString *m_titleString;      // +0x20
	DisplayString *m_descriptionString; // +0x24
	DisplayString *m_shortcutString;   // +0x28
	DisplayString *m_costString;       // +0x2C
	IntPair *m_icon30;                 // +0x30
	IntPair *m_icon34;                 // +0x34
};

Int InGameCommandButtonHelp::Impl::SetWidthAndComputeHeight(Int width)
{
	m_width = width;
	m_nameString->setWordWrap(m_width);
	m_costString->setWordWrap(m_width);

	UnicodeString title = m_title;
	UnicodeString description = m_description;
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
	m_nameString->setText(m_name);
	m_nameString->getSize(&width2, &height);
	float total = (float)height;

	Int titleHeightInt;
	m_titleString->setText(title);
	m_titleString->getSize(&width2, &titleHeightInt);
	float titleHeight = (float)titleHeightInt;
	if (hasText(title) && icons.y > titleHeight)
		titleHeight = icons.y;

	UnicodeString shortcut;
	if (m_shortcutKey != 0)
	{
		UnicodeString key(&m_shortcutKey, 1);
		const void *keyData = *(const void *const *)&key;
		shortcut.format(&TheGameText->fetchRef("TOOLTIP:Shortcut"),
			keyData ? (const unsigned short *)((const char *)keyData + 8) : (const unsigned short *)L"");
	}
	Int shortcutHeightInt;
	m_shortcutString->setText(shortcut);
	m_shortcutString->getSize(&width2, &shortcutHeightInt);
	float shortcutHeight = (float)shortcutHeightInt;
	float lineHeight;
	if (m_shortcutKey != 0)
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

	m_descriptionString->setText(description);
	if (hasText(description))
	{
		m_descriptionString->getSize(&width2, &height);
		float descriptionHeight = (float)height;
		if (icons.y > descriptionHeight)
			descriptionHeight = icons.y;
		total += descriptionHeight;
	}

	m_costString->setText(!m_cost.isEmpty() ? m_cost : UnicodeString((const unsigned short *)L" "));
	m_costString->getSize(&width2, &height);
	total += (float)height;

	return (Int)total;
}
