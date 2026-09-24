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
// The empty-name literal reuses the pinned g_bfmeEmptyF9 spelling; the
// language state and the Arial literal ride DIR32 masking like the donors.
// SHAPE LAW (the wall this donor breaks): the size guard must stay an
// if/else assignment (fontChar NULL vs worker call), not an early return;
// only the assignment form keeps fontChar live across the check, which is
// what pulls the ebx/edi saves above the float conversion and selects the
// retail jne top plus the shared far false epilogue. Early-return rewrites
// of the same logic save at first use and desync the whole head.

extern char g_bfmeEmptyF9[];

struct GameFont
{
	int m_reserved0;          // +0x00, untouched by this body
	int m_reserved1;          // +0x04, untouched by this body
	const char *m_nameData;   // +0x08, inline AsciiString buffer pointer
	float m_pointSize;        // +0x0C
	int m_height;             // +0x10, handle word at +0x2C
	void *m_fontData;         // +0x14
	unsigned char m_bold;     // +0x18
	int m_extra;              // +0x1C
};

struct FontCharsHandle
{
	char m_pad[8];
	void *m_alternate;        // +0x08
	char m_pad10[0x2C - 0x0C];
	int m_cachedHeight;       // +0x2C
};

struct GlobalLanguageData
{
	char m_pad[0x18];
	const char *m_unicodeNameData;  // +0x18, inline AsciiString buffer pointer
};

extern GlobalLanguageData *TheGlobalLanguageData;

class W3DFontLibrary
{
public:
	bool loadFontData(GameFont *font);
};

void *Rva0009017D(const char *name, float pointSize, bool bold, int extra);

// ?loadFontData@W3DFontLibrary@@QAE_NPAVGameFont@@@Z @0x000902A6
bool W3DFontLibrary::loadFontData(GameFont *font)
{
	FontCharsHandle *fontChar;

	if (font == 0)
		return false;

	if ((unsigned int)font->m_pointSize > 100)
		fontChar = 0;
	else
		fontChar = (FontCharsHandle *)Rva0009017D(font->m_nameData ? font->m_nameData + 8 : g_bfmeEmptyF9,
			font->m_pointSize, font->m_bold ? true : false, font->m_extra);

	if (fontChar == 0)
		return false;

	font->m_fontData = fontChar;
	font->m_height = fontChar->m_cachedHeight;

	FontCharsHandle *unicodeFontChar;
	GlobalLanguageData *language = TheGlobalLanguageData;
	if (language)
		unicodeFontChar = (FontCharsHandle *)Rva0009017D(language->m_unicodeNameData ? language->m_unicodeNameData + 8 : g_bfmeEmptyF9,
			font->m_pointSize, font->m_bold ? true : false, font->m_extra);
	else
		unicodeFontChar = (FontCharsHandle *)Rva0009017D("Arial Unicode MS",
			font->m_pointSize, font->m_bold ? true : false, font->m_extra);

	if (unicodeFontChar)
		fontChar->m_alternate = unicodeFontChar;

	return true;
}
