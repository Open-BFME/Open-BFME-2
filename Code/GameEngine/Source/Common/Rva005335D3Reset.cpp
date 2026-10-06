// cl: /MD
// ?rva005335D3@Rva005312BE@@QAEXXZ @ 0x005335D3 145B.
// Reset grid 8x7 words at +0x1B596, frees Item arrays via 0x00532F9F,
// zeroes header and rect, preserves word at +0 into +4, sets flag +0x1BA31.
// Callees rowed 0x0002FD80 0x00532F9F. Callers 0x002F46ED 0x00533B8C.
void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *p);
class Rva00531132
{
public:
    void rva00531132(bool add, int value);
    int rva0053117F(int index);
    int m_count;
    int m_items[12];
};
class Rva005312BEItem
{
public:
    ~Rva005312BEItem();
    Rva00531132 m_set;
    unsigned char m_cleared;
    unsigned char m_35;
    char m_pad36[2];
    void *m_p38;
    char m_pad3C[0x44 - 0x3C];
};
struct Rva005312BECell
{
    unsigned short m_w;
    char m_pad[0x14 - 2];
};
struct Rva005312BERect
{
    int x0;
    int y0;
    int x1;
    int y1;
};
class Rva005312BE
{
public:
    void rva005335D3();
    unsigned short m_00;
    unsigned short m_02;
    unsigned short m_04;
    unsigned short m_06;
    char m_pad08[0x1B596 - 8];
    Rva005312BECell m_grid[8][7];
    unsigned short m_1B9F6;
    char m_pad1BA00[0x1BA30 - 0x1B9F8];
    unsigned char m_flag1BA30;
    unsigned char m_flag1BA31;
    char m_pad3[0x1BA34 - 0x1BA32];
    Rva005312BEItem *m_pData;
    Rva005312BEItem **m_ppItems;
    int m_outer;
    int m_inner;
    Rva005312BERect m_rect;
};

void Rva005312BE::rva005335D3()
{
    int i;
    int j;
    for (i = 0; i < 8; ++i)
        for (j = 0; j < 7; ++j)
            m_grid[i][j].m_w = 0;
    operator delete[](m_ppItems);
    delete[] m_pData;
    unsigned short saved = m_00;
    m_pData = 0;
    m_ppItems = 0;
    m_inner = 0;
    m_outer = 0;
    m_06 = 0;
    m_02 = 0;
    m_1B9F6 = 0;
    m_flag1BA30 = 0;
    m_rect.x0 = 0;
    m_rect.x1 = 0;
    m_rect.y0 = 0;
    m_rect.y1 = 0;
    m_04 = saved;
    m_flag1BA31 = 1;
}
