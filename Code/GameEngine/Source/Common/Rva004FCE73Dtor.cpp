// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva004FCE73@@UAE@XZ @0x004FCE73 66B.
// Virtual dtor storing vtable 0x00863560, destroying AsciiString vector at
// +0x14 via the rowed STLport dtor, then freeing heap member at +0x04 via
// the rowed _free. Evidence: unlock lane (unblocks 0x004FD7DF deleting
// dtor); caller 0x004FD7E2 passes this in ecx with ret 4 test-low-bit
// deleting shape; same and/or EH-state plus push-pop free idiom as STLport
// siblings; neighbours carry /O1 /MD.
#include <vector>

#include "ascii_string.h"


extern "C" void free(void *ptr);

struct Rva004FCE73Holder {
    void *p;
    ~Rva004FCE73Holder() { if (p) free(p); }
};

class Rva004FCE73 {
public:
    virtual ~Rva004FCE73();
private:
    Rva004FCE73Holder m_04;
    char pad08[0x14 - 0x08];
    _STL::vector<AsciiString> m_14;
};

Rva004FCE73::~Rva004FCE73()
{
}
