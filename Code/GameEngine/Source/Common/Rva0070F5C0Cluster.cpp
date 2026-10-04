// cl: (none -- build.py base flags)
//
// ?rva0070F5C0@Rva0070F5C0@@QAEXPAVAptCIH@@H@Z @0x0070F5C0 184B. Iterates the
// indexed frame-action bucket m_table[idx] (8-byte {count, items} entries) and
// for each element whose first dword is 1, pushes an "AptFrameActions" debug
// record on the global AptActionInterpreter 0x00E182E0, runs the action via
// 0x007002C0 and unwinds the frame through 0x00706950. Evidence: source-assert
// file AptMovie.cpp shared by neighbours 0x0070E900/0x0070F040/0x0070F370; the
// {count,items} table and *q==1 gate match rowed Rva0070F680; arg1 is an AptCIH
// (0x006E0CB0 walker then 0x006CD650 animation getter); info string
// "AptFrameActions" at 0x008EF8C8 and record layout {this,0,name,0x200000} match
// the 0x00700090 debug-push contract.

class AptCIH;

class AptCIH
{
public:
    const AptCIH *rva006E0CB0() const;
};

class Rva006CD650
{
public:
    void *rva006CD650();
};

struct Rva00700090Info
{
    void *m_0;
    int m_4;
    const char *m_8;
    int m_c;
};

class Rva00700090
{
public:
    void *rva00700090(Rva00700090Info *info);
};

class Rva007002C0
{
public:
    void rva007002C0(int a, void *b, int c, void *d);
};

class Rva00706950
{
public:
    void rva00706950(void *a, Rva00700090Info *info);
};

extern char g_aptDateInterpreter;

struct Rva0070F5C0Entry
{
    int count;
    int **items;
};

class Rva0070F5C0
{
public:
    int m_0;
    Rva0070F5C0Entry *m_table;
    void rva0070F5C0(AptCIH *pCIH, int idx);
};

void Rva0070F5C0::rva0070F5C0(AptCIH *pCIH, int idx)
{
    for (int i = 0; i < m_table[idx].count; ++i) {
        int *q = m_table[idx].items[i];
        if (*q == 1) {
            Rva00700090Info info;
            info.m_0 = pCIH;
            info.m_4 = 0;
            info.m_8 = "AptFrameActions";
            info.m_c = 0x200000;
            void *r = ((Rva00700090 *)&g_aptDateInterpreter)->rva00700090(&info);
            void *p = pCIH ? ((Rva006CD650 *)pCIH->rva006E0CB0())->rva006CD650() : 0;
            ((Rva007002C0 *)&g_aptDateInterpreter)->rva007002C0(q[1], pCIH, -1, p);
            ((Rva00706950 *)&g_aptDateInterpreter)->rva00706950(r, &info);
        }
    }
}
