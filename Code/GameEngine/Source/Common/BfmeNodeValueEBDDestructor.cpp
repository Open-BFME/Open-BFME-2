// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// The value destructor reached by the matched EBD tree erase and scalar
// deleting destructor. Retail adjusts this by four before tailcalling the
// mapped-value destructor at 0x0038240F.
// BFME1 STLport tree model (BfmeNodeValueEBD 8B tail plus mapped-value 8B
// with two 4B members) guides the layout; retail bytes prove the member
// split (release/dtor on +4 via 0x0036E70, dtor on +0 via 0x0036410).
// CountUpBuffer is the one-pointer member at mapped-value +4; retail reaches
// 0x0036E70 at that adjusted this. The matched row is StringBase<unsigned
// short>::releaseBuffer, the same wide-buffer release operation. Bind the
// element-dtor spelling without changing the verified caller.
#pragma comment(linker, "/alternatename:??1CountUpBuffer@@QAE@XZ=?releaseBuffer@?$StringBase@G@@AAEXXZ")

#include "ascii_string.h"

class CountUpBuffer
{
public:
    ~CountUpBuffer();
private:
    void *m_data;
};

class BfmeMappedValueEBD
{
public:
    ~BfmeMappedValueEBD();
private:
    AsciiString m_first;
    CountUpBuffer m_second;
};

BfmeMappedValueEBD::~BfmeMappedValueEBD()
{
}

class BfmeNodeValueEBD
{
public:
    ~BfmeNodeValueEBD();
private:
    unsigned m_key;
    BfmeMappedValueEBD m_value;
};

BfmeNodeValueEBD::~BfmeNodeValueEBD()
{
}
