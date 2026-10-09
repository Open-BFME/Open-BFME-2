// cl: /O1 /G7 /arch:SSE /MD
// Native twins5CCBB0/5CCBC0 load receiver4 then listener4, null-guard and
// invoke the compiler's vcall thunks for slots14/18, not a direct vcall.
class Rva005CCBB0Listener {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10();
    virtual void slot14(); virtual void slot18();
};
struct Rva005CCBB0Holder { int pad; Rva005CCBB0Listener *listener; };
class Rva005CCBB0 {
public:
    void rva005CCBB0();
    void rva005CCBC0();
    int pad00;
    Rva005CCBB0Holder *holder;
};
void Rva005CCBB0::rva005CCBB0()
{
    Rva005CCBB0Listener *p = holder->listener;
    if (p) (p->*&Rva005CCBB0Listener::slot14)();
}
void Rva005CCBB0::rva005CCBC0()
{
    Rva005CCBB0Listener *p = holder->listener;
    if (p) (p->*&Rva005CCBB0Listener::slot18)();
}
