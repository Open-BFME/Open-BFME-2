// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail RVA 0x00300C7E, 142 bytes (the reloc size 10 is stale).
// MapMetaData::bfme_getDisplayName, the player-count-suffixed display-name
// getter called by AptMapPreview::UpdateMapTitle. The base name comes from
// the sibling bfme_getBaseDisplayName TU; when requested and the count reaches
// two, a " (%d)" suffix is formatted (UnicodeString::format is a __cdecl
// member, so this rides the stack: push count, push format, push this) and
// concatenated. Layout shared with that TU: label +0x00, count +0x20,
// file name +0x50, cached base name +0xF8. Every out-of-line copy this TU
// emits matches its string_base/unicode_string row and folds.

typedef unsigned short WideChar;

#include "ascii_string.h"

#include "unicode_string.h"


class MapMetaData
{
public:
	UnicodeString bfme_getBaseDisplayName();
	UnicodeString bfme_getDisplayName(bool includePlayerCount);

private:
	UnicodeString m_displayNameLabel;
	char m_pad04[0x20 - 0x04];
	int m_playerCount;
	char m_pad24[0x50 - 0x24];
	AsciiString m_fileName;
	char m_pad54[0xF8 - 0x54];
	UnicodeString m_cachedBaseDisplayName;
};

UnicodeString MapMetaData::bfme_getDisplayName(bool includePlayerCount)
{
	UnicodeString name = bfme_getBaseDisplayName();
	if (includePlayerCount && m_playerCount >= 2)
	{
		UnicodeString suffix;
		suffix.format(L" (%d)", m_playerCount);
		((StringBase<WideChar> &)name).concat(suffix);
	}
	return name;
}
