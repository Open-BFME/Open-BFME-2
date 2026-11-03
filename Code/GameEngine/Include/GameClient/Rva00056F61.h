/* Target facts: Rva00056F61 is a non-polymorphic view of AsciiString-keyed bucket storage, with no virtual functions or evidenced parent. The ledger has no constructor or destructor under this placeholder name. LivingWorldManager::CreateSound (RVA 0x0021399A, receiver adjustment 0x002139AC) uses this view at +0x204. Its owner constructs that member at 0x00213F45 through 0x00213E11 -> 0x002138E5, which initializes the vector at +4 through 0x00025100 and zeros +0x10 without a vptr store. ~LivingWorldManager calls the non-virtual table destructor 0x002129DD there at 0x0021467F, and destroys the next subobject at +0x218 (0x00214666). The count ends at +0x14 and that next subobject bounds the table to 0x14 bytes. Its destructor clears through 0x003A2A41 and frees +4 without storing a vptr; the leading four bytes remain opaque.
   Target layout: find (0x00056F61) hashes through 0x00055041, subtracts +4 from +8, divides by four, reloads +4 and walks node links at +0, comparing the AsciiString at node+4 through 0x000069D6. Insert (0x002249ED) calls resize 0x00212858, bucketIndex 0x00223149 and node allocation 0x002241AC, updates the bucket at +4 and increments the four-byte count at +0x10. Resize swaps the three-word bucket vector at +4 through 0x00026B60, establishing pointers at +4, +8 and +0x0C. Iterator find (0x0041534B) calls 0x00056F61 and fills {node, this}; both lookups only hash and compare existing storage (0x00055041 -> 0x0002BA61; 0x000069D6 -> 0x00006733 -> 0x00005816), with no allocation, callback or C++ throw.
   Target declarations: rvaXXXXXXXX retains its ledger identity at RVA 0xXXXXXXXX. The find-or-insert rows 0x0020D67C and 0x0021386C return node+8 or insert-result+4; 0x003A3763 returns the boolean payload there. The insert row 0x002249ED returns the value at node+4. These methods are declared out of line; no constructor, destructor, copy or assignment identity is inferred for this placeholder. */
#pragma once

class AsciiString;
class Rva0022304A;
struct Rva0041534BIter;

class Rva00056F61
{
public:
    __declspec(nothrow) void *rva00056F61(const AsciiString *key);
    __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *key);
    Rva0022304A &rva002249ED(const Rva0022304A &value);
    void *rva0020D67C(const AsciiString *key);
    void *rva0021386C(const AsciiString *key);
    bool *rva003A3763(const AsciiString *key);

    void *field00;
    void **m_beginBuckets;
    void **m_endBuckets;
    void **m_storageEnd;
    unsigned int m_numElements;
};
