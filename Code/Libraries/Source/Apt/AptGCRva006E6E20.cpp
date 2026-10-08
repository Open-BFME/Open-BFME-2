// cl: /MD
// ?Rva006E6E20Collect@@YAXXZ, retail 0x006E6E20 346B.
// AptGC mark/sweep collector between ReleaseValues 0x006E6D90 and CleanAll
// 0x006E6F80. Retail asserts pObject->getRefCount() > 0 at AptGC.cpp:151,
// gates on getGCRootCount plus double get(), marks via setGCMark(true) plus
// virtual slot 0x34, sweeps via PreDestroy 0x28/Destroy 0x2c, then slot 0x24
// with cleaned count, log, ClearPools and tail ClearTemporaryPool. Vtable
// slot identities from ForceDelete precedent; pool/byte/log globals from packet.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class AptValue {
public:
    virtual void unused0();
    virtual void unused1();
    virtual void ForceDelete();
    virtual void unused3();
    virtual void unused4();
    virtual void unused5();
    virtual void unused6();
    virtual void unused7();
    virtual void unused8();
    virtual void unused9();
    virtual void PreDestroy();
    virtual void DestroyGCPointers();
    virtual void unused12();
    virtual void unused13();
public:
    unsigned int getRefCount() const;
    void setGCMark(bool value);
};
class BfmeAptValue006DCD20 {
public:
    unsigned int getGCRootCount() const;
};
class Rva006DBB40ShrAndField {
public:
    bool get() const;
};
class AptValueVector {
public:
    void ReleaseValues();
};
class AptValueGC_PoolManager {
public:
    AptValue *GetFirstAptValue();
    AptValue *GetNextAptValue(const AptValue *pValue);
};
class AptBoolean { public: static void ClearPool(); };
class AptInteger { public: static void ClearPool(); };
class AptFloat { public: static void ClearPool(); };
class StringPool { public: static void ClearTemporaryPool(); };
void __cdecl Rva006CD330();
void __cdecl Rva006CC110Log(int code, const char *format, ...);
extern AptValueVector *g_releaseVectorAtE17710;
extern class Rva006D2A60 *g_pChainBlockAllocatorF4;
extern unsigned char g_00E180EC;
extern const char g_00CEC468[];
void __cdecl Rva006E6E20Collect()
{
    int cleaned = 0;
    g_releaseVectorAtE17710->ReleaseValues();
    AptValue *pValue = (*(AptValueGC_PoolManager **)&g_pChainBlockAllocatorF4)->GetFirstAptValue();
    while (pValue) {
        if (!(pValue->getRefCount() > 0)) {
            g_bfmeAptAssertAtE17734("pObject->getRefCount() > 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptGC.cpp", 0x97);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        if (((const BfmeAptValue006DCD20 *)pValue)->getGCRootCount() != 0) {
            if (!((const Rva006DBB40ShrAndField *)pValue)->get()) {
                if (!((const Rva006DBB40ShrAndField *)pValue)->get()) {
                    pValue->setGCMark(true);
                    pValue->unused13();
                }
            }
        }
        pValue = (*(AptValueGC_PoolManager **)&g_pChainBlockAllocatorF4)->GetNextAptValue(pValue);
    }
    Rva006CD330();
    pValue = (*(AptValueGC_PoolManager **)&g_pChainBlockAllocatorF4)->GetFirstAptValue();
    unsigned char saved = g_00E180EC;
    g_00E180EC = 1;
    while (pValue) {
        if (!((const Rva006DBB40ShrAndField *)pValue)->get()) {
            pValue->PreDestroy();
            pValue->DestroyGCPointers();
        }
        pValue = (*(AptValueGC_PoolManager **)&g_pChainBlockAllocatorF4)->GetNextAptValue(pValue);
    }
    g_00E180EC = saved;
    pValue = (*(AptValueGC_PoolManager **)&g_pChainBlockAllocatorF4)->GetFirstAptValue();
    while (pValue) {
        if (!((const Rva006DBB40ShrAndField *)pValue)->get()) {
            ++cleaned;
            pValue->unused9();
        } else {
            pValue->setGCMark(false);
        }
        pValue = (*(AptValueGC_PoolManager **)&g_pChainBlockAllocatorF4)->GetNextAptValue(pValue);
    }
    g_releaseVectorAtE17710->ReleaseValues();
    if (cleaned)
        Rva006CC110Log(4, g_00CEC468, cleaned);
    AptBoolean::ClearPool();
    AptInteger::ClearPool();
    AptFloat::ClearPool();
    StringPool::ClearTemporaryPool();
}
