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
struct Parent00575E4E {
    char pad[8];
    Rva002B7250 holder;
};
class Rva00575E4EBase1 {
public:
    Rva00575E4EBase1() {}
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
    virtual ~Rva00575E4E();
private:
    Parent00575E4E *m_parentC;
};
Rva00575E4E::~Rva00575E4E()
{
    m_parentC->holder.rva002B7250((CreateAHeroData *)(Rva00575E4EBase2 *)this);
}
