// cl: /O1 /DNDEBUG /MD /EHsc
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

template <typename T> class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;
private:
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    ~StringBase() { releaseBuffer(); }
    void releaseBuffer();
    BfmeStringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
    UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
    ~UnicodeString() {}
};

class MapMetaData
{
public:
    UnicodeString bfme_getDisplayName(bool includePlayerCount);
};

class BfmeAptWindowManager
{
public:
    void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
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
