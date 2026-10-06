// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /EHsc /Oi-
//
// ?parseTooltipText@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x00315CFD, 112 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseTooltipText): quote-scan, strlen guards, strtok value, length check,
// m_tooltipString.set plus setTooltipText(TheGameText->fetch(c)).
// BFME2 facts (all retail-measured):
// - strlen rides a plain extern decl (E8 to the 0x629170 slot); /Oi-
//   keeps it out-of-line (initDelayFilter precedent).
// - strtok rides the msvcr71 import at 0xBBA5EC (dllimport decl; the
//   single site emits the direct indirect call like retail).
// - stringSeps "\n\r\t\"" lives at 0xC0C2B8.
// - The length guard compares against 0x80 (MAX_TEXT_LABEL has no in-tree
//   define; 128 is retail-measured).
// - StringBase::set is the matched narrow row at 0x55F5 (public QAEXPBD).
// - TheGameText fetch is vtable slot 0x3C returning UnicodeString by
//   value (VersionUnicode.cpp recipe, 14 pad virtuals); the fetch result
//   flows by value into setTooltipText with copy elision (no push, no
//   caller-side dtor, like retail).
// - m_tooltipString sits at instData+0x190 (retail lea ecx,[esi+0x190]).
// - Identity: the .data dispatch table at 0x9BE198 pairs 'TOOLTIPTEXT'
//   with 0x715CFD (entries are name@+0/fn@+4; the walker at 0x31701C
//   compares names and calls [eax+4]).

#include <string.h>
#include <assert.h>

#define DEBUG_LOG(x) ((void)0)

// Retail-measured (no in-tree define exists).
#define MAX_TEXT_LABEL 128

typedef int Int;
typedef bool Bool;
typedef unsigned short wchar_t;

#ifndef NULL
#define NULL 0
#endif

class UnicodeString;
class AsciiString;

#include "ascii_string.h"
#include "unicode_string.h"



// Retail fetch call uses vtable offset 0x3c (VersionUnicode.cpp recipe).
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

class WinInstanceData
{
public:
	void setTooltipText(UnicodeString text);

	char m_pad[0x190];
	AsciiString m_tooltipString;
};

// ?parseTooltipText@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseTooltipText(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *ptr = buffer;
	char *c;
	char *stringSeps = "\n\r\t\"";

	// scan to the first " mark
	while (*ptr != '"')
		ptr++;
	ptr++;  // skip the "
	if (strlen(ptr) == 1)
		return true;
	c = strtok(ptr, stringSeps);  // value
	if (strlen(c) >= MAX_TEXT_LABEL)
	{
		DEBUG_LOG(("TextTooltip label '%s' is too long, max is '%d'\n", c, MAX_TEXT_LABEL));
		assert(0);
		return false;
	}
	instData->m_tooltipString.set(c);
	instData->setTooltipText(TheGameText->fetch(c));

	return true;
}

static const void *s_parseTooltipTextAnchor = (const void *)parseTooltipText;
