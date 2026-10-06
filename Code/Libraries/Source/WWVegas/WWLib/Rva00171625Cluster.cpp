// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Address-derived recovery of 0x00171625 (42B), a Rva00171024 member that
// returns the ref-counted handle at +0x18 after a +0x1c-flagged refresh.
// Evidence: target reads byte [ecx+0x1c], calls thiscall 0x001711A6 with this,
// then copies the 4-byte member at +0x18 through the rowed AssetReference copy
// ctor 0x000424BB into the hidden return pointer ([ebp+8]); ret 4. Layout
// follows sibling ctor row ??0Rva00171024@@QAE@HH@Z at 0x00171024, which
// establishes +0x14 iterator and +0x18/+0x1C (this body) members.
// Identity of the class is not proven; names are address-derived.

class CountedAsset
{
public:
    void Release_Ref();
};

class AssetReference
{
public:
    AssetReference(const AssetReference &other);
    ~AssetReference();
private:
    CountedAsset *m_object;
};

class Rva00171024
{
public:
    void rva001711a6();
    AssetReference rva00171625();
private:
    char m_pad[0x18];
    AssetReference m_18;
    bool m_1c;
    bool m_1d;
};

AssetReference Rva00171024::rva00171625()
{
    if (m_1c)
        rva001711a6();
    return m_18;
}
