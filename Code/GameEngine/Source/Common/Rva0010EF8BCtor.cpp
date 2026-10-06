// cl: /MD
// ??0Rva0010EF8B@@QAE@ABVRva0036CA00Str@@HH@Z @0x0010EF8B 38B. Derived ctor passes Str to rowed base 0x001164D3 then stores two ints at +0xC +0x10 then vtable 0x00BCFA9C.
// Evidence: retail push esi push [esp+8] mov esi ecx call base mov [esi+0xC] mov [esi+0x10] mov [esi] vtable ret 0xC; new size 0x14 in caller 0x0010FEF3; LINK lane; base copied from Rva001164D3Ctor.cpp.
class Rva0036CA00Str {
    void *m_item;
public:
    __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &other);
    ~Rva0036CA00Str();
};
struct CountBase {
    volatile int m_count;
    __forceinline CountBase() : m_count(0) {}
    virtual void dummy();
};
class Rva001164D3 : public CountBase {
public:
    Rva001164D3(const Rva0036CA00Str &s);
    ~Rva001164D3();
private:
    Rva0036CA00Str m_str;
};
class Rva0010EF8B : public Rva001164D3 {
public:
    Rva0010EF8B(const Rva0036CA00Str &s, int a, int b);
    ~Rva0010EF8B();
private:
    int m_a;
    int m_b;
};
Rva0010EF8B::Rva0010EF8B(const Rva0036CA00Str &s, int a, int b) : Rva001164D3(s), m_a(a), m_b(b) {}
