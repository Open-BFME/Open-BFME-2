// cl: /MD
// ??0Rva0010EF61@@QAE@ABVRva0036CA00Str@@MH@Z @0x0010EF61 42B. Derived ctor passes const Rva0036CA00Str& to rowed base 0x001164D3 then stores float at +0xC and int at +0x10 then vtable 0x00BCFA94.
// Evidence: retail push esi push [esp+8] mov esi ecx call base mov int movss float mov [esi+0x10] mov [esi] vtable movss [esi+0xC] ret 0xC; twins 0x0010EEF1 0x0010EECE same base; callers 0x0010FEB6 0x00110056.
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
class Rva0010EF61 : public Rva001164D3 {
public:
    Rva0010EF61(const Rva0036CA00Str &s, float f, int v);
private:
    float m_f;
    int m_v;
};
Rva0010EF61::Rva0010EF61(const Rva0036CA00Str &s, float f, int v) : Rva001164D3(s), m_f(f), m_v(v) {}
