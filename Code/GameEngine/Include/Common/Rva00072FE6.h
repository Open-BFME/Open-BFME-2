// Target facts (code addresses are RVAs): Rva00072FE6 has no virtual functions, vptr or vftable. Destructor 0x000730DE calls clear 0x00072FE6 at 0x000730F3, then frees the pointer at +0 through 0x00030830 at 0x00073103; it never stores a table. Its EAX immediate 0x00B5EDED is the EH handler, not a vftable. Wrapper 0x00073116 jumps directly to this destructor without adjusting this.
// Target facts: constructor 0x004E2382 constructs this member at +8 through 0x000D3A71 (call 0x004E23A1), then the next member at +0x14 (0x004E23AA); destructor 0x004E2941 calls 0x000730DE on +8 at 0x004E296E. The member occupies 0x0C bytes. Constructor chain 0x000D3A80 -> 0x002F0BF4 initializes header +0 and count +4, with no vptr. Clear 0x00072FE9 tests count +4; 0x00072FEF loads header +0 and resets its links +4/+8/+0x0C at 0x00073000/0x00072FFB/0x00073006. Bytes +8..+0x0B remain opaque.
// Target facts: the ledger names clear 0x00072FE6, node erase 0x00072F7C, range erase 0x0007300F and key erase 0x000733D8. Node erase follows right +0x0C (0x00072F89) and left +8 (0x00072F93), frees nodes through 0x00030830 and calls no payload destructor. Range erase compares the header's left link at 0x0007301A and calls clear at 0x00073028; its two by-value iterator arguments and key erase's const-int reference follow the ledger spellings. These methods and the nonvirtual destructor are declared out of line.
#pragma once
#ifndef BFME2_RVA00072FE6_H
#define BFME2_RVA00072FE6_H

#include "RvaTreeFamilyHolder.h"

struct Rva00072F7CNode;

namespace _STL
{
    template <class T1, class T2> struct pair;
    template <class T> struct _Nonconst_traits;
    template <class Value, class Traits> struct _Rb_tree_iterator;
}

class Rva00072FE6
{
public:
    typedef _STL::pair<const int, void *> V;
    typedef _STL::_Rb_tree_iterator<V, _STL::_Nonconst_traits<V> > iterator;

    ~Rva00072FE6();
    void rva00072FE6();
    void rva00072F7C(Rva00072F7CNode *node);
    void rva0007300F(iterator first, iterator last);
    unsigned int rva000733D8(const int &key);

    RvaTreeFamilyHolder header00;
    unsigned int count04;
    unsigned char unknown08[4];
};

typedef char Rva00072FE6RetailSize[(sizeof(Rva00072FE6) == 0x0C) ? 1 : -1];

#endif
