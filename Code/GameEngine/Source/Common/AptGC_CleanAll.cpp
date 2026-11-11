// cl: /MD
//
// ?CleanAll@AptGC@@SAXXZ, retail 0x006e6f80, 201 bytes. Banked partial (score 1.0) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Partial: target 0x006E6F80, 201 bytes. Donor identity APT0.19.03 release.
// Caller instruction shape is reconstructed; unvalidated callee identities
// remain a blocker. See reverse/apt_donor_01903.json for exact call targets.
#include "../../../Libraries/Source/Apt/AptValue.h"
#include "../../../Libraries/Source/Apt/AptValueVector.h"
class AptValueGC_PoolManager {
public:
    AptValue *GetFirstAptValue();
    AptValue *GetNextAptValue(const AptValue *);
};
#include "../../../Libraries/Source/Apt/AptBoolean.h"
#include "../../Include/Common/AptInteger.h"
#include "../../../Libraries/Source/Apt/AptFloat.h"
void Rva0070B590Drain();	// 0x0070B590, the temporary string pool drain
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
    Rva0070B590Drain();
}
