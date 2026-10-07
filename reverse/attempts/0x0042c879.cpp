// ?rva0042C879@Rva0042C833@@QAEHPAVGameMessage@@@Z
// partial score=0.93 date=2026-10-07
// cl: /MD /Oy-
// Native Ghidra 0042C879..0042C8D1, RET4. Receiver layout is the one
// established by constructor 0042C7E0 and rowed destructor 0042C833:
// a forwarding callback at +14 and the mouse handler's owner at +8.
// The input number 3 and the two GameMessage argument reads are target
// facts. Original receiver/method names remain unknown and address-derived.
// 005E6817 is the seven-byte +4/virtual-slot-zero forwarding thunk; this
// caller establishes its one-argument, full-int-result interface.
union GameMessageArgumentType
{
    int integer;
    float real;
    int boolean, objectID, drawableID;
    unsigned int teamID;
    struct Loc { float x, y, z; } location;
    struct Pix { int x, y; } pixel;
    struct PixReg { int loX, loY, hiX, hiY; } pixelRegion;
    unsigned int timestamp;
    unsigned short wChar;
};
class GameMessage
{
public:
    const GameMessageArgumentType *getArgument(int index) const;
    char unknown00[0x10];
    int type;
};
struct Rva0042C083Param { int m_00, m_04; };
class Rva0042C7B1
{
public:
    int rva0042C7B1(const Rva0042C083Param *point, int argument);
};
class Rva005E6817
{
public:
    int rva005E6817(GameMessage *message);
};
class Rva0042C833
{
public:
    int rva0042C879(GameMessage *message);
private:
    char unknown00[0x14];
    Rva005E6817 *callback;
};

int Rva0042C833::rva0042C879(GameMessage *message)
{
    if (callback)
    {
        int result = callback->rva005E6817(message);
        if (result == 1)
            return result;
    }
    if (message->type != 3)
        return 0;

    const GameMessageArgumentType *argument = message->getArgument(0);
    Rva0042C083Param point =
        *reinterpret_cast<const Rva0042C083Param *>(&argument->pixel);
    return reinterpret_cast<Rva0042C7B1 *>(this)->rva0042C7B1(
        &point, message->getArgument(1)->integer);
}
