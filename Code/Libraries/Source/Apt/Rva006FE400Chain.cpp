// cl: /MD
// ?rva006FE400@Rva006FE400@@QAEHPAXPAURva008A4570Owner@@@Z @0x006FE400 42B
// Evidence: chain from 0x0070DFB0 landing; calls virtual slot 7 (0x1C) on this+0x20
// with same args then rowed 0x0070DFB0 on this; test-je shares int return; ret 8.
struct Rva008A4570Owner;

struct Slot7Obj {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual int slot7(void *a1, Rva008A4570Owner *a2);
};

class Rva006D6470Owner {
public:
    virtual int rva0070DFB0(void *a1, Rva008A4570Owner *a2);
};

class Rva006FE400 {
    char m_pad[0x20];
    Slot7Obj *m_p20;
public:
    int rva006FE400(void *a1, Rva008A4570Owner *a2);
};

int Rva006FE400::rva006FE400(void *a1, Rva008A4570Owner *a2)
{
    int r = m_p20->slot7(a1, a2);
    if (r)
        return r;
    return ((Rva006D6470Owner *)this)->Rva006D6470Owner::rva0070DFB0(a1, a2);
}
