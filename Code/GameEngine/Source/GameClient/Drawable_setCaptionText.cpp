// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Drawable::setCaptionText, native 0x00278064..0x00278190 (300B, RET4).
// Semantic guide: ZH GeneralsMD Drawable.cpp:4317 and BFME1
// cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 Drawable_setCaptionText.cpp.
// WB 0x00CB0420 independently retains the caption/filter/font branches;
// retail proves caption+344, manager slot38, UI+7A0/+7A4, and font float/bool ABI.
// Canonical BFME2 strings and existing named providers replace the donor's
// BFME1-only layout and ILT calls. Drawable.cpp still uses the ZH header/ABI,
// so this target-specific member follows the adjacent Drawable caption units.
//
// Inline UI accessors preserve the font argument evaluation order. The
// by-value filtering helper gives the sanitized copy its own parameter lifetime:
// VC7 reuses the dead incoming reference home, exactly as native does. It is
// an implementation helper, not a claim about an original retail method.
#include "ascii_string.h"
#include "unicode_string.h"

// Native compare is non-allocating and retains no EH state for getText().
template <> __declspec(nothrow) int StringBase<unsigned short>::compare(const StringBase<unsigned short> &) const;

class GameFont;
#include "../../Include/GameClient/DisplayString.h"
#include "../../Include/GameClient/DisplayStringManager.h"
extern DisplayStringManager *TheDisplayStringManager;
class LanguageFilter { public: void filterLine(UnicodeString &line); };
extern LanguageFilter *TheLanguageFilter;
#include "../../Include/Common/GlobalLanguageClass.h"
extern GlobalLanguage *TheGlobalLanguageData;
#include "../../Include/GameClient/FontLibrary.h"
extern FontLibrary *TheFontLibrary;
class InGameUI;
extern InGameUI *TheInGameUI;
struct CaptionUIFields
{
    char pad[0x7A0];
    int pointSize;
    int getPointSize() const { return pointSize; }
    bool bold;
    bool isBold() const { return bold; }
};
class Rva00274DB6AsciiField { public: AsciiString get() const; };
class DisplayString;
class Rva00271496
{
public:
	void rva00271496();
private:
	unsigned char m_pre[0x344]; // +0x00
	DisplayString *m_ptr; // +0x344
};
#include "../../Include/GameClient/Drawable.h"

static __forceinline void setSanitizedCaption(Drawable *draw, UnicodeString sanitized)
{
    TheLanguageFilter->filterLine(sanitized);
    if (!draw->m_captionDisplayString)
    {
        draw->m_captionDisplayString = TheDisplayStringManager->newDisplayString();
        GameFont *font = TheFontLibrary->getFont(&((Rva00274DB6AsciiField *)TheInGameUI)->get(),
            (float)TheGlobalLanguageData->adjustFontSize(((CaptionUIFields *)TheInGameUI)->getPointSize()), ((CaptionUIFields *)TheInGameUI)->isBold());
        draw->m_captionDisplayString->setFont(font);
        draw->m_captionDisplayString->setText(sanitized);
    }
    else
    {
        if (draw->m_captionDisplayString->getText().compare(sanitized) != 0)
            draw->m_captionDisplayString->setText(sanitized);
    }
}

void Drawable::setCaptionText(const UnicodeString &captionText)
{
    if (captionText.isEmpty())
    {
        ((Rva00271496 *)this)->rva00271496();
        return;
    }
    setSanitizedCaption(this, captionText);
}
