// cl: /O1 /MD
// ?rva0057C236@Rva0057C236@@QAEXXZ @0x0057C236 54B
// UnloadContent Apt setter via rowed AptCall 0x00524EF4 with team+8 or empty string.
// Evidence: retail pushes TheRva00222A8BTarget plus [esi] plus team+8-or-empty plus UnloadContent,
// clears byte at +0x18; sibling Rva005FB6E2 same Apt plus team-plus-8 or empty pattern.
class Rva00222A8BTarget;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function);
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
struct Rva0057C236Team
{
    char m_pad[8];
    char m_name[1];
};
class Rva0057C236
{
public:
    void rva0057C236();
private:
    void *m_level;
    Rva0057C236Team *m_team;
    char m_pad08[0x18 - 8];
    bool m_flag;
};
void Rva0057C236::rva0057C236()
{
    if (!m_flag)
        return;
    const char *name;
    if (m_team)
        name = m_team->m_name;
    else
        name = g_Rva0107301CEmptyString;
    Rva00524EF4AptCall(TheRva00222A8BTarget, m_level, name, "UnloadContent");
    m_flag = false;
}
// ?rva0057C2CC@Rva0057C2CC@@QAEXXZ @0x0057C2CC 8B
// UnloadContent forwarder via member at +4 tail-jmp to rowed 0x0057C236.
// Evidence: retail mov ecx [ecx+4] jmp 0x0057C236; caller 0x005D1857 loads ecx from [esi+4] then calls.
class Rva0057C2CC
{
public:
    void rva0057C2CC();
private:
    char m_pad00[4];
    Rva0057C236 *m_p;
};
void Rva0057C2CC::rva0057C2CC()
{
    m_p->rva0057C236();
}
