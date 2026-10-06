// cl: /MD
// ??0Rva0010EE4F@@QAE@ABVRva0036CA00Str@@@Z @0x0010EE4F 24B. Derived ctor passes const Rva0036CA00Str& to rowed base 0x001164D3 then stores vtable 0x00BCFA4C.
// Evidence: retail push esi push [esp+8] mov esi ecx call base mov [esi] vtable ret 4; sibling 0x0010EE9E same shape same base; caller 0x0010FA30 in 0x0010F9F1.
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
class Rva0010EE4F : public Rva001164D3 {
public:
    Rva0010EE4F(const Rva0036CA00Str &s);
};
Rva0010EE4F::Rva0010EE4F(const Rva0036CA00Str &s) : Rva001164D3(s) {}
