// cl: /MD
// ?set@Rva001F38C1Slot@@QAEXABURva001F38C1Arg@@@Z @0x001F38C1 109B.
// Copies arg+0x00..+0x2C (12 dwords) to +0xBC..+0xE8 and clears byte at
// +0x1A0. Same family as Rva001F3899Slot::set on this page (bulk copy plus
// +0x1A0 clear); callers at 0x000B76CF/0x000B7758/0x000C70BC/0x001E2067/
// 0x001FAC99/0x001FAFC7. Honest Rva names; /O1 for the frameless copy plus
// byte-clear idiom.
struct Rva001F38C1Arg {
    int m_00;
    int m_04;
    int m_08;
    int m_0C;
    int m_10;
    int m_14;
    int m_18;
    int m_1C;
    int m_20;
    int m_24;
    int m_28;
    int m_2C;
};
class Rva001F38C1Slot {
public:
    void set(const Rva001F38C1Arg &arg);
    char m_lead[0xbc];
    int m_bc;
    int m_c0;
    int m_c4;
    int m_c8;
    int m_cc;
    int m_d0;
    int m_d4;
    int m_d8;
    int m_dc;
    int m_e0;
    int m_e4;
    int m_e8;
    char m_pad[0x1a0 - 0xec];
    unsigned char m_flag;
};
void Rva001F38C1Slot::set(const Rva001F38C1Arg &arg)
{
    m_bc = arg.m_00;
    m_c0 = arg.m_04;
    m_c4 = arg.m_08;
    m_c8 = arg.m_0C;
    int *d = &m_cc;
    d[0] = arg.m_10;
    d[1] = arg.m_14;
    d[2] = arg.m_18;
    d[3] = arg.m_1C;
    d = &m_dc;
    d[0] = arg.m_20;
    d[1] = arg.m_24;
    d[2] = arg.m_28;
    d[3] = arg.m_2C;
    m_flag = 0;
}
