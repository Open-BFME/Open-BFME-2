// cl: /Oy- /MD
// ?rva005F61E4@Rva005F61E4@@QAEXXZ @ 0x005F61E4 60B chain via rowed AptCall 0x005FB5E6.
// Flag clearer with _hide literal, flag byte at +0x37, team +8 level +4.
// Evidence: EBP frame, rowed AptCall, literals _hide and SetLeaderRankProgressBarState,
// empty g_Rva0107301CEmptyString, manager TheRva00222A8BTarget, caller jmp 0x005F6309.
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);
struct Rva005F61E4Team
{
    char m_pad[8];
    const char *m_name;
};
class Rva005F61E4
{
public:
    void rva005F61E4();
private:
    char m_pad0[4];
    unsigned int m_level;
    Rva005F61E4Team *m_team;
    char m_pad0C[0x37 - 0x0C];
    unsigned char m_flag;
};
void Rva005F61E4::rva005F61E4()
{
    if (!m_flag)
        return;
    const char *team;
    if (m_team)
        team = (const char *)((char *)m_team + 8);
    else
        team = g_Rva0107301CEmptyString;
    Rva005FB5E6AptCall(TheRva00222A8BTarget, (void *)m_level, team, "SetLeaderRankProgressBarState", "_hide");
    m_flag = 0;
}
