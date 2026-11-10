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
#include <hash_map>

// The rowed unsigned-key POD iterator has exactly the native two-word ABI
// and uses the same 0039FD3E bucket provider. Declare its external increment
// so the compiler preserves the target's out-of-line call at 0041F99B.
typedef _STL::hash_map<unsigned int, int>::iterator Rva0041E832PodIterator;
namespace _STL
{
template <> Rva0041E832PodIterator &Rva0041E832PodIterator::operator++();
}

class Rva00415AE0
{
public:
    ~Rva00415AE0();
};

#include "../../Include/GameClient/Rva000411084.h"

#include "../../Include/GameLogic/Rva000427195.h"

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

class Rva0022A809Subsystem : public SubsystemInterface
{
public:
    virtual ~Rva0022A809Subsystem();
private:
    Rva00415366 m_table;
};

Rva0022A809Subsystem::~Rva0022A809Subsystem()
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

// The table clear is the ICF-folded hashtable clear at 0x001DBCDC. Its
// address-named provider row there is Rva004DFC20::clear (the opaque-table
// spelling already rowed in Rva004E013BOwnedResources.cpp); call that name.
#include "../../Include/Common/Rva004DFC20.h"

struct Rva0041F4A7Buckets
{
    ~Rva0041F4A7Buckets();
    void **begin;
    void **end;
    void **storageEnd;
};

class Rva0041F4A7
{
public:
    ~Rva0041F4A7();
private:
    void *unused00;
    Rva0041F4A7Buckets buckets;
    unsigned int count;
};

// The rowed 0041F760 destructor's current name comes from a WorldBuilder
// lead marked wb-name-unverified. Reuse that provider name without promoting
// it to a newly established target identity.
class ArmyDefinition
{
public:
    ~ArmyDefinition();
};

struct Rva0041F94ANode
{
    Rva0041F94ANode *next;
    unsigned int key;
    ArmyDefinition *value;
};

class Rva0041F94A : public SubsystemInterface
{
public:
    virtual ~Rva0041F94A();
private:
    Rva0041F4A7 m_table;
};

// Native 0041F94A..0041F9D2, 136 bytes, vtable 00C3B8C8. Same target-
// supported ownership algorithm, with independently different providers.
Rva0041F94A::~Rva0041F94A()
{
    Rva000411084 iterator;
    reinterpret_cast<Rva000427195 *>(&m_table)->first(&iterator);
    while (iterator.m_current != 0)
    {
        ArmyDefinition *value =
            static_cast<Rva0041F94ANode *>(iterator.m_current)->value;
        if (value != 0)
            delete value;
        ++*reinterpret_cast<Rva0041E832PodIterator *>(&iterator);
    }
    reinterpret_cast<Rva004DFC20 *>(&m_table)->clear();
}

// GameEngine::init's Rva0022BD25Subsystem (ctor 0x0041F913) stores the same
// vtable 0x00C3B8C8, whose slot 0 0x0041F9D2 calls this destructor.
#pragma comment(linker, "/alternatename:??1Rva0022BD25Subsystem@@UAE@XZ=??1Rva0041F94A@@UAE@XZ")
