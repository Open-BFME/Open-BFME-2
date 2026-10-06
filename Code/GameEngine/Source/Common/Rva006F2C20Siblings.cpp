// cl: /MD
// ?rva006F2C20@Rva006F2C20@@UAEXXZ @0x006F2C20 45B
// Recovered from the ?rva0070DF80@Rva006DE2B0@@ recipe at 0x0070DF80. Same
// operand-masked shape: call the +0 object's forwarder, then if the AptRef at
// +0x20 is set and not already marked, setGCMark(true) and tail-jump through
// vtable slot 0x34. Only the first forwarder call (a thunk of the rowed
// Rva006D6360::rva006DCC00 at 0x006DCC00) and the member offset (+0x20 here,
// +0x1C in the template) differ; get/setGCMark and slot 0x34 are shared.
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

class Rva006F2C20 {
    char m_pad[0x1c];
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
    virtual void rva006F2C20();
};

void Rva006F2C20::rva006F2C20()
{
    ((Rva006D6360 *)this)->rva006DCC00();
    if (!m_ctor)
        return;
    if (static_cast<unsigned char>(((const Rva006DBB40ShrAndField *)m_ctor)->get()))
        return;
    m_ctor->setGCMark(true);
    m_ctor->unused13();
}
