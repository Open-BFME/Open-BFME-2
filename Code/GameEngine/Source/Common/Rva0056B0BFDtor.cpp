// cl: /EHsc /MD
// ??1Rva0056B0BF@@UAE@XZ @0x0056B0BF 90B. Dtor with three vptrs unregistering
// via rowed erase 0x002B7250 then base dtor 0x0056AC26.
// Evidence: caller at 0x0056B359 is deleting dtor; sibling shape of 0x00575E4E
// with extra base; [edi] restore is 0x007ED658 same family as prior Base2.
class CreateAHeroData;
class Rva002B7250 {
public:
    void rva002B7250(CreateAHeroData *v);
};
struct Parent0056B0BF {
    char pad[8];
    Rva002B7250 holder;
};
class Rva0056AC26 {
public:
    virtual ~Rva0056AC26();
private:
    char m_pad04[4];
};
class __declspec(novtable) Rva0056B0BFB1 {
public:
    virtual ~Rva0056B0BFB1() {}
    int m_a8;
    int m_bC;
};
class Rva0056B0BFB2 {
public:
    Rva0056B0BFB2() {}
    virtual ~Rva0056B0BFB2() {}
};
class Rva0056B0BF : public Rva0056AC26, public Rva0056B0BFB1, public Rva0056B0BFB2 {
public:
    virtual ~Rva0056B0BF();
private:
    Parent0056B0BF *m_parent18;
};
Rva0056B0BF::~Rva0056B0BF()
{
    m_parent18->holder.rva002B7250((CreateAHeroData *)(Rva0056B0BFB2 *)this);
}
