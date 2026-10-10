// cl: /O2 /G7 /DNDEBUG /MD /EHsc /arch:SSE /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
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

// The callsite sets ecx to this font object, pushes one WCHAR, and the body
// returns a character-record pointer with RET 4.  This name and ABI are
// already pinned independently by the matching font-spacing thunk.
class FontCharsClass
{
public:
	const FontCharsClassCharDataStruct *loadCharacterData(unsigned short character);

	__forceinline int Get_Char_Height() const
	{
		return char_height;
	}

	// Inline copy of the rowed FontCharsClass::Get_Char_Spacing (0x00158760, FontCharsClassGetCharSpacingThunk.cpp),
	// which retail inlines here; a distinct name keeps its COMDAT from colliding with that row.
	__forceinline int Get_Char_Spacing_Inline(unsigned short character)
	{
		const FontCharsClassCharDataStruct *data = loadCharacterData(character);
		if (data != 0 && data->Width != 0) {
			if ((character >= 0x0e01 && character <= 0x0e3a)
				|| (character >= 0x0e3f && character <= 0x0e5b)) {
				return data->Width + data->ExtraSpacing;
			}
			return data->Width - pixel_overlap - char_overhang;
		}
		return 0;
	}

private:
	char fields00[0x2c];
	int char_height;
	char fields30[4];
	int char_overhang;
	int pixel_overlap;
};

#include "vector2.h"
class Render2DSentenceClass {
public:
    Vector2 Get_Text_Extents(const unsigned short *text);
private:
    char m_pad00[0x4C];
    FontCharsClass *Font;
};
Vector2 Render2DSentenceClass::Get_Text_Extents(const unsigned short *text) {
    Vector2 extent(0,Font->Get_Char_Height());
    while (*text) {
        unsigned short ch = *text++;
        if (ch != '\n') extent.X += Font->Get_Char_Spacing_Inline(ch);
    }
    return extent;
}
