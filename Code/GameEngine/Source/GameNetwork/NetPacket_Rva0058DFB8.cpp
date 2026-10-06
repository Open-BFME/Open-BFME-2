// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0058DFB8@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DFB8 143B.
// Static NetCommandMsg factory reading 1-byte bool plus 4-byte enum from data+offset.
// Evidence: unlock lane plus sibling 0x0058E047 plus new-0x24 plus
// Rva004D580E ctor plus memcpy-1-4 plus dup_0006ede3 row TYPES wrong
// (object-symbol ?setActive@Script@@QAEX_N@Z) plus dup_00317b9b row TYPES wrong
// (object-symbol ?setCurrentTask@DozerAIUpdate@@UAEXW4DozerTask@@@Z); declared as used.
typedef unsigned char UnsignedByte;
class NetCommandMsg;
class Rva004D580E
{
public:
    Rva004D580E();
private:
    char m_pad[0x24];
};
enum DozerTask
{
    DOZER_TASK_ZERO = 0
};
class Script
{
public:
    void setActive(bool active);
};
class DozerAIUpdate
{
public:
    virtual void setCurrentTask(DozerTask task);
};
extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
void *__cdecl operator new(unsigned int size);
class NetPacket
{
public:
    static NetCommandMsg *rva0058DFB8(unsigned char *data, int &readOffset);
};
NetCommandMsg *NetPacket::rva0058DFB8(unsigned char *data, int &readOffset)
{
    Rva004D580E *msg = new Rva004D580E();
    bool flag = false;
    memcpy(&flag, data + readOffset, 1);
    readOffset += 1;
    ((Script *)msg)->setActive(flag);
    DozerTask task = DOZER_TASK_ZERO;
    memcpy(&task, data + readOffset, 4);
    readOffset += 4;
    ((DozerAIUpdate *)msg)->DozerAIUpdate::setCurrentTask(task);
    return (NetCommandMsg *)msg;
}
