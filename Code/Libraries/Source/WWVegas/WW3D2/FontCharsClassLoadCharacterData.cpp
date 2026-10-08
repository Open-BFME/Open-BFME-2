// cl: /DNDEBUG /MD
//
// FontCharsClass::loadCharacterData, retail 0x00158580 (260 bytes).
// Dedicated TU: the Thai-first glyph-ensure helper behind Get_Char_Spacing
// (9 fontchars callers). Reconstructed from a full instruction decode; no
// ZH/BFME1 body exists (BFME1 only declares it).
//
// Structure (all retail-measured): Thai composed ranges
// 0x0E01-0x0E3A / 0x0E3F-0x0E5B go through the screen DC (the font's HFONT
// at +0x48 selected in, GetGlyphIndicesW with GGI_MARK_NONEXISTING_GLYPHS
// over the stack argument itself, font restored); a resolved glyph index
// feeds Get_Char_Data, a missing one falls back to the alternate font and
// then to the bitmap path. Smaller characters read the 256-entry direct
// table at +0x4C; larger ones go through the page filler at 0x00155220 and
// the page table at +0x44C keyed by the base word at +0x45C. A null entry
// is rasterized through 0x00156A60; a -1 entry falls back to the alternate
// font (with a self-link guard) and then to null.
// The two callees keep opaque descriptive names: their addresses come from
// this body's own REL32 displacements, their true identities are unproven.

struct FontCharsClassCharDataStruct;

struct HDC__;
typedef struct HDC__ *HDC;
struct HGDIOBJ__;
typedef struct HGDIOBJ__ *HGDIOBJ;
typedef HGDIOBJ HFONT;

extern "C" __declspec(dllimport) HGDIOBJ __stdcall SelectObject(HDC hdc, HGDIOBJ obj);
extern "C" __declspec(dllimport) int __stdcall GetGlyphIndicesW(HDC hdc, const unsigned short *str, int count, unsigned short *indices, int flags);

// Cached screen-DC provider: retail reads the HDC from +0x10 of the
// structure at 0x00DF6F24 (same model as the banked Create_GDI_Font unit;
// all 21 image-wide references sit in fontchars code).
struct FontScreenDCGlobals
{
	unsigned char reserved[0x10];
	HDC screen_dc;
};
extern class FontCharsClassGdiState *g_fontCharsGdiState;

class FontCharsClass
{
public:
	FontCharsClassCharDataStruct const *loadCharacterData(unsigned short character);

private:
	void *m_uns00;
	void *m_uns04;
	FontCharsClass *AlternateUnicodeFont; // +0x08
	char m_unreconstructed_0C[0x48 - 0x0C];
	HFONT m_gdiFont; // +0x48
	FontCharsClassCharDataStruct const *m_glyphTable[256]; // +0x4C
	FontCharsClassCharDataStruct const **m_glyphPages; // +0x44C
	char m_unreconstructed_450[0x45C - 0x450]; // +0x450: character map (see Get_Char_Data unit)
	unsigned short m_pageBase; // +0x45C

	FontCharsClassCharDataStruct const *Get_Char_Data(unsigned short ch);
	void ensureCharPage(unsigned short ch); // retail 0x00155220, opaque
	FontCharsClassCharDataStruct const *loadCharBitmap(unsigned short ch); // retail 0x00156A60, opaque
};

FontCharsClassCharDataStruct const *FontCharsClass::loadCharacterData(unsigned short character)
{
	if ((character >= 0x0E01 && character <= 0x0E3A)
		|| (character >= 0x0E3F && character <= 0x0E5B)) {
		HFONT font = m_gdiFont;
		unsigned int glyph = 0xFFFF;
		HDC screen_dc = (*(FontScreenDCGlobals **)&g_fontCharsGdiState)->screen_dc;
		HGDIOBJ old_font = ::SelectObject(screen_dc, font);
		::GetGlyphIndicesW((*(FontScreenDCGlobals **)&g_fontCharsGdiState)->screen_dc, &character, 1, (unsigned short *)&glyph, 1);
		::SelectObject(screen_dc, old_font);
		if ((unsigned short)glyph != 0xFFFF)
			return Get_Char_Data((unsigned short)glyph);
		FontCharsClass *alt = AlternateUnicodeFont;
		if (alt != 0)
			return alt->loadCharacterData(character);
	}

	FontCharsClassCharDataStruct const *data;
	if (character < 0x100) {
		data = m_glyphTable[character];
	} else {
		ensureCharPage(character);
		data = m_glyphPages[character - m_pageBase];
	}
	if (data == 0)
		data = loadCharBitmap(character);
	if (data != (FontCharsClassCharDataStruct const *)-1)
		return data;
	FontCharsClass *alt = AlternateUnicodeFont;
	if (alt != 0 && this != alt)
		return alt->loadCharacterData(character);
	return 0;
}
