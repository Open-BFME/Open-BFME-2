// cl: /DNDEBUG /MD
// ?Rva006F7C70Free@@YGXPAURva006F7C70Item@@@Z @0x006F7C70 215B evidence AptDisplayList unlink asserts plus 0x1C/0x14 pool free via rowed 0x006DB270; callers at 0x006F8380
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva006DB270
{
public:
    void freeBlock(void *block, int blockSize);
};
extern Rva006DB270 *g_pChainBlockAllocator;
struct Rva006F7C70Item
{
    int m_00;
    void *m_arr;
    Rva006F7C70Item *m_next;
    Rva006F7C70Item *m_prev;
};
void __stdcall Rva006F7C70Free(Rva006F7C70Item *pItem)
{
    if (pItem == 0) {
        g_bfmeAptAssertAtE17734("pItem != NULL", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x16A);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (pItem->m_prev != 0) {
        if (pItem->m_prev->m_next != pItem) {
            g_bfmeAptAssertAtE17734("pItem->pPrev->pNext == pItem", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x16E);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        pItem->m_prev->m_next = pItem->m_next;
    }
    if (pItem->m_next != 0) {
        if (pItem->m_next->m_prev != pItem) {
            g_bfmeAptAssertAtE17734("pItem->pNext->pPrev == pItem", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x173);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        pItem->m_next->m_prev = pItem->m_prev;
    }
    void *arr = pItem->m_arr;
    pItem->m_00 = 0;
    pItem->m_next = 0;
    pItem->m_prev = 0;
    if (arr != 0) {
        ((int *)arr)[0] = 0;
        ((int *)arr)[1] = 0;
        ((int *)arr)[2] = 0;
        g_pChainBlockAllocator->freeBlock(arr, 0x1C);
        pItem->m_arr = 0;
    }
    g_pChainBlockAllocator->freeBlock(pItem, 0x14);
}
