// cl: /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc
// ?getDisplayName@PlayerTemplate@@QBE?AVUnicodeString@@XZ @0x00449B8F (27B):
// PlayerTemplate::getDisplayName, by-value forward of the display-name member
// at +0x14. Retail calls the wide StringBase copy-ctor at 0x37050 directly
// (not the 18B UnicodeString copy at 0x6618): the TU-local UnicodeString
// copy-ctor forwards to StringBase inline (unicode_string.cpp model), so the
// return inlines to the single base call. Shard TU: GameSlotApparent.cpp
// calls this out-of-line and is EDI-sensitive, so the definition lives here
// (same-class-in-2-TUs precedent; cf. PlayerTemplateGetName.cpp).

typedef unsigned short wchar_t;

class UnicodeString;

#include "unicode_string.h"


class PlayerTemplate
{
public:
	UnicodeString getDisplayName() const;

private:
	char m_pad[0x14];
	UnicodeString m_displayName;
};

// ?getDisplayName@PlayerTemplate@@QBE?AVUnicodeString@@XZ
UnicodeString PlayerTemplate::getDisplayName() const
{
	return m_displayName;
}
