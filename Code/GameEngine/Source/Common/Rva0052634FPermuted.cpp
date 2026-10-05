// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
//
// ??1Rva0052634F@@QAE@XZ, retail 0x0052634f, 210 bytes. Banked partial (score 0.93) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Evidence: pin ??1Rva0052634F@@QAE@XZ; callers 0x005264C0 (deleting dtor) and 0x00526F1E (clear); vtable 0x00867F0C at +0 reset to base 0x00867E3C; EH prolog via 0x00629188; conditional Rva003591F4Arg records at +0x1C8/+0x1D0 with flags +0x1D8/+0x1D9 via pinned 0x003591F4 on g_00E01E28 (same pattern as rowed 0x00525783 in AptStateCalls.cpp); unregister via rowed 0x002B7250 on +0x10; member dtors rowed 0x005242D7 (+0x38) 0x00524436 (+0x20) 0x0052413E (+0x14); AsciiString releaseBuffer at +0x0C.
#include "ascii_string.h"

struct Rva003591F4Arg
{
    Rva003591F4Arg(const Rva003591F4Arg &other) : m_id(other.m_id), m_flag(other.m_flag) {}
    int m_id;
    bool m_flag;
};

class Rva00E01E28Owner
{
public:
    void rva003591F4(Rva003591F4Arg arg);
};
extern Rva00E01E28Owner *g_00E01E28;

class CreateAHeroData;
class Rva002B7250
{
public:
    void rva002B7250(CreateAHeroData *v);
};

class Rva005242D7
{
public:
    ~Rva005242D7();
    char m_body[0x10];
};
class Rva00524436
{
public:
    ~Rva00524436();
    char m_body[0x18];
};
class Rva0052413E
{
public:
    ~Rva0052413E();
    char m_body[0x0C];
};

class Rva0052634F_Base
{
public:
    virtual void v00();
    ~Rva0052634F_Base() {}
};

class Rva0052634F : public Rva0052634F_Base
{
public:
    ~Rva0052634F();
private:
    char m_pad04[0x08];
    AsciiString m_name0C;
    Rva002B7250 *m_ptr10;
    Rva0052413E m_m14;
    Rva00524436 m_m20;
    Rva005242D7 m_m38;
    char m_pad48[0x180];
    Rva003591F4Arg m_recC8;
    Rva003591F4Arg m_recD0;
    bool m_hasC8;
    bool m_hasD0;
};

// ?releaseBuffer@?$StringBase@D@@AAEXXZ present-unmatched
Rva0052634F::~Rva0052634F()
{
    if (m_hasC8)
    {
        if (g_00E01E28)
            g_00E01E28->rva003591F4(m_recC8);
    }
    if (m_hasD0)
    {
        if (g_00E01E28)
            g_00E01E28->rva003591F4(m_recD0);
    }
    m_ptr10->rva002B7250((CreateAHeroData *)this);
}
