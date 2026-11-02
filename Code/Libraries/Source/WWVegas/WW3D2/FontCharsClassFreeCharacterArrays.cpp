// cl: /DNDEBUG /MD C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
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

#include <new>

#include "FontCharsClass.h"

// ?Free_Character_Arrays@FontCharsClass@@AAEXXZ
void FontCharsClass::Free_Character_Arrays()
{
	if (UnicodeCharArray != 0) {
		int count = (LastUnicodeChar - FirstUnicodeChar) + 1;
		for (int index = 0; index < count; index++) {
			if (UnicodeCharArray[index] != 0 && UnicodeCharArray[index] != (FontCharsClassCharDataStruct *)-1) {
				::operator delete(UnicodeCharArray[index]);
				UnicodeCharArray[index] = 0;
			}
		}
		::operator delete[](UnicodeCharArray);
		UnicodeCharArray = 0;
	}
	for (int index = 0; index < 256; index++) {
		if (ASCIICharArray[index] != 0 && ASCIICharArray[index] != (FontCharsClassCharDataStruct *)-1) {
			::operator delete(ASCIICharArray[index]);
			ASCIICharArray[index] = 0;
		}
	}
}
