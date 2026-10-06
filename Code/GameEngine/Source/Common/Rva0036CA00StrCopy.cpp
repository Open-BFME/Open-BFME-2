// cl: /Ob0 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
class Rva0036CA00Str {
    void *m_item;
public:
    __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &other);
    ~Rva0036CA00Str();
};
Rva0036CA00Str::Rva0036CA00Str(const Rva0036CA00Str &other) : m_item(other.m_item) {
    if (m_item) InterlockedIncrement((long volatile *)((char *)m_item + 4));
}
