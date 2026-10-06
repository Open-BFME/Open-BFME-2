// cl: /DNDEBUG /MD /EHsc
//
// ?parseImageOffset@@YA_NPADPAVWinInstanceData@@0PAX@Z,
// retail 0x00314F99, 66 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseImageOffset): strtok the two offsets, atoi each.
// BFME2 facts (all retail-measured):
// - strtok rides the msvcr71 import at 0xBBA5EC, atoi at 0xBBA624
//   (both dllimport decls; retail calls them indirectly).
// - seps " \t\n\r" lives at 0xC0C23C.
// - m_imageOffset sits at instData+0x17C (x) and +0x180 (y).
// - Identity: the .data dispatch table at 0x9BE198 pairs 'IMAGEOFFSET'
//   with 0x714F99.

typedef int Int;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

struct ImageOffset
{
	Int x;
	Int y;
};

class WinInstanceData
{
public:
	unsigned char m_pad0[0x17C]; // +0
	ImageOffset m_imageOffset; // +0x17C
};

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *str);

// ?parseImageOffset@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseImageOffset(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *c;

	c = strtok(buffer, " \t\n\r");
	instData->m_imageOffset.x = atoi(c);

	c = strtok(NULL, " \t\n\r");
	instData->m_imageOffset.y = atoi(c);

	return true;
}

static const void *s_parseImageOffsetAnchor = (const void *)parseImageOffset;
