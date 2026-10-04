// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// Entries retained by the holder at TheInGameUI+0x58C. Original entry and
// container names remain unknown. Retail 0x004E4E76..0x004E4E9E walks the
// circular list at entry+0x34, invokes slot 2 on non-null node+8 pointers,
// then clears the nodes through the already recovered POD-list operation.
// The predecessor ends at 0x004E4E76; the destructor at 0x004E5086 calls
// this entry directly. The following 5-byte tail thunk ends at Ghidra's
// 0x004E4EA3 boundary.
#include "ascii_string.h"

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

// This-only tail alias immediately after rva004E4E76; next entry is 4E4EA3.
void Rva004E5086::rva004E4E9E()
{
    rva004E4E76();
}

// Retail 4E5086/66B destroys list members at +38 then +34 after cleanup.
// Two EH states preserve both member cleanups if slot 2 throws.
Rva004E5086::~Rva004E5086()
{
    rva004E4E76();
}

struct ResourceOwnedEntryNode
{
    ResourceOwnedEntryNode *next;
    ResourceOwnedEntryNode *prev;
    Rva004E5086 entry;
};
class ResourceOwnedEntryList
{
public:
    void rva004E54ED();
    ResourceOwnedEntryNode *head;
};
extern "C" void __cdecl free(void *);

// Retail 4E54ED/49B: destroy each node+8 entry, free the node, reset head.
void ResourceOwnedEntryList::rva004E54ED()
{
    ResourceOwnedEntryNode *node = head->next;
    if (node != head)
    {
        do
        {
            ResourceOwnedEntryNode *old = node;
            node = node->next;
            old->entry.~Rva004E5086();
            free(old);
        } while (node != head);
    }
    head->next = head;
    head->prev = head;
}

class ResourceEntryCollector
{
public:
    __declspec(noinline) void rva004E551E();
private:
    char unknown00[4];
    ResourceOwnedEntryList entries;
};

// Retail 4E551E/8B adjusts to the +4 list and forwards its cleanup.
void ResourceEntryCollector::rva004E551E()
{
    entries.rva004E54ED();
}

class Rva004E7C1C
{
public:
    void rva004E7C1C();
private:
    void *head;
};
class Rva004E7B13
{
public:
    void rva004E7BAF();
    void rva004E7C4D();
private:
    void *head;
    int count;
};

// Clear tail wrapper between the 4E7C1C list body and 4E7C52 tree destructor.
void Rva004E7B13::rva004E7C4D()
{
    rva004E7BAF();
}

class ResourceEntryOwner
{
public:
    __declspec(noinline) void rva004E7CBA(const AsciiString &value);
    __declspec(noinline) void rva004E7CEF();
private:
    char unknown00[4];
    int users;
    AsciiString name;
    Rva004E7C1C list;
    Rva004E7B13 tree;
    char unknown18[4];
    ResourceEntryCollector collector;
};

// Retail 4E7CBA..4E7CEF compares the argument with the +8 narrow string.
// A changed name is copied before the +C list and +10 tree are cleared.
// The string identity follows the rowed compare/set callees, not adjacency.
void ResourceEntryOwner::rva004E7CBA(const AsciiString &value)
{
    if (value.compare(name))
    {
        name = value;
        list.rva004E7C1C();
        tree.rva004E7BAF();
    }
}

// Retail 4E7CEF/39B decrements +4 and clears all three stores at <=0.
void ResourceEntryOwner::rva004E7CEF()
{
    --users;
    if (users <= 0)
    {
        list.rva004E7C1C();
        tree.rva004E7BAF();
        collector.rva004E551E();
    }
}

class Rva004E7B0CHolder
{
public:
    void rva004E7D16(const AsciiString &value);
    void rva004E7D1D();
private:
    ResourceEntryOwner *owner;
};

// Native 4E7D16/7B forwards the same stack argument through holder+0.
void Rva004E7B0CHolder::rva004E7D16(const AsciiString &value)
{
    owner->rva004E7CBA(value);
}

// TheInGameUI+0x58C is a pointer holder; retail forwards through its +0.
void Rva004E7B0CHolder::rva004E7D1D()
{
    owner->rva004E7CEF();
}
