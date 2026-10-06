// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva001EEBD5@Mouse@@QAEXVUnicodeString@@PBU_MouseSixteen@@1@Z, retail 0x001EEBD5, 118 bytes.
// Mouse wide-text plus two 16-byte payload setter. Evidence: Mouse neighbours
// (same /O1 area, +0x4Fxx offsets near rva001EEA6D); by-value wide-string temp
// via rowed private StringBase<G> copyctor plus rowed releaseBuffer EH
// cleanup (GadgetStaticText/MouseRva001EEC4B friend pattern); virtual slot 1
// on +0x4FA8; guarded 16-byte copies into +0x4FAC/+0x4FBC.
class Mouse;
#include "unicode_string.h"
struct _MouseSixteen { int v[4]; };
struct MouseFontThunk {
    virtual void slot0();
    virtual void setText(UnicodeString text);
};
class Mouse {
    char m_pad[0x4FA8];
    MouseFontThunk *m_4FA8;
    _MouseSixteen m_4FAC;
    _MouseSixteen m_4FBC;
public:
    void rva001EEBD5(UnicodeString text, const _MouseSixteen *a, const _MouseSixteen *b);
};
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
void Mouse::rva001EEBD5(UnicodeString text, const _MouseSixteen *a, const _MouseSixteen *b)
{
    if (m_4FA8) {
        _ReadWriteBarrier();
        m_4FA8->setText(text);
        if (a)
            m_4FAC = *a;
        if (b)
            m_4FBC = *b;
    }
}
