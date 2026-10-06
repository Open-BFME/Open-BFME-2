// cl: /MD
// ?rva006E0EB0@Rva006E0EB0@@QAEPAXI@Z @ 0x006E0EB0 74B
// Honest address name: __thiscall teardown plus conditional pool free.
// Target evidence: retail clears +0/+8/+0xC frees array at +4 size 0x1C via
// rowed freeBlock 0x006DB270 through g_pChainBlockAllocator 0x00E176E8 then
// if flag&1 frees this size 0x14 and returns this ret 4. Matches
// Rva006E0DE0Remove layout. Prev/next share /O2 /MD.
class Rva006DB270
{
public:
    void freeBlock(void *block, int blockSize);
};
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006E0EB0
{
public:
    void *rva006E0EB0(unsigned int flag);
private:
    int m_00;
    void *m_arr;
    int m_08;
    int m_0C;
    int m_10;
};
void *Rva006E0EB0::rva006E0EB0(unsigned int flag)
{
    void *arr = m_arr;
    m_00 = 0;
    m_08 = 0;
    m_0C = 0;
    if (arr != 0)
    {
        ((int *)arr)[0] = 0;
        ((int *)arr)[1] = 0;
        ((int *)arr)[2] = 0;
        g_pChainBlockAllocator->freeBlock(arr, 0x1C);
        m_arr = 0;
    }
    if (flag & 1)
        g_pChainBlockAllocator->freeBlock(this, 0x14);
    return this;
}
