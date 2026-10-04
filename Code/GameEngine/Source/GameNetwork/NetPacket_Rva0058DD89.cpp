// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0058DD89@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @ 0x0058DD89 (105B): static factory news 0x3C Rva004CEEE8 then reads 8 bytes into local order and calls setPlayerOrder. Evidence: sibling factories 0x0058DCEB and 0x0058E047 plus rowed Rva004CEEE8 0x004CEEE8 plus rowed setPlayerOrder 0x004D577B. Callers 0x00592756 and 0x00594089.
class NetCommandMsg;
class Rva004CEEE8
{
public:
    Rva004CEEE8();
private:
    char m_pad[0x3C];
};
class BFMENetRouterFallbackCommandMsg
{
public:
    void setPlayerOrder(const int *players);
};
void *__cdecl operator new(unsigned int size);
class NetPacket
{
public:
    static NetCommandMsg *rva0058DD89(unsigned char *data, int &readOffset);
};
NetCommandMsg *NetPacket::rva0058DD89(unsigned char *data, int &readOffset)
{
    Rva004CEEE8 *msg = new Rva004CEEE8();
    int order[8];
    for (int i = 0; i < 8; ++i, ++readOffset)
        order[i] = data[readOffset];
    ((BFMENetRouterFallbackCommandMsg *)msg)->setPlayerOrder(order);
    return (NetCommandMsg *)msg;
}
