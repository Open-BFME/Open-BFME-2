// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005F9364@Rva005F9364@@QAEXABVUnicodeString@@@Z @ 0x005F9364 103B
// Honest address name: __thiscall Apt RegionName key setter, twin of 0x005FB770 PlayerName.
// Target evidence: 103B retail, EH_prolog, format string
// "APT:_level%u.%s_RegionName" at VA 0x008758D4, rowed AsciiString::format
// 0x00038150, pinned bfmeSetText 0x00225301, rowed releaseBuffer 0x00036410,
// manager at VA 0x009FE4CC, default %s at VA 0x007BAC1C, callers 0x005F960C 0x005FA7BD.
template <typename T> struct BfmeStringData
{
    int refCount;
    unsigned short length;
    unsigned short capacity;
    T text[1];
};
#include "ascii_string.h"
#include "unicode_string.h"
class BfmeAptWindowManager
{
public:
    void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
struct TeamNameHolder
{
    char m_pad[8];
    const char *m_name;
};
class Rva005F9364
{
public:
    void rva005F9364(const UnicodeString &regionName);
    void rva005F960C(const UnicodeString &regionName);
private:
    char m_pad[4];
    unsigned int m_level;
    TeamNameHolder *m_team;
    char m_pad0C[0x1C - 0x0C];
    UnicodeString m_cachedName;
};
void Rva005F9364::rva005F9364(const UnicodeString &regionName)
{
    AsciiString key;
    const char *teamName;
    if (m_team)
        teamName = (const char *)((char *)m_team + 8);
    else
        teamName = "";
    key.format("APT:_level%u.%s_RegionName", m_level, teamName);
    ((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, regionName, true);
}
void Rva005F9364::rva005F960C(const UnicodeString &regionName)
{
    if (regionName.compare(m_cachedName) != 0)
    {
        rva005F9364(regionName);
        m_cachedName.set(regionName);
    }
}
class Rva005F9775
{
public:
    void rva005F9775(const UnicodeString &regionName);
private:
    char m_pad[4];
    Rva005F9364 *m_member;
};
void Rva005F9775::rva005F9775(const UnicodeString &regionName)
{
    m_member->rva005F960C(regionName);
}
