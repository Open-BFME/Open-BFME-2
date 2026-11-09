// Target facts (code addresses are RVAs): Rva0038404A has no virtual functions, vptr or vftable. Destructor 0x00385BE1 calls clear 0x00384E8E at 0x00385BF6, then frees the pointer at +0 through 0x00030830 at 0x00385C06; it stores no table. Its EAX immediate 0x00B7FA5F names the EH handler at RVA 0x0077FA5F, not a vftable. Wrapper 0x00385D20 jumps to this destructor without adjusting this.
// Target facts: GameSpyInfo constructor 0x00385FE1 constructs these members at +0x34 and +0x40 through 0x005B400A (calls 0x00386028 and 0x00386034), then the next member at +0x4C. Destructor 0x00386374 calls 0x00385BE1 on +0x40 and +0x34 at 0x0038646C and 0x00386478; unwind actions 0x0077FB1B and 0x0077FB26 call 0x00385D20 on those receivers. Each member occupies 0x0C bytes. Constructor 0x005B400A calls 0x00383356, which initializes header +0 and count +4 and the header's links +4/+8/+0x0C without a vptr. Bytes +8..+0x0B remain opaque.
// Target facts: clear 0x00384E8E tests count +4 at 0x00384E91, loads header +0 at 0x00384E97, calls node erase 0x0038404A at 0x00384E9C and resets the header links and count. Node erase follows right +0x0C at 0x00384057 and left +8 at 0x00384061, calls payload destructor 0x00382B3F on node+0x10 at 0x00384067 and frees the node at 0x0038406D. The ledger declares both methods and the nonvirtual destructor out of line.
#pragma once
#ifndef BFME2_RVA0038404A_H
#define BFME2_RVA0038404A_H

#include "RvaTreeFamilyHolder.h"

struct Rva0038404ANode;

class Rva0038404A
{
public:
    ~Rva0038404A();
    void rva0038404A(Rva0038404ANode *node);
    void rva00384E8E();

    RvaTreeFamilyHolder m_00Head;
    int m_04Flag;
    unsigned char unknown08[4];
};

typedef char Rva0038404ARetailSize[(sizeof(Rva0038404A) == 0x0C) ? 1 : -1];

#endif
