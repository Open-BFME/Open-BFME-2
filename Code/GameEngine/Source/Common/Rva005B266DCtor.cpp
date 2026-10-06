// cl: /MD
// ??0Rva005B266D@@QAE@H@Z @0x005B266D 34B: thiscall ctor for 28-byte value object.
// Evidence: leaf (no callees); caller 0x005B4695 constructs local at [ebp-0x2c] from esi then rep-movsd 7 dwords (28B);
// and [0x18],0 plus or ecx,-1 plus byte [0x14],0 give /O1 shape; ret-4 thiscall with one int arg.
struct Rva005B266D {
    int m_00;
    int m_04;
    int m_08;
    int m_0C;
    int m_10;
    unsigned char m_14;
    char m_pad15[3];
    int m_18;
    Rva005B266D(int arg);
};
Rva005B266D::Rva005B266D(int arg)
{
    m_00 = arg;
    m_04 = -1;
    m_08 = -1;
    m_0C = -1;
    m_10 = -1;
    m_14 = 0;
    m_18 = 0;
}
