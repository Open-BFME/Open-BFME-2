// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?rva001EEA6D@Mouse@@QAEXVUnicodeString@@HPBURGBColor@@M@Z @0x001EEA6D 360B
// Mouse tooltip setter with house-color adjust. Same color math as ZH/BFME1
// Mouse::setCursorTooltip over m_tooltipColorText at +0x128C and
// m_tooltipColorBackground at +0x12BC into m_tooltipTextColor at +0x4FDC and
// m_tooltipBackColor at +0x4FEC with delay at +0x4FCC and string at +0x12FC.
// Flags at +0x12E0/+0x12E1/+0x12E2 are useText/useBack/adjust. BFME2 drops
// the Display width and isEmpty logic so width is unused. Callers at
// 0x1EB5FC 0x2125C5 0x2227C0 and 8 newly ready bodies.
#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/RGBColor.h"
struct RGBAColorInt
{
public:
	unsigned int red; // +0x00
	unsigned int green; // +0x04
	unsigned int blue; // +0x08
	unsigned int alpha; // +0x0C
};
class Mouse {
	char _pad0[0x128C];
	RGBAColorInt m_128C;
	char _pad1[0x12BC - (0x128C + 16)];
	RGBAColorInt m_12BC;
	char _pad2[0x12E0 - (0x12BC + 16)];
	unsigned char m_12E0;
	unsigned char m_12E1;
	unsigned char m_12E2;
	char _pad3[0x12FC - (0x12E0 + 3)];
	UnicodeString m_12FC;
	char _pad4[0x4FCC - (0x12FC + 4)];
	int m_4FCC;
	char _pad5[0x4FDC - (0x4FCC + 4)];
	RGBAColorInt m_4FDC;
	RGBAColorInt m_4FEC;
public:
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);
};
void Mouse::rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width)
{
	(void)width;
	m_4FCC = delay;
	UnicodeString *dst = &m_12FC;
	const UnicodeString *src = &tooltip;
	dst->set(*src);
	if (color) {
		if (m_12E0) {
			if (m_12E2) {
				m_4FDC.red = (int)((color->red + 1.0f) * 255.0f / 2.0f);
				m_4FDC.green = (int)((color->green + 1.0f) * 255.0f / 2.0f);
				m_4FDC.blue = (int)((color->blue + 1.0f) * 255.0f / 2.0f);
			} else {
				m_4FDC.red = (int)(color->red * 255.0f);
				m_4FDC.green = (int)(color->green * 255.0f);
				m_4FDC.blue = (int)(color->blue * 255.0f);
			}
			m_4FDC.alpha = m_128C.alpha;
		}
		if (m_12E1) {
			if (m_12E2) {
				m_4FEC.red = (int)(color->red * 255.0f * 0.5f);
				m_4FEC.green = (int)(color->green * 255.0f * 0.5f);
				m_4FEC.blue = (int)(color->blue * 255.0f * 0.5f);
			} else {
				m_4FEC.red = (int)(color->red * 255.0f);
				m_4FEC.green = (int)(color->green * 255.0f);
				m_4FEC.blue = (int)(color->blue * 255.0f);
			}
			m_4FEC.alpha = m_12BC.alpha;
		}
	} else {
		m_4FDC = m_128C;
		m_4FEC = m_12BC;
	}
}
