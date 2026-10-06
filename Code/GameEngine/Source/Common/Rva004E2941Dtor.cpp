// cl: /Ireference/shims/bfme2_ascii /EHs /MD
// ??1Rva004E2382@@QAE@XZ @ 0x004E2941 (74B).
// Dtor of Rva004E2382 whose ctor is 0x004E2382: frees vector buffer at +0x14
// via rowed _free 0x00030830 then destroys trivial tree at +8 via rowed
// 0x000730DE then destroys AsciiString at +0 via rowed 0x00036410. Layout
// from ctor (AsciiString +0 nulled plus int +4 zeroed plus 12B at +8 plus
// vector at +0x14 via Vector_base 0x00211E58). Ctor uses generic empty-set
// ctor 0x000D3A71 for +8; true type is trivial tree Rva00072FE6 with no
// payload dtor per 0x00072F7C which only frees nodes. Caller 0x004E3E91
// builds temp via ctor then destroys via this body. /EHs for C-call states.
#include "ascii_string.h"

extern "C" void __cdecl free(void *p);

class Rva00072FE6 {
public:
    ~Rva00072FE6();
private:
    char m_pad[12];
};

struct Rva004E2382Vec {
    void *m_start;
    void *m_finish;
    void *m_end;
};

class Rva004E2382 {
public:
    ~Rva004E2382();
private:
    AsciiString m_00;
    int m_04;
    Rva00072FE6 m_08;
    Rva004E2382Vec m_14;
};

Rva004E2382::~Rva004E2382()
{
    if (m_14.m_start != 0)
        free(m_14.m_start);
}
