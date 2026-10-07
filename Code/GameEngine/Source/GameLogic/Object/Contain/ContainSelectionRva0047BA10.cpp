// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native Ghidra 0047BA10..0047BA69, 89B, RET8. This is the contain-interface
// receiver; accesses at this-1C/-18 are module data and the owner Object.
// Original override and concrete contain class remain unresolved.
// Complete base-operation 46781F (665B, RET8) forwards Object*/bool to
// 463097 and performs the common contain state/update work on this receiver.
// Selection callees are native twins of named GameLogic operations: rowed
// deselect23C9F8 is 171B RET12 and select23C924 is 212B RET16. Their byte
// guards prove bool affect-client (and select bool mode) with a 32-bit mask.
// Pointer-only RVA call views avoid adding private canonical GameLogic copies.

class Object;
class GameLogic;
extern GameLogic *TheGameLogic;

class Rva0046781F
{
public:
    void rva0046781F(Object *object, bool flag);
};
class Rva0047BA10SelectionView
{
public:
    void rva0023C9F8(Object *object, unsigned int mask, bool affectClient);
    void rva0023C924(Object *object, bool mode, unsigned int mask, bool affectClient);
};
struct Rva0047BA10Data
{
    char unknown00[0x1B4];
    bool selectOwner;
};
struct Rva0047BA10Prefix
{
    char unknown00[4];
    Rva0047BA10Data *data;
    Object *owner;
};
class Rva0047BA10
{
public:
    void rva0047BA10(Object *object, bool flag);
};

void Rva0047BA10::rva0047BA10(Object *object, bool flag)
{
    reinterpret_cast<Rva0046781F *>(this)->rva0046781F(object, flag);
    Rva0047BA10Prefix *prefix = reinterpret_cast<Rva0047BA10Prefix *>(
        reinterpret_cast<char *>(this) - 0x20);
    Rva0047BA10Data *data = prefix->data;
    if (data)
    {
        reinterpret_cast<Rva0047BA10SelectionView *>(TheGameLogic)
            ->rva0023C9F8(object, 0xFFFFF, true);
        if (flag && data->selectOwner)
            reinterpret_cast<Rva0047BA10SelectionView *>(TheGameLogic)
                ->rva0023C924(prefix->owner, true, 0xFFFFF, true);
    }
}
