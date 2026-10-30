// cl: /MD /EHsc
// ?rva000F1AD8@W3DShadowGeometryManager@@QAEXXZ @0x000F1AD8 95B
// Evidence: unlock lane calls rowed First Next Reset plus virtual release; table at +0; iterator on stack.
class HashableClass {
public:
 virtual void release();
 int m_ref;
 HashableClass *m_next;
};
class HashTableClass {
public:
 void Reset();
 __declspec(noinline) ~HashTableClass();
private:
 int HashTableSize;
 HashableClass **HashTable;
};
struct IterBase {
 const HashTableClass *m_table;
 IterBase(HashTableClass *hashTable) : m_table(hashTable) {}
};
// The target-region defaults now emit the kept iterator support copies.
// The former optimization window made the deleting destructor differ; removing
// it preserves both 95B loop bodies and lets this unit link.
class HashTableIteratorClass : public IterBase {
 int m_index;
 HashableClass *m_cur;
 HashableClass *m_next;
public:
 HashTableIteratorClass(HashTableClass *hashTable) : IterBase(hashTable) {}
 virtual ~HashTableIteratorClass() {}
 void First();
 void Next();
 bool Is_Done() { return m_cur == 0; }
 HashableClass *Get_Current() { return m_cur; }
};
// The loops below walk their tables through WWLib's per-manager iterator
// subclasses, not HashTableIteratorClass itself (target facts): each inline
// ctor stores VA 0x00BCF9AC, whose one slot is the deleting dtor 0x00108D17
// calling the destructor 0x00108650, and that destructor stores VA 0x00BCEF9C:
// the subclass's own store is dead behind the expanded empty base destructor.
// 0x00BCEF9C is HashTableIteratorClass's one-slot table, emitted beside
// HashableClass's 0x00BCEF94 (deleting dtor, pure Get_Key) and stored by the
// iterator ctor 0x000EF9F3 with the table at +4. Zero Hour and BFME 1 derive
// W3DShadowGeometryManagerIterator and W3DShadowTextureManagerIterator from
// HashTableIteratorClass with no members of their own; ICF leaves one table.
class W3DShadowGeometryManagerIterator : public HashTableIteratorClass {
public:
 W3DShadowGeometryManagerIterator(HashTableClass *hashTable) : HashTableIteratorClass(hashTable) {}
};
class W3DShadowTextureManagerIterator : public HashTableIteratorClass {
public:
 W3DShadowTextureManagerIterator(HashTableClass *hashTable) : HashTableIteratorClass(hashTable) {}
};
struct W3DShadowGeometryManager {
 HashTableClass *m_00;
 void rva000F1AD8();
};
void W3DShadowGeometryManager::rva000F1AD8()
{
 HashTableClass *hashTable = m_00;
 W3DShadowGeometryManagerIterator it(hashTable);
 it.First();
 while (!it.Is_Done()) {
 HashableClass *hashable = it.Get_Current();
 HashableClass *b = hashable ? (HashableClass*)((char*)hashable - 8) : 0;
 if (--b->m_ref == 0)
 b->release();
 it.Next();
 }
 m_00->Reset();
}


// BFME1 1399ad37 W3DProjectedShadowManagerDestructor and bfmeGo928F
// identify this texture-manager helper. Retail 0x108A79..0x108AD8 (95B)
// uses the same loop as rva000F1AD8 but owns its own EH handler at VA B64523.
// Its first hash-table pointer is at +0; iterator current is frame-14.
// Emit the real body rather than binding the caller to the other method
// through /alternatename and a gen-alias ledger row.
class BfmeSub928F
{
public:
    void bfmeTail928F();
    __declspec(noinline) ~BfmeSub928F();
    HashTableClass *m_texturePtrTable;
    HashTableClass *m_missingTextureTable;
};
void BfmeSub928F::bfmeTail928F()
{
    HashTableClass *hashTable = m_texturePtrTable;
    W3DShadowTextureManagerIterator it(hashTable);
    it.First();
    while (!it.Is_Done())
    {
        HashableClass *hashable = it.Get_Current();
        HashableClass *b = hashable ? (HashableClass*)((char*)hashable - 8) : 0;
        if (--b->m_ref == 0)
            b->release();
        it.Next();
    }
    m_texturePtrTable->Reset();
}

// BFME1 1399ad37 W3DProjectedShadowManagerDestructor.cpp supplies this
// nonvirtual texture-manager destructor. Retail 0x109BEB..0x109C27 (60B)
// clears textures at 0x108A79, deletes the two HashTableClass pointers at
// +0 and +4 through their rowed destructor 0x613B90, then clears the fields.
// The scalar wrappers at 0x109DB3 and 0xF0B65 are both 28B (ret 4). Their
// call sites and the constructor's size/table fields establish nonvirtual
// ownership; the withdrawn Rva virtual declarations were emission scaffolds.
BfmeSub928F::~BfmeSub928F()
{
    bfmeTail928F();
    delete m_texturePtrTable;
    m_texturePtrTable = 0;
    delete m_missingTextureTable;
    m_missingTextureTable = 0;
}

// ?Rva00109DB3EmissionPattern absent-from-retail
void Rva00109DB3EmissionPattern(BfmeSub928F *manager, HashTableClass *hashTable)
{
    delete manager;
    delete hashTable;
}
