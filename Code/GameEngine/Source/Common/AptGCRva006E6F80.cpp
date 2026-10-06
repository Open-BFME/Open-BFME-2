// cl: /MD
//
// ?CleanAll@AptGC@@SAXXZ, retail 0x006e6f80, 201 bytes. Banked partial (score 1.0) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Partial: target 0x006E6F80, 201 bytes. Donor identity APT0.19.03 release.
// Caller instruction shape is reconstructed; unvalidated callee identities
// remain a blocker. See reverse/apt_donor_01903.json for exact call targets.
class AptValue {
    virtual void unused0(); virtual void unused1(); virtual void unused2();
    virtual void unused3(); virtual void unused4(); virtual void unused5();
    virtual void unused6(); virtual void unused7(); virtual void unused8();
public:
    virtual void DeleteThis();
    virtual void PreDestroy();
    virtual void DestroyGCPointers();
private:
    friend class AptGC;
    void SetDestroyedGC();
};
class AptValueVector { public: void ReleaseValues(); };
class AptValueGC_PoolManager {
public:
    AptValue *GetFirstAptValue();
    AptValue *GetNextAptValue(const AptValue *);
};
class AptBoolean { public: static void ClearPool(); };
class AptInteger { public: static void ClearPool(); };
class AptFloat { public: static void ClearPool(); };
class StringPool { public: static void ClearTemporaryPool(); };
void __cdecl Rva006CC110Log(int,const char *,...);
extern AptValueVector *g_releaseVectorAtE17710;
class Rva006D2A60;
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
extern bool g_aptReleaseGateAtE180EC;
class AptGC { public: static void CleanAll(); };
void AptGC::CleanAll()
{
    int cleaned=0;
    g_releaseVectorAtE17710->ReleaseValues();
    AptValue *value=((AptValueGC_PoolManager *)g_pChainBlockAllocatorF4)->GetFirstAptValue();
    bool saved=g_aptReleaseGateAtE180EC;
    g_aptReleaseGateAtE180EC=true;
    while (value) {
        value->PreDestroy();
        value->DestroyGCPointers();
        value=((AptValueGC_PoolManager *)g_pChainBlockAllocatorF4)->GetNextAptValue(value);
        ++cleaned;
    }
    g_aptReleaseGateAtE180EC=saved;
    g_releaseVectorAtE17710->ReleaseValues();
    value=((AptValueGC_PoolManager *)g_pChainBlockAllocatorF4)->GetFirstAptValue();
    while (value) {
        value->SetDestroyedGC();
        value->DeleteThis();
        value=((AptValueGC_PoolManager *)g_pChainBlockAllocatorF4)->GetNextAptValue(value);
    }
    g_releaseVectorAtE17710->ReleaseValues();
    if (cleaned) Rva006CC110Log(4,"Apt-GC-CleanAll------------- Cleaned %d objects\n",cleaned);
    AptBoolean::ClearPool();
    AptInteger::ClearPool();
    AptFloat::ClearPool();
    StringPool::ClearTemporaryPool();
}
