// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// ??0Rva0033B830@@QAE@ABV?$StringBase@D@@ABVRva002390CB@@@Z @0x0033B830 30B.
// Two-member record ctor: StringBase<char> at +0 via pinned copy 0x365F0 then
// Rva002390CB at +4 via rowed copy 0x2390CB then return this with ret 8.
// Layout matches 12B BfmeStringRecord002CF550 (StringBase plus Rva002390CB).
// Caller 0x0033BEF5 is the hidden-dest forwarder that becomes ready and its
// caller 0x0033DBE5 builds the StringBase temp via 0x37BA0 plus Upgrades.
template <typename T>
class StringBase
{
    friend struct Rva0033B830;
    StringBase(const StringBase<T> &other);
    void *m_data;
};

class Rva002390CB
{
public:
    Rva002390CB(const Rva002390CB &other);
};

struct Rva0033B830
{
    StringBase<char> m0;
    Rva002390CB m4;
    Rva0033B830(const StringBase<char> &a, const Rva002390CB &b);
};

Rva0033B830::Rva0033B830(const StringBase<char> &a, const Rva002390CB &b) : m0(a), m4(b)
{
}
