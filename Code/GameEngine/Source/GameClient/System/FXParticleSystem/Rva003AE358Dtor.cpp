// cl: /MD
// ??1Rva003AE358@@UAE@XZ @0x003AE358, 41B.
// Dtor restores three vptrs (+0x10 guarded g_00BBB554, +8 guarded 0x00C1C780, +0 plain g_00C1B320) with no base call. Evidence: caller ??_G at 0x003AE33C, vtable slot 0 entries 0x0081CA04/0x0081CAA4/0x0081D3A0, sibling V3InlineTemplateDtor 0x003A583E shape plus copy ctors 0x003AE0AF/0x003AE2A9 three-vptr layout.
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");
extern "C" const void *const __identifier("??_7V3Vt01111D90@@6B@")[];
class __declspec(novtable) Rva003AE358
{
public:
    virtual ~Rva003AE358();
private:
    void *m_v0;
    char m_pad04[4];
    void *m_v8;
    char m_pad0C[4];
    void *m_v10;
};
Rva003AE358::~Rva003AE358()
{
    unsigned char *b10 = this ? (unsigned char *)this + 0x10 : 0;
    reinterpret_cast<Snapshot *>(b10)->Snapshot::~Snapshot();
    unsigned char *b08 = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)b08 = (unsigned int)&__identifier("??_7Rva003F498ACallback@@6B@");
    *(volatile unsigned int *)this = (unsigned int)__identifier("??_7V3Vt01111D90@@6B@");
}
