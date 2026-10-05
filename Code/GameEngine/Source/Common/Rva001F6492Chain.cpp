// cl: /O1 /MD /arch:SSE /EHsc
// Forwarding chain 001F6492 .. 001FA7CE (seven 42B bodies) with the
// Rva001F5D0E.cpp shape: null-checked virtual slot 0xc on the pointer at +0
// with (int,int) then the same call on the next link at +4. Next-link callees
// by REL32: 001F6492 -> rowed 001F5D0E; 001F8213 -> 001F6492; 001F8960 ->
// 001F8213; 001F8DE2 -> 001F8960; 001F9424 -> 001F8DE2; 001FA4C6 -> 001F9424;
// 001FA7CE -> 001FA4C6. Original names unknown so address-derived Rva names.
class Rva001F6492Helper {
public:
    virtual ~Rva001F6492Helper();
    virtual void m1();
    virtual void m2();
    virtual void m3(int a, int b);
};
class Rva001F5D0E {
public:
    void rva001F5D0E(int a, int b);
};
class Rva001F6492 {
public:
    void rva001F6492(int a, int b);
private:
    Rva001F6492Helper *m_ptr;
    Rva001F5D0E m_next;
};
void Rva001F6492::rva001F6492(int a, int b)
{
    Rva001F6492Helper *p = m_ptr;
    if (p)
        p->m3(a, b);
    m_next.rva001F5D0E(a, b);
}
class Rva001F8213 {
public:
    void rva001F8213(int a, int b);
private:
    Rva001F6492Helper *m_ptr;
    Rva001F6492 m_next;
};
void Rva001F8213::rva001F8213(int a, int b)
{
    Rva001F6492Helper *p = m_ptr;
    if (p)
        p->m3(a, b);
    m_next.rva001F6492(a, b);
}
class Rva001F8960 {
public:
    void rva001F8960(int a, int b);
private:
    Rva001F6492Helper *m_ptr;
    Rva001F8213 m_next;
};
void Rva001F8960::rva001F8960(int a, int b)
{
    Rva001F6492Helper *p = m_ptr;
    if (p)
        p->m3(a, b);
    m_next.rva001F8213(a, b);
}
class Rva001F8DE2 {
public:
    void rva001F8DE2(int a, int b);
private:
    Rva001F6492Helper *m_ptr;
    Rva001F8960 m_next;
};
void Rva001F8DE2::rva001F8DE2(int a, int b)
{
    Rva001F6492Helper *p = m_ptr;
    if (p)
        p->m3(a, b);
    m_next.rva001F8960(a, b);
}
class Rva001F9424 {
public:
    void rva001F9424(int a, int b);
private:
    Rva001F6492Helper *m_ptr;
    Rva001F8DE2 m_next;
};
void Rva001F9424::rva001F9424(int a, int b)
{
    Rva001F6492Helper *p = m_ptr;
    if (p)
        p->m3(a, b);
    m_next.rva001F8DE2(a, b);
}
class Rva001FA4C6 {
public:
    void rva001FA4C6(int a, int b);
private:
    Rva001F6492Helper *m_ptr;
    Rva001F9424 m_next;
};
void Rva001FA4C6::rva001FA4C6(int a, int b)
{
    Rva001F6492Helper *p = m_ptr;
    if (p)
        p->m3(a, b);
    m_next.rva001F9424(a, b);
}
class Rva001FA7CE {
public:
    void rva001FA7CE(int a, int b);
private:
    Rva001F6492Helper *m_ptr;
    Rva001FA4C6 m_next;
};
void Rva001FA7CE::rva001FA7CE(int a, int b)
{
    Rva001F6492Helper *p = m_ptr;
    if (p)
        p->m3(a, b);
    m_next.rva001FA4C6(a, b);
}
