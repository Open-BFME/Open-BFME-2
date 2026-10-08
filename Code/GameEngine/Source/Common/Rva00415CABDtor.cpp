// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// Native 0x00415CAB..0x00415D33, 136 bytes. The deleting wrapper at
// 0x00415E6E and vtable 0x00C3A288 establish this address-derived owner.
// Target evidence: SubsystemInterface teardown; table at +0x0C; two-word
// iterator; node-owned pointer at +8; Rva00415AE0 value destructor.
// WindowVideoManager::~WindowVideoManager is the matched algorithm lead,
// not evidence that either the owner or its values are video objects.
// The table's clear and destructor are independently rowed native providers.

typedef bool Bool;
#include "subsystem_interface.h"

class Rva00415AE0
{
public:
    ~Rva00415AE0();
};

class Rva000411084
{
public:
    void *next();
    void *m_current;
    void *m_owner;
};

class Rva000427195
{
public:
    void *first(Rva000411084 *iterator);
    void rva003A2A41();
};

class Rva00415366
{
public:
    ~Rva00415366();
private:
    void *m_unused00;
    void **m_beginBuckets;
    void **m_endBuckets;
    void **m_storageEnd;
    unsigned int m_numElements;
};

struct Rva00415CABNode
{
    Rva00415CABNode *next;
    unsigned int key;
    Rva00415AE0 *value;
};

class Rva00415CAB : public SubsystemInterface
{
public:
    virtual ~Rva00415CAB();
private:
    Rva00415366 m_table;
};

Rva00415CAB::~Rva00415CAB()
{
    Rva000411084 iterator;
    Rva000427195 *table = reinterpret_cast<Rva000427195 *>(&m_table);
    table->first(&iterator);
    while (iterator.m_current != 0)
    {
        Rva00415AE0 *value =
            static_cast<Rva00415CABNode *>(iterator.m_current)->value;
        if (value != 0)
            delete value;
        iterator.next();
    }
    table->rva003A2A41();
}
