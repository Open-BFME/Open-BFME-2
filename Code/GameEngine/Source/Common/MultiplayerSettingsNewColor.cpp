// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?newMultiplayerColorDefinition@MultiplayerSettings@@QAEPAVMultiplayerColorDefinition@@VAsciiString@@@Z,
// retail 0x003813B7, 137 bytes. Dedicated TU (the shared
// MultiplayerSettings.cpp TU carries the ZH-shaped body unmatched; a same-TU
// definition would capture its callees' REL32 locally).
//
// ZH donor is in-tree (MultiplayerSettings.cpp::newMultiplayerColorDefinition:
// default tmp + getNumColors + list-assign + size + return slot). BFME2 deltas,
// all read off the body: the lazy numColors refill is inline (cache +0x40
// from master +0x38 while zero, TWICE -- once per list access, no size() call
// and no m_numColors store); the list at +0x34 is reached through the opaque
// lookup helper (pinned 0x3812E6, one int* arg -- the extra &tmp push ahead of
// the first call is hoisted early for the trailing operator=); the slot is
// assigned from tmp through the 0x380CAE row; the AsciiString name param is
// ignored on the value path (ZH does the same) and only torn down.
// The list address stays in edi across both lookups via a named reference.

#include "ascii_string.h"


struct RGBColor
{
	float red;
	float green;
	float blue;
	void setFromInt(int value);
};

class MultiplayerColorDefinition
{
public:
	MultiplayerColorDefinition();
	MultiplayerColorDefinition *operator=(const MultiplayerColorDefinition &other);

private:
	AsciiString m_tooltipName; // +0x00
	RGBColor m_rgbValue; // +0x04
	int m_color; // +0x10
	RGBColor m_rgbValueNight; // +0x14
	int m_colorNight; // +0x20
	RGBColor m_rgbExtra1; // +0x24
	RGBColor m_rgbExtra2; // +0x30
	bool m_extraFlag; // +0x3C
};

struct RetailColorList
{
	MultiplayerColorDefinition *lookup(int *which);
};

typedef int Int;

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *newMultiplayerColorDefinition(AsciiString name);
};

// ?newMultiplayerColorDefinition@MultiplayerSettings@@QAEPAVMultiplayerColorDefinition@@VAsciiString@@@Z
MultiplayerColorDefinition *MultiplayerSettings::newMultiplayerColorDefinition(AsciiString name)
{
	unsigned char *self = reinterpret_cast<unsigned char *>(this);
	int *masterCount = reinterpret_cast<int *>(self + 0x38);
	int *numColorsPtr = reinterpret_cast<int *>(self + 0x40);

	MultiplayerColorDefinition tmp;
	if (*numColorsPtr == 0)
		*numColorsPtr = *masterCount;
	Int numColors = *numColorsPtr;
	RetailColorList &colorList = *reinterpret_cast<RetailColorList *>(self + 0x34);
	colorList.lookup(&numColors)->operator=(tmp);
	*numColorsPtr = *masterCount;
	return colorList.lookup(&numColors);
}
