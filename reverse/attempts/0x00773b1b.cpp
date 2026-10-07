// Unwind@00b73b1b
// partial score=1.0 date=2026-10-07
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

struct TargetRef00217D4C
{
    virtual void *destroy(unsigned);
    int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

struct TreeHintRef00217D4C
{
    TargetRef00217D4C *m_ptr;
    TreeHintRef00217D4C() : m_ptr(0) {}
    TreeHintRef00217D4C(TargetRef00217D4C *v) : m_ptr(v)
    {
        if (m_ptr) ++m_ptr->references;
    }
    TreeHintRef00217D4C(const TreeHintRef00217D4C &v) : m_ptr(v.m_ptr)
    {
        if (m_ptr) ++m_ptr->references;
    }
    ~TreeHintRef00217D4C()
    {
        if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
    }
};

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

class Rva002833A3C5Owner
{
public:
    void rva002833A3(void *, void *key);
    void rva002833C5(void *, void *key);
private:
    char pad[0x3c];
    Rva00283033 *m_map3c;
    Rva00283033 *m_map40;
};
void Rva002833A3C5Owner::rva002833A3(void *, void *key)
{
    m_map40->rva00283033(key);
}
void Rva002833A3C5Owner::rva002833C5(void *, void *key)
{
    m_map3c->rva00283033(key);
}
