// Target facts (addresses are RVAs): this is nonvirtual pointer-vector storage, with no vtable or registered parent. The initializer 0x00211E58 clears pointers +0/+4 and initializes +8 through 0x0014F3C4. Constructor 0x0040A530 calls it at 0x0040A53A, then writes the owning wrapper's byte +0xC at 0x0040A542: the storage prefix is 0xC bytes, and that wrapper is 0x10 bytes. CreateAHeroManager constructs the wrapper at +0x174 (0x0021FEC3) and initializes its following flag at +0x184 (0x0021FEC8). No virtual functions occur in these lifetimes or the member rows below.
// Destructor row ??1Rva0040A3F9 (0x0007FAB3, 14 bytes) conditionally frees the pointer at +0 through 0x00030830; the wrapper destructor 0x0040A603 calls its ownership-aware clear 0x0040A59B, then inlines that buffer cleanup. Its unwind action 0x007854A8 jumps to 0x0007FAB3 with the same receiver. The ownership test at 0x0040A5A2 reads the wrapper's +0xC byte. Neither destructor stores a table; the registered manager's table is outside this member, at manager +0. The rowed destructor remains declared out of line.
// Member ledger rows: findIndex 0x0040A3F9, rva0040A441 0x0040A441, rva0040A32F 0x0040A32F, findHeroData 0x0040A3B1 and rva0040A5CF 0x0040A5CF. Their pointer ranges use +0/+4, and indexed lookup loads four-byte elements. Erase calls the vector operation 0x001FF51F with the same receiver. GetDefaultHero 0x0021A6C8 computes the element count from the manager's +0x174/+0x178 pointers; size exposes that same inline operation. Field labels identify offsets without claiming original names; AsciiString is used only by reference.
#pragma once

#ifndef BFME2_COMMON_RVA0040A3F9_H
#define BFME2_COMMON_RVA0040A3F9_H

class AsciiString;
class CreateAHeroData;

class Rva0040A3F9
{
public:
    ~Rva0040A3F9();

    int findIndex(CreateAHeroData *value) const;
    bool rva0040A441(CreateAHeroData *value);
    CreateAHeroData *rva0040A32F(int index);
    CreateAHeroData *findHeroData(int key);
    CreateAHeroData *rva0040A5CF(const AsciiString &name);
    int size() const { return m_field04 - m_field00; }

    CreateAHeroData **m_field00;
    CreateAHeroData **m_field04;
    CreateAHeroData **m_field08;
};

#endif
