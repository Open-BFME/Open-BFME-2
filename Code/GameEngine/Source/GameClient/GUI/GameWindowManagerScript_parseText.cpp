// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Oi-
//
// ?parseText@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x00315D6D, 68 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseText): quote-scan, strtok value, length check, label store. BFME2
// stores the label through AsciiString::set (retail calls the matched
// narrow row at 0x55F5 on instData+0x188); the BFME1 ancestor assigns a
// char* directly.
// BFME2 facts (all retail-measured):
// - strlen rides a plain extern decl (E8 to the 0x629170 slot); /Oi-
//   keeps it out-of-line (initDelayFilter precedent).
// - strtok rides the msvcr71 import at 0xBBA5EC (dllimport decl; the
//   single site emits the direct indirect call like retail).
// - stringSeps "\n\r\t\"" lives at 0xC0C2B8.
// - The length guard compares against 0x80 (MAX_TEXT_LABEL, 128,
//   retail-measured; no in-tree define exists).
// - StringBase::set is the matched narrow row at 0x55F5 (public QAEXPBD).
// - Identity: the .data dispatch table at 0x9BE198 pairs 'TEXT'
//   with 0x715D6D (entries are name@+0/fn@+4; the walker at 0x31701C
//   compares names and calls [eax+4]).

#include <string.h>
#include <assert.h>

#define DEBUG_LOG(x) ((void)0)

// Retail-measured (no in-tree define exists).
#define MAX_TEXT_LABEL 128

typedef int Int;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

class UnicodeString;
class AsciiString;

#include "ascii_string.h"


class WinInstanceData
{
public:
	char m_pad[0x188];
	AsciiString m_textLabelString;
};

// ?parseText@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseText(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *ptr = buffer;
	char *c;
	char *stringSeps = "\n\r\t\"";

	// scan to the first " mark
	while (*ptr != '"')
		ptr++;
	ptr++;  // skip the "
	c = strtok(ptr, stringSeps);  // value
	if (strlen(c) >= MAX_TEXT_LABEL)
	{
		DEBUG_LOG(("Text label '%s' is too long, max is '%d'\n", c, MAX_TEXT_LABEL));
		assert(0);
		return false;
	}
	instData->m_textLabelString.set(c);

	return true;
}

static const void *s_parseTextAnchor = (const void *)parseText;
