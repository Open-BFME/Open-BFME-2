// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?parseHeaderTemplate@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x00315CCF, 46 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseHeaderTemplate): quote-scan, strtok the name, store it.
// BFME2 facts (all retail-measured):
// - strtok rides the msvcr71 import at 0xBBA5EC (dllimport decl; the
//   single site emits the direct indirect call like retail).
// - stringSeps "\"" lives at 0xC0C2B4.
// - StringBase::set is the matched narrow row at 0x55F5 (public QAEXPBD,
//   Version-lesson idiom; AsciiString inline set forwards to it).
// - m_headerTemplateName sits at instData+0x194.
// - Identity: the .data dispatch table at 0x9BE198 pairs 'HEADERTEMPLATE'
//   with 0x715CCF (entries are name@+0/fn@+4; the walker at 0x31701C
//   compares names and calls [eax+4]).

typedef int Int;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

#include "ascii_string.h"


class WinInstanceData
{
public:
	char m_pad[0x194];
	AsciiString m_headerTemplateName;
};

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// ?parseHeaderTemplate@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseHeaderTemplate(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *c, *ptr;
	char *stringSeps = "\"";

	// scan to the first " mark
	ptr = buffer;
	while (*ptr != '"')
		ptr++;
	ptr++;  // skip the first "
	c = strtok(ptr, stringSeps);  // name value

	instData->m_headerTemplateName.set(c);

	return true;
}

static const void *s_parseHeaderTemplateAnchor = (const void *)parseHeaderTemplate;
