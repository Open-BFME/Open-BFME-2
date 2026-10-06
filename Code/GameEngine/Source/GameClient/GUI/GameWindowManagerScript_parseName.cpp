// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?parseName@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x00316355, 71 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseName): quote-scan, strtok the name, store it, key it.
// BFME2 facts (all retail-measured):
// - strtok rides the msvcr71 import at 0xBBA5EC (dllimport decl; the
//   single site emits the direct indirect call like retail).
// - stringSeps "\"" lives at 0xC0C2B4.
// - StringBase::set is the matched narrow row at 0x55F5 (public QAEXPBD;
//   AsciiString inline set forwards to it).
// - m_decoratedNameString sits at instData+0x18C, m_id at instData+0x04.
// - nameToKey(const AsciiString&) at 0x9FA65 is a matched row (declared,
//   never defined here); TheNameKeyGenerator is the extern pointer at
//   0xDF36A4 (DIR32 from retail).
// - Identity: the .data dispatch table at 0x9BE198 pairs 'NAME'
//   with 0x716355 (entries are name@+0/fn@+4; the walker at 0x31701C
//   compares names and calls [eax+4]).

#include <assert.h>

typedef int Int;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "ascii_string.h"


class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class WinInstanceData
{
public:
	unsigned char m_pad0[4];  // +0
	Int m_id;  // +4
	unsigned char m_pad1[0x18C - 8];  // +8
	AsciiString m_decoratedNameString;  // +0x18C
};

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// ?parseName@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseName(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *c, *ptr;
	char *stringSeps = "\"";

	// scan to the first " mark
	ptr = buffer;
	while (*ptr != '"')
		ptr++;
	ptr++;  // skip the first "
	c = strtok(ptr, stringSeps);  // name value
	instData->m_decoratedNameString.set(c);

	// given the name assign a window ID from the key generator
	assert(TheNameKeyGenerator);
	if (TheNameKeyGenerator)
		instData->m_id = (Int)TheNameKeyGenerator->nameToKey(instData->m_decoratedNameString);

	return true;
}

static const void *s_parseNameAnchor = (const void *)parseName;
