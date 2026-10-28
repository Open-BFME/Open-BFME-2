// cl: /MD
// ?getMasterPlayer@AIGameTeam@@QAEPAXXZ @0x004E93E8 49B search ptr array +0xc +0x10 for [elem+0x5c]==1 or global flag caller 0x004E9710
struct Elem004E93E8 { char _pad[0x5c]; int m_playerType; };
struct Glob004E93E8 { char _pad[0x860]; unsigned char m_forceAI; };
// TheSkirmishAIManager is owned as a Rva002A8F24 (Rva005EEA20Find.cpp); this
// unit reads it through its own view.
class Rva002A8F24;
extern Rva002A8F24 *TheSkirmishAIManager;
// The player array is the pointer vector at +0xC; read its begin/end words.
struct AIGameTeamPlayersView
{
    char _pad0[0xc];
    Elem004E93E8 **m_begin;
    Elem004E93E8 **m_end;
};
class AIGameTeam
{
public:
    void *getMasterPlayer();

private:
    char m_pad[0x28];
};

void *AIGameTeam::getMasterPlayer()
{
    void *found = 0;
    const AIGameTeamPlayersView *players = (const AIGameTeamPlayersView *)this;
    Elem004E93E8 **playerIt = players->m_begin;
    Elem004E93E8 **playersEnd = players->m_end;
    for (;;) {
        if (playerIt == playersEnd)
            break;
        Elem004E93E8 *cur = *playerIt;
        if (cur->m_playerType == 1 || ((Glob004E93E8 *)TheSkirmishAIManager)->m_forceAI != 0)
            found = cur;
        ++playerIt;
        if (found == 0)
            continue;
        break;
    }
    return found;
}
