// cl: /DNDEBUG /MD /EHsc
// BFME2 port of Open-BFME-1 Code/Libraries/Source/WWVegas/WW3D2/Rva0093C4A0.cpp:
// GDI missing-glyph check with three retail exceptions (LF/CR/0x95).
// BFME2 adaptations: font-state global moved to 0x00DF6F24; /G7 so the
// missing-scan loop emits add (not inc). Dedicated TU so the already-matched
// Rva0093C870Owner::Check in Rva0093C870ChildCheck.cpp keeps its shape.
extern class FontCharsClassGdiState *g_fontCharsGdiState;

#include <windows.h>

extern "C" __declspec(dllimport) DWORD WINAPI GetGlyphIndicesW(
	HDC dc, LPCWSTR text, int count, LPWORD glyphs, DWORD flags);

struct FontCharsGDIState
{
	int refs;
	void *old_bitmap;
	void *bitmap;
	int unused;
	void *dc;
};

#define TheFontCharsGDIState (*(FontCharsGDIState **)&g_fontCharsGdiState)

class Rva0093C4A0Target
{
public:
	bool Check(const unsigned short *text, unsigned short *glyphs, int count);

private:
	char m_gap00[0x48];
	HFONT m_font;
};

bool Rva0093C4A0Target::Check(
	const unsigned short *text, unsigned short *glyphs, int count)
{
	bool missing;
	int i;
	register int remaining = count;
	if (remaining != 0)
	{
		HGDIOBJ font = m_font;
		register HDC dc = TheFontCharsGDIState->dc;
		missing = false;
		HGDIOBJ old_font[2];
		old_font[1] = SelectObject(dc, font);
		GetGlyphIndicesW(TheFontCharsGDIState->dc, text, remaining, glyphs, 1);

		i = 0;
		for (; i < remaining; ++i)
		{
			if (glyphs[i] == 0xffff &&
				text[i] != 0x000a && text[i] != 0x000d && text[i] != 0x0095)
			{
				missing = true;
				break;
			}
		}

		SelectObject(dc, old_font[1]);
		bool success = !missing;
		return success;
	}

	return false;
}
