// cl: /EHsc /MD
// ??1Rva0056B2DD@@UAE@XZ @0x0056B2DD 113B. Dtor unregistering via rowed erase
// 0x002B7250, conditional rowed call 0x003EE966 through TheLivingWorldManager+0x268,
// then base dtor 0x0056AC26. Evidence: deleting-dtor caller at 0x0056B49B;
// extends sibling 0x0056B0BF with the TheLivingWorldManager guard and int member +0x1C.
class CreateAHeroData;
class Rva002B7250 {
public:
    void rva002B7250(CreateAHeroData *v);
};
struct Parent0056B2DD {
    char pad[8];
    Rva002B7250 holder;
};
class Rva0056AC26 {
public:
    virtual ~Rva0056AC26();
private:
    char m_pad04[4];
};
class __declspec(novtable) Rva0056B2DDB1 {
public:
    virtual ~Rva0056B2DDB1() {}
    int m_a8;
    int m_bC;
};
class Rva0056B2DDB2 {
public:
    Rva0056B2DDB2() {}
    virtual ~Rva0056B2DDB2() {}
};
class Rva003EE966 {
public:
    void rva003EE966(int v);
};
class Rva0021294A {
public:
    char m_pad[0x268];
    Rva003EE966 *m_268;
};
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;
class Rva0056B2DD : public Rva0056AC26, public Rva0056B2DDB1, public Rva0056B2DDB2 {
public:
    virtual ~Rva0056B2DD();
private:
    Parent0056B2DD *m_parent18;
    int m_x1C;
};
Rva0056B2DD::~Rva0056B2DD()
{
    m_parent18->holder.rva002B7250((CreateAHeroData *)(Rva0056B2DDB2 *)this);
    Rva003EE966 *p = ((Rva0021294A *)TheLivingWorldManager)->m_268;
    if (p != 0)
        p->rva003EE966(m_x1C);
}
