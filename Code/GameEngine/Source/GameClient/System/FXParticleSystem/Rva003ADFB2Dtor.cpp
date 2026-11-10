// cl: /MD
// ??1Rva003ADFB2@@UAE@XZ @0x003ADFB2 41B Dtor restores three vptrs (+0xC guarded g_00BBB554 +0x8 guarded 0x00C1C780 +0x0 plain g_00C1B320) with no base call. Evidence: caller ??_G at 0x003AE270; sibling Rva003AE358Dtor 0x003AE358 shape plus V3InlineTemplateDtor 0x003A583E neg-lea-sbb-and idiom.
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");
extern "C" const void *const __identifier("??_7V3Vt01111D90@@6B@")[];
class __declspec(novtable) Rva003ADFB2
{
public:
    virtual ~Rva003ADFB2();
private:
    void *m_v0;
    char m_pad04[4];
    void *m_v8;
    void *m_v0C;
};
Rva003ADFB2::~Rva003ADFB2()
{
    unsigned char *b0C = this ? (unsigned char *)this + 0x0C : 0;
    reinterpret_cast<Snapshot *>(b0C)->Snapshot::~Snapshot();
    unsigned char *b08 = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)b08 = (unsigned int)&__identifier("??_7Rva003F498ACallback@@6B@");
    *(volatile unsigned int *)this = (unsigned int)__identifier("??_7V3Vt01111D90@@6B@");
}
