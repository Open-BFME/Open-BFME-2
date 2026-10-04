// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva005FB770@Rva005FB770@@QAEXABVUnicodeString@@@Z @ 0x005FB770 103B
// Honest address name: __thiscall Apt PlayerName key setter beside AptMapPreview.
// Target evidence: 103B retail, EH_prolog, format string
// "APT:_level%u.%s_PlayerName" at VA 0x879F60, rowed AsciiString::format
// 0x38150, pinned bfmeSetText 0x225301, rowed releaseBuffer 0x36410,
// manager at VA 0xDFE4CC, default %s at VA 0xBBAC1C, 2 callers.
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
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
struct TeamNameHolder
{
    char m_pad[8];
    const char *m_name;
};
class Rva005FB770
{
public:
    void rva005FB770(const UnicodeString &playerName);
    void rva005FBBC0(const UnicodeString &playerName);
    void rva005FB7D7(const UnicodeString &value);
    void rva005FB903(int count);
    void rva005FB872(int color);
    void rva005FB961(float v);
    void rva005FB9C6(float v);
    void rva005FB8B4(float v);
private:
    char m_pad[4];
    unsigned int m_level;
    TeamNameHolder *m_team;
    char m_pad0C[0x28 - 0x0C];
    UnicodeString m_cachedName;
    char m_pad2C[0x38 - 0x2C];
    int m_cachedCount;
};
void Rva005FB770::rva005FB770(const UnicodeString &playerName)
{
    AsciiString key;
    const char *teamName;
    if (m_team)
        teamName = (const char *)((char *)m_team + 8);
    else
        teamName = "";
    key.format("APT:_level%u.%s_PlayerName", m_level, teamName);
    g_bfmeAptWindowManager->bfmeSetText(key, playerName, true);
}
void Rva005FB770::rva005FBBC0(const UnicodeString &playerName)
{
    if (playerName.compare(m_cachedName) != 0)
    {
        rva005FB770(playerName);
        m_cachedName.set(playerName);
    }
}
void Rva005FB770::rva005FB7D7(const UnicodeString &value)
{
    AsciiString key;
    const char *teamName;
    if (m_team)
        teamName = (const char *)((char *)m_team + 8);
    else
        teamName = "";
    key.format("APT:_level%u.%s_UnitCount", m_level, teamName);
    g_bfmeAptWindowManager->bfmeSetText(key, value, true);
}
void Rva005FB770::rva005FB903(int count)
{
    if (count == m_cachedCount)
        return;
    UnicodeString tmp;
    if (count >= 0)
        tmp.format(L"%d", count);
    rva005FB7D7(tmp);
    m_cachedCount = count;
}
class Rva005FBB68
{
public:
    void rva005FBB4D(int color);
    void rva005FBB68(int count);
    void rva005FBB70(float v);
    void rva005FBB83(float v);
    void rva005FBB55(float v);
private:
    char m_pad[4];
    Rva005FB770 *m_member;
};
void Rva005FBB68::rva005FBB4D(int color)
{
    return m_member->rva005FB872(color);
}
void Rva005FBB68::rva005FBB68(int count)
{
    return m_member->rva005FB903(count);
}
void Rva005FBB68::rva005FBB70(float v)
{
    m_member->rva005FB961(v);
}
void Rva005FBB68::rva005FBB83(float v)
{
    m_member->rva005FB9C6(v);
}
void Rva005FBB68::rva005FBB55(float v)
{
    m_member->rva005FB8B4(v);
}
