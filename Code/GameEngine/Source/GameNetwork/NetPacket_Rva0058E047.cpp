// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0058E047@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E047 105B.
// Static NetCommandMsg factory reading 1-byte relay flag from data+offset.
// Evidence: unlock lane plus sibling 0x0058E511 plus new-0x20 plus
// Rva004D582B ctor plus memcpy-1 plus dup_0006EDE3 row TYPES wrong;
// retail calls thiscall bool setter at 0x0006EDE3 whose row is gen-alias
// YAXXZ but object-symbol is ?setActive@Script@@QAEX_N@Z; declared as used.
typedef unsigned char UnsignedByte;
class NetCommandMsg;
class Rva004D582B
{
public:
    Rva004D582B();
private:
    char m_pad[0x20];
};
class Rva004D5795
{
public:
    Rva004D5795();
private:
    char m_pad[0x20];
};
class Script
{
public:
    void setActive(bool active);
};
extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
void *__cdecl operator new(unsigned int size);
class NetPacket
{
public:
    static NetCommandMsg *rva0058E047(unsigned char *data, int &readOffset);
    static NetCommandMsg *rva0058DDF2(unsigned char *data, int &readOffset);
};
NetCommandMsg *NetPacket::rva0058E047(unsigned char *data, int &readOffset)
{
    Rva004D582B *msg = new Rva004D582B();
    bool flag = false;
    memcpy(&flag, data + readOffset, 1);
    readOffset += 1;
    ((Script *)msg)->setActive(flag);
    return (NetCommandMsg *)msg;
}

// ?rva0058DDF2@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z, retail 0x0058DDF2, 105 bytes:
// the same 1-byte-flag reader constructing the rowed Rva004D5795 message (same
// 0x20 size) instead of Rva004D582B, the only difference from rva0058E047's bytes.
NetCommandMsg *NetPacket::rva0058DDF2(unsigned char *data, int &readOffset)
{
    Rva004D5795 *msg = new Rva004D5795();
    bool flag = false;
    memcpy(&flag, data + readOffset, 1);
    readOffset += 1;
    ((Script *)msg)->setActive(flag);
    return (NetCommandMsg *)msg;
}
