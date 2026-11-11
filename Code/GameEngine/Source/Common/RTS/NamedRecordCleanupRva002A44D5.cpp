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

#include "../../../Include/GameClient/DisplayStringManager.h"
extern DisplayStringManager *TheDisplayStringManager;

#include "../../../../GameEngineDevice/Include/Rva001F8437.h"
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
#include <new>

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

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x001F8437 reads ??$_M_find@VAsciiString@@@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@H@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@H@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@H@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@H@_STL@@@1@ABVAsciiString@@@Z
#pragma comment(linker, "/alternatename:?rva001F8437@Rva001F8437@@QAEPAXABVAsciiString@@@Z=??$_M_find@VAsciiString@@@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@H@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@H@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@H@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@H@_STL@@@1@ABVAsciiString@@@Z")
//   0x00056BC3 reads ?erase@?$_Rb_tree@VAsciiString@@V1@U?$_Identity@VAsciiString@@@_STL@@U?$less@VAsciiString@@@3@V?$allocator@VAsciiString@@@3@@_STL@@QAEXU?$_Rb_tree_iterator@VAsciiString@@U?$_Nonconst_traits@VAsciiString@@@_STL@@@2@@Z
#pragma comment(linker, "/alternatename:?rva00056BC3@Rva00056BC3@@QAEXURva00056BC3Iter@@@Z=?erase@?$_Rb_tree@VAsciiString@@V1@U?$_Identity@VAsciiString@@@_STL@@U?$less@VAsciiString@@@3@V?$allocator@VAsciiString@@@3@@_STL@@QAEXU?$_Rb_tree_iterator@VAsciiString@@U?$_Nonconst_traits@VAsciiString@@@_STL@@@2@@Z")
