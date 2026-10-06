// cl: /MD
// ?set@Rva001F3899Slot@@QAEXABURva001F3899Arg@@@Z @0x001F3899 40B.
// Copies arg+0/+4/+8 to +0xc8/+0xd8/+0xe8 and clears byte at +0x1a0. Callers at
// 0x000C70D8/0x000C7337/0x000C7CC3/0x001E225A among 24 sites. Honest Rva names;
// /O1 for the frameless copy plus byte-clear idiom.
struct Rva001F3899Arg {
    int m_00;
    int m_04;
    int m_08;
};
class Rva001F3899Slot {
public:
    void set(const Rva001F3899Arg &arg);
    char m_lead[0xc8];
    int m_c8;
    char m_pad1[0xd8 - 0xcc];
    int m_d8;
    char m_pad2[0xe8 - 0xdc];
    int m_e8;
    char m_pad3[0x1a0 - 0xec];
    unsigned char m_flag;
};
void Rva001F3899Slot::set(const Rva001F3899Arg &arg)
{
    m_c8 = arg.m_00;
    m_d8 = arg.m_04;
    m_e8 = arg.m_08;
    m_flag = 0;
}
