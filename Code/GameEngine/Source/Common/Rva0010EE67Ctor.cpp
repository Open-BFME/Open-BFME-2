// cl: /MD
// ??0Rva0010EE67@@QAE@ABVRva0036CA00Str@@H@Z @0x0010EE67 31B. Derived ctor passes const Rva0036CA00Str& to rowed base 0x001164D3 then stores int at +0xC then vtable 0x00BCFA54.
// Evidence: retail push esi push [esp+8] mov esi ecx call base mov eax [esp+0xC] mov [esi+0xC] eax mov [esi] vtable ret 8; siblings 0x0010EECE float variant; caller 0x0010FAAD in 0x0010FA6B.
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
class Rva0010EE67 : public Rva001164D3 {
public:
    Rva0010EE67(const Rva0036CA00Str &s, int v);
private:
    int m_v;
};
Rva0010EE67::Rva0010EE67(const Rva0036CA00Str &s, int v) : Rva001164D3(s), m_v(v) {}
