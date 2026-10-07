// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /EHsc /MD /DNDEBUG
// ??0Rva003FAFB9@@QAE@ABV0@@Z @0x003FAF13 166B
// Copy ctor of the 0x00C37A08 class (dtor 0x003FAFB9 methods 0x003FAB93 and 0x003FAC3F).
// Evidence: vtable store 0x00C37A08 StringBase copy 0x365F0 at +4 pos movs +8/+C/+10
// Rva0036CA00Str copy 0xA8C7C at +14 FixedStorage copy 0x2CF0F0 at +18 Region2D copy
// 0x4254E at +1C m_2c=1 plus bytes +30/+31/+32 src m_2c>=5 with new referent gating rva003FAB93.
#include "ascii_string.h"
#include "Common/Snapshot.h"

class Rva0036CA00Str {
public:
    __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &other);
    ~Rva0036CA00Str();
    void *m_item;
};

class BfmeFixedStorage002CF0F0 {
public:
    __declspec(nothrow) BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &other);
    char m_bytes[4];
};

struct Region2D {
    Region2D(const Region2D &that);
    float x_min;
    float y_min;
    float x_max;
    float y_max;
};

class Rva003FAB93 {
public:
    void rva003FAB93();
};

class Rva003FAFB9 : public Snapshot {
public:
    Rva003FAFB9(const Rva003FAFB9 &src);
    virtual ~Rva003FAFB9();
private:
    AsciiString m_str04;
    float m_x08;
    float m_y0C;
    float m_z10;
    Rva0036CA00Str m_holder14;
    BfmeFixedStorage002CF0F0 m_stor18;
    Region2D m_region1C;
    unsigned int m_2c;
    unsigned char m_30;
    unsigned char m_31;
    unsigned char m_32;
};

Rva003FAFB9::Rva003FAFB9(const Rva003FAFB9 &src)
    : m_str04(src.m_str04)
    , m_x08(src.m_x08)
    , m_y0C(src.m_y0C)
    , m_z10(src.m_z10)
    , m_holder14(src.m_holder14)
    , m_stor18(src.m_stor18)
    , m_region1C(src.m_region1C)
{
    m_2c = 1;
    m_30 = src.m_30;
    m_31 = src.m_31;
    m_32 = src.m_32;
    if (src.m_2c >= 5 && m_holder14.m_item != 0)
        ((Rva003FAB93 *)this)->rva003FAB93();
}
