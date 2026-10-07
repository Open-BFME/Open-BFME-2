// cl: /MD /EHsc
// ?rva000F1AD8@Rva000F1AD8@@QAEXXZ @0x000F1AD8 95B
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
 IterBase(HashTableClass *t) : m_table(t) {}
};
// The target-region defaults now emit the kept iterator support copies.
// The former optimization window made the deleting destructor differ; removing
// it preserves both 95B loop bodies and lets this unit link.
class HashTableIteratorClass : public IterBase {
 int m_index;
 HashableClass *m_cur;
 HashableClass *m_next;
public:
 HashTableIteratorClass(HashTableClass *t) : IterBase(t) {}
 virtual ~HashTableIteratorClass() {}
 void First();
 void Next();
 bool Is_Done() { return m_cur == 0; }
 HashableClass *Get_Current() { return m_cur; }
};
struct Rva000F1AD8 {
 HashTableClass *m_00;
 void rva000F1AD8();
};
void Rva000F1AD8::rva000F1AD8()
{
 HashTableClass *t = m_00;
 HashTableIteratorClass it(t);
 it.First();
 while (!it.Is_Done()) {
 HashableClass *e = it.Get_Current();
 HashableClass *b = e ? (HashableClass*)((char*)e - 8) : 0;
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
    HashTableClass *t = m_texturePtrTable;
    HashTableIteratorClass it(t);
    it.First();
    while (!it.Is_Done())
    {
        HashableClass *e = it.Get_Current();
        HashableClass *b = e ? (HashableClass*)((char*)e - 8) : 0;
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
void Rva00109DB3EmissionPattern(BfmeSub928F *p, HashTableClass *q)
{
    delete p;
    delete q;
}
