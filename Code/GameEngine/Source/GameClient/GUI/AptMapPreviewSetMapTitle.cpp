// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail RVA 0x0057C8D1, 205 bytes. AptMapPreview is anchored by its
// registered callback names; member and APT manager names describe recovered
// behavior because their original spellings are unknown.
// Caller 0x0057E058 supplies MapMetaData with filename at +0x50 and
// player count at +0x20. The bool getter includes the player count in the title.

template <typename T> struct BfmeStringData
{
    int refCount;
    unsigned short length;
    unsigned short capacity;
    T text[1];
};

#include "ascii_string.h"


#include "unicode_string.h"

class MapMetaData
{
public:
    UnicodeString bfme_getDisplayName(bool includePlayerCount);
};

class BfmeAptWindowManager
{
public:
    void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
    void rva00225375(const AsciiString &, const AsciiString &, bool);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class AptMapPreview
{
public:
    void bfmeSetMapTitle(MapMetaData *map);
};

void AptMapPreview::bfmeSetMapTitle(MapMetaData *map)
{
    if (g_bfmeAptWindowManager)
    {
        if (map)
        {
            AsciiString key("APT:MapTitle");
            g_bfmeAptWindowManager->bfmeSetText(key, map->bfme_getDisplayName(true), false);
        }
        else
            g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:MapTitle"), UnicodeString(L" "), false);
    }
}

// ?rva00225375@BfmeAptWindowManager@@QAEXABVAsciiString@@0_N@Z @0x00225375 77B
// translate second Ascii to Unicode local then bfmeSetText with bool.
// Evidence: calls rowed translate 0x006CB6A0 plus pinned bfmeSetText 0x00225301
// plus rowed releaseBuffer 0x00036E70 with same this; nine callers.
void BfmeAptWindowManager::rva00225375(const AsciiString &key, const AsciiString &value, bool flag)
{
    UnicodeString translated;
    translated.translate(value);
    bfmeSetText(key, translated, flag);
}
