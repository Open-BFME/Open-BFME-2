// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0058DCEB@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DCEB 158B.
// Static NetCommandMsg factory reading three 4-byte fields from data+offset.
// Evidence: unlock lane plus sibling 0x0058E047 plus new-0x28 plus
// Rva004CEEC3 ctor plus triple memcpy-4 direct store to +0x1c +0x20 +0x24.
class NetCommandMsg;
class Rva004CEEC3
{
public:
    Rva004CEEC3();
private:
    char m_pad[0x1C];
public:
    unsigned int m_1c;
    unsigned int m_20;
    unsigned int m_24;
};
extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
void *__cdecl operator new(unsigned int size);
class NetPacket
{
public:
    static NetCommandMsg *rva0058DCEB(unsigned char *data, int &readOffset);
};
NetCommandMsg *NetPacket::rva0058DCEB(unsigned char *data, int &readOffset)
{
    Rva004CEEC3 *msg = new Rva004CEEC3();
    unsigned int v0 = 0;
    memcpy(&v0, data + readOffset, 4);
    readOffset += 4;
    msg->m_1c = v0;
    unsigned int v1 = 0;
    memcpy(&v1, data + readOffset, 4);
    readOffset += 4;
    msg->m_20 = v1;
    unsigned int v2 = 0;
    memcpy(&v2, data + readOffset, 4);
    readOffset += 4;
    msg->m_24 = v2;
    return (NetCommandMsg *)msg;
}
