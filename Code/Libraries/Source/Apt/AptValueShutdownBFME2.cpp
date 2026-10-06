// cl: /O2 /MD
// Original Godfather Jan26 MAP names AptValueShutdown(int). Later source
// 230e7c503b5dbf7e-AptValue.cpp supplies shutdown semantics; PC fixes exact
// global-slot sequence (optional later objects are absent) and virtual slot11.
// All14 newly defined globals below independently read as zero4B native slots;
// address-qualified names preserve uncertainty about individual object identity.
// Existing E18650/E18064/E180C0 storage is reused, never duplicated.
// Hash allocation20B is independently established by constructor70A740 and
// free size20 here; address-derived destructor70A840 already has a provider.
#include "AptObject/AptScriptFunction.h"
class Rva006DB270 { public: void freeBlock(void *,int); };
extern Rva006DB270 *g_pChainBlockAllocator;
#pragma optimize("s", on)
class Rva0070A840 { unsigned char nativeHash[20]; public: void rva0070A8B0(); ~Rva0070A840(); static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocator->freeBlock(p,n); } };
#pragma optimize("", on)
AptNativeHash *g_bfmeAptHashAtE180E4;
extern AptValue *gpGlobalGlobalObject;
extern int g_00E18064;
class AptRenderingContext;
extern AptRenderingContext *g_aptRenderingContextAtE180C0;
AptValue *g_shutdownAtE18360;
AptValue *g_shutdownAtE18070;
AptValue *g_shutdownAtE180B8;
AptValue *g_shutdownAtE18068;
AptValue *g_shutdownAtE180BC;
AptValue *g_shutdownAtE180AC;
AptValue *g_shutdownAtE180A8;
AptValue *g_shutdownAtE18080;
AptValue *g_shutdownAtE18084;
AptValue *g_shutdownAtE180B4;
AptValue *g_shutdownAtE18074;
AptValue *g_shutdownAtE1806C;
AptValue *g_shutdownAtE180E8;
void AptValueShutdown(int bQuiet)
{
    if(g_bfmeAptHashAtE180E4) {
        ((Rva0070A840 *)g_bfmeAptHashAtE180E4)->rva0070A8B0();
        delete (Rva0070A840 *)g_bfmeAptHashAtE180E4;
        g_bfmeAptHashAtE180E4=0;
    }
    g_shutdownAtE18360->DestroyGCPointers();g_shutdownAtE18360->Release();g_shutdownAtE18360=0;
    gpGlobalGlobalObject->DestroyGCPointers();gpGlobalGlobalObject->Release();gpGlobalGlobalObject=0;
    g_shutdownAtE18070->DestroyGCPointers();g_shutdownAtE18070->Release();g_shutdownAtE18070=0;
    g_shutdownAtE180B8->DestroyGCPointers();g_shutdownAtE180B8->Release();g_shutdownAtE180B8=0;
    g_shutdownAtE18068->DestroyGCPointers();g_shutdownAtE18068->Release();g_shutdownAtE18068=0;
    g_shutdownAtE180BC->DestroyGCPointers();g_shutdownAtE180BC->Release();g_shutdownAtE180BC=0;
    g_shutdownAtE180AC->DestroyGCPointers();g_shutdownAtE180AC->Release();g_shutdownAtE180AC=0;
    g_pChainBlockAllocator->freeBlock(g_aptRenderingContextAtE180C0,0x3C0);
    g_shutdownAtE180A8->DestroyGCPointers();g_shutdownAtE180A8->Release();g_shutdownAtE180A8=0;
    g_shutdownAtE18080->DestroyGCPointers();g_shutdownAtE18080->Release();g_shutdownAtE18080=0;
    g_shutdownAtE18084->DestroyGCPointers();g_shutdownAtE18084->Release();g_shutdownAtE18084=0;
    g_shutdownAtE180B4->DestroyGCPointers();g_shutdownAtE180B4->Release();g_shutdownAtE180B4=0;
    g_shutdownAtE18074->DestroyGCPointers();g_shutdownAtE18074->Release();g_shutdownAtE18074=0;
    g_shutdownAtE1806C->DestroyGCPointers();g_shutdownAtE1806C->Release();g_shutdownAtE1806C=0;
    g_shutdownAtE180E8->DestroyGCPointers();g_shutdownAtE180E8->Release();g_shutdownAtE180E8=0;
    ((AptValue *&)g_00E18064)->DestroyGCPointers();((AptValue *&)g_00E18064)->Release();((AptValue *&)g_00E18064)=0;
}
#pragma comment(linker, "/alternatename:?rva0070A8B0@Rva0070A840@@QAEXXZ=?DestroyGCPointers@AptNativeHash@@QAEXXZ")
#pragma comment(linker, "/alternatename:?gpGlobalGlobalObject@@3PAVAptValue@@A=?g_00E18650@@3VEAStringC@@A")

// Existing address-derived consumer spells the native hash tag as class.
#pragma comment(linker, "/alternatename:?g_bfmeAptHashAtE180E4@@3PAVAptNativeHash@@A=?g_bfmeAptHashAtE180E4@@3PAUAptNativeHash@@A")
