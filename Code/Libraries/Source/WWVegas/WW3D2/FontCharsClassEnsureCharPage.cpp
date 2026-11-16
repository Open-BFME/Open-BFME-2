// cl: /DNDEBUG /MD
//
// FontCharsClass::ensureCharPage, retail 0x00155220 (249 bytes).
// Dedicated TU: the caller (loadCharacterData) lives in
// FontCharsClassLoadCharacterData.cpp, so the body lives here (a TU holding
// a row must not define that row's callees, and vice versa).
//
// Structure (all retail-measured): characters below 0x100 need no page.
// Otherwise the [FirstUnicodeChar, LastUnicodeChar] word range at +0x45C/+0x45E grows to
// include the character (already inside -> return). A fresh pointer array is
// array-newed, zeroed, the overlapping old slice is copied over, and the old
// array is array-deleted.

#include <string.h>
#include <new>

#include "FontCharsClass.h"

void FontCharsClass::ensureCharPage(unsigned short character)
{
	if (character < 0x100)
		return;
	if (FirstUnicodeChar <= character && character <= LastUnicodeChar)
		return;
	unsigned short newBase = FirstUnicodeChar < character ? FirstUnicodeChar : character;
	unsigned short newTop = LastUnicodeChar > character ? LastUnicodeChar : character;
	unsigned short count = (unsigned short)(newTop - newBase + 1);
	FontCharsClassCharDataStruct **newPages =
		(FontCharsClassCharDataStruct **) ::operator new[]((unsigned int)count * 4);
	memset(newPages, 0, (unsigned int)count * 4);
	if (UnicodeCharArray != 0) {
		memcpy(&newPages[FirstUnicodeChar - newBase], UnicodeCharArray, (unsigned int)(LastUnicodeChar - FirstUnicodeChar) * 4 + 4);
		::operator delete[](UnicodeCharArray);
		UnicodeCharArray = 0;
	}
	UnicodeCharArray = newPages;
	FirstUnicodeChar = newBase;
	LastUnicodeChar = newTop;
}
