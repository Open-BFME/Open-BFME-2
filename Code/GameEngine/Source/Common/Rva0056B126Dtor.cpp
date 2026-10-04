// cl: /O1 /EHsc /MD
// ??1Rva0056B126@@UAE@XZ, RVA 0x0056B126, 90 bytes.
// Dtor with three vptrs unregistering via rowed erase 0x002B7250 then base dtor 0x0056AC26.
// Evidence: caller at 0x0056B3D9 is deleting dtor; sibling shape of 0x0056B0BF with holder at parent+4.
class CreateAHeroData;
class Rva002B7250 {
public:
    void rva002B7250(CreateAHeroData *v);
};
struct Parent0056B126 {
    char pad[4];
    Rva002B7250 holder;
};
class Rva0056AC26 {
public:
    virtual ~Rva0056AC26();
private:
    char m_pad04[4];
};
class __declspec(novtable) Rva0056B126B1 {
public:
    virtual ~Rva0056B126B1() {}
    int m_a8;
    int m_bC;
};
class Rva0056B126B2 {
public:
    Rva0056B126B2() {}
    virtual ~Rva0056B126B2() {}
};
class Rva0056B126 : public Rva0056AC26, public Rva0056B126B1, public Rva0056B126B2 {
public:
    virtual ~Rva0056B126();
private:
    Parent0056B126 *m_parent18;
};
Rva0056B126::~Rva0056B126()
{
    m_parent18->holder.rva002B7250((CreateAHeroData *)(Rva0056B126B2 *)this);
}
