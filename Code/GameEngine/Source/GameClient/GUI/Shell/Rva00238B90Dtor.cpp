// cl: /EHsc /MD
//
// ??1Rva00238B90@@UAE@XZ @0x00238B90 (123B):
// Virtual dtor storing vtable 0x007ED654 then destroying seven
// StringBase<char> members at +0x50 +0x18 +0x14 +0x10 +0x0C +0x08 +0x04
// via rowed releaseBuffer 0x00036410 with EH states 5-0. Order is reverse
// declaration. Evidence: unlock lane; vtable store plus seven
// releaseBuffer calls; caller 0x00238C0B is the 28B ??_G.
template <typename T> class StringBase
{
public:
    ~StringBase() { releaseBuffer(); }
private:
    void releaseBuffer();
    T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

class Rva00238B90
{
public:
    virtual ~Rva00238B90();
private:
    StringBase<char> m_04;
    StringBase<char> m_08;
    StringBase<char> m_0C;
    StringBase<char> m_10;
    StringBase<char> m_14;
    StringBase<char> m_18;
    char m_pad1C[0x50 - 0x1C];
    StringBase<char> m_50;
};
Rva00238B90::~Rva00238B90() {}
