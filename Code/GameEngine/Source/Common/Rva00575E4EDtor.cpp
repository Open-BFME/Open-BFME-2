// cl: /EHsc /MD
// ??1Rva00575E4E@@UAE@XZ @0x00575E4E 78B. Destructor unregistering a two-base
// listener from its parent holder through the rowed erase 0x002B7250.
// Evidence: deleting-dtor caller at 0x00576041 calls this then operator delete;
// retail sets two vtables, calls parent+8 erase with second base as arg,
// then sets two vtables (base restores) with no further calls.
class CreateAHeroData;
class Rva002B7250 {
public:
    void rva002B7250(CreateAHeroData *v);
};
struct Rva002BA8F1Listener;
class Rva005A0B4CList : public Rva002B7250 {
public:
    void append(Rva002BA8F1Listener *listener);
};
struct Parent00575E4E {
    char pad[8];
    Rva005A0B4CList holder;
};
class Rva00575E4EBase1 {
public:
    Rva00575E4EBase1(int value) : m_x4(value) {}
    virtual ~Rva00575E4EBase1() {}
    int m_x4;
};
class Rva00575E4EBase2 {
public:
    Rva00575E4EBase2() {}
    virtual ~Rva00575E4EBase2() {}
};
class Rva00575E4E : public Rva00575E4EBase1, public Rva00575E4EBase2 {
public:
    Rva00575E4E(int value, Parent00575E4E *parent);
    virtual ~Rva00575E4E();
private:
    Parent00575E4E *m_parentC;
};
Rva00575E4E::~Rva00575E4E()
{
    m_parentC->holder.rva002B7250((CreateAHeroData *)(Rva00575E4EBase2 *)this);
}

// Native 00576172..005761C6 constructor has the two final vptrs that
// the rowed destructor restores at +0 and +8. Its unwind also destroys
// both bases. The int at +4 and parent at +0C are target evidence; the
// parent list at +8 is shared with the destructor. Matched 005761C6 is
// the compiler-shape lead; the application class identity is unknown.
Rva00575E4E::Rva00575E4E(int value, Parent00575E4E *parent)
    : Rva00575E4EBase1(value), m_parentC(parent)
{
    parent->holder.append((Rva002BA8F1Listener *)static_cast<Rva00575E4EBase2 *>(this));
}
