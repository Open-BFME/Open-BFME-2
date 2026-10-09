// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Oi-
//
// ?parseTooltip@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x00315BA3, 82 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseTooltip): default tooltip text via wide set plus setTooltipText.
// BFME2 facts (all retail-measured):
// - Retail builds a UnicodeString temp (8B stack: temp plus by-value arg
//   slot), nulls it (and [ebp-0x10],0), sets wide L"Need tooltip
//   translation" (0xC0C270) through the matched StringBase<wchar>::set row
//   at 0x565D, copy-constructs the by-value argument through the
//   StringBase<wchar> copy pin at 0x37050, calls setTooltipText through the
//   pin at 0x322352, releases the temp through the releaseBuffer pin at
//   0x36E70, returns 1. EH prolog via 0x629188, scope 0xB7A55D.
// - UnicodeString stays implicit (copy/dtor inline to the StringBase member
//   calls, no out-of-line emission); the nulling default comes from an
//   inline StringBase() member-init chain.
// - Identity: the .data dispatch table at 0x9BE198 pairs 'TOOLTIP' with
//   0x715BA3 (entries are name@+0/fn@+4; the walker at 0x31701C compares
//   names and calls [eax+4]).

typedef int Int;
typedef bool Bool;
typedef unsigned short wchar_t;

#ifndef NULL
#define NULL 0
#endif

class UnicodeString;

#include "unicode_string.h"


class WinInstanceData
{
public:
	void setTooltipText(UnicodeString text);
};

// ?parseTooltip@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseTooltip(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	UnicodeString tooltip;
	tooltip.set(L"Need tooltip translation");

	instData->setTooltipText(tooltip);
	return true;
}

static const void *s_parseTooltipAnchor = (const void *)parseTooltip;
