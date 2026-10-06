// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?rva000535CC@Rva000535CC@@QAEXPAX@Z @0x000535CC 58B: thiscall gate plus float.
// Checks target+0x4C then this+0x6AC/+0x6B0 before setting target+0x45 and
// target+0x30 from table int at this+0x10+0x78 via cvtsi2ss. Prev/next are
// MilesAudioManager TUs with identical cl; offsets match its table at +0x10
// and pad bytes at +0x6AC/+0x6B0. Callers are 0x0005C23C x3.
struct Table78
{
    char m_pad[0x78];
    int m_v78;
};

struct ArgTarget
{
    char m_pad0[0x30];
    float m_f30;
    char m_pad34[0x45 - 0x34];
    unsigned char m_b45;
    char m_pad46[0x4C - 0x46];
    unsigned char m_b4C;
};

class Rva000535CC
{
public:
    void rva000535CC(void *p);
private:
    char m_pad0[0x10];
    Table78 *m_table;
    char m_pad14[0x6AC - 0x14];
    unsigned char m_b6AC;
    char m_pad6AD[0x6B0 - 0x6AD];
    int m_i6B0;
};

void Rva000535CC::rva000535CC(void *p)
{
    if ((*(ArgTarget **)p)->m_b4C == 0)
        return;
    if (m_b6AC != 0)
        return;
    (*(ArgTarget **)p)->m_b4C = 0;
    if (m_i6B0 != 0)
        return;
    (*(ArgTarget **)p)->m_b45 = 1;
    (*(ArgTarget **)p)->m_f30 = (float)m_table->m_v78;
}
