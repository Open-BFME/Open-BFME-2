// cl: /MD
// ?rva006DB090@Rva006DB090@@QAEXPAXI@Z @0x006DB090 136B evidence DogmaAllocator.cpp via string_xrefs file plus assert pNowFree NULL Pointer plus caller 0x006DB270 freeBlock same-this
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva006DB090 {
    void **m_table;
    void *m_unk04;
    int m_unk08;
    int m_unk0C;
    union {
        unsigned int m_cfg;
        struct { unsigned char m_nextIdx; unsigned char m_sizeIdx; unsigned char m_prevIdx; unsigned char m_flagsHi; };
    };
    int m_unk14;
    int m_count;
public:
    void rva006DB090(void *pNowFree, unsigned int nSize);
};
void Rva006DB090::rva006DB090(void *pNowFree, unsigned int nSize)
{
    if (pNowFree == 0) {
        g_bfmeAptAssertAtE17734("pNowFree != NULL && \"Attempting to Deallocate a NULL Pointer!\"", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\DogmaAllocator.cpp", 590);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    void **slot = &m_table[nSize >> 2];
    void *old = *slot;
    ++m_count;
    *slot = pNowFree;
    ((void **)pNowFree)[m_cfg & 0xff] = old;
    if (m_cfg & 0x10000000)
        ((unsigned int *)pNowFree)[m_sizeIdx] = (unsigned int)nSize;
    if (m_cfg & 0x20000000) {
        if (old != 0)
            ((void **)old)[m_prevIdx] = pNowFree;
        ((void **)pNowFree)[m_prevIdx] = 0;
    }
}
