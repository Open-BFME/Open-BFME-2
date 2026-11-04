// cl: /MD
// ?rva005335D3@PathfindZoneManager@@QAEXXZ @ 0x005335D3 145B.
// Reset grid 8x7 words at +0x1B596, frees Item arrays via 0x00532F9F,
// zeroes header and rect, preserves word at +0 into +4, sets flag +0x1BA31.
// Callees rowed 0x0002FD80 0x00532F9F. Callers 0x002F46ED 0x00533B8C.
#include <new>
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
#include "../../Include/GameLogic/PathfindZoneManager.h"

void PathfindZoneManager::rva005335D3()
{
    int i;
    int j;
    for (i = 0; i < 8; ++i)
        for (j = 0; j < 7; ++j)
            field1B594[i][j].first = 0;
    operator delete[](field1BA38);
    delete[] field1BA34;
    unsigned short saved = capacity;
    field1BA34 = 0;
    field1BA38 = 0;
    field1BA40 = 0;
    field1BA3C = 0;
    end = 0;
    first = 0;
    field1B9F4.first = 0;
    field1BA30 = 0;
    field1BA44.lo.x = 0;
    field1BA44.hi.x = 0;
    field1BA44.lo.y = 0;
    field1BA44.hi.y = 0;
    second = saved;
    field1BA31 = 1;
}
