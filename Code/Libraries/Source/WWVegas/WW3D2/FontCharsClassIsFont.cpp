// cl: /O2 /arch:SSE

// FontCharsClass::Is_Font, retail 0x00154840 (66 bytes).
// Donor is ZH render2dsentence.cpp Is_Font (name/size/bold triple match with
// a false default); BFME2 repairs: the point size is a float compared with an
// SSE unordered-aware inequality (movss/ucomiss plus the lahf/test/jp NaN
// guard the toolchain emits for !=), and a fourth detail argument joins the
// comparison. The name goes through the _strcmpi import (dllimport decl, rides
// 0xBBA518 per the parseListboxData precedent); the member at +0x44 reads as
// the compared name, size at +0x3C, detail at +0x40, bold byte at +0x460.

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

class FontCharsClass
{
public:
	bool Is_Font(const char *font_name, float point_size, bool is_bold, int extra);

private:
	char m_pad00[0x3C];
	float m_pointSize;        // +0x3C
	int m_extraDetail;        // +0x40
	const char *m_comparedName;  // +0x44
	char m_pad48[0x460 - 0x48];
	unsigned char m_boldFlag;  // +0x460
};

// ?Is_Font@FontCharsClass@@QAE_NPBDMMH@Z @0x00154840
bool FontCharsClass::Is_Font(const char *font_name, float point_size, bool is_bold, int extra)
{
	if (_strcmpi(m_comparedName, font_name) == 0) {
		if (point_size != m_pointSize)
			return false;
		if (extra != m_extraDetail)
			return false;
		if (is_bold == m_boldFlag)
			return true;
	}
	return false;
}
