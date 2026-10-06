// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP=
// Target-only view of the complete 110B destructor at 0x003EF14A.
// The queue's Rva00382574 name is refuted by this body's different layout.
// Target facts: primary vptr C363C8; unregister this from global E02E88 via
// matched 2B7250; cleanup 3EE9F1(this); secondary vptr at +4C becomes
// C363B8; destroy narrow strings +1C/+18 via matched 36410; destroy the
// container at +8 through 4E2E58; restore primary base vptr BFDF68.
// Original class, container type, and member names remain unknown.
#include "ascii_string.h"

class CreateAHeroData;
class Rva002B7250 {
public:
    void rva002B7250(CreateAHeroData *);
};
// g_registryAtE02E88: matched references place it at VA 0xe02e88 (zero-filled; a plain-data view).
Rva002B7250 g_registryAtE02E88;
extern const void *const g_vtableAtBFDF68[];
const void *const g_vtableAtBFDF68[1] = { 0 };

class Rva003EF14ABase {
public:
    virtual void slot0();
    // ?Rva003EF14ABase::~Rva003EF14ABase present-unmatched
    ~Rva003EF14ABase() { *(const void **)this = g_vtableAtBFDF68; }
};

class Rva004E2E58Value;
struct Rva004E2E58Node {
    unsigned unknown00;
    Rva004E2E58Node *parent04;
    Rva004E2E58Node *left08;
    Rva004E2E58Node *right0C;
    void *unknown10;
    Rva004E2E58Value *value14;
};
namespace _STL {
    struct _Rb_tree_node_base;
    template <class T> class _Rb_global {
    public:
        static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
    };
}

namespace _STL { void __cdecl free(void *); }
struct Rva004E21FE {
    void rva004E21FE();
};
// Local ownership view, not a recovered donor type. Retail frees the
// header after clearing its nodes; the intermediate EH state proves
// that ownership must remain live while the clear call can unwind.
struct Rva004E2990HeaderOwner {
    Rva004E2E58Node *header00;
    // ?Rva004E2990HeaderOwner::~Rva004E2990HeaderOwner present-unmatched
    ~Rva004E2990HeaderOwner() {
        if (header00)
            _STL::free(header00);
    }
};
class Rva004E2990 {
protected:
    Rva004E2990HeaderOwner owner;
    unsigned count04;
public:
    ~Rva004E2990();
};

class Rva004E2E58 : public Rva004E2990 {
public:
    // Opaque span between the independently observed member at +8 and
    // string at +18. Its exact container extent is not yet established.
    // Second word is cleared by 0x003EF1B8 (and [esi+0x14],0 under /O1).
    unsigned unknown08[2];
    ~Rva004E2E58();
    void rva004E21D5();
};

class Rva003EF14ASecondary {
public:
    virtual void slot0();
    // ?Rva003EF14ASecondary::~Rva003EF14ASecondary present-unmatched
    ~Rva003EF14ASecondary() {}
};

// ?slot0@Rva003EF14ASecondary@@UAEXXZ present-unmatched
void Rva003EF14ASecondary::slot0() { }

// Only the two called vslots and reference word are recovered. The names
// and signatures of unused slots remain opaque in this local call view.
class Rva003EE9F1Ref {
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0C() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1C() = 0;
    virtual void slot20() = 0;
    virtual void slot24() = 0;
    virtual void slot28() = 0;
    virtual void slot2C() = 0;
    virtual void slot30() = 0;
    virtual void slot34() = 0;
    virtual void slot38() = 0;
    virtual void slot3C() = 0;
    virtual void slot40() = 0;
    unsigned references;
    // ?Rva003EE9F1Ref::dropReference present-unmatched
    void dropReference() {
        if (--references == 0)
            slot00();
    }
};

struct Rva00072F7CNode {
    unsigned unknown00;
    Rva00072F7CNode *parent04;
    Rva00072F7CNode *left08;
    Rva00072F7CNode *right0C;
};
struct Rva00072FE6 {
    // Only the receiver at record+8 is known; the remaining record bytes
    // are opaque. This span preserves the independently measured 0x20 stride.
    Rva00072F7CNode *header00;
    unsigned count04;
    char unknown08[0x10];
    void rva00072FE6();
    void rva00072F7C(Rva00072F7CNode *);
};
struct Rva004E2199Record {
    unsigned unknown00;
    Rva003EE9F1Ref *ref04;
    Rva00072FE6 container08;
};
class Rva004E2E58Value {
public:
    virtual ~Rva004E2E58Value();
    void rva004E2199();
private:
    char unknown04[0x10];
    Rva004E2199Record *begin14;
    Rva004E2199Record *end18;
    unsigned unknown1C;
    bool flag20;
};

class Rva003EF14A : public Rva003EF14ABase {
    Rva003EE9F1Ref *ref04;
    Rva004E2E58 container08;
    AsciiString string18;
    AsciiString string1C;
    char unknown20[0x28];
    Rva003EF14ASecondary *link48;
    Rva003EF14ASecondary secondary4C;
public:
    virtual void slot0();
    ~Rva003EF14A();
    void rva003EE9F1();
    void rva003EF1B8();
};

// ?slot0@Rva003EF14A@@UAEXXZ present-unmatched
void Rva003EF14A::slot0() { }

Rva003EF14A::~Rva003EF14A()
{
    g_registryAtE02E88.rva002B7250((CreateAHeroData *)this);
    rva003EE9F1();
}

// Complete 41B body; cleans values in the +8 container, calls ref vslot
// +40, drops the +4 count, calls ref vslot 0 on zero, and clears this+4.
void Rva003EF14A::rva003EE9F1()
{
    container08.rva004E21D5();
    if (ref04) {
        ref04->slot40();
        ref04->dropReference();
        ref04 = 0;
    }
}

void Rva003EF14A::rva003EF1B8()
{
    g_registryAtE02E88.rva002B7250((CreateAHeroData *)this);
    link48 = &secondary4C;
    rva003EE9F1();
    container08.unknown08[1] = 0;
}

// Complete 60B boundary at 0x004E2199. Caller 4E21E9 supplies the node's
// payload at +14; every record stride and called virtual slot is retail-read.
void Rva004E2E58Value::rva004E2199()
{
    for (Rva004E2199Record *record = begin14; record != end18; ++record) {
        if (record->ref04) {
            record->ref04->slot40();
            record->ref04->dropReference();
            record->ref04 = 0;
        }
        record->container08.rva00072FE6();
    }
    flag20 = false;
}

// Complete 41B body at 0x004E21D5. Tree nodes survive this pass: each
// non-null payload at node+14 is reset, then the matched iterator advances.
void Rva004E2E58::rva004E21D5()
{
    for (Rva004E2E58Node *node = owner.header00->left08; node != owner.header00;
         node = (Rva004E2E58Node *)_STL::_Rb_global<bool>::_M_increment(
             (_STL::_Rb_tree_node_base *)node)) {
        if (node->value14)
            node->value14->rva004E2199();
    }
}

// Complete 56B Ghidra boundary at 0x004E2990. Caller 4E2EA9 invokes this
// after its payload destruction and node-clear pass.
Rva004E2990::~Rva004E2990()
{
    ((Rva004E21FE *)this)->rva004E21FE();
}

// Complete 100B owned-value destructor at 0x004E2E58. Global delete is
// deliberate: retail invokes payload vslot0 with flags0 and then scalar
// operator delete at 2FD60. Nodes are cleared before header ownership ends.
Rva004E2E58::~Rva004E2E58()
{
    for (Rva004E2E58Node *node = owner.header00->left08; node != owner.header00;
         node = (Rva004E2E58Node *)_STL::_Rb_global<bool>::_M_increment(
             (_STL::_Rb_tree_node_base *)node)) {
        ::delete node->value14;
    }
    ((Rva004E21FE *)this)->rva004E21FE();
}

// Independent 45B boundary at 0x00072F7C, ending in ret4 at 72FA6..A8.
// Recurses into right links, preserves each left link, and frees the node.
// No element destructor is called; the node payload identity is unknown.
void Rva00072FE6::rva00072F7C(Rva00072F7CNode *node)
{
    if (!node)
        return;
    do {
        rva00072F7C(node->right0C);
        Rva00072F7CNode *left = node->left08;
        _STL::free(node);
        node = left;
    } while (node);
}

// Complete 41B boundary at 0x00072FE6. Removes the root at header+4,
// restores left/right links to the sentinel, and clears root and count.
void Rva00072FE6::rva00072FE6()
{
    if (count04) {
        rva00072F7C(header00->parent04);
        header00->left08 = header00;
        header00->parent04 = 0;
        header00->right0C = header00;
        count04 = 0;
    }
}

// Target identity: the five-byte boundary at 0x004E2E53 preserves this and
// tail-jumps to the rowed no-argument destructor at 0x004E2990. Keep the
// wrapper's method name address-derived; its enclosing target type is unknown.
class Rva004E2E53
{
public:
    void rva004E2E53();
};

void Rva004E2E53::rva004E2E53()
{
    ((Rva004E2990 *)this)->~Rva004E2990();
}
