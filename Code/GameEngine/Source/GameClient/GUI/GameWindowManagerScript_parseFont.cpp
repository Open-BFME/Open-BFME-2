// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /EHsc /Oi-
//
// ?parseFont@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x00315BF5, 218 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseFont): quote-scanned name plus strcpy plus scanInt size/bold plus
// TheFontLibrary getFont plus m_font store. BFME2 deltas (all retail-measured):
// size travels as float (cvtsi2ss), bold as a setne byte, getFont takes the
// name by address (AsciiString temp constructed in the guarded block through
// the matched StringBase<char> ctor row at 0x37BA0, destroyed through the
// releaseBuffer pin at 0x36410), m_font sits at instData+0x184.
// BFME2 facts (all retail-measured):
// - scanInt is the GameWindowManagerScript file-static at 0x00314E96
//   (matched row plus pin; TEXTCOLOR precedent).
// - strtok rides the msvcr71 import at 0xBBA5EC (dllimport decl, cached in
//   esi across the six sites like retail).
// - strcpy rides the _strcpy thunk at 0x629176 (plain decl, /Oi- keeps it
//   out-of-line like the _strncpy precedent).
// - getFont rides the new pin at 0x2189E1 (dozens of font-fetch sites read
//   the same address; worker forwards to 0x21857E).
// - TheFontLibrary global at 0xDFE33C rides a TU-local extern (COMMON merge,
//   TheGameText precedent, no pin).
// - Identity: the .data dispatch table at 0x9BE198 pairs 'FONT' with
//   0x715BF5 (entries are name@+0/fn@+4; the walker at 0x31701C compares
//   names and calls [eax+4]).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

class AsciiString;
class GameFont;

#include "ascii_string.h"


class FontLibrary
{
public:
	GameFont *getFont(const AsciiString *name, float size, Bool bold);
};

extern FontLibrary *TheFontLibrary;
// TheFontLibrary: matched references place it at VA 0xdfe33c (zero-filled .bss).
FontLibrary * TheFontLibrary;

class WinInstanceData
{
public:
	char m_pad[0x184];
	GameFont *m_font;
};

// scanInt lives in GameWindowManagerScript.cpp (file-static at 0x00314E96).
// Declared extern (not static: MSVC rejects defined-never statics with
// C2129); the decoration is identical and the pin resolves the address.
Int scanInt(const char *source, Int &val);

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);
extern "C" char *__cdecl _mbscpy(char *dst, const char *src);

// ?parseFont@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseFont(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *c, *ptr;
	char *seps = " ,\n\r\t";
	char *stringSeps = ":,\n\r\t\"";
	char fontName[256];
	Int fontSize;
	Int fontBold;

	// "NAME"
	c = strtok(buffer, seps);  // label
	// scan to the first " mark
	ptr = buffer;
	while (*ptr != '"')
		ptr++;
	ptr++;  // skip the "
	c = strtok(ptr, stringSeps);  // value
	_mbscpy(fontName, c);

	// "SIZE"
	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanInt(c, fontSize);

	// "BOLD"
	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanInt(c, fontBold);

	if (TheFontLibrary != NULL)
	{
		GameFont *font;
		{
			AsciiString asciiName(fontName);

			font = TheFontLibrary->getFont(&asciiName, (float)fontSize, fontBold != 0);
		}
		if (font != NULL)
			instData->m_font = font;
	}

	return true;
}

static const void *s_parseFontAnchor = (const void *)parseFont;
