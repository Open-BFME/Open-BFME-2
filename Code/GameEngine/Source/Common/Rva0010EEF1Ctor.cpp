// cl: /MD
// ??0Rva0010EEF1@@QAE@ABVRva0036CA00Str@@M@Z @0x0010EEF1 35B. Derived ctor passes const Rva0036CA00Str& to rowed base 0x001164D3 then stores float at +0xC then vtable 0x00BCFA7C.
// Evidence: retail push esi push [esp+8] mov esi ecx call base movss float mov [esi] vtable ret 8; siblings 0x0010EE9E 0x0010EF8B same base and shape; caller 0x0010FD21.
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
class Rva0010EEF1 : public Rva001164D3 {
public:
    Rva0010EEF1(const Rva0036CA00Str &s, float f);
private:
    float m_f;
};
Rva0010EEF1::Rva0010EEF1(const Rva0036CA00Str &s, float f) : Rva001164D3(s), m_f(f) {}
