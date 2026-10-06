// cl: /DNDEBUG /MD
// ?Rva0031455ELink@Rva0031455E@@QAEXPAV1@@Z @ 0x0031455E (35B).
// Honest address-derived list link: virtual slot 2 then insert this into list headed at arg plus 0x1DC with next at plus 0x04 and owner at plus 0x08.
// Evidence: neighbors 0x0031450A plus 0x003145F0 plus twin unlink 0x00314581 sharing plus 0x04 plus 0x08 plus 0x1DC layout.
class Rva0031455E
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    ~Rva0031455E();
    void Rva0031455ELink(Rva0031455E *arg);
    void Rva00314581Unlink();
private:
    void *m_04;
    void *m_08;
    char m_pad[0x1DC - 0x0C];
    void *m_1DC;
};
void Rva0031455E::Rva0031455ELink(Rva0031455E *arg)
{
    v2();
    if (arg) {
        m_08 = arg;
        m_04 = arg->m_1DC;
        arg->m_1DC = this;
    }
}
// ?Rva00314581Unlink@Rva0031455E@@QAEXXZ @ 0x00314581 (21B).
// Honest address-derived list unlink: if owner at plus 0x08 then move next at plus 0x04 into owner plus 0x1DC and clear plus 0x08.
// Evidence: twin link 0x0031455E sharing plus 0x04 plus 0x08 plus 0x1DC layout.
void Rva0031455E::Rva00314581Unlink()
{
    Rva0031455E *owner = (Rva0031455E *)m_08;
    if (owner) {
        owner->m_1DC = m_04;
        m_08 = 0;
    }
}

Rva0031455E::~Rva0031455E()
{
    Rva00314581Unlink();
}

void Rva0031455EDelete(Rva0031455E *p) { delete p; }

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?v0@Rva0031455E@@UAEXXZ=??_GRva0031455E@@QAEPAXI@Z")
#pragma comment(linker, "/alternatename:?v1@Rva0031455E@@UAEXXZ=?Rva0031455ELink@Rva0031455E@@QAEXPAV1@@Z")
#pragma comment(linker, "/alternatename:?v2@Rva0031455E@@UAEXXZ=?Rva00314581Unlink@Rva0031455E@@QAEXXZ")
