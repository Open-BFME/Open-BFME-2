// cl: /DNDEBUG /MD
//
// FontCharsClass::ensureCharPage, retail 0x00155220 (249 bytes).
// Dedicated TU: the caller (loadCharacterData) lives in
// FontCharsClassLoadCharacterData.cpp, so the body lives here (a TU holding
// a row must not define that row's callees, and vice versa).
//
// Structure (all retail-measured): characters below 0x100 need no page.
// Otherwise the [m_pageBase, m_pageTop] word range at +0x45C/+0x45E grows to
// include the character (already inside -> return). A fresh pointer array is
// array-newed, zeroed, the overlapping old slice is copied over, and the old
// array is array-deleted.

#include <string.h>
#include <new>

struct FontCharsClassCharDataStruct;

class FontCharsClass
{
private:
	void *m_uns00;
	void *m_uns04;
	void *m_uns08;
	char m_unreconstructed_0C[0x44C - 0x0C];
	FontCharsClassCharDataStruct const **m_glyphPages; // +0x44C
	char m_unreconstructed_450[0x45C - 0x450];
	unsigned short m_pageBase; // +0x45C
	unsigned short m_pageTop; // +0x45E

	void ensureCharPage(unsigned short character);
};

void FontCharsClass::ensureCharPage(unsigned short character)
{
	if (character < 0x100)
		return;
	if (m_pageBase <= character && character <= m_pageTop)
		return;
	unsigned short newBase = m_pageBase < character ? m_pageBase : character;
	unsigned short newTop = m_pageTop > character ? m_pageTop : character;
	unsigned short count = (unsigned short)(newTop - newBase + 1);
	FontCharsClassCharDataStruct const **newPages =
		(FontCharsClassCharDataStruct const **) ::operator new[]((unsigned int)count * 4);
	memset(newPages, 0, (unsigned int)count * 4);
	if (m_glyphPages != 0) {
		memcpy(&newPages[m_pageBase - newBase], m_glyphPages, (unsigned int)(m_pageTop - m_pageBase) * 4 + 4);
		::operator delete[](m_glyphPages);
		m_glyphPages = 0;
	}
	m_glyphPages = newPages;
	m_pageBase = newBase;
	m_pageTop = newTop;
}
