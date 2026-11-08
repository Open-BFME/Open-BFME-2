// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport46
//
// ??1Rva0035BB4B@@UAE@XZ @0x0035BB4B 368B
// Virtual dtor of large Common record (vptr 0x00816204) over base Overridable.
// Members destroy in reverse: AsciiStrings via releaseBuffer 0x36410, AsciiString
// vectors via 0x2cc70, Rva002390CB vectors via 0x35b825, heap blocks via _free
// 0x30830, then base ??1Overridable.
// Evidence: ecx-first thiscall with vptr store; EH states 0x15-0x0; callers
// 0x001DB060 0x0035BCBE; unwind funclet at 0x007697D9.
#include <stdlib.h>
#include <vector>

#include "ascii_string.h"

#include "../../Include/Common/Overridable.h"

#include "../../Include/Common/Rva002390CB.h"

struct RvaFreePtr {
    char *m_ptr;
    ~RvaFreePtr() { if (m_ptr) free(m_ptr); }
};

class Rva0035BB4B : public Overridable {
public:
    virtual ~Rva0035BB4B();
private:
    AsciiString m_10;
    char m_pad14[0x14];
    RvaFreePtr m_28;
    char m_pad2C[0xC];
    _STL::vector<AsciiString> m_38;
    int m_44;
    AsciiString m_48;
    int m_4C;
    AsciiString m_50;
    AsciiString m_54;
    _STL::vector<AsciiString> m_58;
    _STL::vector<AsciiString> m_64;
    AsciiString m_70;
    AsciiString m_74;
    AsciiString m_78;
    AsciiString m_7C;
    char m_pad80[0x24];
    RvaFreePtr m_A4;
    char m_padA8[0xC];
    _STL::vector<AsciiString> m_B4;
    char m_padC0[8];
    _STL::vector<Rva002390CB> m_C8;
    _STL::vector<Rva002390CB> m_D4;
    _STL::vector<Rva002390CB> m_E0;
    RvaFreePtr m_EC;
    char m_padF0[0x98];
    _STL::vector<AsciiString> m_188;
    char m_pad194[0xA0];
    RvaFreePtr m_234;
    char m_pad238[8];
    AsciiString m_240;
    int m_244;
    AsciiString m_248;
};

Rva0035BB4B::~Rva0035BB4B()
{
}
