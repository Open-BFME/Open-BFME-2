// cl: /MD
// ?rva0070DF80@Rva006DE2B0@@UAEXXZ @0x0070DF80 45B
// Evidence: vtable slot 13 (0x34) of 0x008EB150 (Rva006DE2B0 dtor class);
// calls rowed forwarder 0x006DCC00 (Rva006D6360::rva006DCC00 add 8 to mark);
// m_ctor at +0x1C (pad 0x18 like Rva0070DF60 sibling); get/setGCMark/unused13
// pattern matches AptNativeHashMark.cpp triple-mark with tail-jmp to slot 0x34.
class Rva006DBB40ShrAndField {
public:
    int get() const;
};

class AptValue {
public:
    virtual void AddRef();
    virtual void Release();
    virtual void unused2();
    virtual void unused3();
    virtual void unused4();
    virtual void unused5();
    virtual void unused6();
    virtual void unused7();
    virtual void unused8();
    virtual void unused9();
    virtual void unused10();
    virtual void unused11();
    virtual void unused12();
    virtual void unused13();
    void setGCMark(bool value);
};

class Rva006D6360 {
public:
    void rva006DCC00();
};

class Rva006DE2B0 {
    char m_pad[0x18];
    AptValue *m_ctor;
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual void f10();
    virtual void f11();
    virtual void f12();
public:
    virtual void rva0070DF80();
};

void Rva006DE2B0::rva0070DF80()
{
    ((Rva006D6360 *)this)->rva006DCC00();
    if (!m_ctor)
        return;
    if (static_cast<unsigned char>(((const Rva006DBB40ShrAndField *)m_ctor)->get()))
        return;
    m_ctor->setGCMark(true);
    m_ctor->unused13();
}
