// cl: /MD
// ??0Rva0010EEB6@@QAE@ABVRva0036CA00Str@@@Z @0x0010EEB6 24B. Derived ctor passes const Rva0036CA00Str& to rowed base 0x001164D3 then stores vtable 0x00BCFA6C.
// Evidence: retail push esi push [esp+8] mov esi ecx call base mov [esi] vtable ret 4; siblings 0x0010EE86 0x0010EE4F same shape same base; caller 0x0010FC1D in 0x0010FBDE.
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
class Rva0010EEB6 : public Rva001164D3 {
public:
    Rva0010EEB6(const Rva0036CA00Str &s);
};
Rva0010EEB6::Rva0010EEB6(const Rva0036CA00Str &s) : Rva001164D3(s) {}
