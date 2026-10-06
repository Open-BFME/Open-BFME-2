// cl: /MD
// ??0Rva0010EF14@@QAE@ABVRva0036CA00Str@@MM@Z @0x0010EF14 46B. Derived ctor passes const Rva0036CA00Str& to rowed base 0x001164D3 then stores floats at +0xC and +0x10 then vtable 0x00BCFA84.
// Evidence: retail push esi push [esp+8] mov esi ecx call base movss floats mov [esi] vtable ret 0xC; siblings 0x0010EEF1 0x0010EF61 same base and shape; caller 0x0010FDAC.
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
class Rva0010EF14 : public Rva001164D3 {
public:
    Rva0010EF14(const Rva0036CA00Str &s, float f1, float f2);
private:
    float m_f1;
    float m_f2;
};
Rva0010EF14::Rva0010EF14(const Rva0036CA00Str &s, float f1, float f2) : Rva001164D3(s), m_f1(f1), m_f2(f2) {}
