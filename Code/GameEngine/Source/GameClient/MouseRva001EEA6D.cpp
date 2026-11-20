// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva001EEA6D@Mouse@@QAEXVUnicodeString@@HPBURGBColor@@M@Z @0x001EEA6D 360B
// Mouse tooltip setter with house-color adjust. Same color math as ZH/BFME1
// Mouse::setCursorTooltip over m_tooltipColorText at +0x128C and
// m_tooltipColorBackground at +0x12BC into m_tooltipTextColor at +0x4FDC and
// m_tooltipBackColor at +0x4FEC with delay at +0x4FCC and string at +0x12FC.
// Flags at +0x12E0/+0x12E1/+0x12E2 are useText/useBack/adjust. BFME2 drops
// the Display width and isEmpty logic so width is unused. Callers at
// 0x1EB5FC 0x2125C5 0x2227C0 and 8 newly ready bodies.
#include <string.h>
// Keep the default-color block copies inline.
#pragma intrinsic(memcpy)

#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/RGBColor.h"
#include "../../Include/Common/RGBAColorInt.h"
#include "../../Include/GameClient/Mouse.h"

// The registered Mouse layout keeps the tooltip storage in byte spans.
template <class Field>
static __forceinline Field &tooltipField(unsigned char *address)
{
	return *reinterpret_cast<Field *>(address);
}

void Mouse::rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width)
{
	(void)width;
	tooltipField<int>(field4FA8 + 0x24) = delay;
	UnicodeString *dst = &tooltipField<UnicodeString>(field12E8 + 0x14);
	const UnicodeString *src = &tooltip;
	dst->set(*src);
	if (color) {
		if (field12E0[0]) {
			if (field12E0[2]) {
				tooltipField<RGBAColorInt>(field4FA8 + 0x34).red = (int)((color->red + 1.0f) * 255.0f / 2.0f);
				tooltipField<RGBAColorInt>(field4FA8 + 0x34).green = (int)((color->green + 1.0f) * 255.0f / 2.0f);
				tooltipField<RGBAColorInt>(field4FA8 + 0x34).blue = (int)((color->blue + 1.0f) * 255.0f / 2.0f);
			} else {
				tooltipField<RGBAColorInt>(field4FA8 + 0x34).red = (int)(color->red * 255.0f);
				tooltipField<RGBAColorInt>(field4FA8 + 0x34).green = (int)(color->green * 255.0f);
				tooltipField<RGBAColorInt>(field4FA8 + 0x34).blue = (int)(color->blue * 255.0f);
			}
			tooltipField<RGBAColorInt>(field4FA8 + 0x34).alpha = tooltipField<const RGBAColorInt>(field0C + 0x1280).alpha;
		}
		if (field12E0[1]) {
			if (field12E0[2]) {
				tooltipField<RGBAColorInt>(field4FA8 + 0x44).red = (int)(color->red * 255.0f * 0.5f);
				tooltipField<RGBAColorInt>(field4FA8 + 0x44).green = (int)(color->green * 255.0f * 0.5f);
				tooltipField<RGBAColorInt>(field4FA8 + 0x44).blue = (int)(color->blue * 255.0f * 0.5f);
			} else {
				tooltipField<RGBAColorInt>(field4FA8 + 0x44).red = (int)(color->red * 255.0f);
				tooltipField<RGBAColorInt>(field4FA8 + 0x44).green = (int)(color->green * 255.0f);
				tooltipField<RGBAColorInt>(field4FA8 + 0x44).blue = (int)(color->blue * 255.0f);
			}
			tooltipField<RGBAColorInt>(field4FA8 + 0x44).alpha = tooltipField<const RGBAColorInt>(field0C + 0x12B0).alpha;
		}
	} else {
		memcpy(&tooltipField<RGBAColorInt>(field4FA8 + 0x34), &tooltipField<const RGBAColorInt>(field0C + 0x1280), sizeof(RGBAColorInt));
		memcpy(&tooltipField<RGBAColorInt>(field4FA8 + 0x44), &tooltipField<const RGBAColorInt>(field0C + 0x12B0), sizeof(RGBAColorInt));
	}
}
