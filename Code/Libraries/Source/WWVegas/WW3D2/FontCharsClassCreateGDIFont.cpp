// cl: /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/shims/sweep
// stlport
// Retail 0x00154630, 488 bytes: FontCharsClass::Create_GDI_Font(font_name), a
// GDI-font variant of Zero Hour's FontCharsClass::Create_GDI_Font for BFME 2:
// "Generals" maps to Arial with a 0.4 width scale, PixelOverlap is the clamped
// 0.125 of the point size, CreateFontA builds the font, and the font metrics
// (read from the cached screen DC at 0x00DF6F24 +0x10, no GetDC pair) fill the
// +0x2C/+0x30/+0x34 divisors.
// Frame evidence: retail keeps the previously selected font in its own stack
// slot (it does not reuse the dead font_name argument home as a plain local
// would). A small struct that remembers the DC and the old font, with a
// restore() member, reproduces that slot; a bare HFONT local, a volatile local
// and declaration reordering do not. The struct name is ours; retail names are
// not recovered.
#include <math.h>
#include <string.h>
#include "windows.h"

// (CRT prototype from the standard header)

// Cached screen-DC provider: retail reads the HDC from +0x10 of the structure
// at 0x00DF6F24 (no GetDC/ReleaseDC pair, unlike the ZH DIBSection path).
struct FontScreenDCGlobals
{
	unsigned char reserved[0x10];
	HDC screen_dc;
};
extern FontScreenDCGlobals *FontScreenDCGlobalsPtr;

struct Rva00154630SelectFont
{
	HDC dc;
	HFONT old;
	Rva00154630SelectFont(HDC d, HFONT f) : dc(d) { old = (HFONT)::SelectObject(d, f); }
	void restore() { ::SelectObject(dc, old); }
};
class FontCharsClass
{
	void Create_GDI_Font(const char *font_name);

private:
	unsigned char pad_to_metrics[0x2C];
	int charHeightDiv;		// +0x2C: (extra + tmExtLead + tmHeight - 1) / extra
	int charExtLeadDiv;		// +0x30: tmExtLead / extra
	int charOverhangDiv;		// +0x34: (extra + tmOverhang - 1) / extra
	int PixelOverlap;		// +0x38: clamp((int)floor(point_size*0.125+0.5),0,4)
	float point_size;		// +0x3C
	int extra_setting;		// +0x40
	unsigned char pad_to_font[4];	// +0x44: gdi_font_name lives here in the sibling TU
	HFONT GDIFont;			// +0x48
	unsigned char pad_to_bold[0x414];
	bool is_bold;			// +0x460
};

// ?Create_GDI_Font@FontCharsClass@@AAEXPBD@Z
void FontCharsClass::Create_GDI_Font(const char *font_name)
{
	bool doingGenerals = false;
	if (strcmp(font_name, "Generals") == 0) {
		font_name = "Arial";
		doingGenerals = true;
	}

	float height_base = point_size;
	float width_scale = 0.0f;
	if (doingGenerals) {
		width_scale = height_base * 0.4f;
	}

	PixelOverlap = (int)floor(height_base * 0.125f + 0.5f);
	if (PixelOverlap < 0) {
		PixelOverlap = 0;
	}
	if (PixelOverlap > 4) {
		PixelOverlap = 4;
	}

	int weight = is_bold ? FW_BOLD : FW_NORMAL;

	float width_product = (float)extra_setting * width_scale + 0.5f;
	float height_product = (float)extra_setting * height_base + 0.5f;
	float font_height = (float)floor(height_product);

	GDIFont = ::CreateFontA((int)-font_height, (int)floor(width_product),
		0, 0, weight, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, 0, font_name);

	HDC screen_dc = FontScreenDCGlobalsPtr->screen_dc;
	Rva00154630SelectFont sel(screen_dc, GDIFont);

	TEXTMETRIC text_metric = { 0 };
	::GetTextMetricsA(FontScreenDCGlobalsPtr->screen_dc, &text_metric);

	charHeightDiv = (extra_setting + text_metric.tmExternalLeading + text_metric.tmHeight - 1) / extra_setting;
	charExtLeadDiv = text_metric.tmExternalLeading / extra_setting;
	charOverhangDiv = (extra_setting + text_metric.tmOverhang - 1) / extra_setting;

	sel.restore();
}
