// cl: /O1 /MD /EHsc
// Entries retained by the holder at TheInGameUI+0x58C. Original entry and
// container names remain unknown. Retail 0x004E4E76..0x004E4E9E walks the
// circular list at entry+0x34, invokes slot 2 on non-null node+8 pointers,
// then clears the nodes through the already recovered POD-list operation.
// The predecessor ends at 0x004E4E76; the destructor at 0x004E5086 calls
// this entry directly. The following 5-byte tail thunk ends at Ghidra's
// 0x004E4EA3 boundary.
class ResourceEntrySlot2
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
};
struct ResourceEntryNode
{
    ResourceEntryNode *next;
    ResourceEntryNode *prev;
    ResourceEntrySlot2 *value;
};
class Rva0023DAA5List
{
public:
    ~Rva0023DAA5List();
    void clear();
    ResourceEntryNode *head;
};
#pragma comment(linker, "/alternatename:?clear@Rva0023DAA5List@@QAEXXZ=?clear@?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAEXXZ")
#pragma comment(linker, "/alternatename:??1Rva0023DAA5List@@QAE@XZ=??1?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ")
class Rva004E5086
{
public:
    void rva004E4E76();
    void rva004E4E9E();
    ~Rva004E5086();
private:
    char unknown00[0x34];
    Rva0023DAA5List objects;
    Rva0023DAA5List other;
};
void Rva004E5086::rva004E4E76()
{
    for (ResourceEntryNode *node = objects.head->next; node != objects.head; node = node->next)
    {
        ResourceEntrySlot2 *value = node->value;
        if (value)
            value->slot2();
    }
    objects.clear();
}
