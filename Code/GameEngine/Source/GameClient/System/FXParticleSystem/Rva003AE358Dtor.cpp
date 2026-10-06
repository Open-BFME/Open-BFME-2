// cl: /MD
// ??1Rva003AE358@@UAE@XZ @0x003AE358, 41B.
// Dtor restores three vptrs (+0x10 guarded g_00BBB554, +8 guarded s_slot3E4first, +0 plain g_00C1B320) with no base call. Evidence: caller ??_G at 0x003AE33C, vtable slot 0 entries 0x0081CA04/0x0081CAA4/0x0081D3A0, sibling V3InlineTemplateDtor 0x003A583E shape plus copy ctors 0x003AE0AF/0x003AE2A9 three-vptr layout.
extern const void *const g_00BBB554[];
extern "C" char s_slot3E4first;
extern const void *const g_00C1B320[];
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
    *(volatile unsigned int *)b10 = (unsigned int)g_00BBB554;
    unsigned char *b08 = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)b08 = (unsigned int)&s_slot3E4first;
    *(volatile unsigned int *)this = (unsigned int)g_00C1B320;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00C1B320@@3QBQBXB=??_7V3Vt01111D90@@6B@")
