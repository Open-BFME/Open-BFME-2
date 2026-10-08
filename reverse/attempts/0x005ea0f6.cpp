// ?rva005EA0F6@Rva005EA183@@QAEXXZ
// partial score=1.0 date=2026-10-08
// cl: /DNDEBUG /MD /EHs-c- /O1 /G7 /arch:SSE
class Rva005EA183;
class __declspec(novtable) Rva005EA0F6StateBase
{
public:
    Rva005EA0F6StateBase(Rva005EA183 *owner) : m_owner(owner) {}
    virtual void *slot00(unsigned int flags);
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10(void *,void *);
    virtual void slot14(void *,void *);
    virtual void slot18(void *,void *);
    virtual bool slot1C();
private:
    Rva005EA183 *m_owner;
};
class Rva005EA0F6State : public Rva005EA0F6StateBase
{
public:
    Rva005EA0F6State(Rva005EA183 *owner) : Rva005EA0F6StateBase(owner) {}
    virtual void slot04();
};
class Object { public: virtual void f0(); virtual void f1(); virtual void f2(); };
class Rva00575674 { public: void rva00575674(Object *p); Object *m_ptr; };
class Rva005EA183
{
public: void rva005EA0F6();
private: char m_pad[0x14]; Rva00575674 m_holder;
};
void Rva005EA183::rva005EA0F6()
{
    Rva005EA0F6State *state=new Rva005EA0F6State(this);
    m_holder.rva00575674((Object *)state);
    return m_holder.m_ptr->f1();
}
