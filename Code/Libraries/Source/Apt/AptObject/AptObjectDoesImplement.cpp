#include "AptScriptFunction.h"
// cl: /O2 /MD /EHsc
// Source3994818f06ecc989 supplies semantics; PC confirms hash+8 proto+10 and
// implemented-count low8bits at+1C. Original MAP supplies const method signature.
class EAStringC { void *mpData; public: EAStringC(const char *); ~EAStringC(); };
class AptArray { public: AptValue *GetAt(int) const; };
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
bool AptObject::DoesImplementObject(AptValue *pPrototype) const
{
    AptValue *pProto=mNativeHash.Get__Proto__();
    while (pProto) {
        if (pProto==pPrototype) return true;
        if (pProto->ContainsNativeHashVirtual()) pProto=pProto->GetNativeHashVirtual()->Get__Proto__();
        else break;
    }
    if (mnImplementedObjects>0) {
        EAStringC sTmp("__INTERFACES__");
        AptArray *pTmp=mNativeHash.Lookup(&sTmp)->c_array();
        if (!pTmp) {
            g_bfmeAptAssertAtE17734("pTmp != NULL", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptObject.cpp", 0x12F);
            if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        for (unsigned int i=0;i<mnImplementedObjects;++i) if (pTmp->GetAt(i)==pPrototype) return true;
    }
    return false;
}
#pragma comment(linker, "/alternatename:?Lookup@AptNativeHash@@QBEPAVAptValue@@QBVEAStringC@@@Z=?lookup@Rva0070B380@@QAEPAXABVEAStringC@@@Z")
#pragma comment(linker, "/alternatename:?GetAt@AptArray@@QBEPAVAptValue@@H@Z=?rva006D8A50@BfmeAptValue006DCD20@@QAEPAV1@H@Z")
#pragma comment(linker, "/alternatename:?c_array@AptValue@@QBEPAVAptArray@@XZ=?rva006DCFA0@BfmeAptValue006DCD20@@QAEPAV1@XZ")
