// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native Ghidra 002A44D5..002A4523, 78B, RET4. Owner name unresolved.
// Existing AsciiString find1F8437 establishes the referenced key argument
// and tree at +750; header0 and mapped record pointer at node+14.
// TheDisplayStringManager's established slot3C frees the record's +0C string.
// Record slot0(flags=0) returns the pointer passed to global operator delete,
// as in the verified scalar-delete cleanup at 00373373. Then rowed tree
// erase56BC3 receives the captured one-word iterator by value (RET4).
// The complete 59B erase body uses header0/count4 and destroys key node+10.

class AsciiString;
class DisplayString;

class DisplayStringManager
{
public:
    virtual ~DisplayStringManager();
#define STRING_SLOT(n) virtual void unknown##n();
    STRING_SLOT(04) STRING_SLOT(08) STRING_SLOT(0C) STRING_SLOT(10)
    STRING_SLOT(14) STRING_SLOT(18) STRING_SLOT(1C) STRING_SLOT(20)
    STRING_SLOT(24) STRING_SLOT(28) STRING_SLOT(2C) STRING_SLOT(30)
    STRING_SLOT(34)
#undef STRING_SLOT
    virtual DisplayString *newDisplayString();
    virtual void freeDisplayString(DisplayString *string);
};
extern DisplayStringManager *TheDisplayStringManager;

class Rva001F8437
{
public:
    void *rva001F8437(const AsciiString &key);
};
struct Rva00056BC3Iter
{
    explicit Rva00056BC3Iter(void *value) : node(value) {}
    Rva00056BC3Iter(const Rva00056BC3Iter &other) : node(other.node) {}
    void *node;
};
class Rva00056BC3
{
public:
    void rva00056BC3(Rva00056BC3Iter position);
};
class Rva002A44D5Record
{
public:
    virtual void *release(unsigned int flags);
    char unknown04[8];
    DisplayString *string;
};
struct Rva002A44D5Node
{
    char unknown00[0x14];
    Rva002A44D5Record *record;
};
struct Rva002A44D5Tree
{
    void *header;
};
class Rva002A44D5
{
public:
    void rva002A44D5(const AsciiString &key);
private:
    char unknown00[0x750];
    Rva002A44D5Tree tree;
};
void __cdecl operator delete(void *pointer);

void Rva002A44D5::rva002A44D5(const AsciiString &key)
{
    void *node = reinterpret_cast<Rva001F8437 *>(&tree)->rva001F8437(key);
    if (node != tree.header)
    {
        TheDisplayStringManager->freeDisplayString(
            static_cast<Rva002A44D5Node *>(node)->record->string);
        Rva002A44D5Record *record = static_cast<Rva002A44D5Node *>(node)->record;
        ::operator delete(record ? record->release(0) : 0);
        reinterpret_cast<Rva00056BC3 *>(&tree)->rva00056BC3(Rva00056BC3Iter(node));
    }
}
