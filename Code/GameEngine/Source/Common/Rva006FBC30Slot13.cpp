// cl: /MD
// ?rva006FBC30@Rva006FBC90Owner@@UAEXXZ @0x006FBC30 45B
// Evidence: vtable slot 13 (0x34) of 0x008ED880 (Rva006FBC90Owner dtor class);
// same mark triple as 0x0070DF80 (m_ctor +0x1C get/setGCMark/slot13 CALL) then
// tail-jmp to rowed forwarder 0x006DCC00; chain from 0x006DCC00 landing.
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

class Rva006FBC90Owner {
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
    virtual void rva006FBC30();
};

void Rva006FBC90Owner::rva006FBC30()
{
    if (m_ctor) {
        if (!static_cast<unsigned char>(((const Rva006DBB40ShrAndField *)m_ctor)->get())) {
            m_ctor->setGCMark(true);
            m_ctor->unused13();
        }
    }
    ((Rva006D6360 *)this)->Rva006D6360::rva006DCC00();
}
