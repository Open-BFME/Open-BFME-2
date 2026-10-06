// cl: /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
// ??1Rva003FAFB9@@UAE@XZ @0x003FAFB9 82B chain from 0x003FAC3F
// Dtor: stores 0x00837A08, calls rowed rva003FAC3F, holder Release_Ref at +0x14,
// StringBase releaseBuffer at +4, restores 0x00BBB554. Evidence: EH prolog,
// states 2/1/0, Release_Ref row, StringBase row, base BBB554.
#include "Common/Snapshot.h"
class Rva003FAC3F {
public:
    void rva003FAC3F();
};
class OpaqueRefCounted {
public:
    void Release_Ref();
};
struct RvaHolder14 {
    OpaqueRefCounted *m_ptr;
    ~RvaHolder14() { if (m_ptr != 0) m_ptr->Release_Ref(); }
};
template <typename T> class StringBase {
    void releaseBuffer();
public:
    ~StringBase() { releaseBuffer(); }
private:
    char m_pad[16];
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

class Rva003FAFB9 : public Snapshot {
public:
    virtual ~Rva003FAFB9();
private:
    StringBase<char> m_str04;
    RvaHolder14 m_14;
    unsigned char pad18[0x14];
    unsigned int m_2c;
};
Rva003FAFB9::~Rva003FAFB9()
{
    ((Rva003FAC3F *)this)->rva003FAC3F();
}
