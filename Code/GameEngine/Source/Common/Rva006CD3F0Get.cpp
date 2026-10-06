// cl: /MD
// ?Rva006CD3F0Get@@YAHPAX@Z @0x006CD3F0 75B evidence Apt.cpp eType assert plus get row plus byte table g_00CE8B70 plus type 0x25 field
// Apt.cpp's assert hook and break-on-assert flag, which every Apt unit's
// asserts read. Matched DIR32 references across 44 units place the hook at
// VA 0x00E17734 (zero-filled: installed at run time) and the flag at VA
// 0x00DDC01C, whose retail initial value is 1. This unit carries Apt.cpp code
// (the assert names it), so it defines both.
void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int) = 0;
int g_bfmeAptBreakOnAssertAtDDC01C = 1;
extern unsigned char g_00CE8B70[];
// The caller bounds eType below 47; these are the retail bytes at VA
// 0x00CE8B70 (RVA 0x008E8B70). Preserve the non-const symbol decoration while
// placing the initialized table in retail's .rdata section.
#pragma data_seg(".rdata")
unsigned char g_00CE8B70[47] = {
    0x00, 0x04, 0x00, 0x08, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x24, 0x00, 0x08, 0x60, 0x60, 0x60, 0x60,
    0x60, 0x60, 0x60, 0x60, 0x20, 0x2C, 0x2C, 0x20, 0x20, 0x20, 0x24, 0x20, 0x20, 0x64, 0x20, 0x20,
    0x28, 0x28, 0x24, 0x24, 0x40, 0x10, 0x20, 0x20, 0x00, 0x28, 0x24, 0x34, 0x34, 0x44, 0x60
};
#pragma data_seg()
class Rva006DBB30SarDwordField
{
public:
    int get() const;
};
int __cdecl Rva006CD3F0Get(void *p)
{
    int eType = ((const Rva006DBB30SarDwordField *)p)->get();
    if (!(eType < 47)) {
        g_bfmeAptAssertAtE17734("eType < AptVFT_NumVFTs", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp", 0x880);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    if (eType == 0x25)
        return *(int *)((char *)p + 0xc);
    return (int)g_00CE8B70[eType];
}
