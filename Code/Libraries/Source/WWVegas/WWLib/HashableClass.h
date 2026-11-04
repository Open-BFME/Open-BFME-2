// Target facts (BFME 2 1.06; code addresses are RVAs, tables are VAs): the HashableClass constructor 0x000EF9C2 zeros dword +4, stores table VA 0x00BCEF94 at +0 and returns this; the destructor 0x000EF9CF only restores that table, and the deleting destructor 0x000EF9D6 stores it, then frees through operator delete 0x0002FD60 when flag bit 0 is set. The table holds 0x000EF9D6 and __purecall 0x0003B810, so Get_Key is pure slot 1; VA 0x00BCEF90 holds no code address and VA 0x00BCEF9C starts another table (deleting destructor 0x000EFA0E). HashTableClass::Add 0x00613C60 calls slot 1 for the key and links the entry through +4. W3DShadowGeometry's constructor 0x000F1E48 stores this table at +8 and zeros +0xC, with its own data from +0x10, so sizeof is 8. Unwind code 0x007645D7 jumps to the destructor 0x000EF9CF out of line.
// HashTableClass's constructor 0x00613C20 stores the size at +0, allocates size*4 bytes through operator new 0x0002FDA0 into +4 and clears them, as Reset 0x00613BA0 does; the destructor 0x00613B90 frees +4 through 0x0002FD60 and stores no table, so the class is nonvirtual. 0x000F0AF7 pushes 8 before each operator new and calls the constructor at 0x000F0B21 and 0x000F0B49, so sizeof is 8. The ledger names Hash 0x00613BD0 as private and Add, Remove 0x00613CA0, Find 0x00613D10 and the nonvirtual scalar deleting destructor 0x000F0B65 as public.
// Donor facts: Zero Hour GeneralsMD WWLib/hash.h names both classes, NextHash, Get_Key, HashTableSize, HashTable and the methods, and spells the inline constructor and destructor, the private link and the friend declarations kept here.

#ifndef BFME2_WWLIB_HASHABLECLASS_H
#define BFME2_WWLIB_HASHABLECLASS_H

class HashTableIteratorClass;

class HashableClass
{
public:
    HashableClass(void) : NextHash(0) {}
    virtual ~HashableClass(void) {}

    virtual const char *Get_Key(void) = 0;

private:
    HashableClass *NextHash;
    friend class HashTableClass;
    friend class HashTableIteratorClass;
};

class HashTableClass
{
public:
    HashTableClass(int size);
    ~HashTableClass(void);

    void Reset(void);
    void Add(HashableClass *entry);
    bool Remove(HashableClass *entry);

    HashableClass *Find(const char *key);

private:
    int HashTableSize;
    HashableClass **HashTable;

    int Hash(const char *key);

    friend class HashTableIteratorClass;
};

#endif
