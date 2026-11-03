// FILE: AptNativeHash.h ///////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 AptNativeHash, the APT name-to-value hash of an object.
//
// Target facts:
//  - No base and no virtual functions. The constructor 0x0070A740 (??0AptNativeHash@@QAE@H@Z)
//    stores its argument at +0 and zero at +4, +8, +0xC and +0x10, with no table store and no
//    base-constructor call. The destructor 0x0070A840 (rowed ??1Rva0070A840@@QAE@XZ, which
//    ??1AptNativeHash@@QAE@XZ binds to) stores no table either, and the scalar deleting
//    destructor 0x006DB3C0 that calls it is non-virtual (QAE) and is called from no table.
//  - sizeof 0x14: 0x006F859A pushes 0x14 to the pool allocator 0x006DB160 and 0x006F85B7 then
//    calls 0x0070A740; the deleting destructor 0x006DB3C0 and the EH funclet 0x007AA093 of
//    that allocation free 0x14 bytes through 0x006DB270 and 0x006D8680; 0x006DE1A0 builds a
//    hash at +8 (0x006DE1DE) and stores its next member at +0x1C (0x006DE1F6).
//  - +0 is a signed count (the destructor's jle/jl at 0x0070A851 and 0x0070A88D); +4 points to
//    8-byte items (stride at 0x0070A857, allocBlock(count*8) in 0x0070AB30); +8 and +0xC are
//    released through table slot 1 by Unset__Proto__ 0x0070A5D0 and UnsetPrototype 0x0070A5F0
//    and replaced by Set__Proto__ 0x006DB350 and SetPrototype 0x006DB380; 0x0070B180 ORs and
//    clears event bits in +0x10.
//  - Item +0 is an EAStringC: 0x0070A840 and the rowed hash bodies call EAStringC 0x006D3C20,
//    0x006D2F30, 0x006D36F0, 0x006D3CA0 and operator= 0x006D3030 (in 0x0070AC90) on it. Item +4
//    is an AptValue pointer: 0x0070A680 calls table slot 0 (AddRef) on the value it stores there.
//  - Names from retail assertion text: mpData and mnTotalSize at 0x0070AACA and 0x0070AB7F,
//    the item's mValue at 0x0070A70C (cited as AptNativeHash.h). mp__proto__, mpPrototype and
//    nEventHandlers follow the PDB declaration in the registered AptObject/AptScriptFunction.h.
//  - Every method below has a ledger row or a retail call and stays out of line: retail calls
//    SetPrototype from 0x0070B410, Set__Proto__ from 0x0070B410 and 0x006E2EE0, and Lookup
//    (rowed at 0x0070B380 as Rva0070B380::lookup, which calls the private HashFindKey
//    0x0070AF90) from seventeen bodies. The item key's name is a placeholder until evidence
//    names it.
//  - The class-key is not in retail bytes; struct and the inline Get__Proto__ follow the PDB
//    declaration that AptObject/AptScriptFunction.h carried before it included this header.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef BFME2_APTNATIVEHASH_H
#define BFME2_APTNATIVEHASH_H

class AptValue;
class EAStringC;
class AsciiString;
class BfmeAptValue006DCD20;
struct AptHashItem;

struct AptNativeHash
{
public:
    // Eight-byte item: an EAStringC key at +0 and mValue at +4 (see the facts above).
    struct Entry;

    AptNativeHash(int size); // 0x0070A740
    ~AptNativeHash(); // 0x0070A840

    AptValue *Lookup(const EAStringC *const key) const; // 0x0070B380
    __forceinline AptValue *Get__Proto__() const { return mp__proto__; }
    void Set(const EAStringC *const key, AptValue *const value); // 0x0070B410
    void Unset(const EAStringC *const key); // 0x0070B2C0
    void ClearData(); // 0x0070A910
    void ClearDataNoDelete(); // 0x0070A9B0
    void DestroyGCPointers(); // 0x0070A8B0
    void Set__Proto__(AptValue *const value); // 0x006DB350
    void SetPrototype(AptValue *const value); // 0x006DB380
    void Unset__Proto__(); // 0x0070A5D0
    void UnsetPrototype(); // 0x0070A5F0
    static void UnsetAt(void *pHashItem); // 0x0070A6D0
    void rva0070A610(int index, AptValue *pValue); // 0x0070A610
    void rva0070A680(int index, AptValue *pValue); // 0x0070A680
    AsciiString *rva0070AA40(); // 0x0070AA40
    Entry *rva0070AAA0(Entry *pItem); // 0x0070AAA0
    void rva0070AB30(); // 0x0070AB30
    void rva0070B180(BfmeAptValue006DCD20 *pValue, EAStringC *pStr, int bRemove); // 0x0070B180
    void rva0070B220(void *arg); // 0x0070B220

    int mnTotalSize;
    Entry *mpData;
    AptValue *mp__proto__;
    AptValue *mpPrototype;
    unsigned int nEventHandlers;

private:
    friend class Rva0070B380;
    AptHashItem *HashFindKey(const EAStringC *const key) const; // 0x0070AF90
    void Expand(); // 0x0070ABC0
    void HashSet(const EAStringC *const key, AptValue *const value); // 0x0070AC90
};

#endif // BFME2_APTNATIVEHASH_H
