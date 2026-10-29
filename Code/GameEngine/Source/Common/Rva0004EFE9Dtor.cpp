// cl: /O1 /MD /EHsc
// stlport
// Native 0004EFE9..0004F037, RET0. The rowed deleting destructor at
// 0004F7D8 establishes the address-derived owner. Target bytes set its vptr,
// invoke virtual slot 3 on the +20 object, release that reference, and call
// the base destructor at 004E84A4. The original class identity is unknown.
class Rva00539926Base
{
public:
    virtual ~Rva00539926Base();
};

class RadarEventRef
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    void release();
};

struct Rva0004EFE9Reference
{
    RadarEventRef *value;
    ~Rva0004EFE9Reference()
    {
        if (value)
            value->release();
    }
};

// Just enough of STLport's list<Snapshot *> for the rowed erase 0x00438539:
// the iterator is non-POD, so it comes back through a hidden pointer.
class Snapshot;
#include <list>

namespace _STL
{
    // Bind the element erase to the rowed 0x00438539 worker.
    template <> _List_iterator<Snapshot *, _Nonconst_traits<Snapshot *> >
    list<Snapshot *, allocator<Snapshot *> >::erase(_List_iterator<Snapshot *, _Nonconst_traits<Snapshot *> > position);
}
typedef _STL::list<Snapshot *, _STL::allocator<Snapshot *> > Rva0004F7F4SnapshotList;

struct Rva0004F7F4Owner
{
    char m_unmodelled00[0x1500];
    Rva0004F7F4SnapshotList m_snapshots; // +1500
};

class Rva004EFE9 : public Rva00539926Base
{
public:
    virtual ~Rva004EFE9();
    virtual void rva0004F7F4();
private:
    char m_unmodelled04[0x08];
    Rva0004F7F4Owner *m_owner; // +0C
    Rva0004F7F4SnapshotList::iterator m_position; // +10
    char m_unmodelled14[0x0c];
    Rva0004EFE9Reference m_reference; // +20
};

Rva004EFE9::~Rva004EFE9()
{
    void (RadarEventRef::*callback)() = &RadarEventRef::slot3;
    (m_reference.value->*callback)();
}

// Native 0004F7F4..0004F82B, slot 1 after the deleting destructor: leaves
// the owner's +1500 snapshot list (when there is an owner) and destroys
// itself through the global delete of a virtual-destructor class (slot 0
// with 0, then operator delete).
void Rva004EFE9::rva0004F7F4()
{
    if (m_owner)
        m_owner->m_snapshots.erase(m_position);
    ::delete this;
}
