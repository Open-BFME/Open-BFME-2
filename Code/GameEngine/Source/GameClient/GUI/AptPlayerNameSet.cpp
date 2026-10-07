// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?SetPlayerNameString@Impl@DynamicAutoResolvePlayerPanelMovieClip@StrategicHUD@@QAEXABVUnicodeString@@@Z @ 0x005FB770 103B
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
namespace StrategicHUD {
class DynamicAutoResolvePlayerPanelMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl
{
public:
    void SetPlayerNameString(const UnicodeString &playerName);
    void ShowEliminated();
    void ShowSurvived();
    void rva005FBBC0(const UnicodeString &playerName);
    void SetPlayerUnitCountString(const UnicodeString &value);
    void rva005FB903(int count);
    void rva005FB872(int color);
    void PlayHitAnim(float v);
    void PlayReinforceAnim(float v);
    void SetPlayerHealth(float v);
private:
    char m_pad[4];
    unsigned int m_level;
    TeamNameHolder *m_team;
    char m_pad0C[0x28 - 0x0C];
    UnicodeString m_cachedName;
    char m_pad2C[0x38 - 0x2C];
    int m_cachedCount;
};
void StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl::SetPlayerNameString(const UnicodeString &playerName)
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
void StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl::rva005FBBC0(const UnicodeString &playerName)
{
    if (playerName.compare(m_cachedName) != 0)
    {
        SetPlayerNameString(playerName);
        m_cachedName.set(playerName);
    }
}
void StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl::SetPlayerUnitCountString(const UnicodeString &value)
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
void StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl::rva005FB903(int count)
{
    if (count == m_cachedCount)
        return;
    UnicodeString tmp;
    if (count >= 0)
        tmp.format(L"%d", count);
    SetPlayerUnitCountString(tmp);
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
    StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl *m_member;
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
    m_member->PlayHitAnim(v);
}
void Rva005FBB68::rva005FBB83(float v)
{
    m_member->PlayReinforceAnim(v);
}
void Rva005FBB68::rva005FBB55(float v)
{
    m_member->SetPlayerHealth(v);
}

// ?rva005FB83E@Rva005FB83E@@QAEXPBVImage@@@Z @0x005FB83E 8B unlock tail-jmp forwarder to rowed _PlayerIcon 0x005FB666
// Evidence: prev 0x005FB7D7 ends here; mov ecx,[ecx+4] plus jmp callee; same shape as Rva005FBB68 forwarders above.
class Image;
class Rva005FB666
{
public:
    void rva005FB666(const Image *image);
};
class Rva005FB83E
{
public:
    void rva005FB83E(const Image *image);
private:
    char m_pad[4];
    Rva005FB666 *m_member;
};
void Rva005FB83E::rva005FB83E(const Image *image)
{
    return m_member->rva005FB666(image);
}

// ?rva005FB846@Rva005FB846@@QAEXXZ @0x005FB846 8B unlock tail-jmp forwarder to rowed 0x005FB6E2
// Evidence: mov ecx,[ecx+4] plus jmp callee; same shape as Rva005FBB68 forwarders above.
class Rva005FB846
{
public:
    void rva005FB846();
private:
    char m_pad[4];
    StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl *m_member;
};
void Rva005FB846::rva005FB846()
{
    return m_member->ShowEliminated();
}

// ?rva005FB84E@Rva005FB84E@@QAEXXZ @0x005FB84E 8B unlock tail-jmp forwarder to rowed 0x005FB729
// Evidence: mov ecx,[ecx+4] plus jmp callee; same shape as Rva005FBB68 forwarders above.
class Rva005FB84E
{
public:
    void rva005FB84E();
private:
    char m_pad[4];
    StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl *m_member;
};
void Rva005FB84E::rva005FB84E()
{
    return m_member->ShowSurvived();
}

// ?rva005FBBFC@Rva005FBBFC@@QAEXABVUnicodeString@@@Z @0x005FBBFC 8B unlock tail-jmp forwarder to rva005FBBC0.
// Evidence: target instruction loads the member at +4 and jumps to the rowed Impl method; signature follows that method.
class Rva005FBBFC
{
public:
    void rva005FBBFC(const UnicodeString &value);
private:
    char m_pad[4];
    StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl *m_member;
};
void Rva005FBBFC::rva005FBBFC(const UnicodeString &value)
{
    return m_member->rva005FBBC0(value);
}
