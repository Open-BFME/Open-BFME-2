// cl: /EHsc /MD
// ??1Rva00575EEA@@UAE@XZ @0x00575EEA 78B. Destructor unregistering a two-base
// listener from its parent holder through the rowed erase 0x002B7250.
// Evidence: deleting-dtor caller at 0x005760D0 calls this then operator delete;
// sibling of 0x00575E4E (same shape same base restore 0x0086E60C); retail sets
// two vtables calls parent+8 erase with second base as arg then restores bases.
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
struct Parent00575EEA {
    char pad[8];
    Rva005A0B4CList holder;
};
class Rva00575EEABase1 {
public:
    Rva00575EEABase1(int value) : m_x4(value) {}
    virtual ~Rva00575EEABase1() {}
    int m_x4;
};
class Rva00575EEABase2 {
public:
    Rva00575EEABase2() {}
    virtual ~Rva00575EEABase2() {}
};
class Rva00575EEA : public Rva00575EEABase1, public Rva00575EEABase2 {
public:
    Rva00575EEA(int value, Parent00575EEA *parent);
    virtual ~Rva00575EEA();
private:
    Parent00575EEA *m_parentC;
};
Rva00575EEA::~Rva00575EEA()
{
    m_parentC->holder.rva002B7250((CreateAHeroData *)(Rva00575EEABase2 *)this);
}

// Native 005761C6..0057621A is the constructor of the same class: its
// final two vptrs agree with the rowed destructor and its unwind restores
// both bases. The int is at +4; parent +0C and its list +8 are read again
// by that destructor. The application identity remains unknown. The
// matched 0057605D sibling supplies the compiler shape, not these layouts.
Rva00575EEA::Rva00575EEA(int value, Parent00575EEA *parent)
    : Rva00575EEABase1(value), m_parentC(parent)
{
    parent->holder.append((Rva002BA8F1Listener *)static_cast<Rva00575EEABase2 *>(this));
}
