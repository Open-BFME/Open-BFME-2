// cl: /O1

// W3DFontLibrary::loadFontData, retail 0x000902A6 (186 bytes, FUN_004902a6).
// Donor is the in-tree ZH W3DGameFont.cpp transcription (twin's TU carries
// the present-unmatched marker; this shard lands the body without touching
// their file): null guard, UnsignedInt point-size sanity cap at 100,
// font-worker lookup, metric plus handle stores, global-language alternate
// name with Arial Unicode MS fallback, fallback handle link, TRUE.
// BFME2 repairs against the donor: the worker takes a fourth detail argument
// (the request word at +0x1C, threaded through all three calls), the height
// is a direct member read at handle +0x2C (no virtual call), and the callee
// resolves through the pinned ?Rva0009017D cdecl spelling at 0x0009017D.
// The empty-name fallback is the "" literal at 0x00BBAC1C; the
// language state and the Arial literal ride DIR32 masking like the donors.
// SHAPE LAW (the wall this donor breaks): the size guard must stay an
// if/else assignment (fontChar NULL vs worker call), not an early return;
// only the assignment form keeps fontChar live across the check, which is
// what pulls the ebx/edi saves above the float conversion and selects the
// retail jne top plus the shared far false epilogue. Early-return rewrites
// of the same logic save at first use and desync the whole head.


#include "../../../../../GameEngine/Include/GameClient/GameFontClass.h"
#include "../../../../../GameEngine/Include/GameClient/FontLibrary.h"
#include "../../../../../GameEngine/Include/Common/GlobalLanguageClass.h"

struct FontCharsHandle
{
	char m_pad[8];
	void *m_alternate;        // +0x08
	char m_pad10[0x2C - 0x0C];
	int m_cachedHeight;       // +0x2C
};

// FontLibrary's slots 14/15 (FontLibrary.h); W3DFontLibrary overrides both.
class W3DFontLibrary : public FontLibrary
{
public:
	virtual ~W3DFontLibrary();

protected:
	virtual bool loadFontData(GameFont *font);
	virtual void releaseFontData(GameFont *font);
};

void *Rva0009017D(const char *name, float pointSize, bool bold, int extra);

// ?loadFontData@W3DFontLibrary@@QAE_NPAVGameFont@@@Z @0x000902A6
bool W3DFontLibrary::loadFontData(GameFont *font)
{
	FontCharsHandle *fontChar;

	if (font == 0)
		return false;

	if ((unsigned int)font->pointSize > 100)
		fontChar = 0;
	else
		fontChar = (FontCharsHandle *)Rva0009017D(font->nameString.str(),
			font->pointSize, font->bold ? true : false, font->m_1C);

	if (fontChar == 0)
		return false;

	font->fontData = fontChar;
	font->height = fontChar->m_cachedHeight;

	FontCharsHandle *unicodeFontChar;
	GlobalLanguage *language = TheGlobalLanguageData;
	if (language)
		unicodeFontChar = (FontCharsHandle *)Rva0009017D(language->m_unicodeFontName.str(),
			font->pointSize, font->bold ? true : false, font->m_1C);
	else
		unicodeFontChar = (FontCharsHandle *)Rva0009017D("Arial Unicode MS",
			font->pointSize, font->bold ? true : false, font->m_1C);

	if (unicodeFontChar)
		fontChar->m_alternate = unicodeFontChar;

	return true;
}
