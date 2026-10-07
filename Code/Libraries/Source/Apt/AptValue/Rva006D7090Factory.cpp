// cl: /DNDEBUG /MD /EHsc
// ?rva006D7090@@YAPAXPBD@Z @0x006D7090 285B. Pooled Apt string-value factory: reuse from free list at g_AptStringFreeList with type/refcount asserts else new Rva006D6D20 via pool operator new.
// Evidence: retail free-list pop get()==1 getRefCount()==0 asserts AptString.cpp 0x298/0x29A apply release-vector EAStringC clear SetString else allocBlock 0x10 plus Rva006D6D20 PBD ctor; LINK BONUS caller 0x006CB9F9; callers 0x006CB9F9 0x006CBB00.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva006DBB30SarDwordField
{
public:
    int get() const;
};
class AptValue
{
public:
    unsigned int getRefCount() const;
    void SetString(const char *s);
};
class Rva006DBDB0DwordOrSetter
{
public:
    void apply();
};
class AptValueVector
{
public:
    void rva006E6C00(AptValue *pValue);
};
extern AptValueVector *g_releaseVectorAtE17710;
class EAStringC
{
public:
    bool IsEmpty() const;
};
class BfmeStrVKK
{
public:
    void bfmeTruncVKK(unsigned int n);
};
class Rva006DB270
{
public:
    void freeBlock(void *block, int blockSize);
};
class Rva006DB160
{
public:
    void *allocBlock(int blockSize);
};
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006D6D20
{
public:
    void *m_vtbl;
    int m_04;
    EAStringC m_str;
    Rva006D6D20 *m_next;
    Rva006D6D20(const char *s);
    Rva006D6D20();
    static void *operator new(unsigned int size)
    {
        return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock((int)size);
    }
    static void operator delete(void *block, unsigned int size)
    {
        g_pChainBlockAllocator->freeBlock(block, (int)size);
    }
};
// Retail initializes the free-list data head to zero.
Rva006D6D20 *g_AptStringFreeList = 0;
void *__cdecl rva006D7090(const char *szValue)
{
    Rva006D6D20 *pNewString = g_AptStringFreeList;
    if (pNewString) {
        g_AptStringFreeList = pNewString->m_next;
        if (((const Rva006DBB30SarDwordField *)pNewString)->get() != 1) {
            g_bfmeAptAssertAtE17734("pNewString->getVtblIndex() == AptVFT_StringValue", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptString.cpp", 0x298);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        if (((const AptValue *)pNewString)->getRefCount() != 0) {
            g_bfmeAptAssertAtE17734("pNewString->getRefCount() == 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptString.cpp", 0x29A);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        ((Rva006DBDB0DwordOrSetter *)pNewString)->apply();
        g_releaseVectorAtE17710->rva006E6C00((AptValue *)pNewString);
        EAStringC *str = &pNewString->m_str;
        if (!str->IsEmpty())
            ((BfmeStrVKK *)str)->bfmeTruncVKK(0);
        ((AptValue *)pNewString)->SetString(szValue);
        return pNewString;
    }
    return new Rva006D6D20(szValue);
}

// Native assertions and the existing date-callback evidence name AptString.
// The complete 262-byte factory differs from its 285-byte sibling by default construction
// and relative AptString.inl assertion lines 0x36/0x38. Allocation 16, EAStringC+8,
// free-list link+C and all callees are independently verified target facts.
// INT3 preserves the native materialized assertion-flag load; the intrinsic
// instead folds the test into a memory compare for this shape.
class AptString {public:static AptString *Create();};
AptString *AptString::Create()
{
    Rva006D6D20 *pNewString = g_AptStringFreeList;
    if (pNewString) {
        g_AptStringFreeList = pNewString->m_next;
        if (((const Rva006DBB30SarDwordField *)pNewString)->get() != 1) {
            g_bfmeAptAssertAtE17734("pNewString->getVtblIndex() == AptVFT_StringValue", "..\\..\\include\\apt\\AptValue/AptString.inl", 0x36);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __asm {int 3}
        }
        if (((const AptValue *)pNewString)->getRefCount() != 0) {
            g_bfmeAptAssertAtE17734("pNewString->getRefCount() == 0", "..\\..\\include\\apt\\AptValue/AptString.inl", 0x38);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __asm {int 3}
        }
        ((Rva006DBDB0DwordOrSetter *)pNewString)->apply();
        g_releaseVectorAtE17710->rva006E6C00((AptValue *)pNewString);
        EAStringC *str = &pNewString->m_str;
        if (!str->IsEmpty())
            ((BfmeStrVKK *)str)->bfmeTruncVKK(0);
        return (AptString*)pNewString;
    }
    return (AptString*)new Rva006D6D20;
}
