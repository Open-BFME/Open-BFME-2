// Complete29-byte constructor: pointer field plus atomic-refcounted member.
// Identity follows the independently decoded A8C7C member operation.
// cl: /Ob0 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
class Rva0036CA00Str {
    void *m_item;
public:
    __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &other);
    ~Rva0036CA00Str();
};
class Rva002390CB {
    void *m_00;
    Rva0036CA00Str m_04;
public:
    __declspec(nothrow) Rva002390CB(const Rva002390CB &other);
    ~Rva002390CB();
};
Rva002390CB::Rva002390CB(const Rva002390CB &other) : m_00(other.m_00), m_04(other.m_04) {}
