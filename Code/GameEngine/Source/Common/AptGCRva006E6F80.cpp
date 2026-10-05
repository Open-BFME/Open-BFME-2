// cl: /O2 /MD
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
    static bool sbSuspendRefcountDeletions;
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
void __cdecl AptDebuggerPrint(int,const char *,...);
extern AptValueVector *g_releaseVectorAtE17710;
extern AptValueGC_PoolManager *g_poolAtE176F4;
class AptGC { public: static void CleanAll(); };
void AptGC::CleanAll()
{
    int cleaned=0;
    g_releaseVectorAtE17710->ReleaseValues();
    AptValue *value=g_poolAtE176F4->GetFirstAptValue();
    bool saved=AptValue::sbSuspendRefcountDeletions;
    AptValue::sbSuspendRefcountDeletions=true;
    while (value) {
        value->PreDestroy();
        value->DestroyGCPointers();
        value=g_poolAtE176F4->GetNextAptValue(value);
        ++cleaned;
    }
    AptValue::sbSuspendRefcountDeletions=saved;
    g_releaseVectorAtE17710->ReleaseValues();
    value=g_poolAtE176F4->GetFirstAptValue();
    while (value) {
        value->SetDestroyedGC();
        value->DeleteThis();
        value=g_poolAtE176F4->GetNextAptValue(value);
    }
    g_releaseVectorAtE17710->ReleaseValues();
    if (cleaned) AptDebuggerPrint(4,"Apt-GC-CleanAll------------- Cleaned %d objects\n",cleaned);
    AptBoolean::ClearPool();
    AptInteger::ClearPool();
    AptFloat::ClearPool();
    StringPool::ClearTemporaryPool();
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_poolAtE176F4@@3PAVAptValueGC_PoolManager@@A=?g_pChainBlockAllocatorF4@@3PAVRva006D2A60@@A")
