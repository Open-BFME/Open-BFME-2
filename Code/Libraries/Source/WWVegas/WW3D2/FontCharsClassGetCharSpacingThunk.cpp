// cl: /DNDEBUG /MD
//
// FontCharsClass::Get_Char_Spacing, retail 0x00158760 (90 bytes).
// Dedicated TU (render2dsentence.cpp documents the ABI as
// ?Get_Char_Spacing@FontCharsClass@@QAEHG@Z emitted from this file).
// Verbatim BFME1 FontCharsClassGetCharSpacingThunk.cpp body: the record
// layout (Value@+0, Width@+2, ExtraSpacing@+4) and the overhang offsets
// (CharOverhang@+0x34, PixelOverlap@+0x38, subtracted in that order) all
// match the retail immediates. The one adaptation is the callee: BFME1
// calls Get_Char_Data here, but the retail REL32 decodes to 0x00158580,
// the Thai-first glyph-ensure helper (9 fontchars callers), pinned as
// loadCharacterData per BFME1 FontCharsClass_Get_Char_Data_BFME.cpp.

struct FontCharsClassCharDataStruct
{
	unsigned short Value;
	short Width;
	short ExtraSpacing;
};

class FontCharsClass
{
public:
	int Get_Char_Spacing(unsigned short ch);
	const FontCharsClassCharDataStruct *loadCharacterData(unsigned short ch);

private:
	char m_fields00[0x34];
	int CharOverhang;
	int PixelOverlap;
};

// ?Get_Char_Spacing@FontCharsClass@@QAEHG@Z
inline int FontCharsClass::Get_Char_Spacing(unsigned short ch)
{
	const FontCharsClassCharDataStruct *data = loadCharacterData(ch);
	if (data != 0 && data->Width != 0) {
		if ((ch >= 0x0e01 && ch <= 0x0e3a)
			|| (ch >= 0x0e3f && ch <= 0x0e5b)) {
		return data->Width + data->ExtraSpacing;
	}
	int spacing = data->Width;
	spacing -= PixelOverlap;
	spacing -= CharOverhang;
	return spacing;
	}

	return 0;
}

// The render-2D sentence units inline this method and emit the same select-any
// copy, which a plain definition here collided with. The anchor keeps this
// unit's copy for its row; it is not retail data.
int (FontCharsClass::*_bfmeInlineAnchor_FontCharsClassGetCharSpacingThunk)(unsigned short) = &FontCharsClass::Get_Char_Spacing;
