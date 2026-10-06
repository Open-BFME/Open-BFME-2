// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail RVA 0x00301534, 155 bytes (the reloc size 10 is stale).
// MapMetaData::bfme_getDescriptionFirstLine, the cached map.str description
// first-line accessor called by AptMapPreview::bfmeSetMapDescription.
// Ported from Open-BFME-1
// (Code/GameEngine/Source/GameClient/MapMetaData_getDescriptionFirstLine.cpp,
// retail 0x00452000, 220 bytes) with the manual newline loop replaced by
// StringBase::find: retail finds L'\n' (0x00035AB0, pinned), derives the length
// with a byte-difference shift ((int)found - (int)text) >> 1, then follows the
// BFME1 order exactly (substring, set, copy-out with member destruction).
// A signed / 2 emits cdq/sub/sar and runs 3 bytes long; >> 1 is exact.
// getDescription (0x003009CD, pinned under the BFME1 name) is the hidden-
// retptr UnicodeString loader this calls first, mirroring the BFME1 call
// graph. The sibling AptMapPreviewSetMapDescription.cpp TU stays frameless
// for its 63B body; this EH body lives here (GetFrameEntry/AddFrameEntry rule).
// The TU-local wrappers reproduce the canonical out-of-line shapes byte for
// byte (str 16B, UnicodeString copy 18B and (str,start,len) 26B, both 5B thunks)
// so they fold with the string_base/unicode_string rows.

typedef unsigned short WideChar;

#include "unicode_string.h"


class MapMetaData
{
public:
	UnicodeString getDescription();
	UnicodeString bfme_getDescriptionFirstLine();
};

UnicodeString MapMetaData::bfme_getDescriptionFirstLine()
{
	UnicodeString description = getDescription();
	const WideChar *found = description.find(10);
	if (found)
	{
		const WideChar *text = description.str();
		UnicodeString first(description, 0, ((int)found - (int)text) >> 1);
		description.set(first);
	}
	return description;
}
