// cl: /DNDEBUG /MD
//
// FontCharsClass::Free_Character_Arrays, retail 0x00154890 (166 bytes).
// Dedicated TU: render2dsentence.cpp already carries this body verbatim from
// BFME1 with a present-unmatched marker, but its FontCharsClass comes from
// ZH headers (Unicode at +0x45C, Last at +0x460, First at +0x462, ASCII base
// at +0x5C) while retail proves Unicode at +0x44C, First at +0x45C, Last at
// +0x45E, ASCII at +0x4C (1024B table +0x4C..+0x44C, 12B map gap at +0x450).
// This TU reuses the proven loadCharacterData layout (glyph table + pages +
// 12B gap + page base) with BFME1 First/Last names for the two words.

struct FontCharsClassCharDataStruct;

void __cdecl operator delete[](void *ptr);

class FontCharsClass
{
private:
	void Free_Character_Arrays();

private:
	void *m_uns00;
	void *m_uns04;
	FontCharsClass *m_alternateUnicodeFont; // +0x08
	char m_unreconstructed_0C[0x48 - 0x0C];
	void *m_gdiFont; // +0x48 (HFONT, opaque here)
	FontCharsClassCharDataStruct *m_asciiCharArray[256]; // +0x4C (ASCIICharArray)
	FontCharsClassCharDataStruct **m_unicodeCharArray; // +0x44C (UnicodeCharArray)
	char m_unreconstructed_450[0x45C - 0x450]; // +0x450: 12B character map gap
	unsigned short m_firstUnicodeChar; // +0x45C (pageBase in the load unit)
	unsigned short m_lastUnicodeChar; // +0x45E
};

// ?Free_Character_Arrays@FontCharsClass@@AAEXXZ
void FontCharsClass::Free_Character_Arrays()
{
	if (m_unicodeCharArray != 0) {
		int count = (m_lastUnicodeChar - m_firstUnicodeChar) + 1;
		for (int index = 0; index < count; index++) {
			if (m_unicodeCharArray[index] != 0 && m_unicodeCharArray[index] != (FontCharsClassCharDataStruct *)-1) {
				::operator delete(m_unicodeCharArray[index]);
				m_unicodeCharArray[index] = 0;
			}
		}
		::operator delete[](m_unicodeCharArray);
		m_unicodeCharArray = 0;
	}
	for (int index = 0; index < 256; index++) {
		if (m_asciiCharArray[index] != 0 && m_asciiCharArray[index] != (FontCharsClassCharDataStruct *)-1) {
			::operator delete(m_asciiCharArray[index]);
			m_asciiCharArray[index] = 0;
		}
	}
}
