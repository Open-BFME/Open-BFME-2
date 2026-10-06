// cl: /DNDEBUG /MD
// ?rva0052DA1C@Rva0052DA1C@@QAE_NH@Z, retail 0x0052DA1C, 71 bytes.
// Low-nibble type setter with owner guard at +0x0/+0x28.
// Evidence: unlock lane unblocking 6 callers; same /O1 shape as Common neighbour.
class Rva0052DA1C {
    struct Aux {
        int _pad[10];
        int m_28;
    };
    Aux *m_0;
    int _pad4[2];
    unsigned int m_c;
public:
    bool rva0052DA1C(int arg);
};
bool Rva0052DA1C::rva0052DA1C(int arg)
{
    if (m_0 && m_0->m_28 != 0) {
        if ((m_c & 0xF) == 4)
            return false;
        m_c = (m_c & ~0xB) | 4;
        return true;
    }
    if ((m_c & 0xF) == arg)
        return false;
    m_c ^= ((m_c ^ arg) & 0xF);
    return true;
}
