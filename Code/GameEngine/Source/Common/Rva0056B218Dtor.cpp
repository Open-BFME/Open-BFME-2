// cl: /O1 /EHsc /MD
// ??1Rva0056B218@@UAE@XZ @0x0056B218 118B. Dtor unregistering from two nullable
// parent holders via rowed erase 0x002B7250 then base dtor 0x0056AC26.
// Evidence: deleting-dtor caller at 0x0056B47F; extends sibling 0x0056B0BF
// with a second holder at +0x1C; both nulled after erase.
class CreateAHeroData;
class Rva002B7250 {
public:
    void rva002B7250(CreateAHeroData *v);
};
struct Parent0056B218 {
    char pad[8];
    Rva002B7250 holder;
};
class Rva0056AC26 {
public:
    virtual ~Rva0056AC26();
private:
    char m_pad04[4];
};
class __declspec(novtable) Rva0056B218B1 {
public:
    virtual ~Rva0056B218B1() {}
    virtual void b1Anchor();
    int m_a8;
    int m_bC;
};
class Rva0056B218B2 {
public:
    Rva0056B218B2() {}
    virtual ~Rva0056B218B2() {}
};
class Rva0056B218 : public Rva0056AC26, public Rva0056B218B1, public Rva0056B218B2 {
public:
    virtual ~Rva0056B218();
private:
    Parent0056B218 *m_parent18;
    Parent0056B218 *m_parent1C;
};
Rva0056B218::~Rva0056B218()
{
    if (m_parent18 != 0) {
        m_parent18->holder.rva002B7250((CreateAHeroData *)(Rva0056B218B2 *)this);
        m_parent18 = 0;
    }
    if (m_parent1C != 0) {
        m_parent1C->holder.rva002B7250((CreateAHeroData *)(Rva0056B218B2 *)this);
        m_parent1C = 0;
    }
}
// ?b1Anchor@Rva0056B218B1@@UAEXXZ present-unmatched
void Rva0056B218B1::b1Anchor()
{
}
