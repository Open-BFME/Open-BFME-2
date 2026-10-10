// cl: /O1 /DNDEBUG /MD /EHsc
// ??1LookupTablePostEffect@@UAE@XZ @ 0x00111B9A 79B: dtor installs vtable 0x00BCFAC8,
// calls row 0x00116496 then Field08 inline release at +0x08 via dec and virtual slot0
// then base dtor at 0x0011647B. Prev ctor proves class and vtable. Next slot3 proves +0x08.
class Rva00116496
{
public:
    void rva00116496();
};

class Rva0011647BDwordImmSetter
{
public:
    void apply();
};

struct RefCounted
{
    virtual void Release();
    int m_ref;
};

struct Field08
{
    RefCounted *m_ptr;
// ??1Field08@@QAE@XZ present-unmatched
    ~Field08()
    {
        RefCounted *p = m_ptr;
        if (p && --p->m_ref == 0)
            p->Release();
    }
};

// Base: the class whose empty virtual dtor 0x0011647B (row ??1Rva001164B6@@UAE@XZ)
// restores vtable 0x00BCFB24 (deleting dtor 0x001164B6).
class Rva001164B6
{
public:
    Rva001164B6();
    virtual ~Rva001164B6();
private:
    int m_04;
};

class LookupTablePostEffect : public Rva001164B6
{
public:
    virtual ~LookupTablePostEffect();
private:
    Field08 m_08;
};

LookupTablePostEffect::~LookupTablePostEffect()
{
    ((Rva00116496 *)this)->rva00116496();
}
