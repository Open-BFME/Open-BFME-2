// cl: /Ireference/shims/bfme2_ascii /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00289ABD@@UAE@XZ, retail 0x00289D7A, 239 bytes.
// Dtor: vptr, delete m_rva20 Record, delete the record-pointer vector's elements + erase, slot9 cleanup, delete hash tables, tree dtor, free vec storage, base dtor.
// Evidence: pin ??1Rva00289ABD; callee rows 0x00288BF9 0x0002FD60 0x0031BD55 0x00289180 0x002895BF 0x00288B51 0x00030830 0x001B4E74; caller 0x00289E99 deleting dtor; layout mirrors ctor Rva00289ABDCtor.cpp.
#include <stdlib.h>
#include "ascii_string.h"
#include <vector>

#include <cstddef>

struct Rva00288BF9Record
{
    ~Rva00288BF9Record();
};

class Rva00289371HashTable
{
private:
    struct Node;
public:
    void clear(); // 0x00289371
    ~Rva00289371HashTable(); // 0x002895BF
private:
    void deleteNode(Node *node); // 0x00289164
    char m_functors[4];
    Node **m_bucketsBegin;
    Node **m_bucketsEnd;
    Node **m_bucketsCapacity;
    unsigned int m_numElements;
};

class Rva0028881C
{
public:
	~Rva0028881C();
	void rva002889BB();
private:
	void *m_00Head;
	int m_04Flag;
};

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class ExperienceLevelSystem : public SubsystemInterface
{
public:
    ~ExperienceLevelSystem();
    virtual void rva00289180();
    Rva00289371HashTable *m_hash0C;
    Rva00289371HashTable *m_hash10;
    _STL::vector<Rva00288BF9Record *> m_vec14;
    Rva00288BF9Record *m_rva20;
    unsigned char m_b24;
    Rva0028881C m_map28;
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline ExperienceLevelSystem::~ExperienceLevelSystem()
{
    Rva00288BF9Record *p = m_rva20;
    if (p != 0) {
        p->~Rva00288BF9Record();
        ::operator delete(p);
    }
    m_rva20 = 0;
    _STL::vector<Rva00288BF9Record *> &v = m_vec14;
    for (_STL::vector<Rva00288BF9Record *>::size_type i = 0; i < m_vec14.size(); ++i) {
        Rva00288BF9Record *q = v[i];
        if (q != 0) {
            q->~Rva00288BF9Record();
            ::operator delete(q);
        }
    }
    v.erase(v.begin(), v.end());
    rva00289180();
    Rva00289371HashTable *h0 = m_hash0C;
    if (h0 != 0) {
        h0->~Rva00289371HashTable();
        ::operator delete(h0);
    }
    m_hash0C = 0;
    Rva00289371HashTable *h1 = m_hash10;
    if (h1 != 0) {
        h1->~Rva00289371HashTable();
        ::operator delete(h1);
    }
    m_hash10 = 0;
}

// ?bfmeAnchorRva00289ABDDtor absent-from-retail
void bfmeAnchorRva00289ABDDtor(ExperienceLevelSystem *p)
{
	p->ExperienceLevelSystem::~ExperienceLevelSystem();
}
