// cl: /DNDEBUG /MD /EHsc /O1 /G7
// Native boundaries: removal-by-index 0x0028292B..0x002829BD (146B),
// pointer-key search 0x00283033..0x00283081 (78B), and adjacent callers
// 0x002833A3/0x002833C5 (34B each). Names remain address-derived.
// The old void(out,key) pin at 0x00283033 mistook the hidden result slot for
// an explicit argument. The callee returns a four-byte nontrivial handle;
// both callers destroy that temporary through the rowed fastcall 0x0007DEEF.
// The indexed helper's third stack slot is the index: hidden result, unused
// explicit owner pointer, index. Its ECX receiver contains a listener list
// at +0 and an eight-byte-entry vector at +0x14. Each entry's second word is
// the pointer retained at referent +4. The first word's meaning is unknown.
// Before/after callbacks are member-function pointers to virtual slots 3/2
// (retail vcall thunks 0x005CB265/0x005CC208), not string/data addresses.
// The erase calls the rowed 0x002821CF, whose eight-byte record copy and dtor
// are independently verified. The return copy retains once more and the
// local handle releases on both the normal and exception paths. No original
// application class name or unused virtual-slot ABI is claimed.

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
inline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
    if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
}


class Rva00281A33Listener
{
public:
    virtual void notify(void *, int);
    virtual void unknownSlot1();
    virtual void after(void *, int);
    virtual void before(void *, int);
};
class Rva00281A33List
{
public:
    void forEach(void (Rva00281A33Listener::*)(void *, int), void *, int);
private:
    char data[16];
};
struct Rva002821CFElem { char bytes[8]; };
class Rva002821CF
{
public:
    Rva002821CFElem *erase(Rva002821CFElem *);
};
struct Rva0028292BEntry
{
    char unknown00[4];
    TargetRef00217D4C *second;
};
struct Rva0028292BVectorView
{
    Rva0028292BEntry *start, *finish, *cap;
    Rva0028292BEntry *begin() { return start; }
    Rva0028292BEntry *end() { return finish; }
    unsigned size() const { return finish - start; }
    Rva0028292BEntry &operator[](unsigned i) { return *(begin() + i); }
};
class Rva00283033
{
public:
    TreeHintRef00217D4C rva00283033(void *key);
    TreeHintRef00217D4C rva0028292B(void *, unsigned);
private:
    Rva00281A33List listeners;
    unsigned unknown;
    Rva0028292BVectorView vector;
};

TreeHintRef00217D4C Rva00283033::rva0028292B(void *, unsigned index)
{
    TreeHintRef00217D4C value(vector[index].second);
    listeners.forEach(&Rva00281A33Listener::before, this, (int)value.m_ptr);
    ((Rva002821CF *)&vector)->erase((Rva002821CFElem *)(vector.begin() + index));
    listeners.forEach(&Rva00281A33Listener::after, this, (int)value.m_ptr);
    return value;
}

TreeHintRef00217D4C Rva00283033::rva00283033(void *key)
{
    unsigned i = 0;
    bool found = false;
    for (; i < vector.size(); ++i)
    {
        if (vector[i].second == key)
        {
            found = true;
            break;
        }
    }
    if (!found) return 0;
    return rva0028292B(this, i);
}

// Native TerrainLogic listener tables BC5848/BC5838 slot3 bind these
// existing complete34B bodies. Structural view names; entry-relative fields.
// Root tables BC6F34: empty RET4 followed by three pure callbacks.
class WaterHandle;
class TerrainLogicListenerRootA {
public:
 virtual void vslot0(int);
 virtual void vslot1(int, WaterHandle *) = 0;
 virtual void vslot2(void *, void *) = 0;
 virtual void vslot3(void *, void *) = 0;
 ~TerrainLogicListenerRootA() {}
};
class TerrainLogicListenerA : public TerrainLogicListenerRootA {
public:
 virtual void vslot1(int, WaterHandle *);
 virtual void vslot3(void *, void *);
 ~TerrainLogicListenerA();
};
class TerrainLogicListenerRootB {
public:
 virtual void vslot0(int);
 virtual void vslot1(int, WaterHandle *) = 0;
 virtual void vslot2(void *, void *) = 0;
 virtual void vslot3(void *, void *) = 0;
 ~TerrainLogicListenerRootB() {}
};
class TerrainLogicListenerB : public TerrainLogicListenerRootB {
public:
 virtual void vslot1(int, WaterHandle *);
 virtual void vslot3(void *, void *);
 ~TerrainLogicListenerB();
};

struct TerrainListenerRemovalFields
{
 char pad[0x3c];
 Rva00283033 *m_map3c;
 Rva00283033 *m_map40;
};
void TerrainLogicListenerA::vslot3(void *, void *key)
{
    reinterpret_cast<TerrainListenerRemovalFields *>(this)->m_map40->rva00283033(key);
}
void TerrainLogicListenerB::vslot3(void *, void *key)
{
    reinterpret_cast<TerrainListenerRemovalFields *>(this)->m_map3c->rva00283033(key);
}
