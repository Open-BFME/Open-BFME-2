// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0058E57B@NetPacket@@QAEHXZ @0x0058E57B 57B.
// NetPacket thiscall reading m_packetLen at plus-0x1E0.
// Evidence: next NetPacket_init layout plus-0x1E0 len; idiv-8 plus remainder
// inc is ceil len-div-8; nested 8-step loops with break on len.
class NetPacket
{
public:
    int rva0058E57B();
private:
    void *m_vptr;
    unsigned char m_packet[0x1DC];
    int m_packetLen;
};
int NetPacket::rva0058E57B()
{
    int n = m_packetLen / 8;
    if (m_packetLen % 8 != 0) {
        ++n;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i * 8 + j >= m_packetLen) {
                break;
            }
        }
    }
    return n;
}
