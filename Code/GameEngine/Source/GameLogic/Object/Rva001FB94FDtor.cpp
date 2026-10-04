// cl: /O1 /MD
// ??1Rva001FB94F@@QAE@XZ @0x001FB94F 59B
// Non-virtual dtor with EH prolog: second base Sub005CD540Outer at +4 then
// inlined first-base cleanup calling rowed rva001F4206. Evidence: null-checked
// this+4 adjustment proves second base (BigChainBaseDtors donor comment);
// callees rowed 0x001FA95A SubOuter and 0x001F4206 rva001F4206; caller
// 0x001FBAEE becomes ready; neighbours Rva001FA584Ctor/Rva001FB912Init /O1 /MD;
// honest Rva names; probe p2/p3 byte-exact.
class Rva001F4206
{
public:
    void rva001F4206();
};
class Sub005CD540Outer
{
public:
    ~Sub005CD540Outer();
};
class Rva001FB94FFirst
{
public:
    int m_00;
    ~Rva001FB94FFirst();
};
// ??1Rva001FB94FFirst@@QAE@XZ present-unmatched
inline Rva001FB94FFirst::~Rva001FB94FFirst()
{
    ((Rva001F4206 *)this)->rva001F4206();
}
class Rva001FB94F : public Rva001FB94FFirst, public Sub005CD540Outer
{
public:
    ~Rva001FB94F();
};
Rva001FB94F::~Rva001FB94F()
{
}
class Rva001FBAEE : public Rva001FB94FFirst, public Rva001FB94F
{
public:
    ~Rva001FBAEE();
};
Rva001FBAEE::~Rva001FBAEE()
{
}
class Rva001FBCA1 : public Rva001FB94FFirst, public Rva001FBAEE
{
public:
    ~Rva001FBCA1();
};
Rva001FBCA1::~Rva001FBCA1()
{
}
class Rva001FC0B6 : public Rva001FB94FFirst, public Rva001FBCA1
{
public:
    ~Rva001FC0B6();
};
Rva001FC0B6::~Rva001FC0B6()
{
}
class Rva001F4C67
{
public:
    virtual ~Rva001F4C67();
};
struct RefObj
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    int m_ref;
};
class Rva001FC0F1 : public Rva001F4C67
{
public:
    char m_pad[0x88];
    RefObj *m_8c;
    RefObj *m_90;
    Rva001FC0B6 m_94;
    virtual ~Rva001FC0F1();
};
Rva001FC0F1::~Rva001FC0F1()
{
    if (m_8c) {
        m_8c->v16();
        RefObj *p = m_8c;
        if (p) {
            if (--p->m_ref == 0)
                p->v0();
            m_8c = 0;
        }
    }
    RefObj *q = m_90;
    if (q) {
        if (--q->m_ref == 0)
            q->v0();
        m_90 = 0;
    }
}
