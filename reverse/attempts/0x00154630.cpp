// ?Create_GDI_Font@FontCharsClass@@AAEXPBD@Z
// partial score=0.9 date=2026-09-21
// ?Create_GDI_Font@FontCharsClass@@AAEXPBD@Z
// cl: /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/shims/sweep
// stlport
#include <string.h>
#include "windows.h"

extern "C" __declspec(dllimport) double __cdecl floor(double);

// Cached screen-DC provider: retail reads the HDC from +0x10 of the structure
// at 0x00DF6F24 (no GetDC/ReleaseDC pair, unlike the ZH DIBSection path).
struct FontScreenDCGlobals
{
	unsigned char reserved[0x10];
	HDC screen_dc;
};
extern FontScreenDCGlobals *FontScreenDCGlobalsPtr;

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
	HFONT old_font = (HFONT)::SelectObject(screen_dc, GDIFont);

	TEXTMETRIC text_metric = { 0 };
	::GetTextMetricsA(FontScreenDCGlobalsPtr->screen_dc, &text_metric);

	charHeightDiv = (extra_setting + text_metric.tmExternalLeading + text_metric.tmHeight - 1) / extra_setting;
	charExtLeadDiv = text_metric.tmExternalLeading / extra_setting;
	charOverhangDiv = (extra_setting + text_metric.tmOverhang - 1) / extra_setting;

	::SelectObject(screen_dc, old_font);
}
