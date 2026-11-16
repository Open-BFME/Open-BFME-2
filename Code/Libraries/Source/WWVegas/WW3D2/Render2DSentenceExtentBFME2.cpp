// cl: /O2 /G7 /DNDEBUG /MD /EHsc /arch:SSE /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil
// ZH render2dsentence.cpp Get_Text_Extents; BFME1 donor 9cbfb551fe20.
// Native 158BA0..158C60/192B returns Vector2 through a hidden result pointer.
// The reference Vector2 copy constructor explains the SSE stores, unlike
// an implicit POD copy. Caller105CF6 consumes the two returned float fields.
// Thai spacing helper borrowed from BFME1 surface donor; BFME2 loadCharacterData.
struct FontCharsClassCharDataStruct
{
	unsigned short Value;
	short Width;
	short ExtraSpacing;
};

#include "FontCharsClass.h"

// Retail inlines the rowed FontCharsClass::Get_Char_Spacing (0x00158760,
// FontCharsClassGetCharSpacingThunk.cpp) here; a file-local copy emits no COMDAT.
static __forceinline int Inline_Char_Spacing(FontCharsClass *font, unsigned short character)
{
	const FontCharsClassCharDataStruct *data = font->loadCharacterData(character);
	if (data != 0 && data->Width != 0) {
		if ((character >= 0x0e01 && character <= 0x0e3a)
			|| (character >= 0x0e3f && character <= 0x0e5b)) {
			return data->Width + data->ExtraSpacing;
		}
		return data->Width - font->PixelOverlap - font->CharOverhang;
	}
	return 0;
}

#include "vector2.h"
#include "Render2DSentenceClass.h"
Vector2 Render2DSentenceClass::Get_Text_Extents(const unsigned short *text) {
    Vector2 extent(0,Font->CharHeight);
    while (*text) {
        unsigned short ch = *text++;
        if (ch != '\n') extent.X += Inline_Char_Spacing(Font, ch);
    }
    return extent;
}
