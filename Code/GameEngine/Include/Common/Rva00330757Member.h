// Target facts (code addresses are RVAs): constructor 0x00330757 calls the empty three-word initializer 0x00211E58 at +0, then writes dword -1 at +0x0C. The initializer clears +0/+4 and calls 0x0014F3C4 at +8 with zero; that leaf stores the zero word. These calls allocate nothing and cannot throw.
// Destructor 0x0007FAB3 reads the pointer at +0 and, when nonnull, calls free at 0x00030830. Neither constructor nor destructor stores a vptr or vbptr: this class has no retail virtual functions or table. The vptr at +0 in derived constructor 0x0053FAB7 belongs to that derived class, whose Rva00330757Member subobject starts at +4.
// Constructor 0x0033076E calls 0x00330757 at +0 and constructs its next member at +0x10; 0x0053FAB7 places its first following field at +0x14 after the +4 subobject. Together with the +0x0C dword write these prove a 0x10-byte footprint. The element type and original field identities are unproved, so the storage names are neutral. Both ledger lifetime methods are declared out of line.
#pragma once

#ifndef BFME2_COMMON_RVA00330757MEMBER_H
#define BFME2_COMMON_RVA00330757MEMBER_H

class Rva00330757Member
{
public:
    Rva00330757Member() throw();
    ~Rva00330757Member() throw();

    void *field00;
    void *field04;
    void *field08;
    int field0C;
};

typedef char Rva00330757MemberSizeCheck[sizeof(Rva00330757Member) == 0x10 ? 1 : -1];

#endif
