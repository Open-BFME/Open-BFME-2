// cl: /O1 /Oy- /G7 /DNDEBUG /MD /EHsc
// Version-block lookup over the 0x18-byte records. The search helper
// writes the found record pointer into a local output slot.
extern "C" void *__cdecl memset(void *, int, unsigned);
#pragma intrinsic(memset)

struct VersionBlockEntry
{
    const char *m_key;
    char m_padAfterKey[8];
    const char *m_value;
    char m_padTail[8];
};

class VersionBlockParser
{
public:
    const char *lookupVersionValue(const char *key, const char *defaultValue);
    static const void *findEntry(const void *found, const void *first, const void *last, const char *const *key, const void *match);
private:
    int m_header;
    VersionBlockEntry *m_first;
    VersionBlockEntry *m_last;
};

const char *VersionBlockParser::lookupVersionValue(const char *key, const char *defaultValue)
{
    VersionBlockEntry *found;
    volatile char match;
    memset((void *)&match, 0, 1);
    findEntry(&found, m_first, m_last, &key, (const void *)(unsigned)*(volatile unsigned *)&match);
    if (found == (VersionBlockEntry *)(unsigned)*(volatile unsigned *)&match)
        return defaultValue;
    return found->m_value;
}
