// cl: /Oy- /DNDEBUG /MD /EHsc
// platformsdk
//
// ?parseColor@@YA_NPAHPAD@Z, retail 0x00314F32, 103 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseColor): strtok three color bytes via msvcr71 imports, atoi each,
// winMakeColor through slot 0x118 of the WindowManager at 0x009FEF1C.
// BFME2 facts (all retail-measured):
// - strtok rides the msvcr71 import at 0xBBA5EC, atoi at 0xBBA624
//   (both dllimport decls; retail calls them indirectly via esi/edi).
// - seps " \t\n\r" lives at 0xC0C23C (shared with parseImageOffset).
// - red/green/blue are bytes at [ebp-0xC/-8/-4] (mov al stores).
// - winMakeColor slot 0x118 (70); TheWindowManager global 0x009FEF1C.
// - Identity: caller at 0x00315B3C (mid-function) plus leaf lane.

typedef int Int;
typedef bool Bool;

typedef Int Color;
typedef unsigned char Byte;

#include <windows.h>
#include <string.h>
#include <stdlib.h>

#include "../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;


Bool parseColor(Color *color, char *buffer)
{
	char *c;
	Byte red, green, blue;

	c = strtok(buffer, " \t\n\r");
	red = (Byte)atoi(c);

	c = strtok(NULL, " \t\n\r");
	green = (Byte)atoi(c);

	c = strtok(NULL, " \t\n\r");
	blue = (Byte)atoi(c);

	*color = TheWindowManager->winMakeColor(red, green, blue, 255);

	return true;
}
