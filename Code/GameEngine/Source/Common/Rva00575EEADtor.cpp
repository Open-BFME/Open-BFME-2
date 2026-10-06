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
struct Parent00575EEA {
    char pad[8];
    Rva002B7250 holder;
};
class Rva00575EEABase1 {
public:
    Rva00575EEABase1() {}
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
    virtual ~Rva00575EEA();
private:
    Parent00575EEA *m_parentC;
};
Rva00575EEA::~Rva00575EEA()
{
    m_parentC->holder.rva002B7250((CreateAHeroData *)(Rva00575EEABase2 *)this);
}
