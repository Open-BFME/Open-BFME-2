// ?rva004FD013@Rva004FCE73@@QAEXHPAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@PAH@Z
// partial score=0.97 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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

class ModuleData;

class Rva004FCE73 {
public:
    virtual ~Rva004FCE73();
    void rva004FD013(int unused, _STL::vector<const ModuleData *> *out, int *maxOut);
private:
    Rva004FCE73Holder m_04;
    char pad08[0x10 - 0x08];
    int m_10;
    _STL::vector<AsciiString> m_14;
};

class ModuleData
{
public:
    unsigned char m_pad[0x12c];
    int m_12c;
};

struct PlayerAITypeEntry
{
    AsciiString name;
    char unknown[12];
};

class Rva002104B6
{
public:
    void *rva002104B6(void *p);
};

class LivingWorldLogic
{
public:
    unsigned char m_pad[0xb0];
    Rva002104B6 *m_b0;
};
extern LivingWorldLogic *TheLivingWorldLogic;

Rva004FCE73::~Rva004FCE73()
{
}

// ?rva004FD013@Rva004FCE73@@QAEXHPAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@PAH@Z @0x004FD013 199B
// Evidence: unlock lane unblocks 0x004FD571; rowed Vector_base 0x00211E58 push_back 0x004DFCB0 lookup 0x002104B6 free 0x00030830 EH_prolog;
// this+0x14/0x18 AsciiString vector like dtor m_14; this+0x10 max int; out vector at ebp+c max ptr at ebp+10; TheLivingWorldLogic+0xb0 like Collect.
void Rva004FCE73::rva004FD013(int unused, _STL::vector<const ModuleData *> *out, int *maxOut)
{
    (void)unused;
    _STL::vector<PlayerAITypeEntry> dummy;
    for (unsigned int i = 0; i < m_14.size(); ++i) {
        const ModuleData *found = (const ModuleData *)TheLivingWorldLogic->m_b0->rva002104B6(&m_14[i]);
        if (!found)
            continue;
        for (unsigned int j = 0; j < out->size(); ++j) {
            if ((*out)[j]->m_12c == found->m_12c)
                goto next;
        }
        out->push_back(found);
    next:;
    }
    if (*maxOut < m_10)
        *maxOut = m_10;
}
